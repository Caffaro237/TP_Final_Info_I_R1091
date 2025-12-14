#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

typedef struct datosCliente{
  int numero_de_orden;
  char fechaIngreso[MAX_FECHA_INGRESO];
  char nombre[MAX_NOMBRE];
  char apellido[MAX_APELLIDO];
  char direccion[MAX_DIRECCION];
  char telefono[MAX_TELEFONO];
} CLIENTE;


typedef struct nodoCliente{
  CLIENTE data;
  struct nodoCliente* next;
} NodoCliente;

typedef struct datosEquipo{
  int numero_de_orden;
  char tipo[MAX_TIPO];
  char modelo[MAX_MODELO];//intercambiar modelo y marca hacerlo en todos los lugares usados
  char marca[MAX_MARCA];
  char falla [MAX_FALLA];
} EQUIPO;



typedef struct nodoEquipo{
  EQUIPO data;
  struct nodoEquipo* next;
} NodoEquipo;


typedef struct datosReparaciones{
  int numero_de_orden;
  char reparacionAEfectuar[MAX_REPARACION];
  char presupuesto[MAX_PRESUPUESTO];
  char confirmacion[MAX_CONFIRMACION];
  char reparado [MAX_REPARADO];
  char fechaEgreso[MAX_FECHA_EGRESO];
} REPARACIONES;



typedef struct nodoReparaciones{
  REPARACIONES data;
  struct nodoReparaciones* next;
} NodoReparaciones;


#endif