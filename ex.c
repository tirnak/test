#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/msg.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <mqueue.h>
#define MAX_SIZE 80

struct mq_attr attr;



attr.mq_flags = 0;
attr.mq_maxmsg = 10;
attr.mq_msgsize = MAX_SIZE;
attr.mq_curmsgs = 0;

char buffer[MAX_SIZE];

int main()
{
	
	mqd_t mq = mq_open("/test.mq", O_CREAT | O_RDWR, 0666,);
	if( mq == -1 ) {
		printf("error: %s", strerror(errno));
		return -1;
	}
	memset(buffer, 0, MAX_SIZE);
	int received = msg_receive(mq, buffer, MAX_SIZE, 0);
	if( received == -1 ) {
		printf("error: %s", strerror(errno));
		return -1;
	}
	
	FILE *fd = open(/home/box/message.txt", O_TRUNC | O_WRONLY);
	if( fd == -1 ) {
		printf("error: %s", strerror(errno));
		return -1;
	}
	printf("message is:\n%s", buffer);
	fprintf(fd, "%s", buffer);
	
	return 0;
}
