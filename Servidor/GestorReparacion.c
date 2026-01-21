#include "Headers.h"

void AgregarNodo_Reparaciones (NodoReparaciones** top_reparaciones, REPARACIONES datos)
{
  NodoReparaciones* reparaciones_nuevo=(NodoReparaciones*) malloc(sizeof(NodoReparaciones)); //Creo el reparaciones
  NodoReparaciones* aux = *top_reparaciones;
  reparaciones_nuevo -> data=datos;
  reparaciones_nuevo -> next=NULL;
    
  if (*top_reparaciones!=NULL) // Si la lista ya existe en forma de memoria dinamica
  { 
        
    while(aux->next != NULL) //Voy al ultimo elemento de la lista
    {
      aux=aux->next;
    }
    
    aux->next=reparaciones_nuevo; //El ultimo elemento apunta al nuevo reparaciones
  }
  
  else //No existe la lista, la tengo que crear
  {

    *top_reparaciones=reparaciones_nuevo;

  }
    
}

void AltaDatos_Reparaciones(NodoReparaciones** top_reparaciones, char* datos_crudos)
{
  REPARACIONES reparaciones_nuevo = {0};
  NodoReparaciones* aux=*top_reparaciones;

  reparaciones_nuevo=Datos_crudos_a_REPARACIONES(datos_crudos);

  if (*top_reparaciones!=NULL)
  {
    while(aux->next!=NULL) //Aux apunta al ultimo elemento
    {
      aux=aux->next;
    }

    reparaciones_nuevo.numero_de_orden=(aux->data.numero_de_orden) + 1; //El nuevo reparaciones tiene el siguiente numero de orden
  }

  else {reparaciones_nuevo.numero_de_orden=1000;} //Si es el primero
    
	

  AgregarNodo_Reparaciones(top_reparaciones, reparaciones_nuevo);
  EscribirNuevoReparacion(reparaciones_nuevo);
}

REPARACIONES Datos_crudos_a_REPARACIONES (char* datos_crudos)
{
  char campos[MAX_COLUMNAS][MAX_DATOS] = {0};
  REPARACIONES reparacion = {0};

  SepararPorPuntoComa(datos_crudos, campos);

  strcpy(reparacion.reparacionAEfectuar, campos[0]);
  strcpy(reparacion.presupuesto, campos[1]);
  strcpy(reparacion.confirmacion, campos[2]);
  strcpy(reparacion.reparado, campos[3]);
  strcpy(reparacion.fechaEgreso, campos[4]);

  return reparacion;
}

NodoReparaciones* BusquedaReparaciones_por_numero_de_orden(NodoReparaciones* top_reparaciones, int numero_de_orden)
{
  NodoReparaciones* reparaciones;
  
  reparaciones = top_reparaciones;

  if (top_reparaciones == NULL) {printf ("No existe la lista"); return NULL;}

  while (reparaciones->data.numero_de_orden!=numero_de_orden) //Recorro la lista hasta encontrar el reparaciones con el id
  {
    if (reparaciones->next == NULL) {printf ("No se encontro la reparaciones"); return NULL;} //Si llego al final, me salgo
    
    reparaciones = reparaciones->next;   
  }

  return reparaciones;

}

void Mostrar_reparaciones (NodoReparaciones* reparaciones_a_mostrar)
{
  printf("Repaarción a efectuar: %s\n", reparaciones_a_mostrar->data.reparacionAEfectuar);
  printf("Presupuesto %s\n", reparaciones_a_mostrar->data.presupuesto);
  printf("Confirmación: %s\n", reparaciones_a_mostrar->data.confirmacion);
  printf("Estado de reparación: %s\n", reparaciones_a_mostrar->data.reparado);
  printf("Fecha de egreso: %s\n", reparaciones_a_mostrar->data.fechaEgreso);

}


void EstructuraReparaciones_a_cadena (REPARACIONES reparaciones, char* cadena_reparaciones)
{
 	CLIENTE cliente = {0};
	EQUIPO equipo = {0};
	UnirPorPuntoComa(cliente, equipo, reparaciones, OPCION_REPARACIONES, cadena_reparaciones);
}
