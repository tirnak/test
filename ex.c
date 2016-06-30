#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

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
      int shmid;
      int new = 1; 
      
      shmid = shm_open("/test.shm", O_CREAT|O_RDWR, 0666);
      check(shmid, "key");
      int trunc = ftruncate(shmid, 1048576);
      check(trunc, "trunc");
      char *ptr = mmap(0,1048576, PROT_READ | PROT_WRITE, MAP_SHARED, shmid, 0);
      memset(ptr, 13, 1048576);
      return 0;
}
