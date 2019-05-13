// 이 안에서 cp210x와 시리얼 통신을 하기위한 준비를 해야할 듯?
int snull_open(struct net_device *dev) {
    memcpy(dev->dev_addr, "\0SNUL0", ETH_ALEN);
    if(dev == snull_devs[1]) {
        dev->dev_addr[ETH_ALEN-1]++;
    }
    netif_start_queue(dev);
    return 0;
}

// 전송 코드
int snull_tx(struct sk_buff *skb, struct net_device *dev) {
    int len;
    char *data, shortpkt[ETH_ZLEN];
    struct snull_priv *priv = netdev_priv(dev);

    data = skb->data;
    len = skb->len;
    if(len < ETH_ZLEN) {
        memset(shortpkt, 0 , ETHZLEN);
        memcpy(shortpkt, skb->data, skb->len);
        len = ETH_ZLEN;
        data = shortpkt;
    }
    dev->trans_start = jiffies; // 타임 스탬프

    priv->skb = skb // 데이터를 기억해 뒀다가 인터럽트 시점에서 해제함

    snull_hw_tx(data, len, dev); // 실제 전송하는 코드. 디바이스에 따라 다 다르니까 따로 구현함 여기서 cp210x로 보내야할듯

    return 0;
}

// 수신 코드
void snull_rx(struct net_device *dev, struct snull_packet *pkt) {
    struct sk_buff *skb;
    struct snull_priv *priv = netdev_priv(dev);

    skb = dev_alloc_skb(pkt->datalen+2);
    if(!skb) {
        if(printk_ratelimit()) {
            printk(KERN_NOTICE "snull rx: low on mem - packet dropped\n");
        }
        priv->stats.rx_dropped++;
        goto out
    }
    memcpy(skb_put(skb, pkt->datalen), pkt->data, pkt->datalen);

    // 메타 자료를 쓰고, 수신층으로 전달한다
    skb->dev = dev;
    skb->protocol = eth_type_trans(skb, dev);
    skb->ip_summed = CHECKSUM_UNNECESSARY // 체크섬을 검사하지마라. 그렇단 말은 ip 계층은 여기서 역시 처리하는게 아니란거고 사용자 영역에서 처리하는 건가?
    priv->stats.rx_packets++;
    priv->stats.rx_bytes += pkt->datalen;
    netif_rx(skb);

    out:
        return;
}

// 인터럽트 처리기
static void snull_regular_interrupt(int irq, void *dev_id, struct pt_regs *regs) {
    int statusword;
    struct snull_priv *priv;
    struct snull_packet *pkt = NULL;

    // 일반적으로 디바이스 포인터를 점검해서 확실히 인터럽트가 걸렸는지 체크하고 *dev에 대입함
    struct net_device *dev = (struct net_device *)dev_id;

    if(!dev)
        return;

    // 디바이스를 잠금
    priv = netdev_priv(dev);
    spin_lock(&priv->lock);

    // statusword를 인출. 진짜 네트워크 디바이스는 I/O 명령을 사용함
    statusword = priv->status;
    priv->status = 0;
    if(statusword & SNULL_RX_INTR) {
        pkt = priv->rx_queue;
        if(pkt) {
            priv->rx_queue = pkt->next;
            snull_rx(dev, pkt);
        }
    }

    if(statuswrod & SNULL_TX_INTR) {
        // 전송이 끝남
        priv->stats.tx_packets++;
        priv->stats.tx_bytes += priv->tx_packetlen;
        dev_kfree_skb(priv->skb);
    }

    spin_unlock(&priv->lock);
    if(pkt) snull_release_buffer(pkt);
        return;
}