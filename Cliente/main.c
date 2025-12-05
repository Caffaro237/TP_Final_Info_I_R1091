#include "Headers.h"


int main (void)
{
  char path[200] = "./Clientes.csv";
  char datos[300];
  int32_t opcion=0;
  int32_t num_de_orden=0;

  int sock;
  sock = conectar("localhost", 8000, 1);

  while(opcion != 6)
  {
    
    opcion = menu();
    write(sock, &opcion, sizeof(int32_t));
    
    switch(opcion) 
    {
      
      case 2:
        printf("Escriba los datos del cliente: ");
        scanf("%299s", datos);
        write(sock, datos, 300);
        printf("Escriba los datos del equipo: ");
        scanf("%299s", datos);
        write(sock, datos, 300);
        pausa();
        break;

      case 5:
        printf("Escriba el numero de orden: ");
        scanf("%d", &num_de_orden);
        //Envio el numero de orden
        write(sock, &num_de_orden, sizeof(int32_t));
        //Muestro el cliente
        read(sock, datos, 300);
        if (strcmp(datos,"N"))
        {
          printf ("No se encontro el numero de orden\n");
        }
        else 
        {
          printf("Cliente:\n");
          Mostrar_cadena(datos);
          strcpy(datos, "");
          //Muestro el equipo
          read(sock, datos, 300);
          printf("\nEquipo:\n");
          Mostrar_cadena(datos);

        }
        pausa();
        break;

      case 6:
        printf("Saliendo de la Aplicacion\n");
        break;

      default:
        printf("Opción invalida");
        pausa();
        break;
    
    
    }


  }
  
  
  
  printf("\n");

  return 0;
}
