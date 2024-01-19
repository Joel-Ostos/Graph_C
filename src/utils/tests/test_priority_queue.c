#include <stdio.h>
#include <stdlib.h>
#include "../data_structures.h"

bool compare(Priority_Queue* Q, void* a_, void* b_) 
{
  if (b_ == NULL) return false;
  int* a = (int*) a_;
  int* b = (int*) b_;
  if (*a > *b) return true;
  return false;
}

int main(void) 
{
  Priority_Queue* Q = init_p_queue(2, &compare);
  int a = 20;
  int* p_a = &a;
  int b = 80;
  int* p_b = &b;
  int c = 40;
  int* p_c = &c;
  int d = 30;
  int* p_d = &d;
  int e = 10;
  int* p_e = &e;
  int f = 2;
  int* p_f = &f;
  printf("{%d %d %d %d %d %d}\n",b,a,c,d,e,f);
  p_queue_push(Q, (void*) p_b);
  p_queue_push(Q, (void*) p_a);
  p_queue_push(Q, (void*) p_c);
  p_queue_push(Q, (void*) p_d);
  p_queue_push(Q, (void*) p_e);
  p_queue_push(Q, (void*) p_f);

  for (size_t i = 0; i < Q->occupied; i++) {
    printf("-> %d\n", *(int*)Q->array[i]);
  }
  for (void* i = p_queue_pop(Q); i != NULL; i = p_queue_pop(Q)) {
    printf("\nPop element: %d",*(int*)i);
  }
  if (p_queue_empty(Q)) {
    printf("Empty");
  }
}
