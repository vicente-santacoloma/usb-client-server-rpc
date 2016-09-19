#ifndef EXCEPTION
#define EXCEPTION

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Print a message to stdout and exits the process if the string value to check
 * is greater than the size.
 * 
 * @param property the name of a property.
 * @param value the value to check.
 * @param size the max integer to check.
 * @return none.
 */
void maximum_size_exception(char * property, char * value, int size);

/**
 * Print a message to stdout and exits the process if the int value to check is
 * greater than the size.
 * 
 * @param property the name of a property.
 * @param value the value to check.
 * @param size the max integer to check.
 * @return none.
 */
void maximum_integer_exception(char * property, int value, int size);

/**
 * Print a message to stdout and exits the process if the value to check is a
 * int non positive.
 * 
 * @param property the name of a property.
 * @param value1 the value asociated to the value to check.
 * @param value2 the value to check.
 * @return none.
 */
void non_positive_integer_excetion(char * property, char * value1, int value2);

/**
 * Print a message to stdout and exits the process if the value to check is a
 * float non positive.
 * 
 * @param property the name of a property.
 * @param value1 the value asociated to the value to check.
 * @param value2 the value to check.
 * @return none.
 */
void non_positive_float_excetion(char * property, char * value1, float value2);

/**
 * Print a message to stdout and exits the process if the string value is the
 * empty string.
 * 
 * @param property the name of a property.
 * @param value1 the value asociated to the value to check.
 * @param value2 the value to check.
 * @return none.
 */
void null_string_exception(char * property, char * value);

#endif
