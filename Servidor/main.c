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

*/

#include "Headers.h"

int main (void)
{
    int retorno = 0;
    NodoCliente *TOP_Clientes = NULL;
    NodoEquipo *TOP_Equipo = NULL;
    NodoReparaciones *TOP_Reparaciones = NULL;
  
    int sock;
	int sockdup;

    int32_t opcion = 0;
    char seguir = 's';

    retorno = inicializar(&TOP_Clientes, &TOP_Equipo, &TOP_Reparaciones);

    if(retorno < 0)
    {
        return retorno;
        
    }

	sock = abrir_conexion(PORT, BACKLOG, 1);
    sockdup = aceptar_pedidos(sock, 1);

    while(seguir != 'n')
    {
        read(sockdup, &opcion, sizeof(int32_t));

        switch(opcion) 
        {
            case 2:
                Opcion_2 (sock, sockdup, &TOP_Clientes, &TOP_Equipo, &TOP_Reparaciones);
                break;
                
            case 4:
                Opcion_4 (sock, sockdup, TOP_Clientes);
                break;

            case 5:
                Opcion_5 (sock, sockdup, TOP_Equipo);
                break;
                
            case 6:
                Opcion_6 (sock, sockdup, TOP_Clientes, TOP_Equipo, TOP_Reparaciones);
                break;
            

            
            case 7:
                close(sockdup);
                sockdup = aceptar_pedidos(sock, 1);
                break;

            case -1:
                seguir = 'n';
                close(sockdup);
                break;

            default:
                break;
        }
    }

    close (sock);

    return retorno;
}


int inicializar(NodoCliente **TOP_Clientes, NodoEquipo **TOP_Equipo, NodoReparaciones **TOP_Reparaciones)
{
    int retorno = 0;

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

    return retorno;
}

/*

TOP = Estructura1
TOPSiguiente = Estructura2
TOPSiguiente->Siguiente = NULL


FN AgregarNodo(TOP, Struct)
    Agrega un nodo a lo ultimo
    Desplazando el NULL uno mas adelante


FN Alta_Datos(Datos_sueltos)
    Usas TOP Creado
    No va a existir Numero de Orden 
    Lees la lista, obtenes el ultimo nodo, sacas el numero de orden y le sumas 1
    Creas una struct con esos datos 
    FN AgregarNodo(TOP, Struct)

*/

/*

El servidor siempre va a estar clavado en un read esperando a saber que se va a realizar

printf("1 - Listar clientes\n");
printf("2 - Alta de cliente\n");
printf("3 - Generar Reparacion\n");
printf("4 - Modificar datos de cliente\n");
printf("5 - Modificar datos de equipo\n");
printf("6 - Buscar cliente\n");

2
Servidor Detecta Alta de cliente
Verifica ultimo numero de orden viendo la lista, si no existe ninguno empezar desde 1000, si existe suma uno y guardarlo en una variable
Se pone en modo read de datos de cliente - Una vez recibido, creas la estructura y lo agrega a la lista al final
Se pone en modo read de datos de equipo - Una vez recibido, creas la estructura y lo agrega a la lista al final
                                            Creas la estructura reparacion con todos los valores vacios y lo agregas a la lista

3
Servidor Detecta Generar Reparacion
Se pone en modo read de numero de orden a generar reparacion, (validaciones)
Si existe
Se pone en modo read de datos de reparacion - Una vez recibido, modificar el nodo correspondiente

*/
