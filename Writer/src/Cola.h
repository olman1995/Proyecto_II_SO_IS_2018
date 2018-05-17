
typedef struct Nodo
{

  int pid;
  int lineas;
  int largo_linea;
  int writers;
  int writers_max;
  int writers_init;

  int estado_actual;

  sem_t *semaforo_1;
  int *sms;
  int *estado;
  int *proceso;
  int *finalizar;
  pthread_t hilo;
  struct Nodo *siguiente;
  struct Nodo *anterior;
}Nodo;

typedef struct Cola{
	struct Nodo *fin;
	struct Nodo *inicio;
	pthread_t hilo;
    int *estado;
    int *finalizar;

    sem_t *semaforo_1;
	int lineas;
	int largo_linea;
	int writers;
	int writers_max;
	int writers_init;
}Cola;
Nodo * crear_nodo(int dato_pid,int * estado_i,int * sms_i,int * finalizar_i ,sem_t * sem_1,
		int lineas,int largo_linea,int writers,int writers_max, int writers_init){
	Nodo *dato;
	dato=(Nodo*)malloc(sizeof(Nodo));
	dato->pid=dato_pid;
	dato->sms=sms_i;

	dato->estado_actual = 0;
	dato->proceso=1;
	dato->estado=estado_i;
	dato->finalizar=finalizar_i;
	dato->semaforo_1=sem_1;
	dato->lineas=lineas;
	dato->largo_linea=largo_linea;
	dato->writers=writers;
	dato->writers_max=writers_max;
	dato->writers_init=writers_init;
	dato->siguiente=NULL;

	return dato;
}

void insertar(Cola *cola, int dato_pid,int * estado_i,int * sms_i,int * finalizar_i ,sem_t * sem_1,
		int lineas,int largo_linea,int writers,int writers_max, int writers_init)
{
  Nodo *dato;
  dato=(Nodo*)malloc(sizeof(Nodo));
  dato->pid=dato_pid;
  dato->sms=sms_i;
  dato->estado=estado_i;
  dato->finalizar=finalizar_i;
  dato->semaforo_1=sem_1;
  dato->lineas=lineas;
  dato->largo_linea=largo_linea;
  dato->writers=writers;
  dato->writers_max=writers_max;
  dato->writers_init=writers_init;
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
		if(actual->estado_actual == 0){
			printf("PID: %d estado Normal \n",actual->pid);
		}else if(actual->estado_actual == 1){
			printf("PID: %d estado Bloqueado \n",actual->pid);
		}else if(actual->estado_actual == 2){
			printf("PID: %d estado Memoria \n",actual->pid);
		}else if(actual->estado_actual == 3){
			printf("PID: %d estado Dormido \n",actual->pid);
		}
		actual = actual->siguiente;
	}
}

