#include "Pedido.h"

Vector * pedidos;
char pedidosString [STRING_SIZE];

void cargarPedidos(char * archivoPedidos) {

  FILE *fp;

  if((fp = fopen(archivoPedidos, "r")) == NULL) {
    printf("Error");
    exit(1);
  }

  Pedido * pedido;
  char * producto;
  char convert [33];
  
  bzero(pedidosString, STRING_SIZE);

  while(!feof(fp)) {
    
    pedido = (Pedido *)malloc(sizeof(Pedido));
    producto = (char *)malloc(PRODUCTO_SIZE*sizeof(char));
    fscanf(fp, "%1000[^&] & %d\n", producto, &(pedido->cantidad));
		if((pedido==NULL) || (producto==NULL)){
			perror("malloc");
			exit(1);
		}
    producto[strlen(producto) - 1] = 0;
    null_string_exception("Algun producto del pedido", producto);
    maximum_size_exception("El producto", producto, PRODUCTO_SIZE);
    non_positive_integer_excetion("La cantidad del", producto, pedido->cantidad);
    pedido->producto = producto;
    strcat(pedidosString, pedido->producto);
    strcat(pedidosString, "&");
    sprintf(convert,"%d", pedido->cantidad);
    strcat(pedidosString, convert);
    strcat(pedidosString, "&");
    push_back(&pedidos, pedido);
    //imprimirPedido(pedido);
  }
}

Vector * generarPedido(char * pedidos) {

  Vector * pedidosCliente;
  create(&pedidosCliente);

  Pedido * pedido;
  
  strcpy(pedidosString,pedidos);
  pedidosString[strlen(pedidosString)]= '\0';
  
  char * pch;
  pch = strtok(pedidos, "&");
  while(pch != NULL) {
    pedido = (Pedido*)malloc(sizeof(Pedido));
    pedido->producto = (char *)malloc(strlen(pch));
		if((pedido==NULL) || (pedido->producto==NULL)){
			perror("malloc");
			exit(1);
		}
    strcpy(pedido->producto, pch);
    pch = strtok (NULL, "&");
    pedido->cantidad = atoi(pch);
    pch = strtok (NULL, "&");
    push_back(&pedidosCliente, pedido);    
  }

  return pedidosCliente;
}

void imprimirPedido(Pedido * pedido) {
  printf("%s %d\n", pedido->producto, pedido->cantidad);
}

void imprimirPedidos(Pedido ** p, int t) {
  int k;
  for(k = 0; k < t; ++k) {
    imprimirPedido(p[k]);
  }
}

void clearPedido(Pedido * p) {
  free(p->producto);
  free(p);
}

void clearPedidos(Vector * v) {

  int i;
  Pedido * pedido;
  int vectorSize = size(v);
  for(i = 0; i < vectorSize; ++i) {
    pedido = (Pedido *)at(v, i);
    clearPedido(pedido);
  }
  
  free((v)->array);
  free(v);
}
