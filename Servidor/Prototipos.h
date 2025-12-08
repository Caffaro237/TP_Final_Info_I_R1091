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
void crear_cliente (NodoCliente** top_cliente, CLIENTE datos);
void mostrar_cliente (NodoCliente* cliente);
void crear_equipo (NodoEquipo** top_equipo, EQUIPO datos);
void mostrar_equipo (NodoEquipo* equipo);
int mostrar_por_id (int id, NodoCliente* top_cliente, NodoEquipo* top_equipo);