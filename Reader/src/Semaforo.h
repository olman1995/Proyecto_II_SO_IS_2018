void estado(Nodo *nodo,int estado){
	nodo->estado_actual=estado;
	nodo->estado[nodo->configuracion->readers_init+((nodo->pid-1)*3)]=nodo->pid;
	nodo->estado[nodo->configuracion->readers_init+((nodo->pid-1)*3)+1]=estado;
}

void semaforo(Nodo *nodo){
	estado(nodo,1);
	int cambio=1;
    nodo->proceso++;
	if(nodo->proceso==1){
		sem_wait (nodo->semaforo_1);
	}

	for(int i=0;i<nodo->configuracion->lineas;i++){
		if(cambio == 1){
			//printf("la %d \n",nodo->linea_actual);
			if(nodo->linea_actual == i){
				nodo->linea_actual++;

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
					cambio=0;

				}else{
					estado(nodo,4);
				}
				if(nodo->configuracion->lineas == nodo->linea_actual){
					nodo->linea_actual=0;

				}
			}else{
				estado(nodo,4);
			}

		}else{
			estado(nodo,4);
		}

	}

	estado(nodo,2);
	sleep(nodo->configuracion->tiempo_escribir);

	nodo->proceso--;
	if(nodo->proceso==0){
		sem_post (nodo->semaforo_1);
		sem_wait(nodo->semaforo_1);
			for(int j=1;j<nodo->configuracion->lineas;j++){
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
		sem_post(nodo->semaforo_1);

	}

	estado(nodo,3);
	sleep(nodo->configuracion->tiempo_dormir);
}
