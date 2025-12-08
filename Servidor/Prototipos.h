//Prototipos de Funciones

int menu(void);
int inicializar(NodoCliente **TOP_Clientes, NodoEquipo **TOP_Equipo, NodoReparaciones **TOP_Reparaciones);

//Funciones para manejo archivos
int LeerArchivo(NodoCliente **TOP_Clientes, NodoEquipo **TOP_Equipo, NodoReparaciones **TOP_Reparaciones, int tipoDato);
int LeerLinea(int fd, char **linea);
int EscribirArchivo(CLIENTE *cliente, EQUIPO *equipo, REPARACIONES *reparaciones, int tipoDato);
int CargarDato(NodoCliente **TOP_Clientes, NodoEquipo **TOP_Equipo, NodoReparaciones **TOP_Reparaciones, char *linea, int tipoDato);
int SepararPorComa(char *linea, char campos[][50]);

//Funciones para altas de clientes y equipos
#include "GestorRemito.h"
#include "Mostrar_cliente.h"
