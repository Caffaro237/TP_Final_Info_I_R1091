#include "Estructuras.h"

void* crear_cliente (NODO_CLI** top_cliente);
void mostrar_cliente (NODO_CLI* cliente);
void* crear_equipo (NODO_EQUI** top_equipo);
void mostrar_equipo (NODO_EQUI* equipo);

int mostrar_por_id (int id, NODO_CLI* top_cliente, NODO_EQUI* top_equipo);



int main()
{
  NODO_CLI* top_cliente=NULL;
  NODO_EQUI* top_equipo=NULL;


  crear_cliente(&top_cliente);
  crear_equipo(&top_equipo);
  
  mostrar_por_id (1, top_cliente, top_equipo);
  
  
}

void* crear_equipo (NODO_EQUI** top_equipo)
{
  NODO_EQUI* tmp=(NODO_EQUI*) malloc(sizeof(NODO_EQUI)); //Crear equipo

  tmp->next=*top_equipo; //El nuevo elemnto apunta al primer archivo
  *top_equipo=tmp;//El "top" apunta al nuevo nodo
  
  //AGREGAR SOLICITAR DATOS, NO FORZARLOS COMO HAGO ACA//
  tmp->data.numero_de_orden=1;
  strcpy(tmp->data.tipo, "lolus");
  strcpy(tmp->data.modelo, "asas");
  strcpy(tmp->data.marca, "aca");
  strcpy(tmp->data.falla,"Malardo");
  
  
  return tmp;
}

void* crear_cliente (NODO_CLI** top_cliente)
{
  NODO_CLI* tmp=(NODO_CLI*) malloc(sizeof(NODO_CLI)); //Crear cliente

  tmp->next=*top_cliente; //El nuevo elemnto apunta al primer archivo
  *top_cliente=tmp;//El "top" apunta al nuevo nodo
  
  //AGREGAR SOLICITAR DATOS, NO FORZARLOS COMO HAGO ACA//
  tmp->data.numero_de_orden=1;
  strcpy(tmp->data.nombre, "LOL");
  strcpy(tmp->data.apellido, "SUS");
  strcpy(tmp->data.direccion, "MI CASA");
  
  return tmp;
}

void mostrar_cliente (NODO_CLI* cliente)
{
  printf("Nombre: %s\n", cliente->data.nombre);
  printf("Apellido: %s\n", cliente->data.apellido);
  printf("Dirección: %s\n", cliente->data.direccion);

}

void mostrar_equipo (NODO_EQUI* equipo)
{
  printf("Nombre: %s\n", equipo->data.marca);
  printf("Apellido: %s\n", equipo->data.falla);
  //etc...

}

int mostrar_por_id (int id, NODO_CLI* top_cliente, NODO_EQUI* top_equipo)
{
  NODO_CLI* cliente;
  NODO_EQUI* equipo;
  
  cliente = top_cliente;
  equipo = top_equipo;
  
  while (cliente->data.numero_de_orden!=id) //Recorro la lista hasta encontrar el cliente con el id
  {
    if (cliente->next==NULL) {printf ("No se encontro el cliente"); return -1;} //Si llego al final, me salgo
    
    cliente = cliente->next;   
  }
  
  while (equipo->data.numero_de_orden!=id) //Recorro la lista hasta encontrar el cliente con el id
  {
    if (equipo->next==NULL) {printf ("No se encontro el equipo"); return -1;} //Si llego al final, me salgo
    
    equipo = equipo->next;   
  }
  
  printf ("Datos del cliente\n");
  mostrar_cliente (cliente);
  printf ("Datos del equipo\n");
  mostrar_equipo (equipo);
  
  free(cliente);
  free(equipo);
  return 0;
}
