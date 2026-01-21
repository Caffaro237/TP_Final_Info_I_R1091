#include <stdio.h>
#include <string.h>
#include <stdlib.h> //Memoria dinámica
#include <fcntl.h> //Archivos
#include <unistd.h> //Archivos
#include <sys/types.h> //Archivos
#include <sys/stat.h> //Archivos//
#include <stdint.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>

    
#define PORT 7726  /* El puerto donde se conectará, servidor */
#define BACKLOG 2 /* Tamaño de la cola de conexiones recibidas */
#define SLEEP 200000 /* Sleep de 200 ms */


//Rutas de archivos a usar
#define ARCHIVO_CLIENTES "./Clientes.csv"
#define ARCHIVO_EQUIPOS "./Equipos.csv"
#define ARCHIVO_REPARACIONES "./Reparaciones.csv"


#define MAX_NUMERO_ORDEN 10

//Maxima cantidad de datos para la estructura Cliente
#define MAX_FECHA_INGRESO 50
#define MAX_NOMBRE 50
#define MAX_APELLIDO 50
#define MAX_DIRECCION 50
#define MAX_TELEFONO 50

//Maxima cantidad de datos para la estructura Equipo
#define MAX_TIPO 50
#define MAX_MODELO 50
#define MAX_MARCA 50
#define MAX_FALLA 200

//Maxima cantidad de datos para la estructura Reparacion
#define MAX_REPARACION 200
#define MAX_PRESUPUESTO 15
#define MAX_CONFIRMACION 5
#define MAX_REPARADO 5
#define MAX_FECHA_EGRESO 50


//Maxima cantidad de datos  para el copiado a las estructuras desde buffer
#define MAX_COLUMNAS 6
#define MAX_DATOS 300
#define MAX_DATOS_BUFFER 1000


//Listado de opciones menu
#define OPCION_LISTAR_CLIENTES 1
#define OPCION_ALTA_CLIENTE 2
#define OPCION_GENERAR_REPARACION 3
#define OPCION_MODIFICAR_CLIENTE 4
#define OPCION_MODIFICAR_EQUIPO 5
#define OPCION_BUSCAR_CLIENTE 6
#define OPCION_ENVIAR_WHATSAPP 7
#define OPCION_CERRAR_SERVIDOR -1


//Opciones de utilizacion de datos
#define OPCION_CLIENTES 1
#define OPCION_EQUIPOS 2
#define OPCION_REPARACIONES 3


//Opciones de modificacion de cliente
#define OPCION_FECHA_INGRESO 0
#define OPCION_NOMBRE 1
#define OPCION_APELLIDO 2
#define OPCION_DIRECCION 3
#define OPCION_TELEFONO 4


//Opciones de modificacion de equipo
#define OPCION_TIPO 0
#define OPCION_MARCA 1
#define OPCION_MODELO 2
#define OPCION_FALLA 3


#include "Estructuras.h"
#include "Prototipos.h"
