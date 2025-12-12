//Para compilacion desde terminal con gcc usar esta linea
//gcc ./Cliente/*.c -o ./Cliente/Cliente -Wall

//Para compilacion desde VS Code usar estos include
/*

#include "socket.c"
#include "menu.c"
#include "MAnejo_datos.c"
#include "Funciones_principales.c"

*/

#include "Headers.h"

int main (void)
{

    int32_t opcion=0;
    int sock;
    
    sock = conectar("localhost", PORT, 1);

    while(opcion != 7)
    {

        opcion = menu();
        write(sock, &opcion, sizeof(int32_t));
      
        switch(opcion) 
        {
           

            case 2:
                Opcion_2(sock);
                pausa();
                break;

            case 4:
                Opcion_4(sock);
                pausa();
                break;

            case 6:
                Opcion_6(sock);
                pausa();
                break;

            case 5:
                Opcion_5(sock);
                pausa();
                break;

            case 7:
                printf("Saliendo de la Aplicacion\n");
                close (sock);
                break;
                
            case -1:
                printf("Cerrando servidor\n");
                opcion = 7;// Para salir del while
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
