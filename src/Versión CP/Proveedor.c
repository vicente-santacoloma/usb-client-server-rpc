#include "Proveedor.h"

Vector * proveedores;

void cargarProveedores(char * archivoProveedores) {

  FILE *fp;

  if((fp = fopen(archivoProveedores,"r")) == NULL) {
    printf("Error");
    exit(1);
  }

  Proveedor * proveedor;
  char * nombre;
  char * dns;

  while(!feof(fp)) {
    
    proveedor = (Proveedor *)malloc(sizeof(Proveedor));
    nombre = (char *)malloc(NOMBRE_SIZE*sizeof(char));
    dns = (char *)malloc(DNS_SIZE*sizeof(char));
		if((proveedor==NULL) || (nombre==NULL) || (dns==NULL)){
			perror("malloc");
			exit(1);
		}
    fscanf(fp, "%1000[^&] & %1000[^&] & %d\n", nombre, dns, &(proveedor->puerto));
    null_string_exception("Algun proveedor", nombre);
    null_string_exception("Algun dns", dns);
    non_positive_integer_excetion("El puerto del proveedor", nombre, proveedor->puerto);
    nombre[strlen(nombre) - 1] = 0;
    dns[strlen(dns) - 1] = 0;
    null_string_exception("Algun proveedor", nombre);
    null_string_exception("Algun dns", dns);
    maximum_size_exception("El proveedor", nombre, NOMBRE_SIZE);
    maximum_size_exception("El dns", dns, DNS_SIZE);
    maximum_integer_exception("El puerto", proveedor->puerto, PUERTO_SIZE);
    proveedor->nombre = nombre;
    proveedor->dns = dns;
    push_back(&proveedores, proveedor);
    //imprimirProveedor(proveedor);
  }

}

void imprimirProveedor(Proveedor * proveedor) {
  printf("%s %s %d\n", proveedor->nombre, proveedor->dns, proveedor->puerto);
}

void imprimirProveedores(Proveedor ** p, int t) {
  int k;
  for(k = 0; k < t; ++k) {
    imprimirProveedor(p[k]);
  }
}

void clearProveedor(Proveedor * p) {
  free((p)->nombre);
  free((p)->dns);
  free((p));
}

void clearProveedores(Vector * v) {

  int i;
  Proveedor * proveedor;
  int vectorSize = size(v);
  for(i = 0; i < vectorSize; ++i) {
    proveedor = (Proveedor *)at(v, i);
    clearProveedor(proveedor);
  }
  free(v->array);
  free(v);
}


