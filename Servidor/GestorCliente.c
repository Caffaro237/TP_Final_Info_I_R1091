#include "Headers.h"


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
	i++; // Salto la coma

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

void Mostrar_cliente (NodoCliente* cliente_a_mostrar)
{
  printf("Fecha de ingreso: %s\n", cliente_a_mostrar->data.fechaIngreso);
  printf("Nombre: %s\n", cliente_a_mostrar->data.nombre);
  printf("Apellido: %s\n", cliente_a_mostrar->data.apellido);
  printf("Dirección: %s\n", cliente_a_mostrar->data.direccion);
  printf("Telefono: %s\n", cliente_a_mostrar->data.telefono);

}
