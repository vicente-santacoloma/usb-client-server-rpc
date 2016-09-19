#include "Vector.h"

/******************************* Constructor *********************************/

void create(Vector ** v) {
  (*v) = (Vector *)malloc(sizeof(Vector));
  verified_no_memory_available_exception(*v);
  (*v)->array = NULL;
  (*v)->size = 0;
  (*v)->capacity = 0;
}

/******************************** Exceptions *********************************/

void exception(const char *msg) {
  printf("%s\n",msg);
  exit(1);
}

/****************************** Verifications ********************************/

void verified_null_pointer_exception(Vector * v) {
  if(v == NULL)
    exception("null_pointer_exception");
}

void verified_no_memory_available_exception(Vector * v) {
  if(v == NULL)
    exception("no_memory_available_exception");
}

/********************************* Pointers **********************************/

void ** begin(Vector * v) {
  verified_null_pointer_exception(v);
  return v->array;
}

void ** end(Vector * v) {
  verified_null_pointer_exception(v);
  return v->array + v->size - 1;
}

/********************************* Capacity **********************************/

int size(Vector * v) {
  verified_null_pointer_exception(v);
  return v->size;
}

int max_size(Vector * v) {
  verified_null_pointer_exception(v);
  return MAX_SIZE;
}

int capacity(Vector * v) {
  verified_null_pointer_exception(v);
  return v->capacity;
}

int empty(Vector * v) {
  verified_null_pointer_exception(v);
  if(v->size == 0)
    return TRUE;
  else
    return FALSE;
}

/****************************** Element access *******************************/

void * at(Vector * v, int p) {
  verified_null_pointer_exception(v);
  if(0 <= p && p < v->size)
    return v->array[p];
  exception("out_of_range_exception");
  return NULL;
}

void * front(Vector * v) {
  verified_null_pointer_exception(v);
  return v->array[0];
}

void * back(Vector * v) {
  verified_null_pointer_exception(v);
  return v->array[v->size - 1];
}

/********************************* Modifiers *********************************/

void push_back(Vector ** v, void * e) {
  
  verified_null_pointer_exception(*v);
  int old_capacity = (*v)->capacity;
  if((*v)->size == (*v)->capacity) {
    if((*v)->capacity == 0)
      (*v)->capacity = 1;
    else
      (*v)->capacity *= 2;
    if((*v)->capacity > MAX_SIZE)
      exception("max_size_capacity_exceeded _exception");
    void ** new_array = (void **)malloc(((*v)->capacity)*sizeof(void *));
    if(new_array == NULL)
      exception("no_memory_available_exception");
    memcpy(new_array, (*v)->array, old_capacity*sizeof(void *));
    free((*v)->array);
    (*v)->array = new_array;
  }
  ++(*v)->size;
  ((*v)->array)[(*v)->size - 1] = e;

}

void pop_back(Vector ** v) {
  verified_null_pointer_exception(*v);
  //free(((*v)->array)[(*v)->size - 1]);
  --(*v)->size;
}

void clear(Vector * v) {
  verified_null_pointer_exception(v);
  int i;
  int vectorSize = v->size;
  for(i = 0; i < vectorSize; ++i) {
    free(at(v,i));
  }
  free(v->array);
  free(v);
}

/*********************************** Main ************************************/

/*
int main() {

  Vector * v = NULL;
  create(&v);
  int * e;

  int i;
  for(i = 0; i < 700; ++i) {
    e = (int *)malloc(sizeof(int));
    *e = i;
    push_back(&v, e);
    printf("size: %d\n", size(v));
    printf("capacity: %d\n", capacity(v));
    printf("------------------------------");
  }

  printf("size: %d\n", size(v));
  printf("capacity: %d\n", capacity(v));

  printf("\n\n\n");

  printf("i0: %d\n",  *(int*)at(v,0));
  printf("i50: %d\n", *(int*)front(v));
  printf("i99: %d\n", *(int*)back(v));   
  int ** a = (int **)end(v);
  printf("%d\n", *(a[0])); 

  return 0;
}

*/

