#include "Headers.h"


void AgregarNodo_Equipo (NodoEquipo** top_equipo, EQUIPO datos)
{
  NodoEquipo* equipo_nuevo=(NodoEquipo*) malloc(sizeof(NodoEquipo)); //Creo el equipo
  NodoEquipo* aux = *top_equipo;
  equipo_nuevo -> data=datos;
  equipo_nuevo -> next=NULL;
    
  if (*top_equipo!=NULL) // Si la lista ya existe en forma de memoria dinamica
  { 
        
    while(aux->next != NULL) //Voy al ultimo elemento de la lista
    {
      aux=aux->next;
    }
    
    aux->next=equipo_nuevo; //El ultimo elemento apunta al nuevo equipo
  }
  
  else //No existe la lista, la tengo que crear
  {

    *top_equipo=equipo_nuevo;

  }
    
}

void AltaDatos_Equipo(NodoEquipo** top_equipo, char* datos_crudos)
{
  EQUIPO equipo_nuevo;
  NodoEquipo* aux=*top_equipo;

  equipo_nuevo=Datos_crudos_a_EQUIPO(datos_crudos);


  if (*top_equipo!=NULL)
  {
    while(aux->next!=NULL) //Aux apunta al ultimo elemento
    {
      aux=aux->next;
    }
  
    equipo_nuevo.numero_de_orden=aux->data.numero_de_orden + 1; //El nuevo equipo tiene el siguiente numero de orden
  }
  else {equipo_nuevo.numero_de_orden=1000;} //Si es el primero

  

  AgregarNodo_Equipo(top_equipo, equipo_nuevo);
  EscribirNuevoEquipo(equipo_nuevo);
}

EQUIPO Datos_crudos_a_EQUIPO(char* datos_crudos)
{
  char campos[5][200] = {0};
	EQUIPO equipo;

	SepararPorPuntoComa(datos_crudos, campos);

	strcpy(equipo.tipo, campos[1]);
  strcpy(equipo.marca, campos[2]);
  strcpy(equipo.modelo, campos[3]);
  strcpy(equipo.falla, campos[4]);


  return equipo;

}

NodoEquipo* BusquedaEquipo_por_numero_de_orden(NodoEquipo* top_equipo, int numero_de_orden)
{
  NodoEquipo* equipo;
  
  equipo = top_equipo;

  if (top_equipo==NULL) {printf ("No existe la lista"); return NULL;}
  
  while (equipo->data.numero_de_orden!=numero_de_orden) //Recorro la lista hasta encontrar el cliente con el id
  {
    if (equipo->next==NULL) {printf ("No se encontro el equipo"); return NULL;} //Si llego al final, me salgo
    
    equipo = equipo->next;   
  }

  return equipo;

}


void Mostrar_equipo (NodoEquipo* equipo_a_mostrar)
{
  printf("Tipo: %s\n", equipo_a_mostrar->data.tipo);
  printf("Modelo: %s\n", equipo_a_mostrar->data.modelo);
  printf("Marca: %s\n", equipo_a_mostrar->data.marca);
  printf("Falla: %s\n", equipo_a_mostrar->data.falla);
}

void EstructuraEquipo_a_cadena (EQUIPO estruct_equipo, char* cadena_equipo)
{
	CLIENTE x;
	REPARACIONES z;
	UnirPorPuntoComa(x, estruct_equipo, z, 2, cadena_equipo);
}
