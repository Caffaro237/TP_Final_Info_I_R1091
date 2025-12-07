#include "Headers.h"

//Alta de remito
void AltaDatos_Equipo(NodoEquipo** top_equipo, char* datos_crudos);
void AltaDatos_Cliente(NodoCliente** top_cliente, char* datos_crudos);
void AgregarNodo_Equipo (NodoEquipo** top_equipo, EQUIPO datos);
void AgregarNodo_Cliente (NodoCliente** top_cliente, CLIENTE datos);
EQUIPO Datos_crudos_a_EQUIPO(char* datos_crudos); //Devuelve el string en forma de estructura equipo
CLIENTE Datos_crudos_a_CLIENTE (char* datos_crudos); //Devuelve el string en forma de estructura cliente

//Modiifcar datos
void ModificarDatos_Equipo (NodoEquipo* top_equipo, int num_de_orden, char* datos_crudos); //Tiene que reescribir todo los datos
void ModificarDatos_Cliente (NodoCliente* top_cliente, int num_de_orden, char* datos_crudos); //Tiene que reescribir todo los datos

//Busqueda por numeor de orden (devuelven puntero al nodo buscado)
NodoCliente* BusquedaCliente_por_numero_de_orden(NodoCliente* top_cliente, int numero_de_orden);
NodoEquipo* BusquedaEquipo_por_numero_de_orden(NodoEquipo* top_equipo, int numero_de_orden);

//SOLO PARA MOSTRA EN EL SERVIDOR, NO AL CLIENTE
void mostrar_cliente (NodoCliente* cliente);
void mostrar_equipo (NodoEquipo* equipo);
void mostrar_por_id (int id, NodoCliente* top_cliente, NodoEquipo* top_equipo);


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
  while (datos_crudos[i] != ',' && j < 14) 
  {
      equipo_nuevo.tipo[j] = datos_crudos[i];
      i++;
      j++;
  }
  i+=1; //Salto la coma
  equipo_nuevo.tipo[j] = '\0'; // Terminación

  


  //Obtengo el modelo
  j = 0;
  while (datos_crudos[i] != ',' && j < 14) 
  {
      equipo_nuevo.modelo[j] = datos_crudos[i];
      i++;
      j++;
  }
  i+=1; //Salto la coma
  equipo_nuevo.modelo[j] = '\0'; // Terminación




  //Obengo la marca
  j = 0;
  while (datos_crudos[i] != ',' && j < 19) 
  {
      equipo_nuevo.marca[j] = datos_crudos[i];
      i++;
      j++;
  }
  i++; //Salto la coma
  equipo_nuevo.marca[j] = '\0'; // Terminación


  //Obtengo la falla
  j = 0;
  while (datos_crudos[i] != '\0' && j < 19) 
  {
      equipo_nuevo.falla[j] = datos_crudos[i];
      i++;
      j++;
  }
  equipo_nuevo.falla[j] = '\0'; // Terminación

  return equipo_nuevo;
}

void AgregarNodo_Cliente (NodoCliente** top_cliente, CLIENTE datos)
{
  NodoCliente* cliente_nuevo=(NodoCliente*) malloc(sizeof(NodoCliente)); //Creo el cliente
  NodoCliente* aux = *top_cliente;
  cliente_nuevo -> data=datos;
  cliente_nuevo -> next=NULL;
    
  if (*top_cliente!=NULL) // Si la lista ya existe en forma de memoria dinamica
  { 
        
    while(aux->next != NULL) //Voy al ultimo elemento de la lista
    {
      aux=aux->next;
    }
    
    aux->next=cliente_nuevo; //El ultimo elemento apunta al nuevo cliente
  }
  
  else //No existe la lista, la tengo que crear
  {

    *top_cliente=cliente_nuevo;

  }
    
}

void AltaDatos_Cliente(NodoCliente** top_cliente, char* datos_crudos)
{
  CLIENTE cliente_nuevo;
  NodoCliente* aux=*top_cliente;

  cliente_nuevo=Datos_crudos_a_CLIENTE(datos_crudos);

  if (*top_cliente!=NULL)
  {
    while(aux->next!=NULL) //Aux apunta al ultimo elemento
    {
      aux=aux->next;
    }

    cliente_nuevo.numero_de_orden=(aux->data.numero_de_orden) + 1; //El nuevo cliente tiene el siguiente numero de orden
  }

  else {cliente_nuevo.numero_de_orden=1000;} //Si es el primero
    
	

  AgregarNodo_Cliente(top_cliente, cliente_nuevo);

}

CLIENTE Datos_crudos_a_CLIENTE (char* datos_crudos)
{
  int i=0;
  int j=0;
  CLIENTE cliente_nuevo;

  // Obtengo la fechaIngreso
	j = 0;
	// Paro cuando encuentro la coma, o el límite de palabras.
	while (datos_crudos[i] != ',' && j < 10) 
	{
		cliente_nuevo.fechaIngreso[j] = datos_crudos[i];
		i++;
		j++;
	}
	cliente_nuevo.fechaIngreso[j] = '\0'; // Terminación
	 i++; // Salto la coma

	// Obtengo el nombre
	j = 0;
	while (datos_crudos[i] != ',' && j < 14) 
	{
		cliente_nuevo.nombre[j] = datos_crudos[i];
		i++;
		j++;
	}
	cliente_nuevo.nombre[j] = '\0'; // Terminación
	i++; // Salto la coma

	// Obtengo el apellido
	j = 0;
	while (datos_crudos[i] != ',' && j < 14) 
	{
		cliente_nuevo.apellido[j] = datos_crudos[i];
		i++;
		j++;
	}
		cliente_nuevo.apellido[j] = '\0'; // Terminación
	if (datos_crudos[i] == ',') i++; // Salto la coma

	// Obtengo la direccion
	j = 0;
	while (datos_crudos[i] != ',' && j < 19) 
	{
		cliente_nuevo.direccion[j] = datos_crudos[i];
		i++;
		j++;
	}
	cliente_nuevo.direccion[j] = '\0'; // Terminación
	i++; // Salto la coma

	// Obtengo el telefono
	j = 0;
	while (datos_crudos[i] != '\0' && j < 9) 
	{
		cliente_nuevo.telefono[j] = datos_crudos[i];
		i++;
		j++;
	}
		cliente_nuevo.telefono[j] = '\0'; // Terminación

    return cliente_nuevo;
}

NodoCliente* BusquedaCliente_por_numero_de_orden(NodoCliente* top_cliente, int numero_de_orden)
{
  NodoCliente* cliente;
  
  cliente = top_cliente;

  if (top_cliente==NULL) {printf ("No existe la lista"); return NULL;}

  while (cliente->data.numero_de_orden!=numero_de_orden) //Recorro la lista hasta encontrar el cliente con el id
  {
    if (cliente->next==NULL) {printf ("No se encontro el cliente"); return NULL;} //Si llego al final, me salgo
    
    cliente = cliente->next;   
  }

  return cliente;

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

void mostrar_cliente (NodoCliente* cliente)
{
  printf("Fecha de ingreso: %s\n", cliente->data.fechaIngreso);
  printf("Nombre: %s\n", cliente->data.nombre);
  printf("Apellido: %s\n", cliente->data.apellido);
  printf("Dirección: %s\n", cliente->data.direccion);
  printf("Telefono: %s\n", cliente->data.telefono);

}

void mostrar_equipo (NodoEquipo* equipo)
{
  printf("Tipo: %s\n", equipo->data.tipo);
  printf("Modelo: %s\n", equipo->data.modelo);
  printf("Marca: %s\n", equipo->data.marca);
  printf("Falla: %s\n", equipo->data.falla);
}

void mostrar_por_id (int id, NodoCliente* top_cliente, NodoEquipo* top_equipo)
{
  NodoCliente* cliente = BusquedaCliente_por_numero_de_orden(top_cliente,id);
  NodoEquipo* equipo = BusquedaEquipo_por_numero_de_orden(top_equipo,id);
  
  if (cliente!=NULL && equipo!=NULL)
  {
    printf ("\nDatos del cliente\n");
    mostrar_cliente (cliente);
    printf ("\nDatos del equipo\n");
    mostrar_equipo (equipo);
  }
  else{printf("Erro de datos, no se encontro el nuemro de orden");}
}

void ModificarDatos_Equipo (NodoEquipo* top_equipo, int num_de_orden, char* datos_crudos)
{
  EQUIPO cambios_realizados=Datos_crudos_a_EQUIPO(datos_crudos);

  NodoEquipo* aux=BusquedaEquipo_por_numero_de_orden(top_equipo, num_de_orden);

  aux->data=cambios_realizados;
}

void ModificarDatos_Cliente (NodoCliente* top_cliente, int num_de_orden, char* datos_crudos)
{
  CLIENTE cambios_realizados=Datos_crudos_a_CLIENTE(datos_crudos);

  NodoCliente* aux=BusquedaCliente_por_numero_de_orden(top_cliente, num_de_orden);

  aux->data= cambios_realizados;

}