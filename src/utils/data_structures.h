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

// Hashmap definition and functions
HashMap*  init_hashmap(bool mode, size_t n, size_t (*hash)(const char* str, size_t size));
void hashmap_resize(HashMap* map);
bool hashmap_put(HashMap* map, const void* key, size_t size, void* val);
void* hashmap_get(HashMap* map, const void* key, size_t size);
void hashmap_delete(HashMap* map, const void* key, size_t size);
void deinit_hashmap(HashMap* map);

// ArrayList definition and functions

ArrayList* init_array(size_t initial_size);
void array_push_back(ArrayList* list, void* data);
void array_insert_at_index(ArrayList* list, void* data, size_t index);
void array_delete(ArrayList* list, size_t index);
void deinit_array(ArrayList* list);
#endif
