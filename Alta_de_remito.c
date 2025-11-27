#include "Headers.h"
#include "Estructuras.h"

//ASUMO QUE SI NO EXIXSTE UNA LISTA, SU PUNTERO TOP APUNTA A NULL//

void crear_cliente (NODO_CLI** top_cliente, CLIENTE datos);
void mostrar_cliente (NODO_CLI* cliente);
void crear_equipo (NODO_EQUI** top_equipo, EQUIPO datos);
void mostrar_equipo (NODO_EQUI* equipo);

int mostrar_por_id (int id, NODO_CLI* top_cliente, NODO_EQUI* top_equipo);

void crear_equipo (NODO_EQUI** top_equipo, EQUIPO datos)
{
  NODO_EQUI* equipo_nuevo=(NODO_EQUI*) malloc(sizeof(NODO_EQUI)); //Creo el equipo
  equipo_nuevo -> data=datos;
  equipo_nuevo -> next=NULL;
  NODO_EQUI* aux = *top_equipo;
    
  if (*top_equipo!=NULL) // Si la lista ya existe en forma de memoria dinamica
  { 
        
    while(aux->next != NULL) //Voy al ultimo elemento de la lista
    {
      aux=aux->next;
    }
    equipo_nuevo -> data.numero_de_orden = aux ->data.numero_de_orden + 1; //El numero de orden, el anteriro mas uno
    aux->next=equipo_nuevo; //El ultimo elemento apunta al nuevo equipo
  }
  
  else //No existe la lista, hago que el primer elemento de la lista sea el ingresado
  {
    *top_equipo=equipo_nuevo;
  }
}

void crear_cliente (NODO_CLI** top_cliente, CLIENTE datos)
{
  NODO_CLI* cliente_nuevo=(NODO_CLI*) malloc(sizeof(NODO_CLI)); //Creo el cliente
  cliente_nuevo -> data=datos;
  cliente_nuevo -> next=NULL;
  NODO_CLI* aux=*top_cliente;

    
  if (*top_cliente!=NULL) // Si la lista ya existe en forma de memoria dinamica
  { 
        
    while(aux->next != NULL) //Voy al ultimo elemento de la lista
    {
      aux=aux->next;
    }
    
    cliente_nuevo -> data.numero_de_orden = aux -> data.numero_de_orden + 1; //El numero de orden, el anteriro mas uno
    aux->next=cliente_nuevo; //El ultimo elemento apunta al nuevo cliente
  }
  
  else //No existe la lista, la tengo que crear
  {
    *top_cliente=cliente_nuevo;
  }
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
  
  printf ("\nDatos del cliente\n");
  mostrar_cliente (cliente);
  printf ("\nDatos del equipo\n");
  mostrar_equipo (equipo);
  
  free(cliente);
  free(equipo);
  return 0;
}
