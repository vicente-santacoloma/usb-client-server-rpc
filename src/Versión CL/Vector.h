#ifndef VECTOR
#define VECTOR

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef TRUE
#define TRUE  1
#endif
#ifndef FALSE
#define FALSE 0
#endif
#define MAX_SIZE 1073741823

typedef struct Vector {
  void ** array;
  int size;
  int capacity;
} Vector;

/**
 * Constructs a vector container object, initializing its contents.
 *
 * @param v a pointer to pointer to vector.
 * @return none.
 * @complexity constant.
 */
void create(Vector ** v);

/******************************** Exceptions *********************************/

/**
 * Prints a message to stdout and exits the process.
 * 
 * @param v a message.
 * @return none.
 * @complexity constant.
 */
void exception(const char *msg);

/****************************** Verifications ********************************/

/**
 * Throws a null_pointer_exception if the vector is null.
 *
 * @param v a pointer to a vector.
 * @complexity constant.
 * @return none.
 */
void verified_null_pointer_exception(Vector * v);

/**
 * Throws a no_memory_available_exception if no memory is available, or that 
 * some other error occurred which prevented memory being allocated.
 *
 * @param v a pointer to a vector.
 * @complexity constant.
 * @return none.
 */
void verified_no_memory_available_exception(Vector * v);

/********************************* Pointers **********************************/

/**
 * Returns a pointer referring to the first element in the vector container.
 *
 * @param v a pointer to a vector.
 * @return a pointer to the beginning of the sequence.
 * @complexity constant.
 */
void ** begin(Vector * v);

/**
 * Returns a pointer referring to the past-the-end element in the vector container.
 *
 * @param v a pointer to a vector.
 * @return a pointer to the element past the end of the sequence.
 * @complexity constant.
 */
void ** end(Vector * v);

/********************************* Capacity **********************************/ 

/**
 * Returns the number of elements in the vector container.
 *
 * @param v a pointer to a vector.
 * @return the number of elements that conform the vector's content.
 * @complexity constant.
 */
int size(Vector * v);

/**
 * Returns the maximum number of elements that the vector container can hold.
 *
 * @param v a pointer to a vector.
 * @return the maximum number of elements a vector object can have as its 
 * content.
 * @complexity constant.
 */
int max_size(Vector * v);

/**
 * Returns the size of the allocated storage space for the elements of the 
 * vector container.
 *
 * @param v a pointer to a vector.
 * @return the size of the currently allocated storage capacity in the 
 * vector, measured in the number elements it could hold.
 * @complexity constant.
 */
int capacity(Vector * v);

/**
 * Returns whether the vector container is empty, i.e. whether its size is 0.

 * @param v a pointer to a vector.
 * @return true if the vector size is 0, false otherwise.
 * @complexity constant.
 */
int empty(Vector * v);

/****************************** Element access *******************************/ 

/**
 * Returns a reference to the element at position n in the vector.
 *
 * @param v a pointer to a vector.
 * @param p a position in the vector.
 * @return the element at the specified position in the vector.
 * @complexity constant.
 */
void * at(Vector * v, int p);

/**
 * Returns a reference to the first element in the vector container.
 *
 * @param v a pointer to a vector.
 * @return a reference to the first element in the vector.
 * @complexity constant.
 */
void * front(Vector * v);

/**
 * Returns a reference to the last element in the vector container.
 *
 * @param v a pointer to a vector.
 * @return a reference to the last element in the vector.
 * @complexity constant.
 */
void * back(Vector * v);

/********************************* Modifiers *********************************/

/**
 * Adds a new element at the end of the vector, after its current last element. 
 * The content of this new element is initialized to a copy of e.
 *
 * @param v a pointer to pointer to vector.
 * @param e value to be copied to the new element.
 * @return none.
 * @complexity amortized time, reallocation may happen.
 */
void push_back(Vector ** v, void * e);

/**
 * Removes the last element in the vector, effectively reducing the vector size
 * by one and invalidating all iterators and references to it.
 *
 * @param v a pointer to pointer to vector.
 * @return none.
 * @complexity constant.
 */
void pop_back(Vector ** v);

/**
 * All the elements of the vector are dropped: then they are removed and destroyed 
 * from the vector container, leaving the container with a size of 0.
 *
 * @param v a pointer to a vector.
 * @return none
 * @complexity linear on size.
 */
void clear(Vector * v);

#endif
