#include "data_structures.h"
#include <assert.h>
#include <math.h>
#include <string.h>

#define INITIAL_SIZE 123
#define RESIZE_FACTOR 2

HashMap*  init_hashmap(bool mode, size_t n, size_t (*hash)(const char* str, size_t size)) {
  HashMap* map = (HashMap*) malloc(sizeof(HashMap));
  assert(map != NULL);
  if (mode) {
    Element* el = (Element*) calloc(n, sizeof(Element) * n);
    assert(el != NULL);
    map->capacity = n;
    map->occupied = 0;
    map->elements = el;
    map->head = NULL;
    map->tail = NULL;
    map->hash_func = hash;
    return map;
  }
  Element* el = (Element*) calloc(INITIAL_SIZE, sizeof(Element) * INITIAL_SIZE);
  assert(el != NULL);
  map->capacity = INITIAL_SIZE;
  map->occupied = 0;
  map->elements = el;
  map->head = NULL;
  map->tail = NULL;
  map->hash_func = hash;
  return map;
}

void hashmap_resize(HashMap* map, size_t size_k, size_t size_v) {
  assert(map->capacity != 0);
  map->elements = (Element*) realloc(map->elements, sizeof(Element) * (map->capacity * RESIZE_FACTOR));
  assert(map->elements != NULL);
  map->capacity *= RESIZE_FACTOR;
  for (Element* i = map->head; i != NULL; i = i->next) {
    hashmap_put(map, i->key, i->k_size, i->value, size_k * i->k_size, size_v);
    i->key = NULL;
  }
}

bool hashmap_put(HashMap* map, const void* key, size_t size, void* val, size_t size_k, size_t size_v) {
  if (map->capacity == map->occupied) hashmap_resize(map, size_k, size_v);
  size_t index = map->hash_func(key, size) % map->capacity;
  void* n_key = malloc(size_k);
  memcpy(n_key, key, size_k);
  void* n_val = malloc(size_v);
  memcpy(n_val, val, size_v);
  Element el = {.key = n_key, .k_size = size, .value = n_val, .next = NULL};

  if (map->elements[index].key != NULL) {
    if (map->elements[index].k_size == size && memcmp(map->elements[index].key, key, size) == 0) {
      return false;
    }
  }
  if (map->occupied == 0) {
    map->elements[index] = el;
    map->tail = &(map->elements[index]);
    map->head = &(map->elements[index]);
    map->occupied += 1;
    return true;
  }

  while (map->elements[index].key != NULL) {
    index++;
  }

  if (map->elements[index].key == NULL) {
    map->elements[index] = el;
    map->tail->next = &map->elements[index];
    map->tail = &map->elements[index];
    map->occupied += 1;
    return true;
  }
  printf("Cannot put the element\n");
  return false;
}

void* hashmap_get(HashMap* map, const void* key, size_t size) {
  assert(map->hash_func != NULL);
  size_t index = map->hash_func(key, size) % map->capacity;
  if (map->elements[index].key != NULL) {
    if (map->elements[index].k_size == size && memcmp(map->elements[index].key, key, size) == 0) {
      return map->elements[index].value;
    }
  }
  for (Element* i = map->head; i != NULL && i->key != NULL; i = i->next) {
    if (i->k_size == size && memcmp(i->key, key, size) == 0) {
      return i->value;
    }
  }
  printf("\nNot found\n");
  return NULL;
}

void hashmap_delete(HashMap* map, const void* key, size_t size)
{
  size_t index = map->hash_func(key, size) % map->capacity;
  if (memcmp(map->elements[index].key, key, size) == 0) {
    map->elements[index].key = NULL;
    return;
  }
  for (Element* i = &map->elements[index]; i != NULL && i->key != NULL; i = i->next) {
    if (memcmp(i->key, key, size) == 0) {
      i->key = NULL;
      return;
    }
  }
}

void deinit_hashmap(HashMap* map) {
  for (Element* i = map->head; i != NULL; i = i->next) {
    free((void*)i->key);
    free(i->value);
  }
  free(map->elements);
  free(map);
}

// ArrayList

ArrayList* init_array(size_t initial_size)		
{									
  void** arr = (void**)malloc(sizeof(void*)*initial_size);
  assert(arr != NULL);
  ArrayList* list = (ArrayList*) malloc(sizeof(ArrayList));		
  assert(list != NULL);
  list->array = arr;							
  list->capacity = initial_size;						
  list->occupied = 0;							
  return list;
}									

void array_push_back(ArrayList* list, void* data)	
{									
  if (list->occupied < list->capacity) {				
    list->array[list->occupied] = data;				
    list->occupied += 1;						
    return;								
  }									
  list->array = reallocarray(list->array, list->capacity+1, sizeof(data));	
  assert(new != NULL);
  list->array[list->occupied] = data;				
  list->occupied++;
  list->capacity++;
  return;								
}									

void array_insert_at_index(ArrayList* list, void* data, size_t index) 
{									
  if (list->occupied < list->capacity && index <= list->occupied) { 
    memcpy(list->array+index, list->array+index-1, sizeof(void*) * (list->capacity-index)+1); 
    list->array[index] = data;					
    list->occupied += 1;						
    return;								
  }else if (list->occupied == list->capacity && index <= list->occupied){ 
    list->array = (void**) reallocarray(list->array, list->capacity + 1, sizeof(data)); 
    memcpy(list->array+index, list->array+index-1, sizeof(void*) * (list->capacity-index)+1); 
    list->array[index] = data;					
    list->occupied += 1;						
    list->capacity += 1;						
    return;								
  }									
}									

void array_delete(ArrayList* list, size_t index)	
{									
  if (list->occupied <= list->capacity && index <= list->occupied) { 
    memcpy(list->array+index, list->array+index+1, sizeof(void*) * (list->capacity-index)); 
    list->occupied -= 1;						
    return;								
  }									
}									

void deinit_array(ArrayList* list)
{									
  free(list->array);							
  free(list);
}									

// Queue
Queue* init_queue(size_t n) {
  void** array = (void**) malloc(sizeof(void*) * n);
  Queue* queue = (Queue*) malloc(sizeof(Queue));
  queue->array = array;
  queue->capacity = n;
  queue->occupied = 0;
  queue->p_head = 0;
  return queue;
}

void queue_push(Queue* q, void* el) {
  if (q->occupied == q->capacity) {
    q->array = (void**)reallocarray(q->array, q->occupied+1, sizeof(void*));
    assert(q->array != NULL);
    q->array[q->occupied] = el;
    q->occupied++;
    q->capacity++;
    return;
  }
  q->array[q->occupied] = el;
  q->occupied++;
}

void* queue_pop(Queue* queue) {
  if (queue->occupied <= 0) return NULL;
  void* tmp = queue->array[queue->p_head]; 
  queue->p_head++;
  return tmp;
}

void* queue_peek(Queue* queue) {
  if (queue->occupied <= 0) return NULL;
  return queue->array[queue->occupied]; 
}

bool queue_empty(Queue* q) {
  if (q->p_head == q->occupied) return true;
  return false;
}

void deinit_queue(Queue* queue) {
  free(queue->array);
  free(queue);
}

// Priority Queue

Priority_Queue* init_p_queue(size_t initial_size, bool (*priority_function)(Priority_Queue* Q, void* a, void* b))		
{									
  void** arr = (void**)malloc(sizeof(void*)*initial_size);
  assert(arr != NULL);
  Priority_Queue* Q = (Priority_Queue*) malloc(sizeof(Priority_Queue));		
  assert(Q != NULL);
  Q->priority_function = priority_function;
  Q->array = arr;							
  Q->capacity = initial_size;						
  Q->occupied = 0;							
  return Q;
}									

void swap(Priority_Queue* Q, size_t a, size_t b)
{
  void* tmp = Q->array[a];
  Q->array[a] = Q->array[b];
  Q->array[b] = tmp;
}

void shift_up(Priority_Queue* Q, int index)
{
  int parent = floor((index-1)/2);
  while (index != 0 && Q->priority_function(Q, Q->array[parent], Q->array[index])) {
    swap(Q, parent, index);
    index = parent;
    parent = floor((index-1)/2);
  }
}

void shift_down(Priority_Queue* Q, int index)
{
  int a = (2*index)+1;
  int b = (2*index)+2;
  int max = index;
  while ((a < (int)Q->occupied && Q->priority_function(Q, Q->array[max], Q->array[a])) ||
	 (b < (int)Q->occupied && Q->priority_function(Q, Q->array[max], Q->array[b]))) {
    if (b >= (int)Q->occupied || !Q->priority_function(Q, Q->array[a], Q->array[b])) {
      swap(Q, a, max);
      max = a;
    } else {
      swap(Q, b, max);
      max = b;
    }
    a = (2*max)+1;
    b = (2*max)+2;
  }
}

void p_queue_push(Priority_Queue* Q, void* data)	
{
  if (Q->occupied < Q->capacity) {				
    Q->array[Q->occupied] = data;				
    shift_up(Q, Q->occupied);
    Q->occupied += 1;						
    return;								
  }									
  assert(new != NULL);
  Q->array = (void**)reallocarray(Q->array, Q->capacity*2, sizeof(data));
  Q->array[Q->occupied] = data;				
  shift_up(Q, Q->occupied);
  Q->occupied++;
  Q->capacity++;
  return;								
}	

void* p_queue_pop(Priority_Queue* Q)	
{
  if (Q->occupied == 0) return NULL;
  void* tmp = Q->array[0];
  swap(Q, 0, Q->occupied-1);
  Q->occupied--;
  shift_down(Q, 0);
  return tmp;								
}	

void deinit_p_queue(Priority_Queue* list)
{									
  free(list->array);							
  free(list);
}									

// Stack
Stack* init_stack(size_t n) {
  void** array = (void**) malloc(sizeof(void*) * n);
  Stack* stack = (Stack*) malloc(sizeof(Stack));
  stack->array = array;
  stack->capacity = n;
  stack->occupied = 0;
  return stack;
}

void stack_push(Stack* stack, void* el) {
  if (stack->occupied == stack->capacity) {
    stack->array = reallocarray(stack->array, stack->occupied+1, sizeof(void*));
    assert(stack->array != NULL);
    stack->array[stack->occupied] = el;
    stack->occupied++;
    stack->capacity++;
    return;
  }
  stack->array[stack->occupied] = el;
  stack->occupied++;
}

void* stack_pop(Stack* stack) {
  if (stack->occupied <= 0) return NULL;
  void* tmp = stack->array[stack->occupied-1]; 
  stack->occupied--;
  return tmp;
}

void* stack_peek(Stack* stack) {
  if (stack->occupied == 0) return NULL;
  return stack->array[stack->occupied]; 
}

bool stack_empty(Stack* stack) {
  if (stack->occupied == 0) return true;
  return false;
}

void deinit_stack(Stack* stack) {
  free(stack->array);
  free(stack);
}
