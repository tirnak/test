#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

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
      int *array;
      int shmid;
      int new = 1; 
      key_t key = ftok("/tmp/mem.temp", 1);
      check(key, "key");
      
      shmid = shmget(key, 1048576, 0666|IPC_CREAT);
      check(shmid, "shmid");
      char * shm_addr = shmat( shmid, NULL, 0); 
      memset(shm_addr, 42, 1048576);
      return 0;
}
