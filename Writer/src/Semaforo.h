

void estado(Nodo *nodo,int estado){
	nodo->estado_actual=estado;
	nodo->estado[nodo->configuracion->writers_init+((nodo->pid-1)*2)]=nodo->pid;
	nodo->estado[nodo->configuracion->writers_init+((nodo->pid-1)*2)+1]=estado;
}

void semaforo(Nodo *nodo){
	estado(nodo,1);
	int cambio=1;
	time_t t= time(NULL);
	struct tm tm = *localtime(&t);
	int pid;
	int sms_1;
	int sms_2;
	sem_wait (nodo->semaforo_1);
	for(int i=0;i<(nodo->configuracion->lineas);i++){
		if(cambio == 1){
			if(nodo->sms[i*nodo->configuracion->largo_linea+2]==0){
				//nodo->sms[i*nodo->configuracion->largo_linea]=linea;
				pid=nodo->pid;
				sms_1=(rand() % 100);
				sms_2=(rand() % 100);

				nodo->sms[i*nodo->configuracion->largo_linea+1]=pid; //pid
				nodo->sms[i*nodo->configuracion->largo_linea+2]=1;  //estado
				nodo->sms[i*nodo->configuracion->largo_linea+3]=tm.tm_hour;  //hora
				nodo->sms[i*nodo->configuracion->largo_linea+4]=tm.tm_min; //minutos
				nodo->sms[i*nodo->configuracion->largo_linea+5]=tm.tm_mday; //dia
				nodo->sms[i*nodo->configuracion->largo_linea+6]=tm.tm_mon+1; //mes
				nodo->sms[i*nodo->configuracion->largo_linea+7]=tm.tm_year+1900; //anno
				nodo->sms[i*nodo->configuracion->largo_linea+8]=sms_1; //sms
				nodo->sms[i*nodo->configuracion->largo_linea+9]=sms_2; //sms
				escribir_bitacora(nodo->configuracion->f,pid,tm.tm_hour,tm.tm_min,
									tm.tm_mday,tm.tm_mon+1,tm.tm_year+1900,sms_1,sms_2);
				cambio=0;
			}
		}
	}
		estado(nodo,2);
		sleep(nodo->configuracion->tiempo_escribir);
		sem_post (nodo->semaforo_1);
	estado(nodo,3);
	sleep(nodo->configuracion->tiempo_dormir);
}
