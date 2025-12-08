#include "Headers.h"

//Convierte una etsructura a cadena, asi se la paso al cliente
void EstructuraCliente_a_cadena (CLIENTE estruct_cliente, char* cadena_cliente);
void EstructuraEquipo_a_cadena (EQUIPO estruct_equipo, char* cadena_equipo);

void EstructuraCliente_a_cadena (CLIENTE estruct_cliente, char* cadena_cliente)
{
  int i=0;
  int j=0;
	// Obtengo la fechaIngreso
	j = 0;
	// Paro cuando encuentro el final de la estructura, o el límite de palabras.
	while (estruct_cliente.fechaIngreso[j] != '\0' && j < 10) 
	{
			cadena_cliente[i]= estruct_cliente.fechaIngreso[j];
			i++;
			j++;
	}
	cadena_cliente[i] = ','; // Pongo la coma
	i++; // Salto la coma

	// --- Obtengo el nombre ---
	j = 0;
	// Paro cuando encuentro el final de la estructura, o el límite de palabras.
	while (estruct_cliente.nombre[j] != '\0' && j < 14)
	{
			cadena_cliente[i] = estruct_cliente.nombre[j];
			i++;
			j++;
	}
	cadena_cliente[i] = ','; // Pongo la coma
	i++; // Salto la coma

	//Obtengo el apellido
	j = 0;
	// Paro cuando encuentro el final de la estructura, o el límite de palabras.
	while (estruct_cliente.apellido[j] != '\0' && j < 14)
	{
			cadena_cliente[i] = estruct_cliente.apellido[j];
			i++;
			j++;
	}
	cadena_cliente[i] = ','; // Pongo la coma
	i++; // Salto la coma

	//Obtengo la direccion
	j = 0;
	// Paro cuando encuentro el final de la estructura, o el límite de palabras.
	while (estruct_cliente.direccion[j] != '\0' && j < 19)
	{
			cadena_cliente[i] = estruct_cliente.direccion[j];
			i++;
			j++;
	}
	cadena_cliente[i] = ','; // Pongo la coma
	i++; // Salto la coma

	//Obtengo el telefono
	j = 0;
	// Paro cuando encuentro el final de la estructura, o el límite de palabras.
	while (estruct_cliente.telefono[j] != '\0' && j < 9)
	{
			cadena_cliente[i] = estruct_cliente.telefono[j];
			i++;
			j++;
	}
	cadena_cliente[i] = '\0'; //Añadir el terminador nulo ('\0')
	
}

void EstructuraEquipo_a_cadena (EQUIPO estruct_equipo, char* cadena_equipo)
{
 int i=0; // Índice para escribir en cadena_cliente
 int j=0; // Índice para leer en estruct_equipo
    
 
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
