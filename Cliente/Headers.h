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


#define SERVER "localhost"  /* Servidor al que se conectará*/
#define PORT 7726  /* El puerto donde se conectará, servidor */

#define MAX_FECHA_INGRESO 11
#define MAX_NOMBRE 15
#define MAX_APELLIDO 15
#define MAX_DIRECCION 50
#define MAX_TELEFONO 11

#define MAX_TIPO 15
#define MAX_MODELO 15
#define MAX_MARCA 20
#define MAX_FALLA 100

#define MAX_REPARACION 100
#define MAX_PRESUPUESTO 15
#define MAX_CONFIRMACION 5
#define MAX_REPARADO 5
#define MAX_FECHA_EGRESO 11


#include "Prototipos.h"
