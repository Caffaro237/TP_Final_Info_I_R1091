#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

typedef struct datosCliente{
  int numero_de_orden;
  char fechaIngreso[11];
  char nombre[15];
  char apellido[15];
  char direccion[20];
  char telefono[10];
} CLIENTE;


typedef struct nodoCliente{
  CLIENTE data;
  struct nodoCliente* next;
} NodoCliente;

typedef struct datosEquipo{
  int numero_de_orden;
  char tipo[15];
  char modelo[15];
  char marca[20];
  char falla [20];
} EQUIPO;



typedef struct nodoEquipo{
  EQUIPO data;
  struct nodoEquipo* next;
} NodoEquipo;


typedef struct datosReparaciones{
  int numero_de_orden;
  char reparacionAEfectuar[15];
  char presupuesto[15];
  char confirmacion[20];
  char reparado [20];
  char fechaEgreso[11];
} REPARACIONES;



typedef struct nodoReparaciones{
  REPARACIONES data;
  struct nodoReparaciones* next;
} NodoReparaciones;


#endif