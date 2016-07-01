#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

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

void* helloWorld(void *args) {
    printf("Hello from thread!\n");
    pause();
    return 0;
}
 
int main() {
    pthread_t thread;
    int status;
    int status_addr;
    FILE *f = fopen("/home/box/main.pid", "w+");
    check((int) f, "file");
    fprintf("%d\n", getpid());
 
    status = pthread_create(&thread, NULL, helloWorld, NULL);
    check(status, "create");
    printf("Hello from main!\n");
 
    status = pthread_join(thread, (void**)&status_addr);
    check(status, "create");
 
    printf("joined with address %d\n", status_addr);
    _getch();
    return 0;
}
