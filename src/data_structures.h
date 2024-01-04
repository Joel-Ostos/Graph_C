#ifndef _DATASTRUCTURES_H_
#define _DATASTRUCTURES_H_
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// TODO ***: Stack y Queue
// TODO **: Árboles rojinegros

/*
 Documentación:
 LinkedList: Las siguientes estructuras:
  typedef struct LinkedList_##type LinkedList_##type;			
  typedef struct Node_##type Node_##type;				
  struct Node_##type {							
    type data;								
    Node_##type* next;							
    Node_##type* prev;							
  };									
  struct LinkedList_##type {						
    Node_##type* head;							
    Node_##type* tail;							
    size_t size;							
  };									

 Están las siguientes funciones en forma de macro:
  static Node_##type* create_node_##type(type data)			
  LinkedList_##type init_list_##type()					
  void push_back_list_##type(LinkedList_##type* list, type data)	
  void delete_node_list_##type(LinkedList_##type* list, size_t index)	
  void deinit_list_##type(LinkedList_##type* list) 		       

 ArrayList: La siguiente estructura:
  typedef struct ArrayList_##type ArrayList_##type;			
  struct ArrayList_##type {						
    type* array;							
    size_t capacity;							
    size_t occupied;							
    bool state;								
  };									

 Están las siguientes funciones en forma de macro:
  ArrayList_##type init_array_##type(size_t initial_size)		
  ArrayList_##type set_array_##type(type* arr, size_t initial_size)	
  void insert_array_##type(ArrayList_##type* array, type data, size_t index) 
  void push_back_array_##type(ArrayList_##type* array, type data)	
  void delete_array_##type(ArrayList_##type* array, size_t index)	
  void deinit_array_##type(ArrayList_##type* array)			

  Linked List Functions (linkedlist macro)
  1. create_node_##type(type data)
  - Descripción: Crea un nuevo nodo para la lista enlazada.
  - Parámetros: data - el valor del nuevo nodo.
  - Valor de retorno: Retorna un puntero al nuevo nodo creado.

  2. init_list_##type()
  - Descripción: Inicializa una nueva lista enlazada vacía.
  - Valor de retorno: Retorna una nueva lista enlazada vacía.

  3. push_back_list_##type(LinkedList_##type* list, type data)
  - Descripción: Añade un nuevo nodo al final de la lista enlazada.
  - Parámetros: 
  - list - un puntero a la lista enlazada.
  - data - el valor del nuevo nodo.

  4. delete_node_list_##type(LinkedList_##type* list, size_t index)
  - Descripción: Elimina un nodo en una posición específica de la lista enlazada.
  - Parámetros: 
  - list - un puntero a la lista enlazada.
  - index - el índice del nodo a eliminar.

  5. deinit_list_##type(LinkedList_##type* list)
  - Descripción: Desinicializa una lista enlazada, liberando la memoria.
  - Parámetros: list - un puntero a la lista enlazada que se va a desinicializar.

  Array List Functions (arraylist macro)
  1. init_array_##type(size_t initial_size)
  - Descripción: Inicializa un nuevo array dinámico.
  - Parámetros: initial_size - el tamaño inicial del array.
  - Valor de retorno: Retorna un nuevo array dinámico.

  2. set_array_##type(type* arr, size_t initial_size)
  - Descripción: Establece un array dinámico a partir de un array existente.
  - Parámetros: 
  - arr - un puntero al array existente.
  - initial_size - el tamaño del array.

  3. insert_array_##type(ArrayList_##type* array, type data, size_t index)
  - Descripción: Inserta un elemento en una posición específica del array dinámico.
  - Parámetros: 
  - array - un puntero al array dinámico.
  - data - el elemento a insertar.
  - index - la posición donde se insertará el elemento.

  4. push_back_array_##type(ArrayList_##type* array, type data)
  - Descripción: Añade un elemento al final del array dinámico.
  - Parámetros: 
  - array - un puntero al array dinámico.
  - data - el elemento a añadir.

  5. delete_array_##type(ArrayList_##type* array, size_t index)
  - Descripción: Elimina un elemento de una posición específica del array dinámico.
  - Parámetros: 
  - array - un puntero al array dinámico.
  - index - la posición del elemento a eliminar.

  6. deinit_array_##type(ArrayList_##type* array)
  - Descripción: Desinicializa un array dinámico, liberando la memoria.
  - Parámetros: array - un puntero al array dinámico que se va a desinicializar.

  Extension Functions (extension macro)
  1.push_back_arraymatrix_##type(ArrayList_ArrayList_##type* array, ArrayList_##type* data, bool mode)
  - Descripción: Añade un array dinámico al final de un array de arrays dinámicos.
  - Parámetros: 
  - array - un puntero al array de arrays dinámicos.
  - data - un puntero al array dinámico a añadir.
  - mode - un booleano que indica el modo de operación.

 */

#define linkedlist(type)						\
  typedef struct LinkedList_##type LinkedList_##type;			\
  typedef struct Node_##type Node_##type;				\
  struct Node_##type {							\
    type data;								\
    Node_##type* next;							\
    Node_##type* prev;							\
  };									\
  struct LinkedList_##type {						\
    Node_##type* head;							\
    Node_##type* tail;							\
    size_t size;							\
  };									\
  static Node_##type* create_node_##type(type data)			\
  {									\
    Node_##type* node = (Node_##type*)malloc(sizeof(Node_##type));	\
    node->data = data;							\
    node->next = NULL;							\
    node->prev = NULL;							\
    return node;							\
  }									\
  LinkedList_##type init_list_##type()					\
  {									\
    return (LinkedList_##type){						\
      .head = NULL,							\
      .tail = NULL,							\
      .size = 0,							\
    };									\
  }									\
  void push_back_list_##type(LinkedList_##type* list, type data)	\
  {									\
    Node_##type* node = create_node_##type(data);			\
    if (!list->head) {							\
      list->head = node;						\
      list->tail = node;						\
      list->size++;							\
      return;								\
    }									\
    list->head->next = node;						\
    node->prev = list->head;						\
    list->head = node;							\
    list->size++;							\
  }									\
  void delete_node_list_##type(LinkedList_##type* list, size_t index)	\
  {									\
    size_t cont = 0;							\
    if (index != 0 && index <= list->size/2) {				\
      Node_##type* current = list->tail;				\
      while (current){							\
	if (cont == index){						\
	  current->prev->next = current->next;				\
	  current->next->prev = current->prev;				\
	  free(current);						\
	  return;							\
	}								\
	cont++;								\
	current = current->next;					\
      }									\
      return;								\
    } else if (index != list->size-1 && index > list->size/2) {		\
      Node_##type* current = list->head;				\
      cont = (list->size-1)-index;					\
      while (current){							\
	if (cont == index){						\
	  current->prev->next = current->next;				\
	  current->next->prev = current->prev;				\
	  free(current);						\
	  return;							\
	}								\
	cont++;								\
	current = current->prev;					\
      }									\
      return;								\
    } else if (index == 0){						\
      Node_##type* tmp = list->tail->next;				\
      free(list->tail);							\
      list->tail = tmp;							\
    }									\
    Node_##type* tmp = list->head->prev;				\
    free(list->tail);							\
    list->head = tmp;							\
  }									\
  void deinit_list_##type(LinkedList_##type* list)			\
  {									\
    Node_##type* current = list->tail;					\
    while (current) {							\
      Node_##type* tmp = current->next;					\
      free(current);							\
      current = tmp;							\
    }									\
  }									\
  
#define arraylist(type)							\
  typedef struct ArrayList_##type ArrayList_##type;			\
  struct ArrayList_##type {						\
    type* array;							\
    size_t capacity;							\
    size_t occupied;							\
    bool state;								\
  };									\
  void check_##type(type* ptr, size_t num)				\
  {									\
    if (!ptr){								\
      perror("Error -> ");						\
      exit(num);							\
    }									\
    return;								\
  }									\
  ArrayList_##type init_array_##type(size_t initial_size)		\
  {									\
    type* arr = (type*) malloc(sizeof(type)*initial_size);		\
    check_##type(arr,11);						\
    return (ArrayList_##type) {						\
      .array = arr,							\
      .capacity = initial_size,						\
      .occupied = 0,							\
      .state = true,							\
    };									\
  }									\
  ArrayList_##type set_array_##type(type* arr, size_t initial_size)	\
  {									\
    return (ArrayList_##type) {						\
      .array = arr,							\
      .capacity = initial_size,						\
      .occupied = initial_size,						\
      .state = false,							\
    };									\
  }									\
  void push_back_array_##type(ArrayList_##type* array, type data)	\
  {									\
    if (array->state) {							\
      if (array->occupied < array->capacity) {				\
	array->array[array->occupied] = data;				\
	array->occupied += 1;						\
	return;								\
      }									\
      type* new = (type*) malloc(sizeof(type) * (array->capacity+1));	\
      check_##type(new,2);						\
      array->array = memcpy(new, array->array, sizeof(type) * array->capacity); \
      array->array[array->occupied] = data;				\
      array->occupied += 1;						\
      array->capacity += 1;						\
      return;								\
    }									\
    if (array->occupied < array->capacity) {				\
      array->array[array->occupied] = data;				\
      array->occupied += 1;						\
      return;								\
    }									\
    type* new = (type*) malloc(sizeof(type) * (array->capacity+1));	\
    check_##type(new,3);						\
    array->array = memcpy(new, array->array, sizeof(type) * array->capacity); \
    array->array[array->occupied] = data;				\
    array->occupied += 1;						\
    array->capacity += 1;						\
    array->state = true;						\
    return;								\
  }									\
  void insert_array_##type(ArrayList_##type* array, type data, size_t index) \
  {									\
    if (array->occupied < array->capacity && index <= array->occupied) { \
      memcpy(array->array+index, array->array+index-1, sizeof(type) * (array->capacity-index)+1); \
      array->array[index] = data;					\
      array->occupied += 1;						\
      return;								\
    }else if (array->occupied == array->capacity && index <= array->occupied){ \
      array->array = (type*) realloc(array->array,(array->capacity + 1) * sizeof(type)); \
      memcpy(array->array+index, array->array+index-1, sizeof(type) * (array->capacity-index)+1); \
      array->array[index] = data;					\
      array->occupied += 1;						\
      array->capacity += 1;						\
      return;								\
    }									\
  }									\
  void delete_array_##type(ArrayList_##type* array, size_t index)	\
  {									\
    if (array->occupied <= array->capacity && index <= array->occupied) { \
      memcpy(array->array+index, array->array+index+1, sizeof(type) * (array->capacity-index)); \
      array->occupied -= 1;						\
      return;								\
    }									\
  }									\
  void deinit_array_##type(ArrayList_##type* array)			\
  {									\
    free(array->array);							\
    array->array = NULL;						\
  }									\

#define extension(type)							\
  void push_back_arraymatrix_##type(ArrayList_ArrayList_##type* array, ArrayList_##type* data, bool mode) \
  {									\
    if (mode) {								\
      if (array->state) {						\
	if (array->occupied < array->capacity) {			\
	  ArrayList_##type new = init_array_##type(data->occupied);	\
	  new.occupied = data->occupied;				\
	  memcpy(new.array, data->array, sizeof(type)*data->occupied ); \
	  array->array[array->occupied] = new;				\
	  array->occupied += 1;						\
	  return;							\
	}								\
	array->array = (ArrayList_##type*) realloc(array->array,(array->capacity + 1) * sizeof(ArrayList_##type)); \
	ArrayList_##type new = init_array_##type(data->occupied); \
	new.occupied = data->occupied;					\
	memcpy(new.array, data->array, sizeof(type)*data->occupied ); \
	array->array[array->occupied] = new;				\
	array->occupied += 1;						\
	array->capacity += 1;						\
	return;								\
      }									\
      if (array->occupied < array->capacity) {				\
	ArrayList_##type new = init_array_##type(data->occupied); \
	new.occupied = data->occupied;					\
	memcpy(new.array, data->array, sizeof(data->array[0])*data->occupied ); \
	array->array[array->occupied] = new;				\
	array->occupied += 1;						\
	return;								\
      }									\
      ArrayList_##type* anot = (ArrayList_##type*) malloc(sizeof(ArrayList_##type) * (array->capacity+1));	\
      array->array = memcpy(anot, array->array, sizeof(ArrayList_##type) * array->capacity); \
      ArrayList_##type new = init_array_##type(data->occupied);		\
      new.occupied = data->occupied;					\
      memcpy(new.array, data->array, sizeof(data->array[0])*data->occupied ); \
      array->array[array->occupied] = new;				\
      array->occupied += 1;						\
      array->capacity += 1;						\
      array->state = true;						\
      return;								\
    }									\
  }									\

#define queue(type)						\
  typedef struct Queue_##type Queue_##type;			\
  struct Queue_##type {						\
    type* array;						\
    size_t size;						\
    size_t occupied;						\
  };								\
  Queue_##type init_Queue_##type()				\
  {								\
    return (Queue_##type) {					\
      .array = NULL,						\
      .size = 0,						\
      .occupied = 0,						\
    };								\
  }								\
  void Queue_##type##_push(Queue_##type* st, type data)		\
  {								\
    if (st->size == 0){						\
      type* arr = (type*) malloc(sizeof(type)*1);		\
      st->array = arr;						\
      st->array[st->occupied] = data;				\
      st->size += 1;						\
      st->occupied += 1;					\
      return;							\
    }								\
    type* tmp = realloc(st->array, sizeof(type)*(st->size+1));	\
    st->array = tmp;						\
    st->array[st->occupied] = data;					\
    st->occupied+=1;						\
    st->size+=1;						\
  }									\
  type Queue_##type##_pop(Queue_##type* st)				\
  {									\
    type tmp = st->array[0];						\
    type* new = (type*)malloc(sizeof(type)*(st->size-1));		\
    memcpy(new, st->array+1, sizeof(type)*(st->size-1));		\
    free(st->array);							\
    st->array = new;							\
    st->occupied-=1;							\
    st->size-=1;							\
    return tmp;								\
  }									\
  bool Queue_##type##_empty(Queue_##type* st)				\
  {									\
    if (st->size == 0) {						\
      return true;							\
    }									\
    return false;							\
  }									\

#define stack(type)						\
  typedef struct Stack_##type Stack_##type;			\
  struct Stack_##type {						\
    type* array;						\
    size_t size;						\
    size_t occupied;						\
  };								\
  Stack_##type init_stack_##type()				\
  {								\
    return (Stack_##type) {					\
      .array = NULL,						\
      .size = 0,						\
      .occupied = 0,						\
    };								\
  }								\
  void push_stack_##type(Stack_##type* st, type data)		\
  {								\
    if (st->size == 0){						\
      type* arr = (type*) malloc(sizeof(type)*1);		\
      st->array = arr;						\
      st->array[st->occupied] = data;				\
      st->size += 1;						\
      st->occupied += 1;					\
      return;							\
    }								\
    type* tmp = realloc(st->array, sizeof(type)*(st->size+1));	\
    st->array = tmp;						\
    st->array[st->occupied] = data;				\
    st->occupied+=1;						\
    st->size+=1;						\
  }								\
  type pop_stack_##type(Stack_##type* st)			\
  {								\
    type tmp = st->array[(st->occupied)-1];			\
    st->occupied-=1;						\
    st->size-=1;						\
    return tmp;							\
  }								\
  void deinit_stack_##type(Stack_##type* st)			\
  {								\
    if (st) free(st);						\
    else printf("Invalid pointer");				\
  }								\
  bool empty_stack_##type(Stack_##type* st)			\
  {								\
    if (st->size == 0) {					\
      return true;						\
    }								\
    return false;						\
  }								\

#endif
// TODO on line 105: Design Decision, Bitacora TODO (1)
