#ifndef PROVEEDOR
#define PROVEEDOR

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Exception.h"
#include "Vector.h"

#define NOMBRE_SIZE 15
#define DNS_SIZE 25
#define PUERTO_SIZE 65535

extern Vector * proveedores;

typedef struct Proveedor {
  char * nombre;
  char * dns;
  int puerto;
} Proveedor;

/**
 * Carga en un vector todos los proveedores contenidos en el archivos de 
 * proveedores dado.
 * @param archivoProveedores el nombre del archivo de pedidos a realizar por
 * un cliente.
 * @return nada.
 */
void cargarProveedores (char * archivoProveedores);

/**
 * Imprime un proveedor por la salida estandar.
 * @param proveedor un apuntador a un proveedor.
 * @return nada.
 */
void imprimirProveedor(Proveedor * proveedor);

/**
 * Imprime todos los proveedores contenidos en un arreglo de proveedores por la
 * salida estandar.
 * @param p un arreglo de proveedores.
 * @param t el tamano del arreglo de proveedores.
 * @return nada.
 */
void imprimirProveedores(Proveedor ** p, int t);

/**
 * Libera todo el espacio utilizado por un proveedor.
 *
 * @param p un apuntador a proveedor.
 * @return nada.
 */
void clearProveedor(Proveedor * p);

/**
 * Libera todo el espacio utilizado por el vector de proveedores.
 *
 * @param v un apuntador a vector.
 * @return nada.
 */
void clearProveedores(Vector * v);

#endif
