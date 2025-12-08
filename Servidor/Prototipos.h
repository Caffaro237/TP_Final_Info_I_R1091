//Prototipos de Funciones

int menu(void);
int inicializar(NodoCliente **TOP_Clientes, NodoEquipo **TOP_Equipo, NodoReparaciones **TOP_Reparaciones);

//Funciones para manejo archivos
int LeerArchivo(NodoCliente **TOP_Clientes, NodoEquipo **TOP_Equipo, NodoReparaciones **TOP_Reparaciones, int tipoDato);
int LeerLinea(int fd, char **linea);
int EscribirArchivo(CLIENTE *cliente, EQUIPO *equipo, REPARACIONES *reparaciones, int tipoDato);
int CargarDato(NodoCliente **TOP_Clientes, NodoEquipo **TOP_Equipo, NodoReparaciones **TOP_Reparaciones, char *linea, int tipoDato);
int SepararPorComa(char *linea, char campos[][50]);

//Funciones para alta de remito
void AltaDatos_Equipo(NodoEquipo** top_equipo, char* datos_crudos);
void AltaDatos_Cliente(NodoCliente** top_cliente, char* datos_crudos);
void AgregarNodo_Equipo (NodoEquipo** top_equipo, EQUIPO datos);
void AgregarNodo_Cliente (NodoCliente** top_cliente, CLIENTE datos);
EQUIPO Datos_crudos_a_EQUIPO(char* datos_crudos); //Devuelve el string en forma de estructura equipo
CLIENTE Datos_crudos_a_CLIENTE (char* datos_crudos); //Devuelve el string en forma de estructura cliente

//Busqueda por numeor de orden (devuelven puntero al nodo buscado)
NodoCliente* BusquedaCliente_por_numero_de_orden(NodoCliente* top_cliente, int numero_de_orden);
NodoEquipo* BusquedaEquipo_por_numero_de_orden(NodoEquipo* top_equipo, int numero_de_orden);

//Funciones para mostrar la lista en el servidor
void Mostrar_cliente (NodoCliente* cliente);
void Mostrar_equipo (NodoEquipo* equipo);
void Mostrar_por_id (int id, NodoCliente* top_cliente, NodoEquipo* top_equipo);

//Convierte una estructura a cadena
void EstructuraCliente_a_cadena (CLIENTE estruct_cliente, char* cadena_cliente);
void EstructuraEquipo_a_cadena (EQUIPO estruct_equipo, char* cadena_equipo);