#include "Mostrar_datos.h"


int main (void)
{
  char path[200] = "./Clientes.csv";
  char datos[300];
  int opcion;
  int c;
  int num_de_orden;

  int sock;
  sock = conectar("localhost", 8000, 1);

  while(opcion != 6)
  {
    
    opcion = menu();
    write(sock, opcion, sizeof(int));

    switch(opcion) 
    {

      case 2:
        pritnf("Escriba los datos del cliente");
        scanf("%s", &datos);
        write(sock, datos, 300);
        pritnf("Escriba los datos del equipo");
        scanf("%s", &datos);
        write(sock, datos, 300);


      case 5:
        pritnf("Escriba el numero de orden");
        scanf("%d", &num_de_orden);
        //Envio el numero de orden
        write(sock, &num_de_orden, sizeof(int));
        //Muestro el cliente
        read(sock, datos, 300);
        Mostrar_cadena(datos);
        //Muestro el equipo
        read(sock, datos, 300);
        Mostrar_cadena(datos);

      case 6:
        printf("Saliendo de la Aplicacion\n");
        break;

      default:
        printf("Opción invalida");
        break;
    }

    if(opcion != 6)
    {
      // Limpia cualquier caracter previo (incluye el \n que deja scanf)
      while ((c = getchar()) != '\n' && c != EOF);

      printf("Presiona ENTER para continuar...");
      fflush(stdout);
      getchar();
    }
  }
  
  
  
  printf("\n");

  return 0;
}
