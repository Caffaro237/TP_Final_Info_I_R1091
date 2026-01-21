#include "Estructuras.h"

//Prototipos de Funciones

int menu(void);
int inicializar(NodoCliente **TOP_Clientes, NodoEquipo **TOP_Equipo, NodoReparaciones **TOP_Reparaciones);

//Funciones para manejo archivos
int LeerArchivo(NodoCliente **TOP_Clientes, NodoEquipo **TOP_Equipo, NodoReparaciones **TOP_Reparaciones, int tipoDato);
int LeerLinea(int fd, char **linea);
int EscribirNuevoCliente(CLIENTE cliente);
int EscribirNuevoEquipo(EQUIPO equipo);
int EscribirNuevoReparacion(REPARACIONES reparaciones);
int CargarDato(NodoCliente **TOP_Clientes, NodoEquipo **TOP_Equipo, NodoReparaciones **TOP_Reparaciones, char *linea, int tipoDato);
int SepararPorPuntoComa(char *linea, char campos[][MAX_DATOS]);
int UnirPorPuntoComa (CLIENTE cliente, EQUIPO equipo, REPARACIONES reparaciones, int tipoDato, char* buffer);
int GuardarArchivoCompleto(NodoCliente *TOP_Clientes, NodoEquipo *TOP_Equipo, NodoReparaciones *TOP_Reparaciones, int tipoDato);
int GuardarArchivos(NodoCliente *TOP_Clientes, NodoEquipo *TOP_Equipo, NodoReparaciones *TOP_Reparaciones);
int SeleccionarArchivo(char *archivo, int tipoDato);

//Funciones para el cliente
void AltaDatos_Cliente(NodoCliente** top_cliente, char* datos_crudos);
void AgregarNodo_Cliente (NodoCliente** top_cliente, CLIENTE datos);
CLIENTE Datos_crudos_a_CLIENTE (char* datos_crudos); //Devuelve el string en forma de estructura cliente
NodoCliente* BusquedaCliente_por_numero_de_orden(NodoCliente* top_cliente, int numero_de_orden);//Busqueda por numero de orden (devuelven puntero al nodo buscado)
void Mostrar_cliente (NodoCliente* cliente_a_mostrar);//Funcion para mostrar un elemento de la lista cliente


//Funciones para el equipo
void AltaDatos_Equipo(NodoEquipo** top_equipo, char* datos_crudos);
void AgregarNodo_Equipo (NodoEquipo** top_equipo, EQUIPO datos);
EQUIPO Datos_crudos_a_EQUIPO(char* datos_crudos); //Devuelve el string en forma de estructura equipo
NodoEquipo* BusquedaEquipo_por_numero_de_orden(NodoEquipo* top_equipo, int numero_de_orden); //Busqueda por numero de orden (devuelven puntero al nodo buscado)
void Mostrar_equipo (NodoEquipo* equipo_a_mostrar); //Funcion para mostrar un elemento de la lista equipo


//Funciones para reparaciones
void AltaDatos_Reparaciones(NodoReparaciones** top_reparaciones, char* datos_crudos);
void AgregarNodo_Reparaciones (NodoReparaciones** top_reparaciones, REPARACIONES datos);
REPARACIONES Datos_crudos_a_REPARACIONES(char* datos_crudos); //Devuelve el string en forma de estructura reparaciones
NodoReparaciones* BusquedaReparaciones_por_numero_de_orden(NodoReparaciones* top_reparaciones, int numero_de_orden); //Busqueda por numero de orden (devuelven puntero al nodo buscado)
void Mostrar_reparaciones (NodoReparaciones* reparaciones_a_mostrar); //Funcion para mostrar un elemento de la lista reparaciones


void Mostrar_por_id (int id, NodoCliente* top_cliente, NodoEquipo* top_equipo, NodoReparaciones* top_reparaciones);


//Convierte una estructura a cadena
void EstructuraCliente_a_cadena (CLIENTE estruct_cliente, char* cadena_cliente);
void EstructuraEquipo_a_cadena (EQUIPO estruct_equipo, char* cadena_equipo);
void EstructuraReparaciones_a_cadena (REPARACIONES estruct_reparaciones, char* cadena_reparaciones);

//Funciones para conexion por Socket
int abrir_conexion(int port, int backlog, int debug); // función que crea la conexión
int aceptar_pedidos(int, int debug);                  // función que acepta una conexión entrante

//FUNCIONES PRINCIPALES (que van en el main)
void Listar_clientes (int sockdup, NodoCliente *TOP_Clientes, NodoEquipo *TOP_Equipo, NodoReparaciones *TOP_Reparaciones);
void Alta_de_cliente (int sockdup, NodoCliente** TOP_Clientes, NodoEquipo** TOP_Equipo, NodoReparaciones** TOP_Reparaciones);
int Generar_reparacion (int sockdup, NodoReparaciones* TOP_Reparaciones);
int Modificar_datos_de_cliente (int sockdup, NodoCliente *TOP_Clientes);
int Modificar_datos_de_equipo (int sockdup, NodoEquipo *TOP_Equipo);
void Buscar_cliente (int sockdup, NodoCliente *TOP_Clientes, NodoEquipo *TOP_Equipo, NodoReparaciones *TOP_Reparaciones);
void Buscar_Telefono_Cliente(int sockdup, NodoCliente *TOP_Clientes, NodoReparaciones *TOP_Reparaciones);

//Funciones para signals
void SalirCtrlZ(int sig);