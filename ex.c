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

pthread_mutex_t mutexL;
pthread_spinlock_t spinlockL;
pthread_rwlock_t rwlockL;

void mutexTh(void *args) {
    printf("Hello from mutex!\n");
    pthread_mutex_lock(&mutexL);
}

void spinTh(void *args) {
    printf("Hello from spinlock!\n");
    spin_lock(&spinlockL);
}

void readTh(void *args) {
    printf("Hello from read!\n");
    pthread_rwlock_rdlock(&rwlockL);
}

void writeTh(void *args) {
    printf("Hello from write!\n");
    pthread_rwlock_wrlock(&rwlockL);
}
 
int main() {
    pthread_t threadMutex,threadSpin,threadR,threadW;
    
    int status;
    FILE *f = fopen("/home/box/main.pid", "w+");
    // check((int) f, "file");
    fprintf(f, "%d\n", getpid());
    
    status = pthread_mutex_init(&mutexL, NULL);
    check(status, "mutex init");
    pthread_mutex_lock(&mutexL);
    
    status = pthread_spin_init(&spinlockL, PTHREAD_PROCESS_SHARED); 
    check(status, "spinlock init");
    spin_lock(&spinlockL);
    
    status = pthread_rwlock_init(&rwlockL, NULL);
    check(status, "rwlock init");
    status = pthread_rwlock_rdlock(&rwlockL);
    check(status, "rwlock read lock");
    status = pthread_rwlock_wrlock(&rwlockL);
    check(status, "rwlock write lock");

    
    status = pthread_create(&threadMutex, NULL, &mutexTh, NULL);
    check(status, " create mutex thread");
    
    status = pthread_create(&threadSpin, NULL, &spinTh, NULL);
    check(status, " create spin thread");
 
    status = pthread_create(&threadR, NULL, readTh, NULL);
    check(status, "create read");
 
    status = pthread_create(&threadW, NULL, writeTh, NULL);
    check(status, "create write");
    
    printf("Hello from main!\n");
 
    int i;
    std::cin >> i;
    return 0;
}
