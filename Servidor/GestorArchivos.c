#ifndef GESTOR_ARCHIVOS_H
#define GESTOR_ARCHIVOS_H

#include "Headers.h"

#define ARCHIVO_CLIENTES "./Clientes.csv"
#define ARCHIVO_EQUIPOS "./Equipos.csv"
#define ARCHIVO_REPARACIONES "./Reparaciones.csv"

int LeerArchivo(NodoCliente **TOP_Clientes, NodoEquipo **TOP_Equipo, NodoReparaciones **TOP_Reparaciones, int tipoDato)
{
    char *linea;
    int fdFile = 0;
    int retorno = 0;

    char archivo[100];

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

int EscribirNuevoCliente(CLIENTE cliente)
{
    char archivo[100];
    int fdFile = 0;
    char buffer[1000] = "";

    EQUIPO equipo;
    REPARACIONES reparaciones;

    
    strcpy(archivo, ARCHIVO_CLIENTES);

    fdFile = open(archivo, O_WRONLY | O_CREAT, 0644);

    if (fdFile == -1)
    {
        printf("Error al abrir archivo\n");
        return -1;
    }

    memset(buffer, 0, sizeof(buffer));

    if (UnirPorPuntoComa(cliente, equipo, reparaciones, 1, buffer, 1))
    {
        return -1;
    }

    write(fdFile, buffer, strlen(buffer));

    return 0;
}

int EscribirNuevoEquipo(EQUIPO equipo)
{
    char archivo[100];
    int fdFile = 0;
    char buffer[1000] = "";

    CLIENTE cliente;
    REPARACIONES reparaciones;
    
    strcpy(archivo, ARCHIVO_EQUIPOS);

    fdFile = open(archivo, O_WRONLY | O_CREAT, 0644);

    if (fdFile == -1)
    {
        printf("Error al abrir archivo\n");
        return -1;
    }

    memset(buffer, 0, sizeof(buffer));

    if (UnirPorPuntoComa(cliente, equipo, reparaciones, 2, buffer, 1))
    {
        return -1;
    }

    write(fdFile, buffer, strlen(buffer));

    return 0;
}

int EscribirNuevoReparacion(REPARACIONES reparaciones)
{
    char archivo[100];
    int fdFile = 0;
    char buffer[1000] = "";

    CLIENTE cliente;
    EQUIPO equipo;
    
    strcpy(archivo, ARCHIVO_REPARACIONES);

    fdFile = open(archivo, O_WRONLY | O_CREAT, 0644);

    if (fdFile == -1)
    {
        printf("Error al abrir archivo\n");
        return -1;
    }

    memset(buffer, 0, sizeof(buffer));

    if (UnirPorPuntoComa(cliente, equipo, reparaciones, 3, buffer, 1))
    {
        return -1;
    }

    write(fdFile, buffer, strlen(buffer));

    return 0;
}

int CargarDato(NodoCliente **TOP_Clientes, NodoEquipo **TOP_Equipo, NodoReparaciones **TOP_Reparaciones, char *linea, int tipoDato)
{
    char campos[6][200];

    CLIENTE cliente;
    EQUIPO equipo;
    REPARACIONES reparacion;

    int cantidad = SepararPorPuntoComa(linea, campos);

    if(cantidad == 0)
    {
        return -2;
    }   

    switch (tipoDato)
    {
        case 1: //Carga Clientes

            cliente.numero_de_orden = atoi(campos[0]);
            strcpy(cliente.fechaIngreso, campos[1]);
            strcpy(cliente.nombre, campos[2]);
            strcpy(cliente.apellido, campos[3]);
            strcpy(cliente.direccion, campos[4]);
            strcpy(cliente.telefono, campos[5]);

            AgregarNodo_Cliente(TOP_Clientes, cliente);

            break;

        case 2: //Carga Equipos

            equipo.numero_de_orden = atoi(campos[0]);
            strcpy(equipo.tipo, campos[1]);
            strcpy(equipo.marca, campos[2]);
            strcpy(equipo.modelo, campos[3]);
            strcpy(equipo.falla, campos[4]);

            AgregarNodo_Equipo(TOP_Equipo, equipo);

            break;

        case 3: //Carga Reparaciones

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
    char archivo[100];
    int fdFile = 0;
    char buffer[1000] = "";

    SeleccionarArchivo(archivo, tipoDato);

    fdFile = open(archivo, O_WRONLY | O_CREAT | O_TRUNC, 0644); // TRUNC = borra y reescribe

    if (fdFile == -1)
    {
        printf("Error al abrir archivo\n");
        return -1;
    }

    switch (tipoDato)
    {
        case 1:
            while(TOP_Clientes != NULL)
            {
                memset(buffer, 0, sizeof(buffer));

                if (UnirPorPuntoComa(TOP_Clientes->data, TOP_Equipo->data, TOP_Reparaciones->data, 1, buffer, 1))
                {
                    return -1;
                }
                
                write(fdFile, buffer, strlen(buffer));

                TOP_Clientes = TOP_Clientes->next;
            }

            break;
            
        case 2:
            while(TOP_Equipo != NULL)
            {
                memset(buffer, 0, sizeof(buffer));

                if (UnirPorPuntoComa(TOP_Clientes->data, TOP_Equipo->data, TOP_Reparaciones->data, 2, buffer, 1))
                {
                    return -1;
                }
                
                write(fdFile, buffer, strlen(buffer));

                TOP_Equipo = TOP_Equipo->next;
            }

            break;

        case 3:
            while(TOP_Reparaciones != NULL)
            {
                memset(buffer, 0, sizeof(buffer));

                if (UnirPorPuntoComa(TOP_Clientes->data, TOP_Equipo->data, TOP_Reparaciones->data, 3, buffer, 1))
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
        case 1:
            strcpy(archivo, ARCHIVO_CLIENTES);
            break;
            
        case 2:
            strcpy(archivo, ARCHIVO_EQUIPOS);
            break;

        case 3:
            strcpy(archivo, ARCHIVO_REPARACIONES);
            break;
        
        default:
            return -1;
            break;
    }

    return 0;
}

#endif