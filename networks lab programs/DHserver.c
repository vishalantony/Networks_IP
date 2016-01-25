// diffie hellman key exchange using client server

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

int power(int a, int exp, int mod) {
	if(exp == 0) return 1;
	int temp = power(a, exp/2, mod);
	temp = (temp*temp)%mod;
	if(exp%2)
		return (temp*a)%mod;
	return temp;
}

int main(int argc, char ** argv) {
	int sockfd, newsockfd;
	int xa, ya, n, yb, yab;
	int p;
	int rem[100000];
	int pr_root, temp;
	char buf[256];
	int i, j;
	struct sockaddr_in dhserv, dhclient;
	socklen_t cl_sklen = sizeof(dhclient);
	
	if(argc != 2) {
		fprintf(stderr, "args error\n");
		exit(1);
	}
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	memset(&dhserv, 0, sizeof(dhserv));
	memset(&dhclient, 0, sizeof(dhclient));
	dhserv.sin_port = htons(atoi(argv[1]));
	dhserv.sin_addr.s_addr = inet_addr("127.0.0.1");
	dhserv.sin_family = AF_INET;
	bind(sockfd, (struct sockaddr*)&dhserv, sizeof(dhserv));
	listen(sockfd, 4);
	newsockfd = accept(sockfd, (struct sockaddr*)&dhclient, &cl_sklen);
	if(newsockfd < 0 || sockfd < 0) exit(1);
	// diffie hellman part.
	// server chooses the prime number and finds its primitive root.
	// sends this info to client.
	
	
	printf("Enter a large prime number: ");
	scanf("%d", &p);
	
	// finding primitive root:
	
	for(i = p-1; i > 2; i--) {
		memset(rem, 0, sizeof(rem));
		for(j = 1; j < p; j++) {
			if(rem[temp = power(i, j, p)] == 1)
				break;
			else
				rem[temp] = 1;
		}
		if(j == p) {
			pr_root = i;
			break;
		}
	}
	
	printf("Primitive root: %d\n", pr_root);
	sprintf(buf, "Prime %d Root %d\n", p, pr_root);
	write(newsockfd, buf, strlen(buf)); // sent the prime number and primitive root
	
	srand(clock());
	xa = 2+rand()%(p-2);
	ya = power(pr_root, xa, p);
	printf("XSERVER: %d\tYSERVER: %d\n", xa, ya);
	
	n = read(newsockfd, buf, 255); // read yb
	buf[n] = 0;
	yb = atoi(buf);
	
	sprintf(buf, "%d\n", ya);
	write(newsockfd, buf, strlen(buf));	// send YA
	

	yab = power(yb, xa, p);
	printf("Shared secret key is: %d\n", yab);
	
	close(sockfd);
	close(newsockfd);
	return 0;
}
