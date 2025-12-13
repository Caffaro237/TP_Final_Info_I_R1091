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

}

EQUIPO Datos_crudos_a_EQUIPO(char* datos_crudos)
{
  EQUIPO equipo_nuevo;
  int i=0;
  int j=0;
  // Obtengo el tipo
  j = 0;
  // Prao cuanod encuentro la coma, o el límite de palabras.
  while (datos_crudos[i] != ',' && j < (MAX_TIPO - 1)) 
  {
      equipo_nuevo.tipo[j] = datos_crudos[i];
      i++;
      j++;
  }
  i+=1; //Salto la coma
  equipo_nuevo.tipo[j] = '\0'; // Terminación

  


  //Obtengo el modelo
  j = 0;
  while (datos_crudos[i] != ',' && j < (MAX_MODELO - 1)) 
  {
      equipo_nuevo.modelo[j] = datos_crudos[i];
      i++;
      j++;
  }
  i+=1; //Salto la coma
  equipo_nuevo.modelo[j] = '\0'; // Terminación




  //Obengo la marca
  j = 0;
  while (datos_crudos[i] != ',' && j < (MAX_MARCA - 1)) 
  {
      equipo_nuevo.marca[j] = datos_crudos[i];
      i++;
      j++;
  }
  i++; //Salto la coma
  equipo_nuevo.marca[j] = '\0'; // Terminación


  //Obtengo la falla
  j = 0;
  while (datos_crudos[i] != '\0' && j < (MAX_FALLA - 1)) 
  {
      equipo_nuevo.falla[j] = datos_crudos[i];
      i++;
      j++;
  }
  equipo_nuevo.falla[j] = '\0'; // Terminación

  return equipo_nuevo;
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
 int i=0; 
 int j=0; 
    
 
 // Obtengo el tipo

 j = 0;
 // Paro cuando encuentro el final del string, o el límite de palabras.
 while (estruct_equipo.tipo[j] != '\0' && j < 14)
 {
     cadena_equipo[i]= estruct_equipo.tipo[j];
     i++;
     j++;
 }
 cadena_equipo[i] = ','; // Pongo la coma
 i++; // Salto la coma



 // Obtengo el modelo
 j = 0;
 // Paro cuando encuentro el final del string, o el límite de palabras.
 while (estruct_equipo.modelo[j] != '\0' && j < 14)
 {
     cadena_equipo[i] = estruct_equipo.modelo[j];
     i++;
     j++;
 }
 cadena_equipo[i] = ','; // Pongo la coma
 i++; // Salto la coma



 // Obtengo la marca
 j = 0;
 // Paro cuando encuentro el final del string, o el límite de palabras.
 while (estruct_equipo.marca[j] != '\0' && j < 19)
 {
     cadena_equipo[i] = estruct_equipo.marca[j];
     i++;
     j++;
 }
 cadena_equipo[i] = ','; // Pongo la coma
 i++; // Salto la coma



 // Obtengo la falla
 j = 0;
 // Paro cuando encuentro el final del string, o el límite de palabras.
 while (estruct_equipo.falla[j] != '\0' && j < 19)
 {
     cadena_equipo[i] = estruct_equipo.falla[j];
     i++;
     j++;
 }

 cadena_equipo[i] = '\0'; //Añadir el terminador nulo ('\0')
}
