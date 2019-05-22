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
	socklen_t addrlen;
	ssize_t comm_len;


	if(argc != 2) {
		printf("Usage : %s [ipaddress]\n", argv[0]);
		return 1;
	}

	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		perror("socket()");

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
		if(fgets(sdata, MAXLEN-1, stdin) == NULL) {
			perror("fgets()");
			return 1;
		}

		sdata[strlen(sdata) - 1] = 0;

		if(strncmp(sdata, "quit", 5) == 0) {
			break;
		}

		addrlen = sizeof(addr);
		comm_len = sendto(sockfd, (void *)&sdata, sizeof(sdata), 0, (struct sockaddr *)&addr, addrlen);
		if(comm_len == -1)
		{
			perror("sendto()");
			return 1;
		}

		printf("Sent %d Bytes to server\n", comm_len);

		comm_len = recvfrom(sockfd, (void *)&sdata, sizeof(sdata), 0, (struct sockaddr *)&recvaddr, &addrlen);
		if(comm_len == -1)
		{
			perror("recvfom()");
			return 1;
		}
	
		printf("Received %d Bytes from server, data: %s\n", comm_len, sdata);
	}

	close(sockfd);
	return 1;
}
