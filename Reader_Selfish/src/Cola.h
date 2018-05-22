typedef struct Configuracion{
	int lineas;
	int largo_linea;
	int readers_selfish;
	int readers_selfish_max;
	int readers_selfish_init;
	int tiempo_dormir;
	int tiempo_escribir;
}Configuracion;

typedef struct Nodo
{

  int pid;

  int pid_mesajero;
  int hora;
  int minuto;
  int dia;
  int mes;
  int anno;
  int sms_1;
  int sms_2;
  int linea;
  struct Configuracion * configuracion;

  int estado_actual;

  sem_t *semaforo_1;
  int *sms;
  int *estado;
  int *proceso;
  int *finalizar;
  int *linea_actual;

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

Configuracion * crear_configuracion(
		int lineas,
		int largo_linea,
		int readers,
		int readers_max,
		int readers_init,
		int tiempo_dormir,
		int tiempo_escribir){
	Configuracion * configuracion;
	configuracion=(Configuracion*)malloc(sizeof(Configuracion));

	configuracion->lineas=lineas;
	configuracion->largo_linea=largo_linea;
	configuracion->readers_selfish=readers;
	configuracion->readers_selfish_max=readers_max;
	configuracion->readers_selfish_init=readers_init;
	configuracion->tiempo_dormir=tiempo_dormir;
	configuracion->tiempo_escribir=tiempo_escribir;

	return configuracion;
}
void insertar(Cola *cola, int dato_pid,int * estado_i,int * sms_i,int * finalizar_i ,sem_t * sem_1,Configuracion * configuracion,int *linea_actual)
{
  Nodo *dato;
  dato=(Nodo*)malloc(sizeof(Nodo));
  dato->pid=dato_pid;
  dato->sms=sms_i;
  dato->estado=estado_i;
  dato->finalizar=finalizar_i;
  dato->semaforo_1=sem_1;
  dato->siguiente=NULL;
  dato->configuracion=configuracion;
  dato->linea_actual=linea_actual;
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
			printf("PID: %d estado leyendo la linea %d escrita por %d, %d:%d %d/%d/%d sms %d%d  \n",
					actual->pid,actual->linea,actual->pid_mesajero,actual->hora,actual->minuto,
					actual->dia,actual->mes,actual->anno,actual->sms_1,actual->sms_2);
		}else if(actual->estado_actual == 3){
			printf("PID: %d estado Dormido \n",actual->pid);
		}
		actual = actual->siguiente;
	}
}

