#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "Inventario.h"
#include "Proveedor.h"
#include "Pedido.h"

#define TRUE  1
#define FALSE 0

#define BUFFER_SIZE 10000

/*
 * Investigando en interner leimos que una cosa que se podria hacer para
 * "mejorar UPD" es mandar datagramas que no sean fragmentados porque 
 * podrian haber arquitecturas que no me manejaran fragmentacion. Por lo
 * que recomendaron un tamano maximo de 1440, esto se debe a los siguientes 
 * calculos:
 * El header de IP es >= 20 bytes, pero en la mayoria de los casos es de 20 
 * y el header de UDP es de 8 bytes. Por lo que no deja 1500 - 28 = 1472 bytes
 * para la data.
 */
#define MAX_SIZE_DATA_DATAGRAM 1472



/**
 * Carga los parametros entrada del programa cliente en las variables 
 * correspondientes.
 *
 * @param argc numero de argumentos recibidos 
 * @param argv arreglo de strings conteniendo los parametros de entrada del 
 * programa.
 * En la primera posición debe estar ordenes que es el nombre del programa.
 * @param archivoPedidos el string donde se guardara el nombre de archivo que 
 * contiene los pedidos a cargar.
 * @param archivoMaqInter el string donde se guardara el nombre de archivo 
 * que contiene los datos de la maquina intermediaria.
 * @return true si las opciones son correctas, falso en caso contrario.
 */
int cargarParametros(int argc, char *argv[], char ** archivoPedidos, 
                                char **archivoMaqInter) {

  int b [2] = {FALSE, FALSE};
  int k = 1;
  if(argc != 5)
    return FALSE;
  while(k < argc) {
    if(argv[k][0] == '-') {
      switch(argv[k][1]) {
        case 'm':
          if(b[1])
            return FALSE;
          b[1] = TRUE;
          ++k;          
          *archivoMaqInter= argv[k];
          break;
        case 'f':
          if(b[0])
            return FALSE;
          b[0] = TRUE;
          ++k;
          *archivoPedidos = argv[k];
          break;
        default:
          return FALSE;
      } 
    } else
        return FALSE;
    ++k;
  }
  return TRUE;
}

/**
 * Carga el puerto y dns de la maquina intermediaria que se encuentra contenido
 * en el archivo de maq_inter.
 * @param archivoMaq_inter el nombre del archivo de maq_inter.
 * @param puerto Apuntador a entero en donde se guarda el puerto leido del archivo.
 * @param puerto Apuntador a entero en donde se guarda el dns leido del archivo.
 * @return nada.
 */
void cargarMaq_inter(char * archivoMaq_inter, int *puerto, char **dns) {

  FILE *fp;

  if((fp = fopen(archivoMaq_inter,"r")) == NULL) {
    printf("Error");
    exit(1);
  }

  while(!feof(fp)) {
    
    *dns = (char *)malloc(DNS_SIZE*sizeof(char));
		if(dns==NULL){
			perror("malloc");
			exit(1);
		}
    fscanf(fp, "%1000[^&] & %d\n", *dns, puerto);
    null_string_exception("Algun dns", *dns);
    non_positive_integer_excetion("El puerto de la maq_inter", *dns, *puerto);
    (*dns)[strlen(*dns) - 1] = 0;
    null_string_exception("Algun dns", *dns);
    maximum_size_exception("El dns", *dns, DNS_SIZE);
    maximum_integer_exception("El puerto", *puerto, PUERTO_SIZE);
    //imprimirMaq_inter(maq_inter);
  }
}

/**
 * Imprime por la salida estandar el reporte correspondiente a la operacion 
 * basica o a la operacion avanzada segun sea el caso. Para este programa 
 * siempre va a realizar la operacion avanzada.
 *
 * @param reporte reporte a imprimir. 'b' corresponde al avanzado y 'a' al
 * avanzado.
 * @param inventariosProveedoresSolicitud vector que contiene los inventarios a
 * solicitar para cada proveedor.
 * @param inventariosProveedoresFaltantes vector que contiene los inventarios
 * faltantes que no pudieron ser satisfechos por los proveedores.
 * @return nada.
 */
void imprimirReporte(char reporte, Vector * inventariosProveedoresSolicitud, Vector * inventariosProveedoresFaltantes) {

  Vector * inventariosProveedorSolicitud;
  int sizeinventariosProveedoresSolicitud = size(inventariosProveedoresSolicitud);
  int sizePedidos = size(pedidos);
  int sizeInventariosProveedorSolicitud = 0;
  int sizeInventariosProveedoresFaltantes = size(inventariosProveedoresFaltantes);

  Pedido * pedido = NULL;
  Inventario * inventario = NULL;
  int Total = 0;
  int i = 0;
  int j = 0;
  int k = 0;

  printf("\n--------------------------------------------------------------------------------------------\n");
  if(reporte == 'a')
    printf("| PEDIDOS SOLICITADOS                                                                       |\n");
  else
  printf("| CONSULTA                                                                                  |\n");
  printf("---------------------------------------------------------------------------------------------\n");
  printf("| PRODUCTO                       | PROVEEDOR       | PRECIO     | CANTIDAD   | COSTO TOTAL  |\n");
  printf("---------------------------------------------------------------------------------------------\n");
  
  for(i = 0; i < sizePedidos; ++i) {
    pedido = (Pedido *)at(pedidos, i);
    for(j = 0; j < sizeinventariosProveedoresSolicitud; ++j) {
      inventariosProveedorSolicitud = (Vector *)at(inventariosProveedoresSolicitud, j);
      sizeInventariosProveedorSolicitud = size(inventariosProveedorSolicitud);
      for(k = 0; k < sizeInventariosProveedorSolicitud; ++k) {
        inventario = (Inventario *)at(inventariosProveedorSolicitud, k); 
        if((strcmp(pedido->producto, inventario->producto) == 0) && (inventario->cantidad > 0)) {
          printf("| %-30s | %-15s | %-10.2f | %-10d | %-12.2f |\n",
          inventario->producto, (inventario->proveedor)->nombre,
          inventario->precio, inventario->cantidad, 
          (inventario->precio)*(inventario->cantidad));
          Total += (inventario->precio)*(inventario->cantidad);
          break;
        }
      }
    }
  }
  printf("---------------------------------------------------------------------------------------------\n");
  printf("| TOTAL                                                                      | %-12d |\n",Total);
  printf("---------------------------------------------------------------------------------------------\n");
  printf("| PEDIDOS FALTANTES                           |\n");
  printf("-----------------------------------------------\n");
  printf("| PRODUCTO                       | CANTIDAD   |\n");
  printf("-----------------------------------------------\n");

  for(i = 0; i < sizeInventariosProveedoresFaltantes; ++i) {
    inventario = (Inventario *)at(inventariosProveedoresFaltantes, i);
    printf("| %-30s | %-10d |\n", inventario->producto, inventario->cantidad);
  }
  printf("-----------------------------------------------\n\n");

}

/**
 * Ejecucion principal del cliente que se encarga de estableces una comunicacion
 * UDP con el intermediario, donde inicialmente le manda los pedidos con las
 * respectivas cantidades asociadas a cada producto para que este haga su trabajo.
 * Finalmente recibe del intermediario la respuesta definitiva e imprime el reporte
 * de pedido de productos a los proveedores junto con los pedidos faltantes.
 * 
 * @param puerto puerto de la maquina intermediaria.
 * @param dns dns de la maquina intermediaria.
 * y puerto por la que esta va a escuchar.
 * @return nada.
 */
void cliente(int puerto, char *dns) {

  int sockfd;
  int i;
  struct sockaddr_in serv_addr;
  struct sockaddr_in their_addr;
  struct hostent *server;
  char resp;
  char buffer [BUFFER_SIZE];
  char solicitudesHechas[BUFFER_SIZE];
  char pedidosFaltantes[BUFFER_SIZE];
  int addr_len;
  char convert [33];
  int numbytes;
  int total_A_Recibir, acumulador;
  
  char *pedidosStringAux;
  
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0) perror("ERROR al abrir el socket");

  server = gethostbyname(dns);
  if (server == NULL) {
    fprintf(stderr,"ERROR, no se encontro el host\n");
    exit(0);
  }
    
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;

  bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, 
                  server->h_length);
  
  serv_addr.sin_port = htons(puerto);

//   addr_len = sizeof(struct sockaddr);
  //--------------------------ENVIO DE PEDIDOS---------------------------//
  printf("--------------------------ENVIO DE PEDIDOS---------------------------\n");
  sprintf(convert,"%zd", strlen(pedidosString));
  
  if ((numbytes=sendto(sockfd, convert, strlen(convert), 0,
		       (struct sockaddr *)&serv_addr, sizeof(struct sockaddr))) == -1) {
    perror("sendto");
    exit(1);
  }
  
  if ((numbytes=recvfrom(sockfd, &resp, sizeof(char), 0, 
			(struct sockaddr *)&their_addr, (socklen_t *)&addr_len)) == -1) {
    perror("recvfrom");
    exit(1);
  }
  if(resp!='0'){
    perror("ERROR EN ENVIAR TAMANO PEDIDOS\n");
    exit(1);
  }
  
  
  /**
   * Por la explicacion del primer comentario de este archivo (el de MAX_SISE_DATA_DATAGRAM)
   * debemos mandar datagramas con tamano de dato de 1472 bytes, por lo que se debe descomponer
   * el string de pedidos en varios pedazos para ser enviados a traves del socket, y eso se hace
   * a continuacion.
   */
  pedidosStringAux = (char *)malloc(strlen(pedidosString)+1);
	if(pedidosStringAux==NULL){
		perror("malloc");
		exit(1);
	}
  strcpy(pedidosStringAux, pedidosString);
  pedidosStringAux[strlen(pedidosStringAux)] = '\0';
  
  while(strlen(pedidosStringAux) > MAX_SIZE_DATA_DATAGRAM){
    char *pedidosRestantes;
    int tam_restante;
    
    tam_restante = strlen(pedidosStringAux) - MAX_SIZE_DATA_DATAGRAM+1;
    pedidosRestantes = (char *)malloc(tam_restante);
		if(pedidosRestantes==NULL){
			perror("malloc");
			exit(1);
		}
    
    strcpy(pedidosRestantes, &pedidosStringAux[MAX_SIZE_DATA_DATAGRAM]);
    pedidosRestantes[strlen(pedidosRestantes)] = '\0';
    pedidosStringAux[MAX_SIZE_DATA_DATAGRAM] = '\0';
    
    if ((numbytes=sendto(sockfd, pedidosStringAux, strlen(pedidosStringAux), 0,
			(struct sockaddr *)&serv_addr, sizeof(struct sockaddr))) == -1) {
      perror("sendto");
      exit(1);
    }
    
    ///Recibo de la respuesta de recibo.
    if ((numbytes=recvfrom(sockfd, &resp, sizeof(char), 0, 
			   (struct sockaddr *)&their_addr, (socklen_t *)&addr_len)) == -1) {
      perror("recvfrom");
      exit(1);
    }
    if(resp!='0'){
      perror("ERROR EN ENVIAR TAMANO PEDIDOS\n");
      exit(1);
    }
    ///
//     printf("MANDADO\n%s\n", pedidosStringAux);
    
    free(pedidosStringAux);
    
    pedidosStringAux = (char *) malloc(tam_restante);
		if(pedidosStringAux==NULL){
			perror("malloc");
			exit(1);
		}
    strcpy(pedidosStringAux, pedidosRestantes);
    
    free(pedidosRestantes); 
  }
  
  if ((numbytes=sendto(sockfd, pedidosStringAux, strlen(pedidosStringAux), 0,
			(struct sockaddr *)&serv_addr, sizeof(struct sockaddr))) == -1) {
    perror("sendto");
    exit(1);
  }
  
  ///Recibo de la respuesta de recibo.
  if ((numbytes=recvfrom(sockfd, &resp, sizeof(char), 0, 
			(struct sockaddr *)&their_addr, (socklen_t *)&addr_len)) == -1) {
    perror("recvfrom");
    exit(1);
  }
  if(resp!='0'){
    perror("ERROR EN ENVIAR TAMANO PEDIDOS\n");
    exit(1);
  }
  ///
  
  printf("Lo mandado en el socket es:\n%s\nDe tamano: %s\n", pedidosStringAux, convert);
  free(pedidosStringAux);
  /** Fin de Envio de datos (pedidos)*/
  
  bzero(buffer, BUFFER_SIZE);
  
  //---------------------RECEPCION DE SOLICITUDES HECHAS----------------------------------//
  printf("---------------------RECEPCION DE SOLICITUDES HECHAS----------------------------------\n");
  addr_len = sizeof(struct sockaddr);
  if ((numbytes=recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&their_addr, (socklen_t *)&addr_len)) == -1) {
    perror("recvfrom");
    exit(1);
  }
	
  ///Envio de respuesta de recepcion.
  if ((numbytes=sendto(sockfd, &resp, sizeof(char), 0,
			     (struct sockaddr *)&their_addr, sizeof(struct sockaddr))) == -1) {
    perror("sendto");
    exit(1);
  }
  ///
	
  total_A_Recibir = atoi(buffer);
  printf("El total a recibir es de: %d\n", total_A_Recibir);
		
		
  /**
   * El cliente solo va a mandar datagramas UDP con tamano de datos maximo de 1472 bytes,
   * por lo que si los pedidos superan ese tamano se mandaran varios datagramas.
   * El do-while de abajo se encarga de concatenar los datos de los UDP en la
   * variable solicitudesHechas para que despues sirva para crear el vector de solicitudesHechas
   */
  acumulador = 0;
  bzero(solicitudesHechas,BUFFER_SIZE);
  do {
    bzero(buffer,BUFFER_SIZE);

    if ((numbytes=recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&their_addr, (socklen_t *)&addr_len)) == -1) {
      perror("recvfrom");
      exit(1);
    }
		
    ///Envio de respuesta de recepcion.
    if ((numbytes=sendto(sockfd, &resp, sizeof(char), 0,
				    (struct sockaddr *)&their_addr, sizeof(struct sockaddr))) == -1) {
      perror("sendto");
      exit(1);
    }
    ///
		
// 		printf("%s\n\n",buffer);
    strcat(solicitudesHechas, buffer);
    acumulador += strlen(buffer); 
    printf("Recibido del buffer:\n%s\nAcumulador es de %d\n",solicitudesHechas, acumulador);
		  
  } while( acumulador < total_A_Recibir );
  // Aqui concluye la segunda comunicacion cliente-intermediario(recepcion de solicitudes hechas)
	
  bzero(buffer, BUFFER_SIZE);
  //-------------------------RECEPCION DE PEDIDOS FALTANTE----------------------------------------//
  printf("-------------------------RECEPCION DE PEDIDOS FALTANTE-------------------------------------\n");
  addr_len = sizeof(struct sockaddr);
  if ((numbytes=recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&their_addr, (socklen_t *)&addr_len)) == -1) {
    perror("recvfrom");
    exit(1);
  }
	
  ///Envio de respuesta de recepcion.
  if ((numbytes=sendto(sockfd, &resp, sizeof(char), 0,
			     (struct sockaddr *)&their_addr, sizeof(struct sockaddr))) == -1) {
    perror("sendto");
    exit(1);
  }
  ///
	
  total_A_Recibir = atoi(buffer);
  printf("El total a recibir es de: %d\n", total_A_Recibir);
		
		
  /**
   * El cliente solo va a mandar datagramas UDP con tamano de datos maximo de 1472 bytes,
   * por lo que si los pedidos superan ese tamano se mandaran varios datagramas.
   * El do-while de abajo se encarga de concatenar los datos de los UDP en la
   * variable pedidosFaltantes para que despues sirva para crear el vector de pedidosFaltantes
   */
  acumulador = 0;
  bzero(pedidosFaltantes,BUFFER_SIZE);
  do {
    bzero(buffer,BUFFER_SIZE);

    if ((numbytes=recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&their_addr, (socklen_t *)&addr_len)) == -1) {
      perror("recvfrom");
      exit(1);
    }
		
    ///Envio de respuesta de recepcion.
    if ((numbytes=sendto(sockfd, &resp, sizeof(char), 0,
				    (struct sockaddr *)&their_addr, sizeof(struct sockaddr))) == -1) {
      perror("sendto");
      exit(1);
    }
    ///
		  
// 		printf("%s\n\n",buffer);
    strcat(pedidosFaltantes, buffer);
    acumulador += strlen(buffer); 
    printf("Recibido del buffer:\n%s\nAcumulador es de %d\n",pedidosFaltantes, acumulador);	  
  }while( acumulador < total_A_Recibir );
  // Aqui concluye la tercera comunicacion cliente-intermediario (pedidos faltantes).
  
  
  close(sockfd);
  
  Vector * inventariosProveedoresSolicitud = NULL;
  Vector * inventariosProveedoresFaltantes = NULL;
  Vector * inventariosProveedorSolicitud = NULL;
  Inventario * inventario;
  Proveedor * p;

  create(&inventariosProveedoresSolicitud);
  create(&inventariosProveedoresFaltantes);

  if(strlen(solicitudesHechas) != 0) {
    create(&inventariosProveedorSolicitud);
  }

  char * proveedor = NULL;
  char * pch;
  pch = strtok(solicitudesHechas, "&");
  while(pch != NULL) {

    inventario = (Inventario *)malloc(sizeof(Inventario));
    inventario->producto = (char *)malloc(strlen(pch));
		if((inventario==NULL) || (inventario->producto==NULL)){
			perror("malloc");
			exit(1);
		}
    strcpy(inventario->producto, pch);
    pch = strtok (NULL, "&");
    p = (Proveedor *)malloc(sizeof(Proveedor));
    p->nombre = (char *)malloc(strlen(pch));
		if((p==NULL) || (p->nombre==NULL)){
			perror("malloc");
			exit(1);
		}
    strcpy(p->nombre, pch);
    inventario->proveedor = p;
    pch = strtok (NULL, "&");
    inventario->cantidad = atoi(pch);
    pch = strtok (NULL, "&");
    inventario->precio = atof(pch);
    pch = strtok (NULL, "&");

    if((pch != NULL)) {
      if(proveedor != NULL) {
        if((strcmp(proveedor, (inventario->proveedor)->nombre) != 0)) {
          push_back(&inventariosProveedoresSolicitud, inventariosProveedorSolicitud);
          create(&inventariosProveedorSolicitud);
        }
      }
    } else {
      push_back(&inventariosProveedoresSolicitud, inventariosProveedorSolicitud);
    }
    push_back(&inventariosProveedorSolicitud, inventario);
    proveedor = (inventario->proveedor)->nombre;
//   free(inventario->producto);
//   free((inventario->proveedor)->nombre);
//   free(inventario->proveedor);
//   free(inventario);
        
  }
  
  pch = strtok(pedidosFaltantes, "&");
  while(pch != NULL) {

    inventario = (Inventario *)malloc(sizeof(Inventario));
    inventario->producto = (char *)malloc(strlen(pch));
		if((inventario==NULL) || (inventario->producto==NULL)){
			perror("malloc");
			exit(1);
		}
    strcpy(inventario->producto, pch);
    pch = strtok (NULL, "&");
    inventario->cantidad = atoi(pch);
    pch = strtok (NULL, "&");
    push_back(&inventariosProveedoresFaltantes, inventario);    
  }

  imprimirReporte('a', inventariosProveedoresSolicitud, inventariosProveedoresFaltantes);
  
  for(i = 0; i < size(inventariosProveedoresSolicitud); ++i) {
    inventariosProveedorSolicitud = (Vector *)at(inventariosProveedoresSolicitud, i);
    clearInventarios(inventariosProveedorSolicitud);
  }
  free(inventariosProveedoresSolicitud->array);
  free(inventariosProveedoresSolicitud);
  
  clearInventarios(inventariosProveedoresFaltantes);
//   free(inventario->producto);
//   free((inventario->proveedor)->nombre);
//   free(inventario->proveedor);
//   free(inventario);
//   free(p->nombre);
//   free(p);
//   
//   free(pedidosStringAux);

  //FALTA LIBERAR EL ESPACIO USADO POR LOS VECTORES inventariosProveedoresSolicitud y inventariosProveedoresFaltantes
  
}


/**
 * Programa principal.
 *
 * @param argc numero de argumentos recibidos.
 * @param argv arreglo de strings conteniendo los parametros de entrada del 
 * programa.
 * En la primera posición debe estar ordenes que es el nombre del programa.
 * @return 0 si no hubieron errores durante la ejecucion del programa, 1 en 
 * caso contrario.
 */
int main(int argc, char *argv[]) {

  char * archivoPedidos; 
  char * archivoMaqInter;
  char *dns;
  int puerto;

  if(!cargarParametros(argc, argv, &archivoPedidos, &archivoMaqInter)) {
    printf("Formato de entrada invalido\n");
    exit(1);
  }

  create(&proveedores);
  create(&pedidos);
 
  cargarMaq_inter(archivoMaqInter, &puerto, &dns);
  cargarPedidos(archivoPedidos);
  
  //printf("%s & %d\n", dns, puerto);
  cliente(puerto, dns);
  
  clearPedidos(pedidos);
  clearProveedores(proveedores);
  free(dns);
  
  return 0;

}
