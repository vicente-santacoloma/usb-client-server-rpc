#include "Exception.h"

void maximum_size_exception(char * property, char * value, int size) {

  if(((int)strlen(value)) > size) {
    printf("%s %s excede el numero maximo de caracteres permitidos que es de %d\n", 
    property, value, size);
    exit(1);
  }

}

void maximum_integer_exception(char * property, int value, int size) {

  if(value > size) {
    printf("%s %d excede el numero maximo de caracteres o digitos permitidos que es de %d\n", 
    property, value, size);
    exit(1);
  }

}

void non_positive_integer_excetion(char * property, char * value1, int value2) {
  if(value2 <= 0) {
    printf("%s %s debe ser mayor a 0\n", 
    property, value1);
    exit(1);
  }
}

void non_positive_float_excetion(char * property, char * value1, float value2) {
  if(value2 <= 0) {
    printf("%s %s debe ser mayor a 0\n", 
    property, value1);
    exit(1);
  }
}

void null_string_exception(char * property, char * value) {
  if(strcmp(value, "") == 0) {
    printf("%s es nulo o vacio\n", property);
    exit(1);
  }
}


