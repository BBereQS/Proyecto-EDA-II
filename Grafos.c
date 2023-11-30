

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>

#include "List.h"
#include "Queue.h"
#include "Grafos.h"

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

/**
 * @brief Verifica si el vértice tiene vecinos.
 *
 * @param v Puntero al vértice.
 * @return true si el vértice tiene vecinos; false en caso contrario.
 */
bool Vertex_HasNeighbors( Vertex* v )
{
   assert( v );

   return v->neighbors;
}

/**
 * @brief Hace que cursor libre apunte al inicio de la lista de vecinos. Se debe
 * de llamar siempre que se vaya a iniciar un recorrido de dicha lista.
 *
 * @param v El vértice de trabajo (es decir, el vértice del cual queremos obtener 
 * la lista de vecinos).
 */
void Vertex_Start( Vertex* v )
{
   assert( v );

   List_Cursor_front( v->neighbors );
}

/**
 * @brief Mueve al cursor libre un nodo adelante.
 *
 * @param v El vértice de trabajo.
 *
 * @pre El cursor apunta a un nodo válido.
 * @post El cursor se movió un elemento a la derecha en la lista de vecinos.
 */
void Vertex_Next( Vertex* v )
{
   List_Cursor_next( v->neighbors );
}

/**
 * @brief Indica si se alcanzó el final de la lista de vecinos.
 *
 * @param v El vértice de trabajo.
 *
 * @return true si se alcanazó el final de la lista; false en cualquier otro
 * caso.
 */
bool Vertex_End( const Vertex* v )
{
   return List_Cursor_end( v->neighbors );
}

/**
 * @brief Obtiene el índice del vecino actual apuntado por el cursor libre.
 *
 * @param v Puntero al vértice.
 * @return Estructura Data que contiene el índice del vecino.
 */
Data Vertex_GetNeighborIndex( const Vertex* v )
{
   return List_Cursor_get( v->neighbors );
}

/**
 * @brief Establece el color del vértice.
 *
 * @param v Puntero al vértice.
 * @param color Color a establecer.
 */
void Vertex_SetColor( Vertex* v, eGraphColors color )
{
   v->color = color;
}

/**
 * @brief Obtiene el color del vértice.
 *
 * @param v Puntero al vértice.
 * @return Color del vértice.
 */
eGraphColors Vertex_GetColor( Vertex* v )
{
   return v->color;
}

/**
 * @brief Obtiene la información asociada al vértice.
 *
 * @param v Puntero al vértice.
 * @return Información asociada al vértice.
 */
const char* Vertex_GetData( const Vertex* v )
{
   return v->data;
}

/**
 * @brief Establece el predecesor del vértice.
 *
 * @param v Puntero al vértice.
 * @param predecessor_idx Índice del predecesor en la lista de vértices.
 */
void Vertex_SetPredecessor( Vertex* v, int predecessor_idx )
{
    v->predecessor = predecessor_idx;
}

/**
 * @brief Obtiene el índice del predecesor del vértice.
 *
 * @param v Puntero al vértice.
 * @return Índice del predecesor.
 */
int Vertex_GetPredecessor( const Vertex* v )
{
    return v->predecessor;
}

/**
 * @brief Establece el tiempo de descubrimiento del vértice.
 *
 * @param v Puntero al vértice.
 * @param time Tiempo de descubrimiento a establecer.
 */
void Vertex_SetDiscovery_time( Vertex* v, int time )
{
    v->discovery_time = time;
}

/**
 * @brief Obtiene el tiempo de descubrimiento del vértice.
 *
 * @param v Puntero al vértice.
 * @return Tiempo de descubrimiento.
 */
int Vertex_GetDiscovery_time( const Vertex* v )
{
    return v->discovery_time;
}

/**
 * @brief Establece el tiempo de finalización del vértice.
 *
 * @param v Puntero al vértice.
 * @param time Tiempo de finalización a establecer.
 */
void Vertex_SetFinish_time( Vertex* v, int time )
{
    v->finish_time = time;
}

/**
 * @brief Obtiene el tiempo de finalización del vértice.
 *
 * @param v Puntero al vértice.
 * @return Tiempo de finalización.
 */
int Vertex_GetFinish_time( const Vertex* v )
{
    return v->finish_time;
}


//----------------------------------------------------------------------
//                     Funciones privadas
//----------------------------------------------------------------------

/**
 * @brief Busca el índice de la primer coincidencia del valor en la lista de vértices.
 *
 * @param vertices Lista de vértices.
 * @param size Número de elementos en la lista de vértices.
 * @param key Valor a buscar.
 * @return El índice donde se encuentra la primer coincidencia; -1 si no se encontró.
 */
static int find( Vertex vertices[], int size, const char* key )
{
   for( int i = 0; i < size; ++i )
   {
        if (strcmp(vertices[i].data, key) == 0) return i;
   }

   return -1;
}

/**
 * @brief Busca en la lista de vecinos si el índice del vértice vecino ya se encuentra ahí.
 *
 * @param v Puntero al vértice de trabajo.
 * @param index Índice en la lista de vértices del vértice vecino que está por insertarse.
 * @return true si el índice del vértice vecino ya está en la lista; false en caso contrario.
 */
static bool find_neighbor( Vertex* v, int index )
{
   if( v->neighbors )
   {
      return List_Find( v->neighbors, index );
   }
   return false;
}

/**
 * @brief Inserta un vértice vecino en la lista de vecinos del vértice de trabajo.
 *
 * @param vertex Puntero al vértice de trabajo.
 * @param index Índice en la lista de vértices del vértice vecino que está por insertarse.
 * @param weight Peso de la arista entre los vértices.
 */
static void insert( Vertex* vertex, int index, float weigth )
{
   // crear la lista si no existe!
   
   if( !vertex->neighbors )
   {
      vertex->neighbors = List_New();
   }

   if( vertex->neighbors && !find_neighbor( vertex, index ) )
   {
      List_Push_back( vertex->neighbors, index, weigth );

      DBG_PRINT( "insert():Inserting the neighbor with idx:%d, distance:%f\n", index, weight );
   } 
   else DBG_PRINT( "insert: duplicated index\n" );
}


//----------------------------------------------------------------------
//                     Funciones públicas
//----------------------------------------------------------------------


/**
 * @brief Crea un nuevo grafo.
 *
 * @param size Número de vértices que tendrá el grafo. Este valor no se puede
 * cambiar luego de haberlo creado.
 *
 * @return Un nuevo grafo.
 *
 * @pre El número de elementos es mayor que 0.
 */
Graph* Graph_New( int size, eGraphType type )
{
   assert( size > 0 );

   Graph* g = (Graph*) malloc( sizeof( Graph ) );
   if( g )
   {
      g->size = size;
      g->len = 0;
      g->type = type;

      g->vertices = (Vertex*) calloc( size, sizeof( Vertex ) );

      if( !g->vertices )
      {
         free( g );
         g = NULL;
      }
   }

   return g;
   // el cliente es responsable de verificar que el grafo se haya creado correctamente
}

/**
 * @brief Libera la memoria asociada al grafo, incluyendo vértices y listas de vecinos.
 *
 * @param g Doble puntero al grafo que se va a eliminar. Después de esta función, el puntero
 * se establecerá como NULL.
 *
 * @note La función libera la memoria asociada al grafo, incluyendo los datos de los vértices,
 * las listas de vecinos y finalmente la estructura del grafo. Es responsabilidad del cliente
 * asegurarse de no utilizar el puntero después de llamar a esta función.
 */
void Graph_Delete( Graph** g )
{
   assert( *g );

   Graph* graph = *g;
   // para simplificar la notación 

   for( int i = 0; i < graph->size; ++i )
   {
      Vertex* vertex = &graph->vertices[ i ];
      free(vertex->data);
      // para simplificar la notación. 
      // La variable |vertex| sólo existe dentro de este for.

      if( vertex->neighbors )
      {
         List_Delete( &(vertex->neighbors) );
      }
   }

   free( graph->vertices );
   free( graph );
   *g = NULL;
}

/**
 * @brief Imprime información detallada de los vértices del grafo utilizando un recorrido DFS.
 *
 * @param g Puntero al grafo que se va a imprimir.
 *
 * @note La función imprime información detallada de cada vértice del grafo, incluyendo su
 * tiempo de descubrimiento, tiempo de finalización y vecinos alcanzados durante el recorrido
 * DFS. La información se muestra en la consola.
 */
void Graph_Print_dfs( Graph* g )
{
    for( int i = 0; i < g->len; ++i )
    {
      Vertex* vertex = &g->vertices[ i ];

      printf( "[%d] (%s) -- Discovery_t: %d, Finish_t: %d, Neighbors =>", i, Graph_GetDataByIndex( g, i ), Vertex_GetDiscovery_time( vertex ), Vertex_GetFinish_time( vertex ) );
      if( Vertex_HasNeighbors( vertex ) )
      {
         for( List_Cursor_front( vertex->neighbors );
              ! List_Cursor_end( vertex->neighbors );
              List_Cursor_next( vertex->neighbors ) )
         {

            Data d = List_Cursor_get( vertex->neighbors );
            int neighbor_idx = d.index;
            float distance = d.weight;

            printf( "%s->", Graph_GetDataByIndex( g, neighbor_idx ) );
         }
      }
      printf( "Nil\n" );

   }
   printf( "\n" );
}

/**
 * @brief Crea un vértice a partir de los datos reales.
 *
 * @param g     El grafo.
 * @param data  Es la información.
 */
void Graph_AddVertex( Graph* g, const char* data )
{
   assert( g->len < g->size );

   Vertex* vertex = &g->vertices[ g->len ];
   // para simplificar la notación 

   vertex->data = strdup(data);
   vertex->neighbors = NULL;
   vertex->distance = 0.0; 

   ++g->len;
}

int Graph_GetSize( Graph* g )
{
   return g->size;
}

float Graph_GetEdgeWeight(Graph* g, int start, int finish)
{
    List* neighbors = g->vertices[start].neighbors;
    for (List_Cursor_front(neighbors); !List_Cursor_end(neighbors); List_Cursor_next(neighbors))
    {
        Data data = List_Cursor_get(neighbors);
        if (data.index == finish)
        {
            return data.weight;
        }
    }
    return 0.0;
}

/**
 * @brief Imprime la distancia y el camino más corto entre dos calles en el grafo.
 *
 * @param g       Puntero al grafo.
 * @param street1 Nombre de la primera calle.
 * @param street2 Nombre de la segunda calle.
 *
 * @note La función utiliza el recorrido DFS topológico para encontrar el camino más corto
 * entre las dos calles y calcular la distancia total. Imprime la distancia y el camino
 * más corto en la consola.
 */
void PrintDistance(Graph* g, const char* street1, const char* street2)
{
    int numVertices = Graph_GetSize(g);
    int* predecessors = malloc(numVertices * sizeof(int));

    if (predecessors == NULL)
    {
        fprintf(stderr, "Error: No se pudo asignar memoria.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < numVertices; ++i){
        predecessors[i] = -1;
    }

    int street1Index = Graph_GetIndexByValue(g, street1);
    int street2Index = Graph_GetIndexByValue(g, street2);

    if (street1Index == -1 || street2Index == -1)
    {
        fprintf(stderr, "Error: Una de las calles no existe en el grafo\n");
        free(predecessors);
        exit(EXIT_FAILURE);
    }

    // Realizamosel recorrido DFS desde la calle1
    dfs_topol(g, street1);

    // Recuperar el camino más corto utilizando la información del predecesor
    int current = street2Index;
    List* path = List_New();
    float totalDistance = 0.0;

    while (current != -1)
    {
        int predecessorIndex = Vertex_GetPredecessor(&g->vertices[current]);
        
        if (predecessorIndex != -1)
        {
            // Obtener la distancia entre el vértice actual y su predecesor
            totalDistance += Graph_GetEdgeWeight(g, predecessorIndex, current);
        }
    
        List_Push_front(path, current, 0.0);
        current = predecessorIndex;
    }

    // Imprimir la distancia total y el camino más corto
    printf("Distancia entre %s y %s: %.2f km\n", street1, street2, totalDistance);

    if (List_Is_empty(path))
    {
        printf("No hay conexión directa entre %s y %s\n", street1, street2);
    }
    else
    {
        printf("Camino más corto: ");
        for (List_Cursor_front(path); !List_Cursor_end(path); List_Cursor_next(path))
        {
            Data pathData = List_Cursor_get(path);
            printf("%s", Graph_GetDataByIndex(g, pathData.index));
            if (!List_Cursor_end(path))
                printf(" -> ");
        }
        printf("Llegaste! :D ");
        printf("\n");
    }

    // Liberar la memoria
    free(predecessors);
    List_Delete(&path);
}

/**
 * @brief Calcula la distancia entre dos calles en el grafo.
 *
 * @param g       Puntero al grafo.
 * @param street1 Nombre de la primera calle.
 * @param street2 Nombre de la segunda calle.
 *
 * @return Distancia total entre las dos calles en el grafo.
 *
 * @note La función utiliza el recorrido DFS topológico para encontrar el camino más corto
 * entre las dos calles y calcular la distancia total.
 */
float GetDistance(Graph* g, const char* street1, const char* street2){
    int numVertices = Graph_GetSize(g);
    int* predecessors = malloc(numVertices * sizeof(int));

    if (predecessors == NULL)
    {
        fprintf(stderr, "Error: No se pudo asignar memoria.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < numVertices; ++i){
        predecessors[i] = -1;
    }

    int street1Index = Graph_GetIndexByValue(g, street1);
    int street2Index = Graph_GetIndexByValue(g, street2);

    if (street1Index == -1 || street2Index == -1)
    {
        fprintf(stderr, "Error: Una de las calles no existe en el grafo\n");
        free(predecessors);
        exit(EXIT_FAILURE);
    }

    // Realizamosel recorrido DFS desde la calle1
    dfs_topol(g, street1);

    // Recuperar el camino más corto utilizando la información del predecesor
    int current = street2Index;
    List* path = List_New();
    float totalDistance = 0.0;

    while (current != -1)
    {
        int predecessorIndex = Vertex_GetPredecessor(&g->vertices[current]);
        
        if (predecessorIndex != -1)
        {
            // Obtener la distancia entre el vértice actual y su predecesor
            totalDistance += Graph_GetEdgeWeight(g, predecessorIndex, current);
        }
    
        List_Push_front(path, current, 0.0);
        current = predecessorIndex;
    }
    //printf("%f", totalDistance);
    return totalDistance;
}

/**
 * @brief Inserta una relación de adyacencia del vértice |start| hacia el vértice |finish|.
 *
 * @param g      El grafo.
 * @param start  Vértice de salida (el dato)
 * @param finish Vertice de llegada (el dato)
 *
 * @return false si uno o ambos vértices no existen; true si la relación se creó con éxito.
 *
 * @pre El grafo no puede estar vacío.
 */
bool Graph_AddEdge( Graph* g, const char* start, const char* finish, float weigth )
{
   assert( g->len > 0 );

   // obtenemos los índices correspondientes:
   int start_idx = find( g->vertices, g->size, start );
   int finish_idx = find( g->vertices, g->size, finish );

   DBG_PRINT( "AddEdge(): from:%s (with index:%d), to:%s (with index:%d), distance:%f\n", start, start_idx, finish, finish_idx, weight );

   if( start_idx == -1 || finish_idx == -1 ) return false;
   // uno o ambos vértices no existen

   insert( &g->vertices[ start_idx ], finish_idx, weigth );
   // insertamos la arista start-finish

   if( g->type == eGraphType_UNDIRECTED ) insert( &g->vertices[ finish_idx ], start_idx, weigth );
   // si el grafo no es dirigido, entonces insertamos la arista finish-start

   return true;
}

/**
 * @brief Obtiene la cantidad de vértices en el grafo.
 *
 * @param g Puntero al grafo.
 *
 * @return Cantidad de vértices en el grafo.
 */
int Graph_GetLen( const Graph* g )
{
   return g->len;
}


/**
 * @brief Devuelve la información asociada al vértice indicado.
 *
 * @param g          Un grafo.
 * @param vertex_idx El índice del vértice del cual queremos conocer su información.
 *
 * @return La información asociada al vértice vertex_idx.
 */
const char* Graph_GetDataByIndex( const Graph* g, int vertex_idx )
{
   assert( 0 <= vertex_idx && vertex_idx < g->len );

   return g->vertices[ vertex_idx ].data;
}

/**
 * @brief Devuelve una referencia al vértice indicado.
 *
 * Esta función puede ser utilizada con las operaciones @see Vertex_Start(), @see Vertex_End(), @see Vertex_Next().
 *
 * @param g          Un grafo
 * @param vertex_idx El índice del vértice del cual queremos devolver la referencia.
 *
 * @return La referencia al vértice vertex_idx.
 */
Vertex* Graph_GetVertexByIndex( const Graph* g, int vertex_idx )
{
   assert( 0 <= vertex_idx && vertex_idx < g->len );

   return &(g->vertices[ vertex_idx ] );
}

/**
 * @brief Devuelve una referencia al vértice indicado.
 *
 * Esta función puede ser utilizada con las operaciones @see Vertex_Start(), @see Vertex_End(), @see Vertex_Next().
 *
 * @param g   Un grafo
 * @param key Llave de búsqueda (esto es, el |dato|) del vértice del cual queremos devolver la referencia.
 *
 * @return La referencia al vértice que coincida con key (esto es, con el |dato|).
 */
Vertex* Graph_GetVertexByKey( const Graph* g, const char* key )
{
   for( int i = 0; i < Graph_GetLen( g ); ++i )
   {
        if (strcmp(g->vertices[i].data, key) == 0) {
            return &(g->vertices[i]);
        }
   }
   
   return NULL;
}

/**
 * @brief Obtiene el índice de un vértice en el grafo mediante su valor (dato).
 *
 * @param g     Puntero al grafo.
 * @param value Valor (dato) del vértice que se desea encontrar.
 *
 * @return Índice del vértice en el grafo. Si no se encuentra, retorna -1.
 */
int Graph_GetIndexByValue ( Graph* g, const char* value )
{
    for(int i = 0; i < Graph_GetLen( g ); i++)
    {
        if( strcmp(g->vertices[ i ].data, value) == 0)
            return i;
    }
    
    return -1;
}

/**
 * @brief Obtiene el tamaño (número de vértices) del grafo.
 *
 * @param g Puntero al grafo.
 *
 * @return Tamaño del grafo, es decir, el número de vértices.
 */
int Graph_Size( Graph* g )
{
   return g->size;
}

/**
 * @brief Imprime las calles del grafo, excluyendo la calle asociada al vértice proporcionado.
 *
 * @param g      Puntero al grafo.
 * @param vertex Puntero al vértice cuya calle se excluye de la impresión.
 */
void Graph_PrintStreets( Graph* g, Vertex *vertex ){
  
   for( int i = 0; i < g->len; ++i)
   {
       Vertex* vertex_aux = &g->vertices[ i ];
       if( vertex_aux != vertex)
          printf( " -%s\n", Graph_GetDataByIndex( g, i ) );
   }
   printf( "\n" );
  
}


//----------------------------------------------------------------------
//                          dfs_traverse()
//----------------------------------------------------------------------

/**
 * @brief Realiza un recorrido DFS sobre el grafo a partir de un vértice dado.
 *
 * @param g        Puntero al grafo.
 * @param v        Puntero al vértice de inicio para el recorrido DFS.
 * @param pTiempo  Puntero al tiempo de descubrimiento actual.
 * @param list     Puntero a una lista para almacenar el orden de finalización de los vértices.
 */

void dfs_traverse( Graph* g, Vertex* v, int* pTiempo, List* list )
{
    
   *pTiempo += 1;
   Vertex_SetDiscovery_time( v, *pTiempo );
   
   if( Vertex_HasNeighbors( v ) )
   {
      for( Vertex_Start( v ); ! Vertex_End( v ); Vertex_Next( v ) )
      {
         Vertex* w = Graph_GetVertexByIndex( g, Vertex_GetNeighborIndex( v ).index );

         if( Vertex_GetColor( w ) == WHITE )
         {
            DBG_PRINT( "Visiting vertex: (p:%d)->%d\n", Vertex_GetData( v ), Vertex_GetData( w ) );

            Vertex_SetColor( w, GRAY );
            
            Vertex_SetPredecessor( w, Graph_GetIndexByValue(g, Vertex_GetData(v)) );
            
            dfs_traverse( g, w, pTiempo, list );
         }
      }
      DBG_PRINT( "Returning to: %d\n", Vertex_GetData( v ) );
   }
   else
   {
      DBG_PRINT( "Vertex %d doesn't have any neighbors\n", Vertex_GetData( v ) );
   }

   Vertex_SetColor( v, BLACK );
   *pTiempo += 1;
   Vertex_SetFinish_time( v, *pTiempo );
   List_Push_back( list, Graph_GetIndexByValue( g, v->data ), 0.0 );
   
}

/**
 * @brief Realiza un recorrido DFS sobre el grafo para obtener un ordenamiento topológico.
 *
 * @param g     Puntero al grafo.
 * @param start Nombre del vértice de inicio para el recorrido DFS.
 */
void dfs_topol( Graph* g, const char* start )
{
   for( int i = 0; i < Graph_GetLen( g ); ++i )
   {
      Vertex* v = Graph_GetVertexByIndex( g, i );

      Vertex_SetColor( v, WHITE );
      Vertex_SetPredecessor( v, -1 );
      Vertex_SetDiscovery_time( v, 0 );
      Vertex_SetFinish_time( v, 9);
   }
    
   List* salida_topo = List_New();
   
   Vertex_SetColor( Graph_GetVertexByKey( g, start ), GRAY );
   DBG_PRINT( "Visiting start node: %s\n", start );
    
   int tiempo = 0;
   dfs_traverse( g, Graph_GetVertexByKey( g, start), &tiempo, salida_topo );
   
   //Despues de terminar el primer dfs buscamos entre nuestros vértices para encontrar a todos aquellos que faltan por procesarse
   //para poder procesarlos
   for( int i = 0; i < Graph_GetLen( g ); ++i)
   {
       Vertex* vertex = Graph_GetVertexByIndex( g, i );
       if( Vertex_GetColor( vertex ) == WHITE )
            dfs_traverse( g, vertex, &tiempo, salida_topo );
   }
   
   /* Activar en caso de querer conocer el ordenamiento topológico del grafo
   
   printf( "\nOrdenamiento topológico del grafo\n" );
   for( List_Cursor_front( salida_topo );
        ! List_Cursor_end( salida_topo );
        List_Cursor_next( salida_topo ) )
    {
        Data d = List_Cursor_get( salida_topo );
        int index_list = d.index;
        
        printf( "%d->", Vertex_GetData( &g->vertices[ index_list ] ));
    }
    printf( "Nil\n\n" );
    */
    List_Delete( &salida_topo );
}

