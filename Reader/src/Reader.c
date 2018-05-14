/*
 ============================================================================
 Name        : Reader.c
 Author      : 
 Version     : 0.0.1
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <errno.h>
#include <fcntl.h>

int main(void) {
	int len = sizeof(int )*100;
	key_t shmkey=0x1234567;
	int shmid;

    shmid = shmget (shmkey, len, 0644 | IPC_EXCL);
    if (shmid < 0){
        perror ("shmget\n");
        exit (1);
    }


    int *sms;
    sms = shmat(shmid, NULL, 0);
    //printf("PID= %d \t Estado= %d \n",sms[0],sms[1]);

    for(int i=0;i<20;i++){
		if(sms[i*5+1]==1){
			printf("PID= %d \t Estado= %d \n",sms[i*5],sms[i*5+1]);
		}
	}
	return EXIT_SUCCESS;
}
