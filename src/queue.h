#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "graph.h"
typedef struct Queue_element Queue_element;			
struct Queue_element {						
  element** array;						
  size_t size;						
  size_t occupied;						
};								
Queue_element init_Queue_element()				
{								
  return (Queue_element) {					
    .array = NULL,						
    .size = 0,						
    .occupied = 0,						
  };								
}								
void Queue_element_push(Queue_element* st, element* data)		
{								
  if (st->size == 0){						
    element** arr = (element**) malloc(sizeof(element*)*1);		
    st->array = arr;						
    st->array[st->occupied] = data;				
    st->size += 1;						
    st->occupied += 1;					
    return;							
  }								
  element** tmp = realloc(st->array, sizeof(element*)*(st->size+1));	
  st->array = tmp;						
  st->array[st->occupied] = data;				
  st->occupied+=1;						
  st->size+=1;						
}									
element* Queue_element_pop(Queue_element* st)				
{									
  element* tmp = st->array[0];						
  element** new = (element**)malloc(sizeof(element*)*(st->size-1));		
  memcpy(new, st->array+1, sizeof(element*)*(st->size-1));		
  free(st->array);							
  st->array = new;							
  st->occupied-=1;							
  st->size-=1;							
  return tmp;								
}									

bool Queue_element_empty(Queue_element* st)				
{									
  if (st->size == 0) {						
    return true;							
  }									
  return false;							
}									

void deinit_Queue_element(Queue_element* st)				
{								
  free(st->array);
}								
