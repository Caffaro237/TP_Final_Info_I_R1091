//gcc ./Servidor/*.c -o ./Servidor/Server -Wall

#include "Headers.h"

int main (void)
{
    NodoCliente *TOP_Clientes = NULL;
    NodoEquipo *TOP_Equipo = NULL;
    NodoReparaciones *TOP_Reparaciones = NULL;

    char path[200] = "./Clientes.csv";
    char seguir = 's';
    int c;
    int option;

    while(seguir == 's')
    {
        printf("Opcion: ");
        scanf("%d", &option);

        switch(option) //Llama a la funcion para mostrar la sopciones principales
        {
            case 1:
                readFile(TOP_Clientes, TOP_Equipo, TOP_Reparaciones, path);
                break;

            case 2:
                printf("Alta de cliente");
                break;

            case 3:
                printf("Generar Reparacion");
                break;

            case 4:
                printf("Modificar datos de cliente");
                break;

            case 5:
                printf("Modificar datos de equipo");
                break;

            case 6:
                printf("Buscar cliente");
                break;
                
            case -1:
                seguir = 'n';
                break;
            
            default:
                printf("Opcion invalida\n");
                break;
        }
    }
    
    
    printf("Saliendo de la Aplicacion\n");
    printf("\n");

    return 0;
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