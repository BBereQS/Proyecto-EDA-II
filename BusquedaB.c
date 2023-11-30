

#include "BusquedaB.h"

/**
 * @brief Realiza una búsqueda binaria en un arreglo de restaurantes basada en la cantidad de estrellas.
 *
 * @param list         Arreglo de restaurantes ordenado por estrellas.
 * @param len          Longitud del arreglo.
 * @param key          Cantidad de estrellas a buscar.
 * @param found_name   Puntero a una cadena donde se almacenará el nombre del restaurante encontrado.
 *
 * @return true si se encuentra un restaurante con la cantidad de estrellas especificada, false de lo contrario.
 *
 * @note Esta función asume que el arreglo 'list' está ordenado por la cantidad de estrellas.
 */
bool binary_search_stars(Restaurante list[], int len, int key, char* found_name) {
    int first = 0;
    int last = len - 1;
    bool found = false;

    #pragma omp parallel
    {
        while (first <= last) {
            int center = (first + last) / 2;

            #pragma omp critical
            {
                if (list[center].stars == key) {
                    found = true;
                    snprintf(found_name, sizeof(list[center].name), "%s", list[center].name);
                }
            }

            #pragma omp barrier

            if (key < list[center].stars) {
                last = center - 1;
            } else {
                first = center + 1;
            }

            #pragma omp barrier
        }
    }

    return found;
}

/**
 * @brief Intercambia dos elementos de tipo Restaurante.
 *
 * @param val1 Primer restaurante a intercambiar.
 * @param val2 Segundo restaurante a intercambiar.
 *
 * @note Esta función es utilizada internamente para facilitar el ordenamiento y la construcción del montículo.
 */
void swap_b(Restaurante* val1, Restaurante* val2) {
    Restaurante temp = *val1;
    *val1 = *val2;
    *val2 = temp;
}

/**
 * @brief Acomoda un subárbol de un arreglo de restaurantes en forma de montículo.
 *
 * @param list Arreglo de restaurantes.
 * @param n    Número total de elementos en el arreglo.
 * @param root Raíz del subárbol.
 *
 * @note Esta función es utilizada internamente por 'build_max_heap' y 'heap_sort'.
 */
void heapify(Restaurante list[], size_t n, size_t root) {
    size_t left = 2 * root + 1;
    size_t right = 2 * root + 2;
    size_t largest = root;

    if ((left < n) && (list[left].stars > list[root].stars)) {
        largest = left;
    }

    if ((right < n) && (list[right].stars > list[largest].stars)) {
        largest = right;
    }

    if (largest != root) {
        swap_b(&list[root], &list[largest]);
        heapify(list, n, largest);
    }
}

/**
 * @brief Construye un montículo máximo a partir de un arreglo de restaurantes.
 *
 * @param list      Arreglo de restaurantes.
 * @param num_elems Número total de elementos en el arreglo.
 *
 * @note Esta función es utilizada internamente por 'heap_sort'.
 */
void build_max_heap(Restaurante list[], int num_elems) {
    int temp = num_elems / 2;
    for (int i = temp; i > 0; --i) {
        heapify(list, num_elems, i - 1);
    }
}

/**
 * @brief Ordena un arreglo de restaurantes utilizando el algoritmo de ordenación 'Heap Sort'.
 *
 * @param list      Arreglo de restaurantes a ordenar.
 * @param num_elems Número total de elementos en el arreglo.
 *
 * @note Esta función utiliza un montículo máximo para realizar la ordenación.
 */
void heap_sort(Restaurante list[], int num_elems) {
    build_max_heap(list, num_elems);
    for (int i = num_elems; i > 0; --i) {
        swap_b(&list[0], &list[i - 1]);
        heapify(list, i - 1, 0);
    }
}