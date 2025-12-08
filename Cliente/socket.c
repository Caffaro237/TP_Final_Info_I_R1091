/**
 * \file sock-lib.c
 * \brief contiene las funciones simplificadas de manejo de sockets para usar en Informática I
 * \author Alejandro Furfaro
 * \date 2018.09.10
 * \author Oscar Paniagua
 * \date 2022.12.12
 */

#include "socket.h"

/**
 * \fn int conectar (char *hostname, int port)
 * \brief Única función del lado cliente, que crea un socket y conecta a un server que le llega como argumento.
 * \details Se crea un socket y luego se invoca a la función connect para iniciar conexión con el nodo remoto en el
 * cual debe estar ejecutando un programa servidor escuchando conexiones por el mismo port al ue inicia la conexión.
 * El port si es 0 se utiliza el valor por default
 * \return Devuelve un entero con el file descriptor de socket
 * \author Alejandro Furfaro
 * \date 2018.09.10
 * \author Oscar Paniagua
 * \date 2022.12.12
 */
int conectar(char *hostname, int port, int debug)
{
	int sockfd;
	struct hostent *he;			   /* Se utiliza para convertir el nombre del host a su dirección IP */
	struct sockaddr_in their_addr; /* dirección del server donde se conectará */

	// convertimos el nombre del host a su dirección IP
	if ((he = gethostbyname(hostname)) == NULL)
	{
		herror("Error en Nombre de Host");
		exit(1);
	}

	/* Creamos el socket */
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("Error en creación de socket");
		exit(1);
	}
	if (debug)
		fprintf(stderr, "debug:: conectar() socket()=%d\t\t..........OK\n", sockfd);

	if (debug)
		fprintf(stderr, "debug:: conectar() dst port()=%d\t..........OK\n", port);

	port = (port == 0) ? htons(PORT) : htons(port);

	/* Establecemos their_addr con la direccion del server */
	their_addr.sin_family = AF_INET;
	their_addr.sin_port = port;
	their_addr.sin_addr = *((struct in_addr *)he->h_addr);
	bzero(&(their_addr.sin_zero), 8);

	/* Intentamos conectarnos con el servidor */
	if (connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1)
	{
		perror("conectar():: error tratando de conectar al server");
		exit(1);
	}
	if (debug)
		fprintf(stderr, "debug:: conectar() connect()\t\t..........OK\n");

	return sockfd;
}


