#include <mqueue.h>     /* message queue stuff */
#include <sys/stat.h>  
#include <errno.h>      /* errno and perror */
#include <fcntl.h>      /* O_RDONLY */
#include <stdio.h>
#include <string.h>
#define MAX_SIZE 80

struct mq_attr attr;
char buffer[MAX_SIZE+1];

int main()
{
	attr.mq_flags = 0;
	attr.mq_maxmsg = 10;
	attr.mq_msgsize = MAX_SIZE;
	attr.mq_curmsgs = 0;
	mqd_t mq = mq_open("/test.mq", O_CREAT | O_RDWR, 0666, &attr);
	if( mq == -1 ) {
		printf("mq. error: %s", strerror(errno));
		return -1;
	}
	memset(buffer, 0, MAX_SIZE+1);
	int received = mq_receive(mq, buffer, MAX_SIZE + 1, 0);
	if( received == -1 ) {
		printf("receive. error: %s", strerror(errno));
		return -1;
	}
	
	FILE *fd = fopen("/home/box/message.txt", "w+");
	if( fd == -1 ) {
		printf("fopen. error: %s", strerror(errno));
		return -1;
	}
	printf("message is:\n%s", buffer);
	fprintf(fd, "%s", buffer);
	
	return 0;
}
