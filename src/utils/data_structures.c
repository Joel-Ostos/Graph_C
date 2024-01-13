#include "data_structures.h"
#include <assert.h>
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

void hashmap_resize(HashMap* map) {
  if (map->capacity == 0) exit(1);
  map->elements = (Element*) realloc(map->elements, sizeof(Element) * (map->capacity * RESIZE_FACTOR));
  assert(map->elements != NULL);
  map->capacity *= RESIZE_FACTOR;
  for (Element* i = map->head; i != NULL; i = i->next) {
    hashmap_put(map, i->key, i->k_size, i->value);
    i->key = NULL;
  }
}

bool hashmap_put(HashMap* map, const void* key, size_t size, void* val) {
  size_t index = map->hash_func(key, size) % map->capacity;
  void* new_val = malloc (sizeof(void*));
  memcpy(new_val, val, sizeof(void*));
  Element el = {.key = key, .k_size = size, .value = new_val, .next = NULL};

  if (map->capacity == map->occupied) hashmap_resize(map);
  if (map->elements[index].key != NULL) {
    if (memcmp(map->elements[index].key, key, size) == 0) {
      return false;
    }
  }
  if (map->occupied == 0) {
    map->elements[index] = el;
    map->tail = &(map->elements[index]);
    map->head = &(map->elements[index]);
    map->occupied++;
    return true;
  }

  while (map->elements[index].key != NULL) {
    index++;
  }

  if (map->elements[index].key == NULL) {
    map->elements[index] = el;
    map->tail->next = &map->elements[index];
    map->tail = &map->elements[index];
    map->occupied++;
    return true;
  }
  printf("Cannot put the element\n");
  return false;
}

void* hashmap_get(HashMap* map, const void* key, size_t size) {
  size_t index = map->hash_func(key, size) % map->capacity;
  if (map->elements[index].key != NULL) {
    if (memcmp(map->elements[index].key, key, size) == 0) {
      return map->elements[index].value;
    }
  }
  for (Element* i = map->head; i != NULL && i->key != NULL; i = i->next) {
    if (memcmp(i->key, key, size) == 0) {
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
    free(i->value);
    free(i->key);
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
  void* new = reallocarray(list->array, list->capacity+1, sizeof(data));	
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
    list->array = (void*) reallocarray(list->array, list->capacity + 1, sizeof(data)); 
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
