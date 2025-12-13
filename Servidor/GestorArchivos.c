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

        printf("Linea: %s\n", linea);

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

int EscribirArchivo(CLIENTE cliente, EQUIPO equipo, REPARACIONES reparaciones, int tipoDato)
{
    char archivo[100];
    int fdFile = 0;
    char buffer[1000] = "";
    
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

    fdFile = open(archivo, O_WRONLY | O_CREAT, 0644);

    if (fdFile == -1)
    {
        printf("Error al abrir archivo\n");
        return -1;
    }

    switch (tipoDato)
    {
        case 1:
            strcat(buffer, cliente.numero_de_orden);
            strcat(buffer, ",");
            strcat(buffer, cliente.fechaIngreso);
            strcat(buffer, ",");
            strcat(buffer, cliente.nombre);
            strcat(buffer, ",");
            strcat(buffer, cliente.apellido);
            strcat(buffer, ",");
            strcat(buffer, cliente.direccion);
            strcat(buffer, ",");
            strcat(buffer, cliente.telefono);
            strcat(buffer, "\n");
            break;
        case 2:
            strcat(buffer, equipo.numero_de_orden);
            strcat(buffer, ",");
            strcat(buffer, equipo.tipo);
            strcat(buffer, ",");
            strcat(buffer, equipo.marca);
            strcat(buffer, ",");
            strcat(buffer, equipo.modelo);
            strcat(buffer, ",");
            strcat(buffer, equipo.falla);
            strcat(buffer, "\n");
            break;
        case 3:
            strcat(buffer, reparaciones.numero_de_orden);
            strcat(buffer, ",");
            strcat(buffer, reparaciones.reparacionAEfectuar);
            strcat(buffer, ",");
            strcat(buffer, reparaciones.presupuesto);
            strcat(buffer, ",");
            strcat(buffer, reparaciones.confirmacion);
            strcat(buffer, ",");
            strcat(buffer, reparaciones.reparado);
            strcat(buffer, ",");
            strcat(buffer, reparaciones.fechaEgreso);
            strcat(buffer, "\n");
            break;
        
        default:
            return -1;
            break;
    }

    write(fdFile, buffer, strlen(buffer));

    return 0;
}

int CargarDato(NodoCliente **TOP_Clientes, NodoEquipo **TOP_Equipo, NodoReparaciones **TOP_Reparaciones, char *linea, int tipoDato)
{
    char campos[6][50];

    CLIENTE cliente;
    EQUIPO equipo;
    REPARACIONES reparacion;

    int cantidad = SepararPorComa(linea, campos);

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

            AgregarNodo_Cliente(&TOP_Clientes, cliente);

            break;

        case 2: //Carga Equipos

            equipo.numero_de_orden = atoi(campos[0]);
            strcpy(equipo.tipo, campos[1]);
            strcpy(equipo.marca, campos[2]);
            strcpy(equipo.modelo, campos[3]);
            strcpy(equipo.falla, campos[4]);

            AgregarNodo_Equipo(&TOP_Equipo, equipo);

            break;

        case 3: //Carga Reparaciones

            reparacion.numero_de_orden = atoi(campos[0]);
            strcpy(reparacion.reparacionAEfectuar, campos[1]);
            strcpy(reparacion.presupuesto, campos[2]);
            strcpy(reparacion.confirmacion, campos[3]);
            strcpy(reparacion.reparacionAEfectuar, campos[4]);
            strcpy(reparacion.fechaEgreso, campos[5]);

            AgregarNodo_Reparaciones(&TOP_Reparaciones, reparacion);
            
            break;
    
        default:
            return -2;
            break;
    }
    
    return 0;
}

int SepararPorComa(char *linea, char campos[][50])
{
    int i;
    int j = 0;
    int k = 0;

    for (i = 0; linea[i] != '\0'; i++)
    {
        if (linea[i] == ',')
        {
            campos[k][j] = '\0';
            k++;
            j = 0;
        }
        else
        {
            campos[k][j++] = linea[i];
        }
    }

    campos[k][j] = '\0';

    return k + 1; //Cantidad de campos encontrados
}

#endif