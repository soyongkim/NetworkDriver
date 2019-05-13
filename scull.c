#include <linux/type.h>

struct scull_dev {
    struct scull_qset *data;
    int quantum;
    int qset;
    unsigned long size;
    unsigned int access_key;
    struct semaphore sem;
    struct cdev cdev;
};

static void scull_setup_cdev(struct scull_dev *dev, int index) {
    int err, devno = MKDEV(scull_major, scull_minor + index);
    cdev_init(&dev->cdev, &scull_fops);
    dev->cdev.owner = THIS_MODULE;
    dev->cdev.ops = &scull_fops;
    err = cdev_add(&dev->cdev, devno, 1);
    if(err)
        printk(KERN_NOTICE "Error %d adding scull%d", err, index);
}

int scull_open(struct inode *inode, struct file *filep) {
    struct scull_dev *dev;
    dev = container_of(inode->i_cdev, struct scull_dev, cdev);
    filep->private_data = dev;

    if((filep->f_flags & O_ACCMODE) == O_WRONLY) {
        scull_trim(dev);
    }
    return 0;
}

int scull_release(struct inode *inode, struct file *filep) {
    return 0;
}

ssize_t scull_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos) {
    struct scull_dev *dev = filp->private_data;
    struct scull_qset *dptr;
    
}