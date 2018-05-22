
void crear_Lector(Cola *cola,int cantidad,int * estado_i,int * sms_i,int * finalizar_i,sem_t * sem_1,Configuracion * configuracion,int *linea_actual){
	for(int i=1; i < cantidad+1; i++ ){
		insertar(cola,i,estado_i,sms_i,finalizar_i ,sem_1,configuracion,linea_actual);
	}

}
