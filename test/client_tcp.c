#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <net/if.h>

#define MAXLINE 1024
#define PORT_NUM 3600

int main(int argc, char **argv)
{
	struct sockaddr_in serveraddr;
	int server_sockfd;
    struct ifreq ifr;
	socklen_t client_len;
	char buf[MAXLINE];

	if(argc != 2) {
		printf("Usage : %s [ipaddress]\n", argv[0]);
		return 1;
	}

	if((server_sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
	{
		perror("error :");
		return 1;
	}

 	memset(&ifr, 0, sizeof(ifr));
 	snprintf(ifr.ifr_name, sizeof(ifr.ifr_name), "sl0");
    if (setsockopt(server_sockfd, SOL_SOCKET, SO_BINDTODEVICE, (void *)&ifr, sizeof(ifr)) < 0) {
		perror("if error");
		return 1;   
   	}

    memset((void *)&serveraddr, 0x00, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(argv[1]);
	serveraddr.sin_port = htons(PORT_NUM);

    printf("Try to connect to [%s:%d]\n", argv[1], PORT_NUM);
	client_len = sizeof(serveraddr);
	if((connect(server_sockfd, (struct sockaddr *)&serveraddr, client_len)) == -1)
	{
		perror("connect error :");
		return 1;
	}

    while(1) {
        printf("Payload:");
        memset(buf, 0x00, MAXLINE);
        read(0, buf, MAXLINE);
        if(write(server_sockfd, buf, MAXLINE) <= 0)
        {
            perror("write error :");
            return 1;
        }
        memset(buf, 0x00, MAXLINE);
        if(read(server_sockfd, buf, MAXLINE) <= 0)
        {
            perror("read error :");
            return 1;
        }
    }

	close(server_sockfd);
	printf("read : %s", buf);
	return 0;
}

