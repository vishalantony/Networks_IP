#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define svfifo "fifo1"
#define clfifo "fifo2"
#define PERMS 0666

int main(void) {
	int fds, fdc, fd;
	int n;
	char buf[1024];
	mkfifo(svfifo, PERMS);
	mkfifo(clfifo, PERMS);
	printf("Fifos created.\n");
	
	fds = open(svfifo, O_RDONLY);
	printf("Server fifo open for reading\n");
	fdc = open(clfifo, O_WRONLY);
	printf("client fifo open for writing\n");
	
	n = read(fds, buf, 1024);
	buf[n] = '\0';
	fd = open(buf, O_RDONLY);
	while((n = read(fd, buf, 1024)) > 0) {
		write(fdc, buf, n);
	}
	printf("transferred file contents!\n");
	close(fd); close(fdc); close(fds);
	return 0;
}
