#include "Quicksort.h"


/**
 * @brief Imprime los elementos de una lista.
 *
 * @param list La lista de enteros.
 * @param tam Tamaño de la lista.
 * @param msg Mensaje opcional a imprimir antes de la lista.
 */
void print(int* list, size_t tam, char* msg)
{
    printf("%s", msg);
    for (size_t i = 0; i < tam; ++i)
    {
        printf("%d, ", list[i]);
    }
    printf("\n");
}
/**
 * @brief Intercambia dos valores.
 *
 * @param val1 Puntero al primer valor.
 * @param val2 Puntero al segundo valor.
 *
 */
void swap(float* val1, float* val2)
{
    float temp = *val1;
    *val1 = *val2;
    *val2 = temp;
}

/**
 * @brief Implementa el algoritmo de ordenamiento quicksort.
 *
 * @param list La lista de enteros a ordenar.
 * @param first Índice del primer elemento de la lista.
 * @param last Índice del último elemento de la lista.
 */
void quick_sort(float list[], size_t first, size_t last)
{
    int x0 = first;
    int x1 = last;
    int mid = (first + last) / 2;
    float piv = list[mid];

    while (x0 <= x1)
    {
        while (list[x0] < piv)
        {
            ++x0;
        }

        while (list[x1] > piv)
        {
            --x1;
        }

        if (x0 <= x1)
        {

            swap(&list[x0], &list[x1]);
            ++x0;
            --x1;
        }
    }

    if (first < x1)
    {
        quick_sort(list, first, x1);
    }

    if (x0 < last)
    {
        quick_sort(list, x0, last);
    }
}
