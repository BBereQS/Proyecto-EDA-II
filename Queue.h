
#ifndef  QUEUE_INC
#define  QUEUE_INC


#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

//#include "DLL.h"
// Item está definida aquí

typedef struct 
{
	int* q;
   int front;
   int back;
   int len;
   int size;
} Queue;

Queue* Queue_New();
void   Queue_Delete(    Queue* *this );
void   Queue_Enqueue(   Queue* this, int value );
int    Queue_Dequeue(   Queue* this );
int    Queue_Peek(      Queue* this );
bool   Queue_IsEmpty(   Queue* this );
bool   Queue_IsFull(    Queue* this );
size_t Queue_Len(       Queue* this );


#endif   /* ----- #ifndef QUEUE_INC  ----- */
