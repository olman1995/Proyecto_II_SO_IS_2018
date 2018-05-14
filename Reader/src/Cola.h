#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct Nodo
{

  int pid;
  int burst;
  int prioridad;
  pthread_t hilo;
  struct Nodo *siguiente;
  struct Nodo *anterior;

}Nodo;

typedef struct Cola{
	struct Nodo *fin;
	struct Nodo *inicio;
}Cola;


void insertar(Cola *cola, int dato_id,int dato_pid,int dato_burst,int dato_prioridad)
{
  Nodo *dato;
  dato=(Nodo*)malloc(sizeof(Nodo));
  dato->pid=dato_pid;
  dato->burst=dato_burst;
  dato->prioridad= dato_prioridad;
  dato->siguiente=NULL;


  if(cola->fin==NULL){
	  cola->fin=dato;
	  cola->inicio=dato;

  }else{
	dato->anterior=cola->fin;
	cola->fin->siguiente=dato;
	cola->fin=dato;
  }
}


void imprimir(Cola *cola){
	Nodo *actual;
	actual = cola->inicio;

	while(actual != NULL){
		printf("PID: %d \t Burst: %d \t Prioridad: %d \n",actual->pid,actual->burst,actual->prioridad);
		actual = actual->siguiente;
	}

}
