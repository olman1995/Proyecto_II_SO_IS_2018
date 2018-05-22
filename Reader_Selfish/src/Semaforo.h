void estado(Nodo *nodo,int estado){
	nodo->estado_actual=estado;
	nodo->estado[nodo->configuracion->readers_selfish_init+((nodo->pid-1)*3)]=nodo->pid;
	nodo->estado[nodo->configuracion->readers_selfish_init+((nodo->pid-1)*3)+1]=estado;
}

void semaforo(Nodo *nodo){
	estado(nodo,1);
	int cambio=1;

	sem_wait (nodo->semaforo_1);

    srand(time(NULL));
    int i= rand()%20;
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

		nodo->sms[i*nodo->configuracion->largo_linea+1]=0;
		nodo->sms[i*nodo->configuracion->largo_linea+2]=0;
		nodo->sms[i*nodo->configuracion->largo_linea+3]=0;
		nodo->sms[i*nodo->configuracion->largo_linea+4]=0;
		nodo->sms[i*nodo->configuracion->largo_linea+5]=0;
		nodo->sms[i*nodo->configuracion->largo_linea+6]=0;
		nodo->sms[i*nodo->configuracion->largo_linea+7]=0;
		nodo->sms[i*nodo->configuracion->largo_linea+8]=0;
		nodo->sms[i*nodo->configuracion->largo_linea+9]=0;
	}else{
		estado(nodo,4);
	}

	estado(nodo,2);
	sleep(nodo->configuracion->tiempo_escribir);

	sem_post (nodo->semaforo_1);

	estado(nodo,3);
	sleep(nodo->configuracion->tiempo_dormir);
}
