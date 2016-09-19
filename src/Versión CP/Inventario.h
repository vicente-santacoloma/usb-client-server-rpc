#ifndef INVENTARIO
#define INVENTARIO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Exception.h"
#include "Proveedor.h"
#include "Vector.h"

#ifndef TRUE
#define TRUE  1
#endif
#ifndef FALSE
#define FALSE 0
#endif
#define PRODUCTO_SIZE 30
#define INVENTARIO "inventarios.txt"

extern Vector * inventarios;

typedef struct Inventario {
  char * producto;
  Proveedor * proveedor;
  int cantidad;
  float precio;
} Inventario;

/**
 * Carga en un vector todos los inventarios contenidos en el archivo de 
 * inventarios dado.
 * @param archivoInventarios el nombre del archivo de inventarios disponibles
 * de un servidor.
 * @return nada.
 */
void cargarInventarios (char * archivoInventarios);

/**
 * Carga en un vector todos los inventarios que me envia el servidor como
 * cadena de caracteres.
 * @param inventarioString la cadena de caracteres que contiene todos los 
 * inventarios.
 * @param proveedor el proveedor que me envia el inventario.
 * @return el vector que contiene todos los inventarios.
 */
Vector * generarInventario(char * inventarioString, Proveedor * proveedor);

/**
 * Busca el inventario asociado a un determinado producto.
 * @param producto un productor.
 * @return el inventario asociado al producto dado.
 */
Inventario *obtener_Inventario(char *producto);

/**
 * Actualiza el inventario del servidor con el pedido que me envia el cliente
 * como una cadena de caracteres.
 * @param inventarioString la cadena de caracteres que contiene el pedido
 * enviado por el cliente.
 * @return nada.
 */
void actualizarInventario(char * inventarioString);

/**
 * Imprime un inventario por la salida estandar.
 * @param inventario un apuntador a un inventario.
 * @return nada.
 */
void imprimirInventario(Inventario * inventario);

/**
 * Imprime todos los inventarios contenidos en un arreglo de inventarios por la
 * salida estandar.
 * @param i un arreglo de inventarios.
 * @param t el tamano del arreglo de inventarios.
 * @return nada.
 */
void imprimirInventarios(Inventario ** i, int t);

/**
 * Libera todo el espacio utilizado por un inventario.
 *
 * @param p un apuntador a inventario.
 * @return nada.
 */
void clearInventario(Inventario * i);

/**
 * Libera todo el espacio utilizado por el vector de inventarios.
 *
 * @param v un apuntador a vector.
 * @return nada.
 */
void clearInventarios(Vector * v);

#endif
