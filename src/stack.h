#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "graph.h"

typedef struct Stack_element Stack_element;			
struct Stack_element {						
  element** array;						
  size_t size;						
  size_t occupied;						
};								
Stack_element init_stack_element()				
{								
  return (Stack_element) {					
    .array = NULL,						
    .size = 0,						
    .occupied = 0,						
  };								
}								
void push_stack_element(Stack_element* st, element* data)		
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
element* pop_stack_element(Stack_element* st)			
{								
  element* tmp = st->array[(st->occupied)-1];			
  st->occupied-=1;						
  st->size-=1;						
  return tmp;							
}								
element* peek_stack_element(Stack_element* st)			
{								
  element* tmp = st->array[(st->occupied)-1];			
  return tmp;							
}								
void deinit_stack_element(Stack_element* st)			
{								
  if (st) free(st->array);						
  else printf("Invalid pointer");				
}								
bool empty_stack_element(Stack_element* st)			
{								
  if (st->array == 0) {					
    return true;						
  }								
  return false;						
}								
