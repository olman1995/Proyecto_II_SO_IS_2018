void escribir_bitacora(FILE *f,int pid,int hora,int min, int dia, int mes, int anno,int sms_1,int sms_2){
	f = fopen("log_reader.html", "a");

    fprintf(f, "PID %d %d:%d %d/%d/%d sms %d%d <br>\n", pid, hora, min, dia,mes,anno,sms_1,sms_2);
    fclose(f);

}
