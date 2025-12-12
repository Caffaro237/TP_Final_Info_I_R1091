#include "Headers.h"


void Opcion_2 (int sock, int sockdup, NodoCliente** TOP_Clientes, NodoEquipo** TOP_Equipo, NodoReparaciones** TOP_Reparaciones)
{
    char datos_crudos [300];
    read(sockdup, datos_crudos, 300);
    AltaDatos_Cliente(TOP_Clientes, datos_crudos);
    read(sockdup, datos_crudos, 300);
    AltaDatos_Equipo(TOP_Equipo, datos_crudos);
    AltaDatos_Reparaciones(TOP_Reparaciones, "Indefinido,Indefinido,Indefinido,Indefinido,Indefinido"); //Creo la estructura reparación vacia
                

}

void Opcion_4 (int sock, int sockdup, NodoCliente *TOP_Clientes)
{
    int existe_el_cliente = 0;
    int32_t opcion_a_modificar;
    int32_t num_de_orden;
    NodoCliente* puntero_a_cliente;
    char datos_del_cliente [300];
    char datos_a_modificar [50];
    int32_t se_logro_la_modificación;

    read(sockdup, &num_de_orden, sizeof(int32_t));
    puntero_a_cliente=BusquedaCliente_por_numero_de_orden(TOP_Clientes, (int) num_de_orden); //Guardo en un puntero el cliente que quiero
    
    if (puntero_a_cliente!=NULL)
    {
        existe_el_cliente = 1;
        write(sockdup, &existe_el_cliente, sizeof(int));
        
        EstructuraCliente_a_cadena(puntero_a_cliente->data, datos_del_cliente); //Guardo la estructura en un cadena
        
        write(sockdup, datos_del_cliente, 300); //Lo envio al cliente

        
        read(sockdup, &opcion_a_modificar, sizeof(int32_t)); //Recibo la opcion elegida
        read (sockdup, datos_a_modificar, 50);

        switch (opcion_a_modificar) //Modifico el dato y verifico que sea del tamaño correcto
        {
            case 0:
                if (strlen(datos_a_modificar) < MAX_FECHA_INGRESO)
                {
                    strcpy(puntero_a_cliente->data.fechaIngreso, datos_a_modificar);
                    se_logro_la_modificación=1;
                }
                else
                {
                    se_logro_la_modificación=0;
                }
                break;
            case 1:
                if (strlen(datos_a_modificar) < MAX_NOMBRE)
                {
                    strcpy(puntero_a_cliente->data.nombre, datos_a_modificar);
                    se_logro_la_modificación=1;
                }
                else
                {
                    se_logro_la_modificación=0;
                }
                break;
            case 2:
                if (strlen(datos_a_modificar) < MAX_APELLIDO)
                {
                    strcpy(puntero_a_cliente->data.apellido, datos_a_modificar);
                    se_logro_la_modificación=1;
                }
                else
                {
                    se_logro_la_modificación=0;
                }
                break;
            case 3:
                if (strlen(datos_a_modificar) < MAX_DIRECCION)
                {
                    strcpy(puntero_a_cliente->data.direccion, datos_a_modificar);
                    se_logro_la_modificación=1;
                }
                else
                {
                    se_logro_la_modificación=0;
                }
                break;
            case 4:
                if (strlen(datos_a_modificar) < MAX_TELEFONO)
                {
                    strcpy(puntero_a_cliente->data.telefono, datos_a_modificar);
                    se_logro_la_modificación=1;
                }
                else
                {
                    se_logro_la_modificación=0;
                }
                break;

        }
        write(sockdup, &se_logro_la_modificación, sizeof(int32_t)); //Lo digo al cliente si logro hacer la modificación o no
    }
    else
    {
        existe_el_cliente=0;
        write(sockdup, &existe_el_cliente,sizeof(int)); //Lo envio al cliente
    }

}

void Opcion_5 (int sock, int sockdup, NodoEquipo *TOP_Equipo)
{
    int existe_el_equipo = 0;
    int32_t opcion_a_modificar;
    int32_t num_de_orden;
    NodoEquipo* puntero_a_equipo;
    char datos_del_equipo [300];
    char datos_a_modificar [50];
    int32_t se_logro_la_modificación;

    read(sockdup, &num_de_orden, sizeof(int32_t));
    puntero_a_equipo=BusquedaEquipo_por_numero_de_orden(TOP_Equipo, (int) num_de_orden); //Guardo en un puntero el equipo que quiero
    
    if (puntero_a_equipo!=NULL)
    {
        existe_el_equipo = 1;
        write(sockdup, &existe_el_equipo, sizeof(int));
        
        EstructuraEquipo_a_cadena(puntero_a_equipo->data, datos_del_equipo); //Guardo la estructura en un cadena
        
        write(sockdup, datos_del_equipo, 300); //Lo envio al equipo

        
        read(sockdup, &opcion_a_modificar, sizeof(int32_t)); //Recibo la opcion elegida
        read (sockdup, datos_a_modificar, 50);
        switch (opcion_a_modificar)
        {
            case 0:
                if (strlen(datos_a_modificar) < MAX_TIPO)
                {
                    strcpy(puntero_a_equipo->data.tipo, datos_a_modificar);
                    se_logro_la_modificación=1;
                }
                else
                {
                    se_logro_la_modificación=0;
                }
                break;
            case 1:
                if (strlen(datos_a_modificar) < MAX_MODELO)
                {
                    strcpy(puntero_a_equipo->data.modelo, datos_a_modificar);
                    se_logro_la_modificación=1;
                }
                else
                {
                    se_logro_la_modificación=0;
                }
                break;
            case 2:
                if (strlen(datos_a_modificar) < MAX_MARCA)
                {
                    strcpy(puntero_a_equipo->data.marca, datos_a_modificar);
                    se_logro_la_modificación=1;
                }
                else
                {
                    se_logro_la_modificación=0;
                }
                break;
            case 3:
                if (strlen(datos_a_modificar) < MAX_FALLA)
                {
                    strcpy(puntero_a_equipo->data.falla, datos_a_modificar);
                    se_logro_la_modificación=1;
                }
                else
                {
                    se_logro_la_modificación=0;
                }
                break;

        }
        write(sockdup, &se_logro_la_modificación, sizeof(int32_t)); //Lo digo al cliente si logro hacer la modificación o no
    }
    else
    {
        existe_el_equipo=0;
        write(sockdup, &existe_el_equipo,sizeof(int)); //Lo envio al equipo
    }

}


void Opcion_6 (int sock, int sockdup, NodoCliente *TOP_Clientes, NodoEquipo *TOP_Equipo, NodoReparaciones *TOP_Reparaciones)
{
    char datos_crudos[300];
    int32_t num_de_orden;
    int existe_el_cliente = 0;

    NodoCliente* puntero_a_cliente;
    NodoEquipo* puntero_a_equipo;
    NodoReparaciones* puntero_a_reparaciones;

    read(sockdup, &num_de_orden, sizeof(int32_t));
    puntero_a_cliente=BusquedaCliente_por_numero_de_orden(TOP_Clientes, (int) num_de_orden); //Guardo en un puntero el cliente que quiero
                
    if (puntero_a_cliente!=NULL)
    {
        existe_el_cliente = 1;
        write(sockdup, &existe_el_cliente, sizeof(int));
        
        EstructuraCliente_a_cadena(puntero_a_cliente->data, datos_crudos); //Guardo la estructura en un cadena
        
        write(sockdup, datos_crudos, 300); //Lo envio al cliente

        
        puntero_a_equipo = BusquedaEquipo_por_numero_de_orden(TOP_Equipo, (int) num_de_orden); //Guardo en un puntero el equipo que quiero
        
        EstructuraEquipo_a_cadena(puntero_a_equipo->data, datos_crudos); //Guardo la estructura en un cadena
        write(sockdup, datos_crudos, 300); //Lo envio al cliente

        puntero_a_reparaciones = BusquedaReparaciones_por_numero_de_orden(TOP_Reparaciones, (int) num_de_orden); //Guardo en un puntero el equipo que quiero
        
        EstructuraReparaciones_a_cadena(puntero_a_reparaciones->data, datos_crudos); //Guardo la estructura en un cadena
        write(sockdup, datos_crudos, 300); //Lo envio al cliente

    }
    else
    {
        existe_el_cliente=0;
        write(sockdup, &existe_el_cliente,sizeof(int)); //Lo envio al cliente
    }



}