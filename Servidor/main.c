//gcc ./Servidor/*.c -o ./Servidor/Server -Wall

#include "Headers.h"

int main (void)
{
    int retorno = 0;
    NodoCliente *TOP_Clientes = NULL;
    NodoEquipo *TOP_Equipo = NULL;
    NodoReparaciones *TOP_Reparaciones = NULL;

  
    int sock;
	int sockdup;
    char datos_crudos[300];
    int32_t opcion = 0;
    int32_t num_de_orden;
    int existe_el_cliente = 0;
    int i = 0;

    char seguir = 's';

    retorno = inicializar(&TOP_Clientes, &TOP_Equipo, &TOP_Reparaciones);

    if(retorno < 0)
    {
        return retorno;
    }


    NodoCliente* puntero_a_cliente;
    NodoEquipo* puntero_a_equipo;
    NodoReparaciones* puntero_a_reparaciones;

	sock = abrir_conexion(8000, 2, 1);
    sockdup = aceptar_pedidos(sock, 1);

    while(1)
    {
        strcpy(datos_crudos, "");
        read(sockdup, &opcion, sizeof(int32_t));

        switch(opcion) 
        {
            case 2:
                read(sockdup, datos_crudos, 300);
                AltaDatos_Cliente(&TOP_CLIENTE, datos_crudos);
                read(sockdup, datos_crudos, 300);
                AltaDatos_Equipo(&TOP_EQUIPO, datos_crudos);
                break;
                //Agregar creacion de estructura reparación

            case 5:
                read(sockdup, &num_de_orden, sizeof(int32_t));
                puntero_a_cliente=BusquedaCliente_por_numero_de_orden(TOP_CLIENTE, (int) num_de_orden); //Guardo en un puntero el cliente que quiero
                
                if (puntero_a_cliente!=NULL)
                {
                    existe_el_cliente = 1;
                    write(sockdup, &existe_el_cliente, sizeof(int));
                    
                    EstructuraCliente_a_cadena(puntero_a_cliente->data, datos_crudos); //Guardo la estructura en un cadena
                    
                    write(sockdup, datos_crudos, 300); //Lo envio al cliente
                    strcpy(datos_crudos, "");
                    
                    puntero_a_equipo = BusquedaEquipo_por_numero_de_orden(TOP_EQUIPO, (int) num_de_orden); //Guardo en un puntero el equipo que quiero
                    
                    EstructuraEquipo_a_cadena(puntero_a_equipo->data, datos_crudos); //Guardo la estructura en un cadena
                    write(sockdup, datos_crudos, 300); //Lo envio al cliente
                    strcpy(datos_crudos, "");
                }
                else
                {
                    existe_el_cliente=0;
                    write(sockdup, &existe_el_cliente,sizeof(int)); //Lo envio al cliente
                }

                break;

            case 7:
                close(sockdup);
                sockdup = aceptar_pedidos(sock, 1);
                break;

            default:
                break;
        
        }
    
    }
    close (sock);
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
