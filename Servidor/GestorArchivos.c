#include "Headers.h"

int readFile(char path[200])
{
    char *linea;
    int fdFile = 0;

    fdFile = open(path, O_RDONLY);

    if (fdFile == -1)
    {
        printf("Error al abrir archivo\n");
        exit(-1);
    }
    else
    {
        printf("Archivo abierto correctamente\n\n");
    }

    while(readline(fdFile, &linea))
    {
        printf("Linea: %s\n", linea);

        free(linea);
    }

    return 0;
}

int readline(int fd, char **linea)
{
    char lineaAux[2000] = "";
    char buffer = ' ';
    int contador = 0;
    int bytesLeidos = 1;

    while(bytesLeidos)
    {
        bytesLeidos = read(fd, &buffer, sizeof(char));

        if(buffer != '\r')
        {
            if(buffer == '\n')
            {
                break;
            }
            
            lineaAux[contador] = buffer;

            contador = contador + 1;
        }
    }
    
    *linea = (char *)malloc(strlen(lineaAux) + 1);

    strcpy(*linea, lineaAux);

    return bytesLeidos;
}

int writeFile(char path[200])
{
    return 0;
}