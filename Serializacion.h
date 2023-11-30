#ifndef SERIALIZACION_H
#define SERIALIZACION_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_MAXIMO 32

typedef struct{
    char   client[ TAM_MAXIMO];
    char   restaurant[ TAM_MAXIMO ];
    char   date[ TAM_MAXIMO ];
    char   Reserva_hecha[ TAM_MAXIMO ];


} Invoice;

void Serializar(char* client, char* restaurant, char* date);

void read_file(char* file_name); 
void create_json( Invoice* invoice, char* file_name );



#endif /* SERIALIZACION_H */
