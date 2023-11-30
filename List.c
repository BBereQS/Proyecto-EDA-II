
#include "List.h"

/**
 * @brief Crea y devuelve un nuevo nodo con los datos proporcionados.
 * @param index Índice asociado al nodo.
 * @param weight Peso asociado al nodo.
 * @return Puntero al nuevo nodo creado.
 */
static Node* new_node( int index, float weight )
{
   Node* n = (Node*) malloc( sizeof( Node ) );
   if( n != NULL )
   {
      n->data.index = index;
      n->data.weight = weight;

      n->next = NULL;
      n->prev = NULL;
   }

   return n;
}

/**
 * @brief Crea y devuelve una nueva lista vacía.
 * @return Puntero a la nueva lista creada.
 */
List* List_New()
{
   List* lst = (List*) malloc( sizeof(List) );
   if( lst )
   {
      lst->first = lst->last = lst->cursor = NULL;
   }

   return lst;
}

/**
 * @brief Libera la memoria asignada a la lista y sus nodos.
 * @param p_list Puntero al puntero de la lista que se va a eliminar.
 */
void List_Delete( List** p_list )
{
   assert( *p_list );

   while( (*p_list)->first )
   {
      List_Pop_back( *p_list );
   }

   free( *p_list );
   *p_list = NULL;
}

/**
 * @brief Agrega un nuevo nodo al final de la lista.
 * @param list Puntero a la lista.
 * @param data Índice asociado al nodo.
 * @param weight Peso asociado al nodo.
 */
void List_Push_back( List* list, int data, float weight )
{
   assert( list );
   
   Node* n = new_node( data, weight );
   assert( n );

   if( list->first != NULL )
   {
      list->last->next = n;
      n->prev = list->last;
      list->last = n;
   }
   else
   {
      list->first = list->last = list->cursor = n;
   }
}

/**
 * @brief Agrega un nuevo nodo al principio de la lista.
 * @param list Puntero a la lista.
 * @param data Índice asociado al nodo.
 * @param weight Peso asociado al nodo.
 */
void List_Push_front(List* list, int data, float weight)
{
   assert(list);

   Node* n = new_node(data, weight);
   assert(n);

   if (list->first != NULL)
   {
      n->next = list->first;
      list->first->prev = n;
      list->first = n;
   }
   else
   {
      list->first = list->last = list->cursor = n;
   }
}

/**
 * @brief Elimina el último nodo de la lista.
 * @param list Puntero a la lista.
 */
void List_Pop_back( List* list )
{
   assert( list );
   assert( list->first );
   // ERR: no podemos borrar nada de una lista vacía

   if( list->last != list->first )
   {
      Node* x = list->last->prev;
      free( list->last );
      x->next = NULL;
      list->last = x;
   }
   else
   {
      free( list->last );
      list->first = list->last = list->cursor = NULL;
   }

}


/**
 * @brief Verifica si la lista está vacía.
 * @param list Puntero a la lista.
 * @return true si la lista está vacía, false en caso contrario.
 */
bool List_Is_empty( List* list )
{
   assert( list );
   
   return !list->first;
}

/**
 * @brief Busca la primer ocurrencia con la llave key y si la encuentra coloca ahí al cursor.
 *
 * @param list Referencia a una lista.
 * @param key La llave de búsqueda.
 *
 * @return true si encontró el elemento; false en caso contrario.
 * @post Si hubo una ocurrencia el cursor es movido a esa posición; en caso contrario el cursor no se mueve.
 */
bool List_Find( List* list, int key )
{
   assert( list );
   
   Node* start = list->first;
   while( start )
   {
      if( start->data.index == key )
      {
         list->cursor = start;
         return true;
      }

      start = start->next;
   }
   return false;
}

/**
 * @brief Elimina el primer nodo con la llave key en la lista.
 * @param list Puntero a la lista.
 * @param key Llave de búsqueda.
 * @return true si se eliminó el nodo, false en caso contrario.
 * @post Si se elimina un nodo, el cursor se coloca en el nodo a la derecha del eliminado. Si este era el último,
 * el cursor se coloca en el primer nodo de la lista.
 */
bool List_Remove( List* list, int key )
{
   // terminar
   return false;
}

/**
 * @brief Coloca el cursor al principio de la lista.
 * @param list Puntero a la lista.
 */
void List_Cursor_front( List* list )
{
   assert( list );

   list->cursor = list->first;
}

/**
 * @brief Coloca el cursor al final de la lista.
 * @param list Puntero a la lista.
 */
void List_Cursor_back( List* list )
{
   assert( list );
   
   list->cursor = list->last;
}

/**
 * @brief Avanza el cursor al siguiente nodo en la lista.
 * @param list Puntero a la lista.
 * @return true si se pudo avanzar, false si el cursor ya está en el último nodo o la lista está vacía.
 */
bool List_Cursor_next( List* list )
{
   assert( list );
   
   list->cursor = list->cursor->next;
   return list->cursor;
}

/**
 * @brief Retrocede el cursor al nodo anterior en la lista.
 * @param list Puntero a la lista.
 * @return true si se pudo retroceder, false si el cursor ya está en el primer nodo o la lista está vacía.
 */
bool List_Cursor_prev( List* list )
{
   assert( list );
   
   // terminar
   return false;
}

/**
 * @brief Verifica si el cursor ha llegado al final de la lista.
 * @param list Puntero a la lista.
 * @return true si el cursor está al final de la lista, false en caso contrario.
 */
bool List_Cursor_end( List* list )
{
   assert( list );
   
   return list->cursor == NULL;
}

/**
 * @brief Obtiene los datos asociados al nodo actual apuntado por el cursor.
 * @param list Puntero a la lista.
 * @return Estructura de datos asociada al nodo actual.
 * @pre El cursor debe apuntar a un nodo válido.
 */
Data  List_Cursor_get( List* list )
{
   assert( list );
   assert( list->cursor );

   return list->cursor->data;
}

/**
 * @brief Elimina el elemento apuntado por el cursor.
 *
 * @param list Referencia a una lista.
 *
 * @pre El cursor debe apuntar a una posición válida.
 * @post El cursor queda apuntando al elemento a la derecha del elemento eliminado; si
 * este hubiese sido el último, entonces el cursor apunta al primer elemento de la lista.
 */
void List_Cursor_erase( List* list );


/**
 * @brief Aplica la función fn() a cada elemento de la lista. La función fn() es una función unaria.
 *
 * @param list Una lista.
 * @param fn Función unaria que será aplicada a cada elemento de la lista.
 */
void List_For_each( List* list, void (*fn)( int, float ) )
{
   Node* it = list->first;
   // |it| es la abreviación de "iterator", o  en español, "iterador"

   while( it != NULL )
   {
      fn( it->data.index, it->data.weight );

      it = it->next;
   }
}


