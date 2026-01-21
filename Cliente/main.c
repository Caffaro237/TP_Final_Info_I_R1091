//Para compilacion desde terminal con gcc usar esta linea
//gcc ./Cliente/*.c -o ./Cliente/Cliente -Wall

//Para compilacion desde VS Code usar estos include
/*

#include "socket.c"
#include "menu.c"
#include "Manejo_datos.c"
#include "Funciones_principales.c"

*/

#include "Headers.h"

int main (void)
{

    int32_t opcion = 0;
    int sock;
    
    sock = conectar(SERVER, PORT, 1);

    while(opcion != 8)
    {

        opcion = menu();
        write(sock, &opcion, strlen(opcion));
      
        switch(opcion) 
        {
            case LISTAR_CLIENTES:
                Listar_clientes(sock);
                pausa();
                break;

            case ALTA_DE_CLIENTE:
                Alta_de_cliente (sock);
                pausa();
                break;
            
            case GENERAR_REPARACION:
                Generar_raparacion (sock);
                pausa();
                break;

            case MODIFICAR_DATOS_CLIENTE:
                Modificar_datos_de_cliente (sock);
                pausa();
                break;
            
            case MODIFICAR_DATOS_EQUIPO:
                Modificar_datos_de_equipo (sock);
                pausa();
                break;
            
            case BUSCAR_CLIENTE:
                Buscar_cliente(sock);
                pausa();
                break;

            case ENVIAR_WHATSAPP:
                Enviar_WhatsApp(sock);
                pausa();
                break;

            case SALIR:
                printf("Saliendo de la Aplicacion\n");
                close (sock);
                break;
                

            default:
                printf("Opción invalida\n");
                pausa();
                break;


        }
    }
  
    printf("\n");

    return 0;
}
