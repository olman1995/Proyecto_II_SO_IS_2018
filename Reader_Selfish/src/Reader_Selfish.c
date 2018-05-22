/*
 ============================================================================
 Name        : Reader_Selfish.c
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

#include "Cola.h"
#include "CrearLectorEgoista.h"
#include "Hilo.h"
#include "Semaforo.h"

int main(int argc, int *argv[]) {
	//datos iniciales
	int cantidad;
	int tiempo_dormir;
	int tiempo_escribir;
	int final=1;
	int linea_actual=0;
	int *plinea_actual=linea_actual;
	int *pfinal=&final;

	//parametros
	if(argc>2){
		cantidad=strtol(argv[1], NULL, 10);
		tiempo_escribir=strtol(argv[1], NULL, 10);
		tiempo_dormir=strtol(argv[1], NULL, 10);
	}else{
		cantidad = 2;
		tiempo_escribir=2;
		tiempo_escribir=2;
	}
	//cola
	Cola * cola = (Cola*)malloc(sizeof(Cola));



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
    sem_t *psem_1=sem_open("SEM_1", 0);
    sem_t *psem_2=sem_open("SEM_2", 0);

    //crear procesos
    sem_wait(psem_2);
    int lineas=estado[1];
	int largo_linea=estado[2];
	int readers=cantidad;
	int readers_max=estado[6];
	int readers_init=estado[9];
	sem_post(psem_2);
	Configuracion * configuracion;
	configuracion=crear_configuracion(lineas,largo_linea,readers,readers_max,readers_init,tiempo_dormir,tiempo_escribir);
	crear_Lector_egoista(cola,cantidad,estado,sms,pfinal,psem_1,configuracion,linea_actual);


    Nodo * actual;

    actual=cola->inicio;
    while(actual!=NULL){
        iniciar_hilo(actual);
    	actual=actual->siguiente;
    }

    cola->writers=cantidad;
    cola->estado=estado;
    cola->finalizar=pfinal;
    cola->semaforo_1=psem_2;
    iniciar_hilo_estado(cola);

    actual=cola->inicio;
    while(actual!=NULL){
    	ejecutar_hilo(actual);
    	actual=actual->siguiente;

    }
    ejecutar_mostrar_estado(cola);

	return EXIT_SUCCESS;
}
