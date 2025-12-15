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
#include <ctype.h>


#define SERVER "reparacionespcmaster.ddns.net"  /* Servidor al que se conectará*/
#define PORT 7726  /* El puerto donde se conectará, servidor */

#define MAX_FECHA_INGRESO 50
#define MAX_NOMBRE 50
#define MAX_APELLIDO 50
#define MAX_DIRECCION 50
#define MAX_TELEFONO 50

#define MAX_TIPO 50
#define MAX_MODELO 50
#define MAX_MARCA 50
#define MAX_FALLA 200

#define MAX_REPARACION 200
#define MAX_PRESUPUESTO 15
#define MAX_CONFIRMACION 5
#define MAX_REPARADO 5
#define MAX_FECHA_EGRESO 50


#include "Prototipos.h"
