Sistema Cliente-Servidor con RPC
================================

Integrantes
-----------

* 08-10243 Roque Contreras
* 08-11044 Vicente Santacoloma

Descripción
-----------

La ferretería **LA CADENA** desea implementar un sistema de ayuda para la emisión de pedidos a sus proveedores. Este sistema debe asistir en la obtención del mejor precio posible para los artículos buscados.

Estructura
----------

Para la **Versión CP** y **Versión CL** se tiene como archivos comunes:

* **Proveedor.h:** Header del archivo **Proveedor.c**
* **Proveedor.c:** Contiene la estructura **Proveedor**
* **Pedido.h:** Header del archivo **Pedido.c**
* **Pedido.c:** Contiene la estructura **Pedido**
* **Inventario.h:** Header del archivo **Inventario.c**
* **Inventario.c:** Contiene la estructura **Inventario**
* **Vector.h:** Header del archivo **Vector.c**
* **Vector.c:** Contiene la estructura **Vector** que es un contenedor, donde sus elementos están ordenados en estricta secuencia lineal. Está implementado como arreglos dinámicos. Pueden manipular apuntadores a cualquier tipo básico o estructura. 
* **Exception.h:** Header del archivo Exception.c
* **Exception.c:** Contiene las excepciones generadas por un formato inválido en los diversos archivos de entrada.

Para la **Versión CP**:

* **LaCadena_client.c:** Programa cliente pesado que actúa como la ferretería **LA CADENA**.
* **LaCadena_server.c:** Programa servidor que actúa como un proveedor de la ferretería **LA CADENA**.

Para la **Versión CL**:

* **ordenes.c:** Programa cliente ligero que actúa como la ferretería **LA CADENA**. Se encarga solo de la interacción directa con el usuario, sin realizar mayor cómputo.
* **LaCadena_client.c:** Programa cliente/servidor que actúa como intermediario entre la ferreteria **LA CADENA** y el proveedor.
* **LaCadena_server.c:** Programa servidor que actúa como un proveedor de la ferretería **LA CADENA**.

Adicionalmente se tiene para ambas versiones los archivos **LaCadena_clnt.c**, **LaCadena_svc.c** y **LaCadena.h** que son generados por el **rpcgen** y **LaCadena.x** que es el parámetro de entrada del **rpcgen** y que contiene la especificación de las funciones a ser utilizadas como RPC.

Para mayor información acerca de las funciones de cada archivo junto con su descripción revisar los headers(.h).

Protocol de Aplicación
----------------------

* **Versión CP:**

	* Se utilizó RPC como mecanismo de comunicación.
	* Los pases de mensajes que contengan pedidos e inventarios se hacen a través de llamadas a procedimientos remotos del cliente pesado al servidor proveedor.
	* Una vez actualizado el inventario del servidor proveedor, éste es reportado por la salida estándar.

* **Versión CL:**

	* Se utilizó RPC y UDP como mecanismo de comunicación.
	* Los pases de mensajes que contengan pedidos e inventarios se hacen a través de llamadas a procedimientos remotos del intermediario al servidor proveedor. Entre el intermediario y el cliente ligero se realiza el intercambio mediante sockets utilizando el protocolo UDP.
	* Una vez actualizado el inventario del servidor proveedor, éste es reportado por la salida estándar.

Modelo Cliente
--------------

#### Versión CP 

El cliente pesado interactúa con todos los servidores proveedores de manera iterativa, es decir, uno por vez.

#### Versión CL

El cliente ligero interactúa con un único servidor intermediario y éste a su vez interactúa con todos los servidores proveedores de manera iterativa, es decir, uno por vez. Vale destacar que el intermediario es tanto cliente como servidor.

Modelo Servidor
---------------

#### Versión CP

* **Comunicación:**
  * **Orientada a conexiones:** se utiliza el protocolo TCP para la comunicación mediante RPC entre el cliente pesado y el servidor proveedor.

* **Concurrencia:**
  * **Iterativo:** El servidor proveedor solo interactúa con un cliente a la vez. Esta selección se basó en lo especificado en el enunciado del proyecto, donde se indica que solo hay un cliente interactuando con los proveedores simultaneamente.

* **Estado:**
  * **Servidor Sin Estado:** No se requiere almacenar las interacciones anteriores con cada cliente. Cada petición se realiza de forma independiente de acuerdo a la operación indicada.

#### Versión CL

* **Comunicacion:**
	* **Orientada a conexiones:** se utiliza el protocolo TCP para la comunicación mediante RPC entre el intermediario y el proveedor.
	* **No orientado a conexiones:** se utiliza el protocolo UDP para la comunicación entre el cliente ligero y el intermediario.

* **Concurrencia:**
  * **Iterativo:** El servidor solo interactúa con un intermediario a la vez y este a su vez interactúa con solo un cliente ligero. Esta selección se basó en lo especificado en el enunciado del proyecto, donde se indica que solo hay un cliente ligero interactuando con un único intermediario y solo un intermediario interactuando con los proveedores simultaneamente.

* **Estado:**
	* **Servidor Sin Estado:** No se requiere almacenar las interacciones anteriores con cada cliente. Cada petición se realiza de forma independiente de acuerdo a la operación indicada.
 
Instrucciones de Instalación
----------------------------

Para instalar el software primero debemos descomprimir el archivo en formato **.tar.gz** mediante:

```bash
tar -xvf Proyecto2.tar.gz
```

Para compilar el código de la **Versión CP** en OS basado en linux, deberemos posicionarnos en la carpeta **Proyecto2/Versión CP** y luego ejecutar el comando:

```bash
make
```

Luego se producirá dos ejecutables: **RPC-ordenes** y **RPC-proveedor** correspondientes al programa cliente y al programa proveedor respectivamente.

Para compilar el código de la **Versión CL** en OS basado en linux, deberemos 
posicionarnos en la carpeta **Proyecto2/Versión CL** y luego ejecutar el comando:

```bash
make
```

Luego se producirá tres ejecutables: **RPC-ordenes**, **RPC-inter** y **RPC-proveedor** correspondientes al programa cliente, intermediario y al proveedor respectivamente.

Para generar el talón del servidor y del cliente junto con los archivos **.c** del cliente y del servidor, junto con el **.h** con que deben cumplir ambos, se debe posicionar en la carpeta de cada versión y ejecutar:

```bash
rpcgen -C -a LaCadena.x
```
	
Ya estos archivos estan generados en las carpetas respectivas.

Instrucciones de Ejecución
--------------------------

Se debe tener ejecutando el demonio **rpcbind**. En caso de no tenerlo ejecutarlo mediante:

```bash
sudo rpcbind &
```

#### Versión CP 

El programa cliente se ejecuta mediante:

```bash
RPC-ordenes -f [archivo de pedidos] -d [archivo de proveedores]
```

donde:

* **-f** Indica que la siguiente entrada corresponde al archivo de pedidos.
* **-d** Indica que la siguiente entrada corresponde al archivo de proveedores.
* **[archivo de pedidos]** Ruta al archivo que contiene los pedidos.
* **[archivo de proveedores]** Ruta al archivo que contiene los proveedores.

El programa servidor se ejecuta mediante:

```bash
RPC-proveedor
```

#### Versión CL

El programa cliente se ejecuta mediante:

```bash
RPC-ordenes -f [archivo de pedidos] -m [maq inter]
```

donde:

* **-f** Indica que la siguiente entrada corresponde al archivo de pedidos.
* **-m** Indica que la siguiente entrada corresponde al archivo de intermediario.
* **[archivo de pedidos]** Ruta al archivo que contiene los pedidos.
* **[maq inter]** Ruta al archivo que contiene al intermediario.

El programa intermediario se ejecuta mediante:

```bash
RPC-inter -d [archivo de proveedores]
```

donde:

* **-d** Indica que la siguiente entrada corresponde al archivo de proveedores.
* **[archivo de proveedores]** Ruta al archivo que contiene los proveedores.

El programa servidor se ejecuta mediante:

```bash
RPC-proveedor
```

**Nota:** Es posible que se necesiten permisos de super usuario para ejecutar los binarios de ambas versiones.

Formato de Parámetros de Entrada
--------------------------------

#### ARCHIVO DE PEDIDOS

Cada línea del archivo tendrá el formato:

**[nombre producto] & [cantidad a solicitar]**

##### Limitaciones:
* **[nombre producto]** String no vacío de 30 caracteres como máximo.
* **[cantidad a solicitar]** Entero mayor a 0 de 10 dígitos como máximo.

#### ARCHIVO DE PROVEEDORES
Cada línea del archivo tendrá el formato:

**[nombre proveedor] & [direccion dns] & [puerto]**

##### Limitaciones:
* **[nombre proveedor]** String no vacío de 15 caracteres como máximo.
* **[direccion dns]** String no vacío de 25 caracteres como máximo.
* **[puerto]** Entero de 5 dígitos como máximo. Deberá ser menor a 65535 y no estar en uso.

#### ARCHIVO DE INVENTARIOS

Cada línea del archivo tendrá el formato:

**[nombre producto] & [cantidad disponible] & [precio unitario]**

##### Limitaciones:
* **[nombre producto]** String no vacío de 30 caracteres como máximo.
* **[cantidad disponible]** Entero mayor a 0 de 10 dígitos como máximo.
* **[precio unitario]** Float mayor a 0 de 10 dígitos como máximo.

Este archivo se incluirá como un *define* en el archivo **Inventario.h** de la forma:

**define INVENTARIO 'inventarios.txt'**, donde se deberá cambiar **'inventario.txt'** por el archivo de inventarios deseados.

#### MAQUINA INTERMEDIARIO

Tendrá una sola línea con el formato:

**[direccion dns] & [puerto]**

##### Limitaciones:
* **[direccion dns]** String no vacío de 25 caracteres como máximo.
* **[puerto]** Entero de 5 dígitos como máximo. Deberá ser menor a 65535 y no estar en uso.

Cualquier entrada que no se adapte a este formato tendrá un error por la salida estándar.

Estado Actual
-------------

100% Funcional.

Detalles Adicionales
--------------------

El código base para programar el cliente y el intermediario de la **Versión CL** utilizando sockets con UDP fue extraído de la página: [http://www.linuxhowtos.org/C_C++/socket.htm](http://www.linuxhowtos.org/C_C++/socket.htm)
