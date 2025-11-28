//Prototipos de Funciones

int menu(void);

//Funciones para manejo archivos
int readFile(char path[200]);
int readline(int fd, char **linea);
int writeFile(char path[200]);

//Funciones para altas de clientes y equipos
void crear_cliente (NodoCliente** top_cliente, CLIENTE datos);
void mostrar_cliente (NodoCliente* cliente);
void crear_equipo (NodoEquipo** top_equipo, EQUIPO datos);
void mostrar_equipo (NodoEquipo* equipo);
int mostrar_por_id (int id, NodoCliente* top_cliente, NodoEquipo* top_equipo);