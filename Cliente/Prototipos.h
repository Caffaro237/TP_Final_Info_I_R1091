//Funcion con las opciones del cliente
int32_t menu ();

void pausa ();

//Funcion para conexion por Socket
int conectar(char *hostname, int port, int debug); // funcion que se conecta a un servidor

//Muestra los datos separados por coma de una cadena de caracteres
void Mostrar_cadena (char* cadena);


//Pedir datos del cliente
int vreificar_longitud(char* cadena, int tamaño_maximo);
void Pedir_datos_del_cliente(char* cadena_para_guardar_datos);
void Pedir_datos_del_equipo(char* datos_crudos);

//FUNCIONES PRINCIPALES (que van en el main)
void Opcion_2(int sock);
void Opcion_4 (int sock);
void Opcion_5 (int sock);
void Opcion_6 (int sock);