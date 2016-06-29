#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define MSQ_SIZE 100

void check(int toCheck, char* msg) {
	if (toCheck == -1) {
		printf("%s\n", msg);
		printf("%s\n", strerror(errno));
	}
}
void clearBuf(char* buf) {
	memset(buf, 0, sizeof(buf));
}

int main()
{
	key_t key = ftok("/tmp/sem.temp", 1);
	int sem_d = semget(key, 16, 0666 | IPC_CREAT);
	check(sem_d, "semd");
	
	for (int i = 0; i < 17; ++i) {
        	check(semctl( sem_d, i, SETVAL, i), "somewhere in semctl");
	}
        
	
	return 0;
}
