#ifndef GESTOR_ARCHIVOS_H
#define GESTOR_ARCHIVOS_H

#include "Headers.h"

int LeerArchivo(NodoCliente **TOP_Clientes, NodoEquipo **TOP_Equipo, NodoReparaciones **TOP_Reparaciones, int tipoDato)
{
    char *linea;
    int fdFile = 0;
    int retorno = 0;

    char archivo[MAX_DATOS] = "";

    SeleccionarArchivo(archivo, tipoDato);

    fdFile = open(archivo, O_RDONLY);

    if (fdFile == -1)
    {
        printf("Error al abrir archivo\n");
        return -1;
    }

    while(LeerLinea(fdFile, &linea))
    {
        retorno = CargarDato(TOP_Clientes, TOP_Equipo, TOP_Reparaciones, linea, tipoDato);

        if(retorno < 0)
        {
            return retorno;
        }

        free(linea);
    }

    return retorno;
}

int LeerLinea(int fd, char **linea)
{
    char lineaAux[MAX_DATOS_BUFFER] = "";
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

int EscribirNuevoCliente(CLIENTE cliente)
{
    char archivo[MAX_DATOS] = "";
    char buffer[MAX_DATOS_BUFFER] = "";
    int fdFile = 0;

    EQUIPO equipo = {0};
    REPARACIONES reparaciones = {0};

    
    strcpy(archivo, ARCHIVO_CLIENTES);

    fdFile = open(archivo, O_WRONLY | O_CREAT | O_APPEND, 0644);

    if (fdFile == -1)
    {
        printf("Error al abrir archivo\n");
        return -1;
    }

    memset(buffer, 0, sizeof(buffer));

    if (UnirPorPuntoComa(cliente, equipo, reparaciones, OPCION_CLIENTES, buffer))
    {
        return -1;
    }

    write(fdFile, buffer, strlen(buffer));

    return 0;
}

int EscribirNuevoEquipo(EQUIPO equipo)
{
    char archivo[MAX_DATOS] = "";
    char buffer[MAX_DATOS_BUFFER] = "";
    int fdFile = 0;

    CLIENTE cliente = {0};
    REPARACIONES reparaciones = {0};
    
    strcpy(archivo, ARCHIVO_EQUIPOS);

    fdFile = open(archivo, O_WRONLY | O_CREAT | O_APPEND, 0644);

    if (fdFile == -1)
    {
        printf("Error al abrir archivo\n");
        return -1;
    }

    memset(buffer, 0, sizeof(buffer));

    if (UnirPorPuntoComa(cliente, equipo, reparaciones, OPCION_EQUIPOS, buffer))
    {
        return -1;
    }

    write(fdFile, buffer, strlen(buffer));

    return 0;
}

int EscribirNuevoReparacion(REPARACIONES reparaciones)
{
    char archivo[MAX_DATOS] = "";
    char buffer[MAX_DATOS_BUFFER] = "";
    int fdFile = 0;

    CLIENTE cliente = {0};
    EQUIPO equipo = {0};
    
    strcpy(archivo, ARCHIVO_REPARACIONES);

    fdFile = open(archivo, O_WRONLY | O_CREAT | O_APPEND, 0644);

    if (fdFile == -1)
    {
        printf("Error al abrir archivo\n");
        return -1;
    }

    memset(buffer, 0, sizeof(buffer));

    if (UnirPorPuntoComa(cliente, equipo, reparaciones, OPCION_REPARACIONES, buffer))
    {
        return -1;
    }

    write(fdFile, buffer, strlen(buffer));

    return 0;
}

int CargarDato(NodoCliente **TOP_Clientes, NodoEquipo **TOP_Equipo, NodoReparaciones **TOP_Reparaciones, char *linea, int tipoDato)
{
    char campos[MAX_COLUMNAS][MAX_DATOS]= {0};

    CLIENTE cliente = {0};
    EQUIPO equipo = {0};
    REPARACIONES reparacion = {0};

    int cantidad = SepararPorPuntoComa(linea, campos);

    if(cantidad == 0)
    {
        return -2;
    }   

    switch (tipoDato)
    {
        case OPCION_CLIENTES:

            cliente.numero_de_orden = atoi(campos[0]);
            strcpy(cliente.fechaIngreso, campos[1]);
            strcpy(cliente.nombre, campos[2]);
            strcpy(cliente.apellido, campos[3]);
            strcpy(cliente.direccion, campos[4]);
            strcpy(cliente.telefono, campos[5]);

            AgregarNodo_Cliente(TOP_Clientes, cliente);

            break;

        case OPCION_EQUIPOS:

            equipo.numero_de_orden = atoi(campos[0]);
            strcpy(equipo.tipo, campos[1]);
            strcpy(equipo.marca, campos[2]);
            strcpy(equipo.modelo, campos[3]);
            strcpy(equipo.falla, campos[4]);

            AgregarNodo_Equipo(TOP_Equipo, equipo);

            break;

        case OPCION_REPARACIONES:

            reparacion.numero_de_orden = atoi(campos[0]);
            strcpy(reparacion.reparacionAEfectuar, campos[1]);
            strcpy(reparacion.presupuesto, campos[2]);
            strcpy(reparacion.confirmacion, campos[3]);
            strcpy(reparacion.reparado, campos[4]);
            strcpy(reparacion.fechaEgreso, campos[5]);

            AgregarNodo_Reparaciones(TOP_Reparaciones, reparacion);
            
            break;
    
        default:
            return -2;
            break;
    }
    
    return 0;
}

int GuardarArchivoCompleto(NodoCliente *TOP_Clientes, NodoEquipo *TOP_Equipo, NodoReparaciones *TOP_Reparaciones, int tipoDato)
{
    char archivo[MAX_DATOS] = "";
    char buffer[MAX_DATOS_BUFFER] = "";
    int fdFile = 0;

    SeleccionarArchivo(archivo, tipoDato);

    fdFile = open(archivo, O_WRONLY | O_CREAT | O_TRUNC, 0644); // TRUNC = borra y reescribe

    if (fdFile == -1)
    {
        printf("Error al abrir archivo\n");
        return -1;
    }

    switch (tipoDato)
    {
        case OPCION_CLIENTES:
            while(TOP_Clientes != NULL)
            {
                memset(buffer, 0, sizeof(buffer));

                if (UnirPorPuntoComa(TOP_Clientes->data, TOP_Equipo->data, TOP_Reparaciones->data, OPCION_CLIENTES, buffer))
                {
                    return -1;
                }
                
                write(fdFile, buffer, strlen(buffer));

                TOP_Clientes = TOP_Clientes->next;
            }

            break;
            
        case OPCION_EQUIPOS:
            while(TOP_Equipo != NULL)
            {
                memset(buffer, 0, sizeof(buffer));

                if (UnirPorPuntoComa(TOP_Clientes->data, TOP_Equipo->data, TOP_Reparaciones->data, OPCION_EQUIPOS, buffer))
                {
                    return -1;
                }
                
                write(fdFile, buffer, strlen(buffer));

                TOP_Equipo = TOP_Equipo->next;
            }

            break;

        case OPCION_REPARACIONES:
            while(TOP_Reparaciones != NULL)
            {
                memset(buffer, 0, sizeof(buffer));

                if (UnirPorPuntoComa(TOP_Clientes->data, TOP_Equipo->data, TOP_Reparaciones->data, OPCION_REPARACIONES, buffer))
                {
                    return -1;
                }
                
                write(fdFile, buffer, strlen(buffer));

                TOP_Reparaciones = TOP_Reparaciones->next;
            }

            break;
    
        default:
            return -1;
            break;
    }
    
    close(fdFile);
    return 1;
}

int SeleccionarArchivo(char *archivo, int tipoDato)
{
    switch (tipoDato)
    {
        case OPCION_CLIENTES:
            strcpy(archivo, ARCHIVO_CLIENTES);
            break;
            
        case OPCION_EQUIPOS:
            strcpy(archivo, ARCHIVO_EQUIPOS);
            break;

        case OPCION_REPARACIONES:
            strcpy(archivo, ARCHIVO_REPARACIONES);
            break;
        
        default:
            return -1;
            break;
    }

    return 0;
}

#endif