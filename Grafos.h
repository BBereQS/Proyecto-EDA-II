

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include "List.h"
#include "Queue.h"

// 29/03/23:
// Esta versión no borra elementos
// Esta versión no modifica los datos originales

#ifndef DBG_HELP
#define DBG_HELP 0
#endif  

#if DBG_HELP > 0
#define DBG_PRINT( ... ) do{ fprintf( stderr, "DBG:" __VA_ARGS__ ); } while( 0 )
#else
#define DBG_PRINT( ... ) ;
#endif  


typedef struct{
    char name[32];
    char ubicacion[32];
    int stars;
} Restaurante;

// Aunque en este ejemplo estamos usando tipos básicos, vamos a usar al alias |Item| para resaltar
// aquellos lugares donde estamos hablando de DATOS y no de índices.
//typedef int Item;

/**
* @brief Colores para
*/
typedef enum
{
   WHITE, ///< vértice
   GRAY,  ///< vértice
   BLACK, ///< vértice
} eGraphColors;


//----------------------------------------------------------------------
//                           Vertex stuff: 
//----------------------------------------------------------------------


/**
 * @brief Declara lo que es un vértice.
 */
typedef struct
{
   char* data;
   List* neighbors;

   int predecessor;
   eGraphColors color;
   
   int finish_time;
   int discovery_time;
   float distance;
   
} Vertex;

bool Vertex_HasNeighbors( Vertex* v );

void Vertex_Start( Vertex* v );

void Vertex_Next( Vertex* v );

bool Vertex_End( const Vertex* v );

Data Vertex_GetNeighborIndex( const Vertex* v );

void Vertex_SetColor( Vertex* v, eGraphColors color );

eGraphColors Vertex_GetColor( Vertex* v );

const char* Vertex_GetData( const Vertex* v );

void Vertex_SetPredecessor( Vertex* v, int predecessor_idx );

int Vertex_GetPredecessor( const Vertex* v );

void Vertex_SetDiscovery_time( Vertex* v, int timer );

int Vertex_GetDiscovery_time( const Vertex* v );

void Vertex_SetFinish_time( Vertex* v, int timer );

int Vertex_GetFinish_time( const Vertex* v );



//----------------------------------------------------------------------
//                           Graph stuff: 
//----------------------------------------------------------------------

/** Tipo del grafo.
 */
typedef enum 
{ 
   eGraphType_UNDIRECTED, ///< grafo no dirigido
   eGraphType_DIRECTED    ///< grafo dirigido (digraph)
} eGraphType; 

/**
 * @brief Declara lo que es un grafo.
 */
typedef struct
{
   Vertex* vertices; ///< Lista de vértices
   int size;         ///< Tamaño de la lista de vértices

   /**
    * Número de vértices actualmente en el grafo. 
    * Como esta versión no borra vértices, lo podemos usar como índice en la
    * función de inserción
    */
   int len;  

   eGraphType type; ///< tipo del grafo, UNDIRECTED o DIRECTED
} Graph;

//----------------------------------------------------------------------
//                     Funciones privadas
//----------------------------------------------------------------------


static int find( Vertex vertices[], int size, const char* key );

static bool find_neighbor( Vertex* v, int index );

static void insert( Vertex* vertex, int index, float weigth );


//----------------------------------------------------------------------
//                     Funciones públicas
//----------------------------------------------------------------------

Graph* Graph_New( int size, eGraphType type );

void Graph_Delete( Graph** g );

float Graph_GetEdgeWeight(Graph* g, int start, int finish);

void Graph_Print_dfs( Graph* g );

void Graph_AddVertex( Graph* g, const char* data );

int Graph_GetSize( Graph* g );

bool Graph_AddEdge( Graph* g, const char* start, const char* finish, float weigth );

int Graph_GetLen( const Graph* g ); 

const char* Graph_GetDataByIndex( const Graph* g, int vertex_idx );

Vertex* Graph_GetVertexByIndex( const Graph* g, int vertex_idx );

Vertex* Graph_GetVertexByKey( const Graph* g, const char* key );

int Graph_GetIndexByValue ( Graph* g, const char* value );

int Graph_Size( Graph* g );

void PrintDistance(Graph* g, const char* street1, const char* street2);

float GetDistance(Graph* g, const char* street1, const char* street2);

void Graph_PrintStreets( Graph* g, Vertex *vertex );

//----------------------------------------------------------------------
//                          dfs_traverse()
//----------------------------------------------------------------------

void dfs_traverse( Graph* g, Vertex* v, int* pTiempo, List* list );

void dfs_topol( Graph* g, const char* start );
