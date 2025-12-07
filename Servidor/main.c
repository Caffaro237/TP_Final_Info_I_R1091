#include "GestorRemito.h"
#include "Mostrar_cliente.h"

// gcc -Wall main_servidor.c sock-lib.c -o servidor

int main (void)
{
  NodoCliente *TOP_CLIENTE=NULL;
  NodoEquipo *TOP_EQUIPO=NULL;


  //NodoReparaciones *TOP_REPARACION=NULL;

  
	int sock;
	int sockdup;
  char datos_crudos [300];
  int32_t opcion=0;
  int32_t num_de_orden;
  int existe_el_cliente=0;
  int32_t fin_de_la_lista=0;
  int i=0;

  NodoCliente* puntero_a_cliente;
  NodoEquipo* puntero_a_equipo;

	sock=abrir_conexion(8000, 10, 1);
  sockdup = aceptar_pedidos(sock,1);

  while (1)
  {

    strcpy(datos_crudos,"");
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
          existe_el_cliente=1;
          write(sockdup, &existe_el_cliente, sizeof(int));
          EstructuraCliente_a_cadena(puntero_a_cliente->data, datos_crudos); //Guardo la estructura en un cadena
          write(sockdup, datos_crudos, 300); //Lo envio al cliente
          strcpy(datos_crudos, "");
          puntero_a_equipo=BusquedaEquipo_por_numero_de_orden(TOP_EQUIPO, (int) num_de_orden); //Guardo en un puntero el equipo que quiero
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
        sockdup = aceptar_pedidos(sock,1);
        break;

      default:
        break;
      
    }
    
  }
  close (sock);
  
}