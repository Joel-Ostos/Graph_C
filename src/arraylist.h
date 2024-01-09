#ifndef _ARRAYLIST_H_
#define _ARRAYLIST_H_
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

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

#endif
