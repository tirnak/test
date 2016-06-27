#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

int main (void) {

        struct { long type; char text[80]; } message;
        int received;

        /* Generate the ipc key */
        key_t key = ftok("/tmp/msg.temp", 1);
        printf("My key is %d\n", key);

        /* Set up the message queue */
        // int mq_id = msgget(ipckey, 0);
		int mq_id = msgget(key, IPC_CREAT|0666);
        printf("Message identifier is %d\n", mq_id);
        
        if (mq_id == -1) {
        	printf("error: %s", strerror(errno));
        }
        

        received = msgrcv(mq_id, &message, sizeof(message), 0, 0);
		
		FILE *f = fopen("/home/box/message.txt", "w");

        fprintf(f, "%s", message.text);
}
