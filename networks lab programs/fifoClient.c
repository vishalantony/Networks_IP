#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#define svfifo "fifo1"
#define clfifo "fifo2"
#define PERMS 0666

void wait_for_sometime(int a) {
	clock_t start = clock();
	clock_t stop;
	int sec;
	do {
		stop = clock();
		sec = (stop-start)/CLOCKS_PER_SEC;
	}while(sec < a);
}

int main(void) {
	int fds, fdc;
	int n;
	char buf[1024];
	mkfifo(svfifo, PERMS);
	mkfifo(clfifo, PERMS);
	printf("Fifos created.\n");
	
	fds = open(svfifo, O_WRONLY);
	printf("Server fifo open for writing\n");
	fdc = open(clfifo, O_RDONLY);
	printf("client fifo open for reading\n");
	
	write(fds, "samplefile", strlen("samplefile"));
	
	wait_for_sometime(3);
	while((n = read(fdc, buf, 1024)) > 0) {
		write(STDIN_FILENO, buf, n);
	}
	printf("OK");
	close(fdc); close(fds);
	return 0;
}
