#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

void error(char *e) {
	perror(e);
	exit(1);
}

int main(int argc, char ** argv) {
	int sockfd, newsockfd, n;
	char buf[256], cont[10000];
	FILE * fin;
	short int portno;
	struct sockaddr_in serv_add;
	
	if(argc < 2) {
		fprintf(stderr, "usage: <program name> <port no.>\n");
		exit(1);
	}
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0) 
		error("Error opening socket:");
	
	bzero(&serv_add, sizeof(serv_add));
	portno = atoi(argv[1]);
	serv_add.sin_family = AF_INET;
	serv_add.sin_port = htons(portno);
	serv_add.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	if(bind(sockfd, (struct sockaddr *)&serv_add, sizeof(serv_add)) < 0) 
		error("Socket Bind error:");
	
	listen(sockfd, 5);
	
	printf("Waiting for client requests...\n");
	newsockfd = accept(sockfd, NULL, NULL);
	if(newsockfd < 0) 
		error("Accept error:");
	bzero(buf, sizeof(buf));
	n = read(newsockfd, buf, 255);
	if(n < 0) 
		error("Read error: ");
	printf("Server: Client requested contents of \"%s\".\n", buf);
	bzero(cont, sizeof(cont));
	fin = fopen(buf, "r");
	if(fin == NULL) {
		fprintf(stderr, "No such file.\n");
		if(write(newsockfd, "No such file.\n", strlen("No such file.\n")) < 0) 
			error("write error");
		exit(0);
	}
	if(fread(cont, sizeof(char), 9999, fin) == 0) 
		error("fread error");
	printf("Server: Transferring contents to client...\n");
	if(write(newsockfd, cont, strlen(cont)) < 0) 
		error("write error");
	printf("Transferred requested contents.\nTerminating server...\n");
	close(newsockfd);
	close(sockfd);
	fclose(fin);
	return 0;
}
