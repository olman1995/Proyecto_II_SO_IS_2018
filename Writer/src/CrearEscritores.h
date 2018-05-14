
void crear_escritor(Cola *cola,int cantidad,int * estado_i,int * sms_i,int * finalizar_i,sem_t * sem_1,
		int lineas,int largo_linea,int writers,int writers_max, int writers_init){
	int burst;
	int prioridad;
	srand(time(NULL));
	for(int i=1; i < cantidad+1; i++ ){
		burst  = (rand() % 5) +1;
		prioridad =  (rand() % 5) +1;
		insertar(cola,i,estado_i,sms_i,finalizar_i ,sem_1,lineas,largo_linea,writers,writers_max,writers_init);
	}

}
