void estado(Nodo *nodo,int estado){
	nodo->estado_actual=estado;
	//nodo->estado[nodo->writers_init+nodo->pid*2]=nodo->pid;
	//nodo->estado[nodo->writers_init+nodo->pid*2+1]=estado;
}

void semaforo(Nodo *nodo){
	estado(nodo,1);
	int cambio=1;
		sem_wait (nodo->semaforo_1);
		for(int i=0;i<20;i++){
			if(cambio == 1){
				if(nodo->sms[i*5+1]==0){
					nodo->sms[i*5]=nodo->pid;
					nodo->sms[i*5+1]=1;
					cambio=0;
				}
			}
		}
		estado(nodo,2);
		sleep(3);
		sem_post (nodo->semaforo_1);
	estado(nodo,3);
	sleep(3);
}

