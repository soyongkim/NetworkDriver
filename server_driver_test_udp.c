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
	struct sockaddr_in addr, cliaddr;
	char rdata[MAXLEN];
	char msg[MAXLEN];
	socklen_t addrlen;


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

	addrlen = sizeof(addr);
	if(bind(sockfd, (struct sockaddr *)&addr, addrlen) == -1) {
		return 1;
	}

	while(1) {
		printf("Wait...\n");
		addrlen = sizeof(cliaddr);
		recvfrom(sockfd, (void *)&rdata, sizeof(rdata), 0, (struct sockaddr *)&cliaddr, &addrlen);

		printf("Received Data: %s\m", rdata)

		sendto(sockfd, (void *)&rdata, sizeof(rdata), 0, (struct sockaddr *)&cliaddr, addrlen);
	}
	
	close(sockfd);
	return 1;
}
