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

pthread_mutex_t mutex;
pthread_spinlock_t spinlock;
pthread_rwlock_t rwlock;

void mutex(void *args) {
    printf("Hello from mutex!\n");
    pthread_mutex_lock(&mutex);
}

void spin(void *args) {
    printf("Hello from spinlock!\n");
    spin_lock(&spinlock);
}

void read(void *args) {
    printf("Hello from read!\n");
    pthread_rwlock_rdlock(&rwlock);
}

void write(void *args) {
    printf("Hello from write!\n");
    pthread_rwlock_wrlock(&rwlock);
}
 
int main() {
    pthread_t threadMutex,threadSpin,threadR,threadW;
    
    int status;
    FILE *f = fopen("/home/box/main.pid", "w+");
    // check((int) f, "file");
    fprintf(f, "%d\n", getpid());
    
    status = pthread_mutex_init(&lock, NULL);
    check(status, "mutex init");
    pthread_mutex_lock(&mutex);
    
    status = pthread_spin_init(&lock, PTHREAD_PROCESS_SHARED); 
    check(status, "spinlock init");
    spin_lock(&spinlock);
    
    status = pthread_rwlock_init(rwlock, NULL);
    check(status, "rwlock init");
    status = pthread_rwlock_rdlock(&rwlock);
    check(status, "rwlock read lock");
    status = pthread_rwlock_wrlock(&rwlock);
    check(status, "rwlock write lock");

    
    status = pthread_create(&threadMutex, NULL, &mutex, NULL);
    check(status, " create mutex thread");
    
    status = pthread_create(&threadSpin, NULL, &spin, NULL);
    check(status, " create spin thread");
 
    status = pthread_create(&threadR, NULL, read, NULL);
    check(status, "create read");
 
    status = pthread_create(&threadW, NULL, write, NULL);
    check(status, "create write");
    
    printf("Hello from main!\n");
 
    std::cin >> i;
    return 0;
}
