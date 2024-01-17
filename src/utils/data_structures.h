#ifndef _DATA_STRUCTURES_H
#define _DATA_STRUCTURES_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct hashmap HashMap;
typedef struct element Element;
typedef struct arraylist ArrayList;
typedef struct queue Queue;
typedef struct stack Stack;
typedef struct priority_queue Priority_Queue;

struct hashmap {
  size_t capacity;
  size_t occupied;
  Element* elements;
  Element* head;
  Element* tail;
  size_t (*hash_func)(const char* str, size_t size);
};

struct element {
  const void* key;
  size_t k_size;
  void* value;
  Element* next;
  Element* parent;
};

struct arraylist {						
  void** array;							
  size_t capacity;							
  size_t occupied;							
};									

struct queue {
  void** array;
  int capacity;							
  int occupied;							
  int p_head;
};

struct priority_queue {
  void** array;							
  size_t capacity;							
  size_t occupied;							
  bool (*priority_function)(Priority_Queue* arr, void* a, void* b);
};

struct stack {
  void** array;
  int capacity;							
  int occupied;							
};

// Hashmap functions
HashMap*  init_hashmap(bool mode, size_t n, size_t (*hash)(const char* str, size_t size));
void hashmap_resize(HashMap* map, size_t size_k, size_t size_v);
bool hashmap_put(HashMap* map, const void* key, size_t size, void* val, size_t size_k, size_t size_v);
void* hashmap_get(HashMap* map, const void* key, size_t size);
void hashmap_delete(HashMap* map, const void* key, size_t size);
void deinit_hashmap(HashMap* map);

// ArrayList functions

ArrayList* init_array(size_t initial_size);
void array_push_back(ArrayList* list, void* data);
void array_insert_at_index(ArrayList* list, void* data, size_t index);
void array_delete(ArrayList* list, size_t index);
void deinit_array(ArrayList* list);

// Queue functions
Queue* init_queue(size_t n);
void queue_push(Queue* queue, void* el);
void* queue_pop(Queue* queue);
void* queue_peek(Queue* queue);
bool queue_empty(Queue* queue);
void deinit_queue(Queue* queue);

Priority_Queue* init_p_queue(size_t initial_size, bool (*priority_function)(Priority_Queue* Q, void* a, void* b));
void swap(Priority_Queue* Q, size_t a, size_t b);
void shift_up(Priority_Queue* Q, int index);
void shift_down(Priority_Queue* Q, int index);
void p_queue_push(Priority_Queue* Q, void* data);
void* p_queue_pop(Priority_Queue* Q);
void deinit_p_queue(Priority_Queue* list);

// Stack functions
Stack* init_stack(size_t n);
void stack_push(Stack* stack, void* el);
void* stack_pop(Stack* stack);
void* stack_peek(Stack* stack);
bool stack_empty(Stack* stack);
void deinit_stack(Stack* stack);


#endif
