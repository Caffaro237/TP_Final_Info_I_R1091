#include "Headers.h"


int abrir_conexion(int port, int backlog, int debug)
{
	int sockaux; /*socket auxiliar*/
	int aux;	 /*variable auxiliar*/
	struct sockaddr_in my_addr;

	/*Crea un socket y verifica si hubo algún error*/
	if ((sockaux = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		printf("Error en función socket(). Código de error %s\n", strerror(sockaux));
		return -1;
	}

	// reuso por timeout inmediato
	int optval = 1;
	if (setsockopt(sockaux, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
	{
		printf("Error en función setsockopt()\n");
		return -1;
	}

	/* Asignamos valores a la estructura my_addr */

	if (port == 0)
		port = PORT;

	my_addr.sin_family = AF_INET;		  /* familia de sockets INET para UNIX*/
	my_addr.sin_port = htons(port);		  /* convierte el entero formato PC a entero formato network*/
	my_addr.sin_addr.s_addr = INADDR_ANY; /* automaticamente usa la IP local */
	bzero(&(my_addr.sin_zero), 8);		  /* rellena con ceros el resto de la estructura */

	/* Con la estructura sockaddr_in completa, se declara en el Sistema que este proceso escuchará pedidos por la IP y el port definidos*/
	if ((aux = bind(sockaux, (struct sockaddr *)&my_addr, sizeof(struct sockaddr))) == -1)
	{
		printf("Error en función bind. Código de error %s\n", strerror(aux));
		return -1;
	}

	/* Habilitamos el socket para recibir conexiones, con una cola de conexiones en espera que tendrá como máximo el tamaño especificado en BACKLOG*/

	if (backlog == 0)
		backlog = BACKLOG;

	if ((aux = listen(sockaux, backlog)) == -1)
	{
		printf("Error en función listen. Código de error %s\n", strerror(aux));
		return -1;
	}

	if (debug)
	{
		printf("Se abrio la conexion correctamente\n");
		printf("Escuchando en el puerto %d\n", port);
	}


	return sockaux;
}


int aceptar_pedidos(int sockfd, int debug)
{
	int newfd;					   /* Por este socket duplicado del inicial se transaccionará*/
	struct sockaddr_in their_addr; /* Contendra la direccion IP y número de puerto del cliente */
	unsigned int sin_size = sizeof(struct sockaddr_in);

	/*Se espera por conexiones ,*/
	if ((newfd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1)
	{
		printf("Error en función accept. Código de error %s\n", strerror(newfd));
		return -1;
	}
	else
	{
		if (debug)
		{
			printf("Conexión desde: %s\n", inet_ntoa(their_addr.sin_addr));
		}

		return newfd;
	}
}
