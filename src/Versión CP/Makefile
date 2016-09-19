CC=gcc
CFLAGS=-c -Wall

all: RPC-ordenes RPC-proveedor
RPC-ordenes: LaCadena_client.o LaCadena_clnt.o Inventario.o Proveedor.o Pedido.o Vector.o Exception.o
	$(CC) LaCadena_client.o LaCadena_clnt.o  Inventario.o Proveedor.o Pedido.o Vector.o Exception.o -o RPC-ordenes

RPC-proveedor: LaCadena_server.o LaCadena_svc.o Inventario.o Proveedor.o Pedido.o Vector.o Exception.o
	$(CC) LaCadena_server.o LaCadena_svc.o Inventario.o Proveedor.o Pedido.o Vector.o Exception.o -o RPC-proveedor

LaCadena_client.o: LaCadena_client.c 
	$(CC) $(CFLAGS) LaCadena_client.c

LaCadena_server.o: LaCadena_server.c 
	$(CC) $(CFLAGS) LaCadena_server.c

LaCadena_clnt.o: LaCadena_clnt.c
	$(CC) $(CFLAGS) LaCadena_clnt.c

LaCadena_svn.o: LaCadena_svn.c
	$(CC) $(CFLAGS) LaCadena_svn.c

Proveedor.o: Proveedor.h Proveedor.c
	$(CC) $(CFLAGS) Proveedor.c

Pedido.o: Pedido.h Pedido.c
	$(CC) $(CFLAGS) Pedido.c

Inventario.o: Inventario.h Inventario.c
	$(CC) $(CFLAGS) Inventario.c

Vector.o: Vector.h Vector.c
	$(CC) $(CFLAGS) Vector.c

Exception.o: Exception.h Exception.c
	$(CC) $(CFLAGS) Exception.c

clean:
	rm -f *.o RPC-ordenes RPC-proveedor
