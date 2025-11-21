
typedef struct st_data_cli{
  int numero_de_orden;
  char nombre[15];
  char apellido[15];
  char direccion[20];
  //Debe faltar algo, no me acuerdo

} CLIENTE;


typedef struct st_node_cli{
  CLIENTE data;
  struct st_node_cli* next;
  
}NODO_CLI;

typedef struct st_data_equi{
  int numero_de_orden;
  char tipo[15];
  char modelo[15];
  char marca[20];
  char falla [20];
  //Debe faltar algo, no me acuerdo

} EQUIPO;



typedef struct st_node_equ{
  EQUIPO data;
  struct st_node_equ* next;
  
}NODO_EQUI;


