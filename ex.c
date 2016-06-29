#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#define MSQ_SIZE 100

void check(int toCheck, char* msg) {
	if (toCheck == -1) {
		printf("%s\n", msg);
		printf("%s\n", strerror(errno));
	}
	if (1) {
		printf("debug. %s: %d\n", msg, toCheck);
	}
}
void clearBuf(char* buf) {
	memset(buf, 0, sizeof(buf));
}

int main()
{
	sem_t *sem;
	sem_unlink("/test.sem");
	sem = sem_open("/test.sem", O_CREAT, 0666, 66);
	
	return 0;
}
