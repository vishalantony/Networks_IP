#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

#define h_addr  h_addr_list[0]

void error(char *p) {
	perror(p);
	exit(1);
}

int main(int argc, char ** argv) {
	short int portno;
	int sockfd;
	char filename[256], buff[10000];
	struct sockaddr_in serv_addr;
	struct hostent * server;
	
	if(argc < 3) {
		fprintf(stderr, "usage: <program name> <IP Address> <Port Number>\n");
		exit(1);
	}
	portno = htons(atoi(argv[2]));
	sockfd = socket(AF_INET, SOCK_STREAM, 0);	// client's socket
	if(sockfd < 0) {
		error("socket creation: ");
	}
	printf("Client online!\n");
	server = gethostbyname(argv[1]);
	if(server == NULL) {
		fprintf(stderr, "No such host.\n");
		exit(1);
	}
	printf("Server online!\n");
	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = portno;
	bcopy(server->h_addr, (char *)(&serv_addr.sin_addr.s_addr), server->h_length);
	if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		error("connect error: ");
	}
	printf("Connected!\nEnter file name: ");
	scanf("%s", filename);
	if(write(sockfd, filename, strlen(filename)) < 0) {
		error("Write error:");
	}
	bzero(buff, sizeof(buff));
	if(read(sockfd, buff, sizeof(buff)-1) < 0) {
		error("read error:");
	}
	printf("Server returned the following contents:\n");
	write(1, buff, sizeof(buff)-1);
	close(sockfd);
	return 0;
}
