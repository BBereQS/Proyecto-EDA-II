#include "Serializacion.h"

/**
 * @brief Lee y muestra el contenido de un archivo de texto.
 *
 * @param file_name Nombre del archivo de texto a leer.
 *
 */
void read_file(char* file_name) {
    FILE* file = fopen(file_name, "r"); 

    if (file == NULL) {
        printf("Error al abrir el archivo %s\n", file_name);
        return;
    }

    char buffer[1024]; 

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer); 
    }

    fclose(file); 
}

/**
 * @brief Crea un archivo JSON con la información de una reserva.
 *
 * @param invoice Puntero a la estructura Invoice con la información de la reserva.
 * @param file_name Nombre del archivo JSON a crear.
 *
 */
void create_json( Invoice* invoice, char* file_name ) {
    FILE* json_output = fopen( file_name, "w");
    if( !json_output){
        printf( "Error abriendo el archivo\n");
        exit( 1 );
    }

    fprintf( json_output, "{\n");

    fprintf( json_output, "\"client\" : \"%s\",\n", invoice->client );                             
    fprintf( json_output, "\"restaurant\" : \"%s\",\n", invoice->restaurant );  
    fprintf( json_output, "\"Reserva_hecha\" : \"%s\",\n", invoice->Reserva_hecha ); 
    fprintf( json_output, "\"date\" : \"%s\"\n", invoice->date );  
    fprintf (json_output, "\n}");

    fclose (json_output);
}

/**
 * @brief Serializa la información de una reserva y la almacena en un archivo JSON.
 
 * @param client Nombre del cliente.
 * @param restaurant Nombre del restaurante.
 * @param date Fecha de la reserva.
 */
void Serializar(char* client, char* restaurant, char* date){
    Invoice factura;

    strncpy(factura.client, client, sizeof(factura.client) - 1);
    strncpy(factura.restaurant, restaurant, sizeof(factura.restaurant) - 1);
    strncpy(factura.date, date, sizeof(factura.date) - 1);

    setenv("TZ", "America/Mexico_City", 1);
    tzset();

    time_t tiempoActual;
    struct tm *infoTiempo;
    time(&tiempoActual);
    infoTiempo = localtime(&tiempoActual);
    strftime( factura.Reserva_hecha, sizeof(factura.Reserva_hecha), "%Y-%m-%d, %H,%M", infoTiempo);


    create_json( &factura, "Reserva.json");

    fprintf( stderr, "Se creo correctamente la reserva \n");

    read_file( "Reserva.json");
}
