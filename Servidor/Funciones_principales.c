#include "Headers.h"

void Listar_clientes (int sockdup, NodoCliente *TOP_Clientes, NodoEquipo *TOP_Equipo, NodoReparaciones *TOP_Reparaciones)
{
    char datos_cliente[300] = "";
    char datos_equipo[300] = "";
    char datos_reparaciones[300] = "";
    char datos_a_pasar[1000] = "";

    NodoCliente* puntero_a_cliente = TOP_Clientes;
    NodoEquipo* puntero_a_equipo = TOP_Equipo;
    NodoReparaciones* puntero_a_reparaciones = TOP_Reparaciones;

    if (TOP_Clientes == NULL || TOP_Equipo == NULL || TOP_Reparaciones == NULL)//Veo si la lista esta vacia
    {
        memset(datos_a_pasar, 0, sizeof(datos_a_pasar));

        strcpy(datos_a_pasar, "SIN_LISTA");

        write(sockdup, datos_a_pasar, strlen(datos_a_pasar)); //Lo envio al cliente
    }
    

    while (TOP_Clientes != NULL || TOP_Equipo != NULL || TOP_Reparaciones != NULL) //Recorro la lista hasta el final
    {
        memset(datos_cliente, 0, sizeof(datos_cliente));
        memset(datos_equipo, 0, sizeof(datos_equipo));
        memset(datos_reparaciones, 0, sizeof(datos_reparaciones));
        memset(datos_a_pasar, 0, sizeof(datos_a_pasar));

        EstructuraCliente_a_cadena(puntero_a_cliente->data, datos_cliente); //Guardo la estructura en un cadena
            
        EstructuraEquipo_a_cadena(puntero_a_equipo->data, datos_equipo); //Guardo la estructura en un cadena

        EstructuraReparaciones_a_cadena(puntero_a_reparaciones->data, datos_reparaciones); //Guardo la estructura en un cadena

        strcat(datos_a_pasar, datos_cliente);
        strcat(datos_a_pasar, datos_equipo);
        strcat(datos_a_pasar, datos_reparaciones);


        write(sockdup, datos_a_pasar, strlen(datos_a_pasar)); //Lo envio al cliente

        usleep(SLEEP);

        //Paso al siguiente elemento
        puntero_a_cliente = puntero_a_cliente -> next;
        puntero_a_equipo = puntero_a_equipo -> next;
        puntero_a_reparaciones = puntero_a_reparaciones -> next;

        if (puntero_a_cliente == NULL) //Si recorri toda lista
        {
            memset(datos_a_pasar, 0, sizeof(datos_a_pasar));
            strcpy(datos_a_pasar, "SI");

            write(sockdup, datos_a_pasar, strlen(datos_a_pasar)); //Le digo si llegue al final de la lista

            break;
        }
    }
}


void Alta_de_cliente (int sockdup, NodoCliente** TOP_Clientes, NodoEquipo** TOP_Equipo, NodoReparaciones** TOP_Reparaciones)
{
    char datos_crudos[1000] = "";
    
    read(sockdup, datos_crudos, sizeof(datos_crudos));
    AltaDatos_Cliente(TOP_Clientes, datos_crudos);
    
    memset(datos_crudos, 0, sizeof(datos_crudos));

    read(sockdup, datos_crudos, sizeof(datos_crudos));
    AltaDatos_Equipo(TOP_Equipo, datos_crudos);
    
    AltaDatos_Reparaciones(TOP_Reparaciones, "N/A;0;NO;NO;N/A"); //Creo la estructura reparación vacia
}


int Modificar_datos_de_cliente (int sockdup, NodoCliente *TOP_Clientes)
{
    int existe_el_cliente = 0;
    int32_t opcion_a_modificar;
    int32_t num_de_orden;
    NodoCliente* puntero_a_cliente;
    char datos_del_cliente [300] = "";
    char datos_a_modificar [50] = "";
    int32_t se_logro_la_modificacion;

    read(sockdup, &num_de_orden, sizeof(int32_t));
    puntero_a_cliente=BusquedaCliente_por_numero_de_orden(TOP_Clientes, (int) num_de_orden); //Guardo en un puntero el cliente que quiero
    
    if (puntero_a_cliente != NULL)
    {
        existe_el_cliente = 1;
        write(sockdup, &existe_el_cliente, sizeof(existe_el_cliente));
        
        EstructuraCliente_a_cadena(puntero_a_cliente->data, datos_del_cliente); //Guardo la estructura en un cadena
        
        write(sockdup, datos_del_cliente, strlen(datos_del_cliente)); //Lo envio al cliente

        
        read(sockdup, &opcion_a_modificar, sizeof(int32_t)); //Recibo la opcion elegida
        read (sockdup, datos_a_modificar, strlen(datos_a_modificar));

        switch (opcion_a_modificar) //Modifico el dato y verifico que sea del tamaño correcto
        {
            case 0:
                if (strlen(datos_a_modificar) < MAX_FECHA_INGRESO)
                {
                    strcpy(puntero_a_cliente->data.fechaIngreso, datos_a_modificar);
                    se_logro_la_modificacion=1;
                }
                else
                {
                    se_logro_la_modificacion=0;
                }
                break;
            case 1:
                if (strlen(datos_a_modificar) < MAX_NOMBRE)
                {
                    strcpy(puntero_a_cliente->data.nombre, datos_a_modificar);
                    se_logro_la_modificacion=1;
                }
                else
                {
                    se_logro_la_modificacion=0;
                }
                break;
            case 2:
                if (strlen(datos_a_modificar) < MAX_APELLIDO)
                {
                    strcpy(puntero_a_cliente->data.apellido, datos_a_modificar);
                    se_logro_la_modificacion=1;
                }
                else
                {
                    se_logro_la_modificacion=0;
                }
                break;
            case 3:
                if (strlen(datos_a_modificar) < MAX_DIRECCION)
                {
                    strcpy(puntero_a_cliente->data.direccion, datos_a_modificar);
                    se_logro_la_modificacion=1;
                }
                else
                {
                    se_logro_la_modificacion=0;
                }
                break;
            case 4:
                if (strlen(datos_a_modificar) < MAX_TELEFONO)
                {
                    strcpy(puntero_a_cliente->data.telefono, datos_a_modificar);
                    se_logro_la_modificacion=1;
                }
                else
                {
                    se_logro_la_modificacion=0;
                }
                break;

        }
        write(sockdup, &se_logro_la_modificacion, sizeof(se_logro_la_modificacion)); //Lo digo al cliente si logro hacer la modificación o no
    }
    else
    {
        existe_el_cliente=0;
        write(sockdup, &existe_el_cliente,sizeof(existe_el_cliente)); //Lo envio al cliente

        return -1;
    }

    return 0;
}


int Generar_reparacion (int sockdup, NodoReparaciones* TOP_Reparaciones)
{
    NodoReparaciones* reparacion_a_generar;
    int32_t num_de_orden;
    int existe_la_reparacion = 0;
    char datos_crudos[300] = "";
    REPARACIONES reparacion_datos;


    read(sockdup, &num_de_orden, sizeof(int32_t));
    reparacion_a_generar=BusquedaReparaciones_por_numero_de_orden(TOP_Reparaciones, (int) num_de_orden); //Guardo en un puntero la reparacion que quiero
  
    if (reparacion_a_generar != NULL)
    {
        existe_la_reparacion = 1;
        write(sockdup, &existe_la_reparacion, sizeof(existe_la_reparacion));

        read(sockdup, datos_crudos, sizeof(datos_crudos));
        reparacion_datos = Datos_crudos_a_REPARACIONES (datos_crudos);
        reparacion_datos.numero_de_orden = reparacion_a_generar -> data.numero_de_orden;
        reparacion_a_generar -> data = reparacion_datos;

    }
    else
    {
        existe_la_reparacion = 0;
        write(sockdup, &existe_la_reparacion,sizeof(existe_la_reparacion)); //Lo envio al cliente

        return -1;
    }

    return 0;
}


int Modificar_datos_de_equipo (int sockdup, NodoEquipo *TOP_Equipo)
{
    int existe_el_equipo = 0;
    int32_t opcion_a_modificar;
    int32_t num_de_orden;
    NodoEquipo* puntero_a_equipo;
    char datos_del_equipo [300] = "";
    char datos_a_modificar [50] = "";
    int32_t se_logro_la_modificacion;

    read(sockdup, &num_de_orden, sizeof(int32_t));
    puntero_a_equipo=BusquedaEquipo_por_numero_de_orden(TOP_Equipo, (int) num_de_orden); //Guardo en un puntero el equipo que quiero
    
    if (puntero_a_equipo!=NULL)
    {
        existe_el_equipo = 1;
        write(sockdup, &existe_el_equipo, sizeof(existe_el_equipo));
        
        EstructuraEquipo_a_cadena(puntero_a_equipo->data, datos_del_equipo); //Guardo la estructura en un cadena
        
        write(sockdup, datos_del_equipo, strlen(datos_del_equipo)); //Lo envio al equipo

        
        read(sockdup, &opcion_a_modificar, sizeof(int32_t)); //Recibo la opcion elegida
        read (sockdup, datos_a_modificar, strlen(datos_a_modificar));
        switch (opcion_a_modificar)
        {
            case 0:
                if (strlen(datos_a_modificar) < MAX_TIPO)
                {
                    strcpy(puntero_a_equipo->data.tipo, datos_a_modificar);
                    se_logro_la_modificacion=1;
                }
                else
                {
                    se_logro_la_modificacion=0;
                }
                break;
            case 1:
                if (strlen(datos_a_modificar) < MAX_MARCA)
                {
                    strcpy(puntero_a_equipo->data.marca, datos_a_modificar);
                    se_logro_la_modificacion=1;
                }
                else
                {
                    se_logro_la_modificacion=0;
                }
                break;
            case 2:
                if (strlen(datos_a_modificar) < MAX_MODELO)
                {
                    strcpy(puntero_a_equipo->data.modelo, datos_a_modificar);
                    se_logro_la_modificacion=1;
                }
                else
                {
                    se_logro_la_modificacion=0;
                }
                break;
            case 3:
                if (strlen(datos_a_modificar) < MAX_FALLA)
                {
                    strcpy(puntero_a_equipo->data.falla, datos_a_modificar);
                    se_logro_la_modificacion=1;
                }
                else
                {
                    se_logro_la_modificacion=0;
                }
                break;

        }
        write(sockdup, &se_logro_la_modificacion, sizeof(se_logro_la_modificacion)); //Lo digo al cliente si logro hacer la modificación o no
    }
    else
    {
        existe_el_equipo=0;
        write(sockdup, &existe_el_equipo,sizeof(existe_el_equipo)); //Lo envio al equipo

        return -1;
    }

    return 0;
}


void Buscar_cliente (int sockdup, NodoCliente *TOP_Clientes, NodoEquipo *TOP_Equipo, NodoReparaciones *TOP_Reparaciones)
{
    char datos_cliente[300] = "";
    char datos_equipo[300] = "";
    char datos_reparaciones[300] = "";
    char datos_crudos[300] = "";
    int32_t num_de_orden;
    int existe_el_cliente = 0;

    NodoCliente* puntero_a_cliente;
    NodoEquipo* puntero_a_equipo;
    NodoReparaciones* puntero_a_reparaciones;

    memset(datos_crudos, 0, sizeof(datos_crudos));

    read(sockdup, &num_de_orden, sizeof(int32_t));
    
    puntero_a_cliente = BusquedaCliente_por_numero_de_orden(TOP_Clientes, (int) num_de_orden); //Guardo en un puntero el cliente que quiero
    puntero_a_equipo = BusquedaEquipo_por_numero_de_orden(TOP_Equipo, (int) num_de_orden); //Guardo en un puntero el equipo que quiero   
    puntero_a_reparaciones = BusquedaReparaciones_por_numero_de_orden(TOP_Reparaciones, (int) num_de_orden); //Guardo en un puntero el equipo que quiero
        

    if (puntero_a_cliente != NULL || puntero_a_equipo != NULL || puntero_a_reparaciones != NULL)
    {
        existe_el_cliente = 1;
        write(sockdup, &existe_el_cliente, sizeof(existe_el_cliente));


        memset(datos_cliente, 0, sizeof(datos_cliente));
        memset(datos_equipo, 0, sizeof(datos_equipo));
        memset(datos_reparaciones, 0, sizeof(datos_reparaciones));
        memset(datos_crudos, 0, sizeof(datos_crudos));

        EstructuraCliente_a_cadena(puntero_a_cliente->data, datos_cliente); //Guardo la estructura en un cadena
            
        EstructuraEquipo_a_cadena(puntero_a_equipo->data, datos_equipo); //Guardo la estructura en un cadena

        EstructuraReparaciones_a_cadena(puntero_a_reparaciones->data, datos_reparaciones); //Guardo la estructura en un cadena

        strcat(datos_crudos, datos_cliente);
        strcat(datos_crudos, datos_equipo);
        strcat(datos_crudos, datos_reparaciones);


        write(sockdup, datos_crudos, strlen(datos_crudos)); //Lo envio al cliente
    }
    else
    {
        existe_el_cliente = 0;
        write(sockdup, &existe_el_cliente, sizeof(existe_el_cliente)); //Lo envio al cliente
    }
}


void Buscar_Telefono_Cliente(int sockdup, NodoCliente *TOP_Clientes, NodoReparaciones *TOP_Reparaciones)
{
    int32_t num_de_orden;
    int existe_el_cliente = 0;
    char telefono[20] = "";
    char reparado[5] = "";

    NodoCliente* puntero_a_cliente;
    NodoReparaciones* puntero_a_reparaciones;

    read(sockdup, &num_de_orden, sizeof(int32_t));
    puntero_a_cliente = BusquedaCliente_por_numero_de_orden(TOP_Clientes, (int) num_de_orden); //Guardo en un puntero el cliente que quiero
    puntero_a_reparaciones = BusquedaReparaciones_por_numero_de_orden(TOP_Reparaciones, (int) num_de_orden); //Guardo en un puntero el equipo que quiero
                
    if (puntero_a_cliente!=NULL)
    {
        existe_el_cliente = 1;
        write(sockdup, &existe_el_cliente, sizeof(existe_el_cliente));

        strcpy(telefono, puntero_a_cliente->data.telefono);
        strcpy(reparado, puntero_a_reparaciones->data.reparado);

        if(!strcmp(reparado, "NO"))
        {
            write(sockdup, reparado, strlen(reparado)); //Lo envio al cliente
        }
        else
        {
            write(sockdup, telefono, strlen(telefono)); //Lo envio al cliente
        }
    }
    else
    {
        existe_el_cliente = 0;
        write(sockdup, &existe_el_cliente, sizeof(existe_el_cliente)); //Lo envio al cliente
    }
}


int SepararPorPuntoComa(char *linea, char campos[][200])
{
    int i;
    int j = 0;
    int k = 0;

    memset(campos, 0, 6 * 200);

    for (i = 0; linea[i] != '\0'; i++)
    {
        if (linea[i] == ';')
        {
            campos[k][j] = '\0';
            
            if (k < 5)
            {
                k++;
            }

            j = 0;
        }
        else
        {
            campos[k][j++] = linea[i];
        }
    }

    campos[k][j] = '\0';

    return k + 1; //Cantidad de campos encontrados
}


int UnirPorPuntoComa (CLIENTE cliente, EQUIPO equipo, REPARACIONES reparaciones, int tipoDato, char* buffer)
{
    char auxNumeroOrden[5] = "";

    memset(auxNumeroOrden, 0, sizeof(auxNumeroOrden));

    switch (tipoDato)
    {
        case 1:
            sprintf(auxNumeroOrden, "%d", cliente.numero_de_orden);
            strcat(buffer, auxNumeroOrden);
            strcat(buffer, ";");
            strcat(buffer, cliente.fechaIngreso);
            strcat(buffer, ";");
            strcat(buffer, cliente.nombre);
            strcat(buffer, ";");
            strcat(buffer, cliente.apellido);
            strcat(buffer, ";");
            strcat(buffer, cliente.direccion);
            strcat(buffer, ";");
            strcat(buffer, cliente.telefono);
            strcat(buffer, "\n\0");
            break;
        case 2:
            sprintf(auxNumeroOrden, "%d", equipo.numero_de_orden);
            strcat(buffer, auxNumeroOrden);
            strcat(buffer, ";");
            strcat(buffer, equipo.tipo);
            strcat(buffer, ";");
            strcat(buffer, equipo.marca);
            strcat(buffer, ";");
            strcat(buffer, equipo.modelo);
            strcat(buffer, ";");
            strcat(buffer, equipo.falla);
            strcat(buffer, "\n\0");
            break;
        case 3:
            sprintf(auxNumeroOrden, "%d", reparaciones.numero_de_orden);
            strcat(buffer, auxNumeroOrden);
            strcat(buffer, ";");
            strcat(buffer, reparaciones.reparacionAEfectuar);
            strcat(buffer, ";");
            strcat(buffer, reparaciones.presupuesto);
            strcat(buffer, ";");
            strcat(buffer, reparaciones.confirmacion);
            strcat(buffer, ";");
            strcat(buffer, reparaciones.reparado);
            strcat(buffer, ";");
            strcat(buffer, reparaciones.fechaEgreso);
            strcat(buffer, "\n\0");
            break;
        
        default:
            return -1;
            break;
    }

    return 0;
}