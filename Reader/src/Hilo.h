void *leer_sms( void *nodo ){
		 Nodo *nodo_i;
	     nodo_i = (Nodo *) nodo;
	     while(1){
	    	 semaforo(nodo_i);
	     }
}

void iniciar_hilo(Nodo *nodo){
	int retorno;
	retorno = pthread_create(&nodo->hilo,NULL,&leer_sms,(void*)nodo);
	if(retorno){
		fprintf(stderr,"Error - pthread_create() return code: %d\n",retorno);
	}

}

void ejecutar_hilo(Nodo *nodo){
	pthread_join( nodo->hilo, 0);
}

void * mostrar_estado(void * cola_i){

	Cola * cola;
	cola = (Cola *) cola_i;

	while(1){

		printf("\033[H\033[J");
		printf("*****************************************\n");
		printf("Estado Readers \n");
		printf("*****************************************\n");
		imprimir(cola);
		sleep(1);
	}

}

void iniciar_hilo_estado(Cola *cola){
	int retorno;

	retorno = pthread_create(&cola->hilo,NULL,&mostrar_estado,(void*)cola);
	if(retorno){
		fprintf(stderr,"Error - pthread_create() return code: %d\n",retorno);
	}

}
void ejecutar_mostrar_estado(Cola *cola){
	pthread_join( cola->hilo, 0);
}
