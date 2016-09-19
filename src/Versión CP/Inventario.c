#include "Inventario.h"

Vector * inventarios;

void cargarInventarios(char * archivoInventarios) {

  FILE *fp;

  if((fp = fopen(archivoInventarios,"r")) == NULL) {
    printf("Error");
    exit(1);
  }

  Inventario * inventario;
  char * producto;

  while(!feof(fp)) {
    
    inventario = (Inventario *)malloc(sizeof(Inventario));
    producto = (char *)malloc(PRODUCTO_SIZE*sizeof(char));
		if((producto == NULL) || (inventario==NULL)){
			perror("malloc");
			exit(1);
		}
    fscanf(fp, "%1000[^&] & %d & %f\n", producto, &(inventario->cantidad), &(inventario->precio));
    //null_string_exception("Algun producto del inventario", producto);
    producto[strlen(producto) - 1] = 0;
    null_string_exception("Algun producto del inventario", producto);
    maximum_size_exception("El producto", producto, PRODUCTO_SIZE);
    //non_positive_integer_excetion("La cantidad del", producto, inventario->cantidad);
    //non_positive_float_excetion("El precio del", producto, inventario->precio);
    inventario->producto = producto;
    inventario->proveedor = NULL;
    push_back(&inventarios, inventario);
  }

}

Vector * generarInventario(char * inventarioString, Proveedor * proveedor) {

  Vector * inventariosProveedor;
  create(&inventariosProveedor);

  Inventario * inventario;

  char * pch;
  pch = strtok(inventarioString, "&");
  while(pch != NULL) {
    inventario = (Inventario *)malloc(sizeof(Inventario));
    inventario->producto = (char *)malloc(strlen(pch));
		if((inventario == NULL) || (inventario->producto==NULL)){
			perror("malloc");
			exit(1);
		}    
		strcpy(inventario->producto, pch);
    inventario->proveedor = proveedor;
    pch = strtok(NULL, "&");
    inventario->cantidad = atoi(pch);
    pch = strtok(NULL, "&");
    inventario->precio = atof(pch);
    pch = strtok(NULL, "&");
    push_back(&inventariosProveedor, inventario);    
  }

  return inventariosProveedor;
}

Inventario * obtener_Inventario(char * producto) {
  int i;
  int sizeInventarios = size(inventarios);
  Inventario * inventario;
	for(i = 0; i < sizeInventarios; ++i) {
		inventario = (Inventario *)at(inventarios, i);
		if(strcmp(inventario->producto, producto) == 0)
			return inventario;
	}
	return NULL;
}

void actualizarInventario(char * inventarioString) {

  int i;
  int chequear = FALSE;
  int sizeInventarios = size(inventarios);
  Inventario * inventario;
  char * pch;

  pch = strtok(inventarioString, "&");
  while(pch != NULL) {
    for(i = 0; i < sizeInventarios; ++i) {
      inventario = (Inventario *)at(inventarios, i);
      if(strcmp(pch, inventario->producto) == 0) {
        pch = strtok(NULL, "&");
        inventario->cantidad -= atoi(pch);
        chequear = TRUE;
        break;
      } 
    }
    if(!chequear)
      pch = strtok(NULL, "&");
    else
      chequear = FALSE;
    pch = strtok(NULL, "&");
  }
}

void imprimirInventario(Inventario * inventario) {
  printf("%s %d %.2f\n",inventario->producto, inventario->cantidad, inventario->precio);
}

void imprimirInventarios(Inventario ** i, int t) {
  int k;
  for(k = 0; k < t; ++k) {
    imprimirInventario(i[k]);
  }
}

void clearInventario(Inventario * i) {
  free(i->producto);
  free(i->proveedor);
  free(i);
}

void clearInventarios(Vector * v) {

  int i;
  Inventario * inventario;
  int vectorSize = size(v);
  for(i = 0; i < vectorSize; ++i) {
    inventario = (Inventario *)at(v, i);
    clearInventario(inventario);
  }
  
  free((v)->array);
  free(v);
}

