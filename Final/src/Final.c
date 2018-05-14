/*
 ============================================================================
 Name        : Final.c
 Author      : Olman
 Version     : 0.0.2
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <errno.h>
#include <fcntl.h>
#include <semaphore.h>
#include <pthread.h>

int main(int argc, int *argv[]) {


	int largo_3 = sizeof(int )*2;
	key_t shmkey_3=0x1234563;
	int shmid_3;
    shmid_3 = shmget (shmkey_3, largo_3, 0664 | IPC_CREAT);
    if (shmid_3 < 0){
        perror ("shmget\n");
        exit (1);
    }
    int * largo;
	largo = (int *)shmat(shmid_3, 0, 0);

	int largo_1 = largo[0];
	key_t shmkey_1=0x1234561;
	int shmid_1;
    shmid_1 = shmget (shmkey_1, largo_1, 0664 | IPC_CREAT);
    if (shmid_1 < 0){
        perror ("shmget\n");
        exit (1);
    }

    int largo_2 = largo[1];
	key_t shmkey_2=0x1234562;
	int shmid_2;
	shmid_2 = shmget (shmkey_2, largo_2, 0664 | IPC_CREAT);
	if (shmid_2 < 0){
		perror ("shmget\n");
		exit (1);
    }
	int * estado;
	estado = (int *)shmat(shmid_2, 0, 0);
	estado[0] = 0;

    //sleep(10);
    shmctl(shmid_1,IPC_RMID,NULL);
    shmctl(shmid_2,IPC_RMID,NULL);
    shmctl(shmid_3,IPC_RMID,NULL);

    sem_t *psem_1=sem_open("SEM", 0,0664);

    sem_close(psem_1);
    sem_unlink("SEM_7");
    exit (1);
}
