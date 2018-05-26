void estado(Nodo *nodo,int estado){
	nodo->estado_actual=estado;
	nodo->estado[nodo->configuracion->readers_init+((nodo->pid-1)*3)]=nodo->pid;
	nodo->estado[nodo->configuracion->readers_init+((nodo->pid-1)*3)+1]=estado;
}
pthread_mutex_t lock;
void semaforo(Nodo *nodo){
	estado(nodo,1);
	int cambio=1;
    nodo->proceso++;
	if(nodo->proceso==1){
		sem_wait (nodo->semaforo_1);
	}


	pthread_mutex_lock(&lock);
	//	printf("test 2 %d \n",*nodo->linea_actual);


	int i=*nodo->linea_actual;
	if(nodo->sms[i*nodo->configuracion->largo_linea+2] == 1){
		nodo->linea=nodo->sms[i*nodo->configuracion->largo_linea];
		nodo->pid_mesajero=nodo->sms[i*nodo->configuracion->largo_linea+1];
		//nodo->estado=nodo->sms[i*nodo->configuracion->largo_linea+2]; estado
		nodo->hora=nodo->sms[i*nodo->configuracion->largo_linea+3];
		nodo->minuto=nodo->sms[i*nodo->configuracion->largo_linea+4];
		nodo->dia=nodo->sms[i*nodo->configuracion->largo_linea+5];
		nodo->mes=nodo->sms[i*nodo->configuracion->largo_linea+6];
		nodo->anno=nodo->sms[i*nodo->configuracion->largo_linea+7];
		nodo->sms_1=nodo->sms[i*nodo->configuracion->largo_linea+8];
		nodo->sms_2=nodo->sms[i*nodo->configuracion->largo_linea+9];

		escribir_bitacora(nodo->configuracion->f,nodo->pid,nodo->hora,nodo->minuto,
									nodo->dia,nodo->mes,nodo->anno,nodo->sms_1,nodo->sms_2);

		cambio=0;

	}else{
		estado(nodo,4);
	}
	*nodo->linea_actual=*nodo->linea_actual+1;

	if(nodo->configuracion->lineas < *nodo->linea_actual){
		*nodo->linea_actual=0;
		for(int j=0;j<nodo->configuracion->lineas;j++){
			nodo->sms[j*nodo->configuracion->largo_linea+1]=0;
			nodo->sms[j*nodo->configuracion->largo_linea+2]=0;
			nodo->sms[j*nodo->configuracion->largo_linea+3]=0;
			nodo->sms[j*nodo->configuracion->largo_linea+4]=0;
			nodo->sms[j*nodo->configuracion->largo_linea+5]=0;
			nodo->sms[j*nodo->configuracion->largo_linea+6]=0;
			nodo->sms[j*nodo->configuracion->largo_linea+7]=0;
			nodo->sms[j*nodo->configuracion->largo_linea+8]=0;
			nodo->sms[j*nodo->configuracion->largo_linea+9]=0;
		}
	}

	pthread_mutex_unlock(&lock);



	estado(nodo,2);
	sleep(nodo->configuracion->tiempo_escribir);

	nodo->proceso--;
	if(nodo->proceso==0){
		sem_post (nodo->semaforo_1);

	}

	estado(nodo,3);
	sleep(nodo->configuracion->tiempo_dormir);
}
