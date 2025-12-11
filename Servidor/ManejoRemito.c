#include "Headers.h"

void Mostrar_por_id (int id, NodoCliente* top_cliente, NodoEquipo* top_equipo)
{
  NodoCliente* cliente = BusquedaCliente_por_numero_de_orden(top_cliente,id);
  NodoEquipo* equipo = BusquedaEquipo_por_numero_de_orden(top_equipo,id);
  
  if (cliente!=NULL && equipo!=NULL)
  {
    printf ("\nDatos del cliente\n");
    Mostrar_cliente (cliente);
    printf ("\nDatos del equipo\n");
    Mostrar_equipo (equipo);
  }
  else{printf("Erro de datos, no se encontro el nuemro de orden");}
}
