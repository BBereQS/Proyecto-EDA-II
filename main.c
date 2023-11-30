
#include <stdio.h>

#include "Quicksort.h"
#include "Serializacion.h"
#include "BusquedaB.h"
#define MAX_VERTICES 10
#define MAX_NAME 50

int
main ()
{
    Graph *grafo = Graph_New (MAX_VERTICES,	
    			    eGraphType_DIRECTED);	
    
    // creamos los restaurantes
    Restaurante Restaurantes[5] = {
        {"La casa de toño", "Bucareli", 3},
        {"La fonda de doC1a pelos", "Insurgentes", 5},
        {"Taco bell", "Juarez", 1},
        {"Sushi Roll", "Paseo de la Reforma", 4},
        {"Pizzeria Don Pancho", "Eje Central", 2}
    };
    
    // creamos el arreglo de distancias 
    
    float Distancias[5];
    float Distanciastmp[5];
    
    
      // crea los vertices. El orden de insercion no es importante
      Graph_AddVertex (grafo, "Reforma");
      Graph_AddVertex (grafo, "Insurgentes");
      Graph_AddVertex (grafo, "Constituyentes");
      Graph_AddVertex (grafo, "Juarez");
      Graph_AddVertex (grafo, "Chapultepec");
      Graph_AddVertex (grafo, "Paseo de la Reforma");
      Graph_AddVertex (grafo, "Eje Central");
      Graph_AddVertex (grafo, "Sonora");
      Graph_AddVertex (grafo, "Bucareli");
    
      // crea las aristas (conexiones entre vertices) con su respectiva distancia:
      Graph_AddEdge (grafo, "Reforma", "Juarez", 2.5);
      Graph_AddEdge (grafo, "Juarez", "Paseo de la Reforma", 1.8);
      Graph_AddEdge (grafo, "Paseo de la Reforma", "Constituyentes", 4.2);
      Graph_AddEdge (grafo, "Constituyentes", "Insurgentes", 3.0);
      Graph_AddEdge (grafo, "Insurgentes", "Bucareli", 7.2);
      Graph_AddEdge (grafo, "Bucareli", "Eje Central", 1.5);
      Graph_AddEdge (grafo, "Eje Central", "Paseo de la Reforma", 5.0);
      Graph_AddEdge (grafo, "Chapultepec", "Paseo de la Reforma", 2.0);
      Graph_AddEdge (grafo, "Sonora", "Bucareli", 9.7);
      Graph_AddEdge (grafo, "Juarez", "Bucareli", 1.0);
      Graph_AddEdge (grafo, "Bucareli", "Juarez", 1.0);
      Graph_AddEdge (grafo, "Paseo de la Reforma", "Eje Central", 5.0);
      Graph_AddEdge (grafo, "Eje Central", "Paseo de la Reforma", 5.0);
      Graph_AddEdge (grafo, "Bucareli", "Insurgentes", 7.2);
      Graph_AddEdge (grafo, "Insurgentes", "Bucareli", 7.2);
    
      int op, stars;
      char calle[MAX_NAME];
      char tmp[MAX_NAME];
      int tmp2;
      Vertex *vertex;
    
      do
        {
          printf ("\nBienvenido a mapa de CDMX\n");
          printf ("\nMenu:\n");
          printf ("1) Buscar una calle y mostrar recorrido\n");
          printf ("2) Buscar restaurantes\n");
          printf ("3) Salir\n");
          printf ("Ingrese el numero de la opcionn: ");
          scanf ("%d", &op);
    
          switch (op)
    	{
    	case 1:
    	  vertex = Graph_GetVertexByIndex (grafo, op );
    	  Graph_PrintStreets (grafo, vertex);
    
    	  printf ("Ingrese el nombre de la calle en la que te encuentras: ");
    	  scanf ("%s", calle);
    
    	  printf ("Ingrese el nombre de la calle a la cual quieres llegar: ");
    	  scanf ("%s", tmp);
    
    	  dfs_topol (grafo, calle);	
    	  PrintDistance (grafo, calle, tmp);
    	  break;
    	case 2:
    	  vertex = Graph_GetVertexByIndex (grafo, op );
    	   Graph_PrintStreets (grafo, vertex);
    
    	  printf("Ingrese el nombre de la calle en la que te encuentras: \n");
    	  
    	  scanf ("%s", calle);
    
    	  printf ("1)Buscar por distancia\n"); 
    	  printf ("2)Buscar por estrellas\n"); 
    	  scanf( "%i", &tmp2);
    	  
    	  if( tmp2 == 1){
    	   
    	      for( int i = 0 ; i < 5 ; ++i ){
    	          Distancias[i] = GetDistance( grafo, calle, Restaurantes[i].ubicacion);
    	          //printf( "%f\n", Distancias[i]);
    	      }
    	      
    	      for( int i = 0 ; i < 5 ; ++i ){
    	          Distanciastmp[i] = Distancias[i];
    	      }
    	      
    	      quick_sort(Distanciastmp, 0, 4);
    	      //printf( "%f", Distanciastmp[0]);
    	      
    	      for( int i = 0 ; i < 5 ; ++i){
    	          if( Distancias[i] == Distanciastmp[0]){
    	              printf("El restaurante mas cercano es: %s, ubicado en: %s\n",
    	              Restaurantes[i].name, Restaurantes[i].ubicacion);
    	               dfs_topol (grafo, calle);	
    	               PrintDistance (grafo, calle, Restaurantes[i].ubicacion);
    	              printf("¿Deseas hacer una reservacion?\n");
    	              printf("1) si 2) no\n");
    	              scanf( "%i", &tmp2);
    	              
    	              if( tmp2 == 1 ){
    	                  Serializar("Cliente", Restaurantes[i].name, "2023-10-27");
    	              }
    	          }
    	      }
    	      
    	    }else{
    	      vertex = Graph_GetVertexByIndex(grafo , op  );
                int num_restaurants = sizeof(Restaurantes) / sizeof(Restaurante);
                char found_name[50];
                printf("Ingrese el numero de estrellas que deseas que el restaunte tenga: ");
                scanf("%i", &stars);
                    
                heap_sort(Restaurantes, num_restaurants);
                bool found = binary_search_stars(Restaurantes, num_restaurants, stars, found_name);
                if (found) {
                    printf("Restaurante encontrado: %s\n", found_name);
                } else {
                    printf("No se encontraron restaurantes con %d estrellas.\n", stars);
                }
                //dfs_topol (grafo, calle);	
    	        //PrintDistance (grafo, calle, found_name);
    	         printf("¿Deseas hacer una reservacion?\n");
    	              printf("1) si 2) no\n");
    	              scanf( "%i", &tmp2);
    	              
    	              if( tmp2 == 1 ){
    	                  Serializar("Cliente", found_name , "2023-10-27");
    	              }
    	    }
    	    break;
    	case 3:
    	  printf ("Saliendo del programa.\n");
    	  break;
    	default:
    	  printf ("Opcion no valida. Intente de nuevo.\n");
    	}
    
        }
      while (op != 3);
    
      Graph_Delete (&grafo);
      assert (grafo == NULL);
}
