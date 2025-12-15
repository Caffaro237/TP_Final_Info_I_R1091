//Para compilacion desde terminal con gcc usar esta linea
//gcc ./Servidor/*.c -o ./Servidor/Server -Wall

//Para compilacion desde VS Code usar estos include
/*

#include "socket.c"
#include "GestorArchivos.c"
#include "GestorCliente.c"
#include "GestorEquipo.c"
#include "GestorReparacion.c"
#include "ManejoRemito.c"
#include "Funciones_principales.c"
#include "Signals.c"

*/

#include "Headers.h"
#include <pthread.h>

NodoCliente *TOP_Clientes = NULL;
NodoEquipo *TOP_Equipo = NULL;
NodoReparaciones *TOP_Reparaciones = NULL;
int cerrarServidor = 0;
int sock = -1;

typedef struct datosConexion
{
  int sock;
} connection_t;

void* work (void* ptr);

int main (void)
{
    connection_t* connection;
    pthread_t tid;

    int retorno = 0;

    retorno = inicializar(&TOP_Clientes, &TOP_Equipo, &TOP_Reparaciones);

    if(retorno < 0)
    {
        return retorno;
    }

    sock = abrir_conexion(PORT, BACKLOG, 1);

    while(!cerrarServidor)
    {
        connection = (connection_t*) malloc (sizeof(connection_t));
        
        if (!connection)
        {
            continue;
        }
        
        connection->sock = aceptar_pedidos(sock, 1);

        if (connection->sock < 0)
        {
            free(connection); //Libera memoria y no crea el thread
            continue;
        }
    
        if (pthread_create(&tid, 0, work, (void*)connection)!= 0)
        {
            close(connection->sock);
            free(connection);
            continue;
        }

        pthread_detach(tid);
    }

    if(cerrarServidor)
    {
        GuardarArchivoCompleto(TOP_Clientes, TOP_Equipo, TOP_Reparaciones, 1);
        GuardarArchivoCompleto(TOP_Clientes, TOP_Equipo, TOP_Reparaciones, 2);
        GuardarArchivoCompleto(TOP_Clientes, TOP_Equipo, TOP_Reparaciones, 3);
    }
    
    exit(0);
}

void* work (void* ptr)
{
    int existe_orden = 0;
    int sockdup;
    int32_t opcion = 0;
  
	connection_t* conn = (connection_t*) ptr;
    sockdup = conn -> sock;

    free(conn); //Libera el malloc hecho en el main

    while(!cerrarServidor)
    {
        read(sockdup, &opcion, sizeof(int32_t));
        
        switch(opcion) 
        {
            case 1:
                Listar_clientes (sockdup, TOP_Clientes, TOP_Equipo, TOP_Reparaciones);
                break;
                
            case 2:
                Alta_de_cliente (sockdup, &TOP_Clientes, &TOP_Equipo, &TOP_Reparaciones);
                break;
                
            case 3:
                existe_orden = Generar_reparacion (sockdup, TOP_Reparaciones);
                
                if(!existe_orden)
                {
                    GuardarArchivoCompleto(TOP_Clientes, TOP_Equipo, TOP_Reparaciones, 3);
                }

                break;

            case 4:
                existe_orden = Modificar_datos_de_cliente (sockdup, TOP_Clientes);
                
                if(!existe_orden)
                {
                    GuardarArchivoCompleto(TOP_Clientes, TOP_Equipo, TOP_Reparaciones, 1);
                }

                break;

            case 5:
                existe_orden = Modificar_datos_de_equipo (sockdup, TOP_Equipo);
                
                if(!existe_orden)
                {
                    GuardarArchivoCompleto(TOP_Clientes, TOP_Equipo, TOP_Reparaciones, 2);
                }

                break;
                
            case 6:
                Buscar_cliente (sockdup, TOP_Clientes, TOP_Equipo, TOP_Reparaciones);
                break;

            case 7:
                Buscar_Telefono_Cliente(sockdup, TOP_Clientes, TOP_Reparaciones);
                break;
                
            case -1:
                cerrarServidor = 1;
                close(sockdup);
                exit(0);
                break;

            default:
                break;
        }
    }

    return NULL;
}

int inicializar(NodoCliente **TOP_Clientes, NodoEquipo **TOP_Equipo, NodoReparaciones **TOP_Reparaciones)
{
    int retorno = 0;

    signal(SIGINT, SIG_IGN); // Apretar Ctrl+C no cierra el Server
    signal(SIGHUP, SIG_IGN); // Cerrar la terminal no cierra el Server
    signal(SIGPIPE, SIG_IGN); // Cerrar el Cliente cierra el Server
    signal(SIGTSTP, SalirCtrlZ); //Cierra el servidor y todos los threads

    retorno = LeerArchivo(TOP_Clientes, TOP_Equipo, TOP_Reparaciones, 1);

    if(retorno < 0)
    {
        return retorno;
    }

    retorno = LeerArchivo(TOP_Clientes, TOP_Equipo, TOP_Reparaciones, 2);

    if(retorno < 0)
    {
        return retorno;
    }

    retorno = LeerArchivo(TOP_Clientes, TOP_Equipo, TOP_Reparaciones, 3);

    if(retorno < 0)
    {
        return retorno;
    }

    printf("Archivos leidos y cargados con exito.\n\n");

    return retorno;
}

void SalirCtrlZ(int sig)
{
    (void)sig;
    char mensaje[50] = "Guardando archivos y cerrando servidor\n";
    
    system("clear");

    write(1, mensaje, strlen(mensaje));

    cerrarServidor = 1;
    close(sock);
}