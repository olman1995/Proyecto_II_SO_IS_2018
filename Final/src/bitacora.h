void escribir_bitacora(FILE *f){
	f = fopen("../../bitacora.html", "a");

    fprintf(f, "<h1>Bitacora</h1> \n");
    fprintf(f, "<h2>Writer</h2> \n");
    fprintf(f, "<table style='width:500'> \n");
    fprintf(f, "<iframe src='./Writer/Debug/log_writer.html'></iframe>\n");
    fprintf(f, "</table>\n");

    fprintf(f, "<h2>Reader</h2> \n");
    fprintf(f, "<table style='width:500'> \n");
    fprintf(f, "<iframe src='./Reader/Debug/log_reader.html'></iframe>\n");

    fprintf(f, "</table>\n");

    fprintf(f, "<h2>Reader egosita</h2> \n");
    fprintf(f, "<table style='width:500'> \n");
    fprintf(f, "<iframe src='./Reader_Selfish/Debug/log_reader_selfish.html'></iframe>\n");
    fprintf(f, "</table>\n");

    fclose(f);

}
