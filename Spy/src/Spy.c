/*
 ============================================================================
 Name        : Spy.c
 Author      : 
 Version     :
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

int main(void) {
	//datos iniciales
	//memoria compartida
	int largo_3 = sizeof(int )*2;
	key_t shmkey_3=0x1234563;
	int shmid_3;
    int * largo;
	shmid_3 = shmget (shmkey_3, largo_3, 0664 | IPC_CREAT);
    if (shmid_3 < 0){
        perror ("shmget\n");
        exit (1);
    }
    largo = (int *)shmat(shmid_3, NULL, 0);


    int largo_2 = largo[1];
    key_t shmkey_2=0x1234562;
	int shmid_2;
    int * estado;
	shmid_2 = shmget (shmkey_2, largo_2, 0664 | IPC_CREAT);
    if (shmid_2 < 0){
        perror ("shmget\n");
        exit (1);
    }
    estado = (int *)shmat(shmid_2, NULL, 0);
	int largo_1 = largo[0];
    key_t shmkey_1=0x1234561;
	int shmid_1;
    int *sms;
    shmid_1 = shmget (shmkey_1, largo_1, 0664 | IPC_CREAT);
    if (shmid_1 < 0){
		perror ("shmget\n");
		exit (1);
	}
	sms = (int *)shmat(shmid_1, NULL, 0);

	//semaforo
//    sem_t *psem_1=sem_open("SEM_1", 0);
  //  sem_t *psem_2=sem_open("SEM_2", 0);

    //crear procesos
    int lineas=estado[1];
	int largo_linea=estado[2];

	int writers_max=estado[4];
	int readers_max=estado[5];
	int readers_selfish_max=estado[6];

	int writers_init=estado[7];
	int readers_init=estado[8];
	int readers_selfish_init=estado[9];


	printf("\033[H\033[J");
	printf("*****************************************\n");
	printf("lineas \n");
	printf("*****************************************\n");
	for(int i=0;i<lineas;i++){
		printf("Linea %d PID %d Estado %d %d:%d %d/%d/%d SMS %d%d \n",
				sms[i*largo_linea],sms[i*largo_linea+1],sms[i*largo_linea+2],
				sms[i*largo_linea+3],sms[i*largo_linea+4],sms[i*largo_linea+5],
				sms[i*largo_linea+6],sms[i*largo_linea+7],sms[i*largo_linea+8],
				sms[i*largo_linea+9]);
	}
	printf(" \n");
	printf("*****************************************\n");
	printf("writers \n");
	printf("*****************************************\n");
	for(int i=0;i<writers_max;i++){
		if(estado[writers_init+i*2]!=0){
			printf("PID %d estado %d \n",estado[writers_init+(i*2)],estado[writers_init+(i*2)+1]);
		}
	}
	printf(" \n");
	printf("*****************************************\n");
	printf("readers \n");
	printf("*****************************************\n");
	for(int i=0;i<readers_max;i++){
		if(estado[readers_init+i*2]!=0){
			printf("PID %d estado %d \n",estado[readers_init+i*2],estado[readers_init+i*2+1]);
		}
	}
	printf(" \n");
	printf("*****************************************\n");
	printf("readers egoistas \n");
	printf("*****************************************\n");
	for(int i=0;i<readers_selfish_max;i++){
		if(estado[readers_selfish_init+i*2]!=0){
			printf("PID %d estado %d \n",estado[readers_selfish_init+i*2],estado[readers_selfish_init+i*2+1]);
		}
	}
	printf(" \n");
	printf("*****************************************\n");
	printf("Bloqueados \n");
	printf("*****************************************\n");
	for(int i=0;i<writers_max;i++){
		if(estado[writers_init+i*2]!=0){
			if(estado[writers_init+(i*2)+1] == 0){
				printf("PID %d estado %d \n",estado[writers_init+(i*2)],estado[writers_init+(i*2)+1]);
			}

		}
	}
	for(int i=0;i<readers_max;i++){
		if(estado[readers_init+i*2]!=0){
			if(estado[readers_init+i*2+1] == 0){
				printf("PID %d estado %d \n",estado[readers_init+i*2],estado[readers_init+i*2+1]);
			}
		}
	}
	for(int i=0;i<readers_selfish_max;i++){
		if(estado[readers_selfish_init+i*2]!=0){
			if(estado[readers_selfish_init+i*2+1] == 0){
				printf("PID %d estado %d \n",estado[readers_selfish_init+i*2],estado[readers_selfish_init+i*2+1]);
			}
		}
	}
	printf(" \n");
	printf("*****************************************\n");
	printf("Memoria \n");
	printf("*****************************************\n");
	for(int i=0;i<writers_max;i++){
		if(estado[writers_init+i*2]!=0){
			if(estado[writers_init+(i*2)+1] == 1){
				printf("PID %d estado %d \n",estado[writers_init+(i*2)],estado[writers_init+(i*2)+1]);
			}

		}
	}
	for(int i=0;i<readers_max;i++){
		if(estado[readers_init+i*2]!=0){
			if(estado[readers_init+i*2+1] == 1){
				printf("PID %d estado %d \n",estado[readers_init+i*2],estado[readers_init+i*2+1]);
			}
		}
	}
	for(int i=0;i<readers_selfish_max;i++){
		if(estado[readers_selfish_init+i*2]!=0){
			if(estado[readers_selfish_init+i*2+1] == 1){
				printf("PID %d estado %d \n",estado[readers_selfish_init+i*2],estado[readers_selfish_init+i*2+1]);
			}
		}
	}
	printf("*****************************************\n");
	printf("Dormido \n");
	printf("*****************************************\n");
	for(int i=0;i<writers_max;i++){
		if(estado[writers_init+i*2]!=0){
			if(estado[writers_init+(i*2)+1] == 3){
				printf("PID %d estado %d \n",estado[writers_init+(i*2)],estado[writers_init+(i*2)+1]);
			}

		}
	}
	for(int i=0;i<readers_max;i++){
		if(estado[readers_init+i*2]!=0){
			if(estado[readers_init+i*2+1] == 3){
				printf("PID %d estado %d \n",estado[readers_init+i*2],estado[readers_init+i*2+1]);
			}
		}
	}
	for(int i=0;i<readers_selfish_max;i++){
		if(estado[readers_selfish_init+i*2]!=0){
			if(estado[readers_selfish_init+i*2+1] == 3){
				printf("PID %d estado %d \n",estado[readers_selfish_init+i*2],estado[readers_selfish_init+i*2+1]);
			}
		}
	}
	return EXIT_SUCCESS;
}
