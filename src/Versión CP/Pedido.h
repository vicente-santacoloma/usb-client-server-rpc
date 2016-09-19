#ifndef PEDIDO
#define PEDIDO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Exception.h"
#include "Vector.h"

#define STRING_SIZE 10000
#define PRODUCTO_SIZE 30

extern Vector * pedidos;
extern char pedidosString [STRING_SIZE];

typedef struct Pedido {
  char * producto;
  int cantidad;
} Pedido;

/**
 * Carga en un vector todos los pedidos contenidos en el archivos de pedidos
 * dado.
 * @param archivoPedidos el nombre del archivo de pedidos a realizar por
 * un cliente.
 * @return nada.
 */
void cargarPedidos (char * archivoPedidos);

/**
 * Imprime un pedido por la salida estandar.
 * @param pedido un apuntador a un pedido.
 * @return nada.
 */
void imprimirPedido(Pedido * pedido);

/**
 * Imprime todos los pedidos contenidos en un arreglo de pedidos por la
 * salida estandar.
 * @param p un arreglo de pedidos.
 * @param t el tamano del arreglo de pedidos.
 * @return nada.
 */
void imprimirPedidos(Pedido ** p, int t);

/**
 * Libera todo el espacio utilizado por un pedido.
 *
 * @param p un apuntador a pedido.
 * @return nada.
 */
void clearPedido(Pedido * p);

/**
 * Libera todo el espacio utilizado por el vector de pedidos.
 *
 * @param v un apuntador a vector.
 * @return nada.
 */
void clearPedidos(Vector * v);

#endif
