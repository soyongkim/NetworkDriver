#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>

#define PORT_NUM 3800
#define MAXLEN 256

int main(int argc, char **argv) {
	int sockfd;
	struct ifreq ifr;
	struct sockaddr_in addr, recvaddr;
	char sdata[MAXLEN];
	char msg[MAXLEN];
	int left_num;
	int right_num;
	socklen_t addrlen;


	if(argc != 2) {
		printf("Usage : %s [ipaddress]\n", argv[0]);
		return 1;
	}

	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		return 1;
	}

 	memset(&ifr, 0, sizeof(ifr));
 	snprintf(ifr.ifr_name, sizeof(ifr.ifr_name), "sl0");
    	if (setsockopt(sockfd, SOL_SOCKET, SO_BINDTODEVICE, (void *)&ifr, sizeof(ifr)) < 0) {
		perror("if error");
		return 1;   
   	}
	
	memset((void *)&addr, 0x00, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(argv[1]);
	addr.sin_port = htons(PORT_NUM);

	while(1) {
		printf("Payload:");
		fgets(msg, MAXLEN-1, stdin);
		if(strncmp(msg, "quit\n", 5) == 0) {
			break;
		}
		memset((void *)&sdata, 0x00, sizeof(sdata));
		strncpy(sdata, msg, strlen(msg)-1);

		addrlen = sizeof(addr);
		sendto(sockfd, (void *)&sdata, strlen(sdata), 0, (struct sockaddr *)&addr, addrlen);
		//recvfrom(sockfd, (void *)&sdata, sizeof(sdata), 0, (struct sockaddr *)&recvaddr, &addrlen);
	
		printf("Send Msg to VLC: %s\n", sdata);
	}
	close(sockfd);
}
