// diffie hellman key exchange using client server

#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>

#define h_addr h_addr_list[0]

void error(char *message) {
	perror(message);
	exit(1);
}

int power(int a, int exp, int mod) {
	if(exp == 0) return 1;
	int temp = power(a, exp/2, mod);
	temp = (temp*temp)%mod;
	if(exp%2)
		return (temp*a)%mod;
	return temp;
}

int main(int argc, char ** argv) {
	int sockfd, n;
	struct sockaddr_in server;
	struct hostent *serv;
	char buf[256], temp[256];
	int p, pr_root;
	int xb, yb, ya, yba;
	
	
	if(argc != 3) {
		fprintf(stderr, "usage: ./a.out <ip addr> <port>\n");
		exit(1);
	}
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	serv = gethostbyname(argv[1]);
	if(serv == NULL)
		error("gethostbyname");
	bzero(&server, sizeof(server));
	bcopy(serv->h_addr, (char*)&(server.sin_addr.s_addr), serv->h_length);
	server.sin_port = htons(atoi(argv[2]));
	server.sin_family = AF_INET;
	if(connect(sockfd, (struct sockaddr*)&server, sizeof(server)) < 0)
		error("connect");
	
	printf("Connected!\n\n");
	
	n = read(sockfd, buf, 255);	// read prime and root
	buf[n] = '\0';
	sscanf(buf, "%s%d%s%d", temp, &p, temp, &pr_root);
	printf("Prime: %d\t Primitive Root: %d\n", p, pr_root);
	
	srand(clock());
	xb = 2+rand()%(p-2);
	yb = power(pr_root, xb, p);
	printf("XCLIENT: %d\tYCLIENT: %d\n", xb, yb);
	sprintf(buf, "%d\n", yb);
	write(sockfd, buf, strlen(buf));
	
	n = read(sockfd, buf, 255); // read yA
	buf[n] = '\0';
	ya = atoi(buf);
	printf("Recieved YA: %d\n", ya);
	
	
	
	yba = power(ya, xb, p);
	printf("Shared secret key is: %d\n", yba);
	close(sockfd);
	return 0;
}
