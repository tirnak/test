#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <iostream>

void check(int toCheck, const char* msg) {
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

pthread_t thread_cond, thread_barrier;
pthread_mutex_t cond_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;

void* wait_for_cond(void *args) {
    printf("Hello from cond!\n");
    pthread_mutex_lock(&cond_mutex);
    pthread_cond_wait(&condition, &cond_mutex);
}
void* wait_for_barrier(void *args) {
    printf("Hello from barrier!\n");
    pthread_barrier_wait(&barrier);
}
 
int main() {
    
    int status;
    FILE *f = fopen("/home/box/main.pid", "w+");
    // check((int) f, "file");
    fprintf(f, "%d\n", getpid());
    
    //cond_mutex = PTHREAD_MUTEX_INITIALIZER;
    //condition = PTHREAD_COND_INITIALIZER;
    status = pthread_barrier_init(&barrier, NULL, 2);
    check(status, " create mutex thread");
    
    status = pthread_create(&thread_cond, NULL, &wait_for_cond, NULL);
    check(status, " create mutex thread");
    
    status = pthread_create(&thread_barrier, NULL, &wait_for_barrier, NULL);
    check(status, " create spin thread");
 
    printf("Hello from main!\n");
 
    int i;
    std::cin >> i;
    return 0;
}
