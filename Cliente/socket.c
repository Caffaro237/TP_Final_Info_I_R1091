#include "Headers.h"

int conectar(char *hostname, int port, int debug)
{
	int sockfd;
	struct hostent *he;			   /* Se utiliza para convertir el nombre del host a su dirección IP */
	struct sockaddr_in their_addr; /* dirección del server donde se conectará */
	char ipstr[INET_ADDRSTRLEN];

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

	inet_ntop(AF_INET, &their_addr.sin_addr, ipstr, sizeof ipstr);

	if (debug)
	{
		printf("Conectando a %s\n", hostname);
		printf("IP %s:%d\t\t..........OK\n", ipstr, ntohs(their_addr.sin_port));
	}
	
	

	return sockfd;
}
