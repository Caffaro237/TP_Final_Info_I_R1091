#include "Headers.h"

void Listar_clientes (int sock)
{
    char datos [300];
    int32_t termino_la_lista;
    read(sock, &termino_la_lista, sizeof(int32_t));

    if (!termino_la_lista) //Ver si la lista etsa vacia
    {
        while (!termino_la_lista)
        {
            //Muestro el cliente
            read(sock, datos, 300);
            printf("Cliente:\n");
            Mostrar_cadena(datos);
            strcpy(datos, "");
            //Muestro el equipo
            read(sock, datos, 300);
            printf("\nEquipo:\n");
            Mostrar_cadena(datos);
            //Muestro las reparaciones
            read(sock, datos, 300);
            printf("\nReparaciones:\n");
            Mostrar_cadena(datos);

            read(sock, &termino_la_lista, sizeof(int32_t));        
        }
    }
    else
    {
        printf ("No existe la lista\n");
    }
}

void Alta_de_cliente(int sock)
{
    char datos[300];
    Pedir_datos_del_cliente(datos);
    write(sock, datos, strlen(datos));
    Pedir_datos_del_equipo(datos);
    write(sock, datos, strlen(datos));
}

void Modificar_datos_de_cliente (int sock)
{
    int32_t num_de_orden=0;
    int32_t opcion_a_modificar;
    int existe_el_cliente=0;
    int32_t se_logro_la_modificación;
    char datos_del_cliente[300];
    char datos_a_modficar [50];

    printf("Escriba el numero de orden del cliente: ");
    scanf("%d", &num_de_orden);
    
    //Envio el numero de orden
    write(sock, &num_de_orden, sizeof(num_de_orden));
    
    //El servidor me dice si existe el cliente
    read(sock, &existe_el_cliente, sizeof(int));
    
    if(existe_el_cliente)
    {
        //Muestro el cliente
        read(sock, datos_del_cliente, 300);
        printf("Los datos del cliente con numero de orden %d son:\n", num_de_orden);
        Mostrar_cadena(datos_del_cliente);
        pausa();
        do
        {        
            printf("(0) Fecha de ingreso\n");
            printf("(1) Nombre\n");
            printf("(2) Apellido\n");
            printf("(3) Dirección\n");
            printf("(4) Telefono\n");
            printf ("Indique con el numero correspondiente que dato quiere modificar: ");
            scanf("%d", &opcion_a_modificar);

            if (opcion_a_modificar<0 || opcion_a_modificar>4)
            {
                printf("Opcion no valida, intente de vuelta\n");
            }
        } while (opcion_a_modificar<0 || opcion_a_modificar>4);

        write(sock, &opcion_a_modificar, sizeof(opcion_a_modificar)); //Envio la opcion elegida al servidor
        printf("Escriba el dato a reemplazar: ");
        scanf("%s", datos_a_modficar);
        write(sock, datos_a_modficar, strlen(datos_a_modficar));
        read(sock, &se_logro_la_modificación, sizeof(int32_t));

        if (!se_logro_la_modificación)
        {
            printf("NO se logro modificar, tipo de dato incompatible\n");
        }
    }
    else 
    {
        printf ("No se encontro el numero de orden\n");
    }

}

void Generar_raparacion (int sock)
{
    int32_t num_de_orden;
    int existe_la_reparacion = 0;
    char datos[300];


    printf("Escriba el numero de orden de la reparación a generar: ");
    scanf("%d", &num_de_orden);

    //Envio el numero de orden
    write(sock, &num_de_orden, sizeof(num_de_orden));

    //El servidor me dice si existe la reparacion
    read(sock, &existe_la_reparacion, sizeof(int));

    if (existe_la_reparacion)
    {
    Pedir_datos_de_reparacion(datos);
    write(sock, datos, strlen(datos));


    }
    else 
    {
        printf ("No se encontro el numero de orden\n");
    }

}


void Modificar_datos_de_equipo (int sock)
{
    int32_t num_de_orden=0;
    int32_t opcion_a_modificar;
    int existe_el_equipo=0;
    int32_t se_logro_la_modificación;
    char datos_del_equipo[300];
    char datos_a_modficar [50];

    printf("Escriba el numero de orden del equipo: ");
    scanf("%d", &num_de_orden);
    
    //Envio el numero de orden
    write(sock, &num_de_orden, sizeof(num_de_orden));
    
    //El servidor me dice si existe el equipo
    read(sock, &existe_el_equipo, sizeof(int));
    
    if(existe_el_equipo)
    {
        //Muestro el equipo
        read(sock, datos_del_equipo, 300);
        printf("Los datos del equipo con numero de orden %d son:\n", num_de_orden);
        Mostrar_cadena(datos_del_equipo);
        pausa();
        do
        {        
            printf("(0) Tipo\n");
            printf("(1) Modelo\n");
            printf("(2) Marca\n");
            printf("(3) Falla\n");
            printf ("Indique con el numero correspondiente que dato quiere modificar: ");
            scanf("%d", &opcion_a_modificar);

            if (opcion_a_modificar<0 || opcion_a_modificar>3)
            {
                printf("Opcion no valida, intente de vuelta\n");
            }
        } while (opcion_a_modificar<0 || opcion_a_modificar>3);

        write(sock, &opcion_a_modificar, sizeof(opcion_a_modificar)); //Envio la opcion elegida al servidor
        printf("Escriba el dato a reemplazar: ");
        scanf("%s", datos_a_modficar);
        write(sock, datos_a_modficar, strlen(datos_a_modficar));
        read(sock, &se_logro_la_modificación, sizeof(se_logro_la_modificación));

        if (!se_logro_la_modificación)
        {
            printf("NO se logro modificar, tipo de dato incompatible\n");
        }
    }
    else 
    {
        printf ("No se encontro el numero de orden\n");
    }

}

void Buscar_cliente (int sock)
{
    int32_t num_de_orden=0;
    int existe_el_cliente=0;
    char datos[1000] = "";
    printf("Escriba el numero de orden: ");
    scanf("%d", &num_de_orden);
    
    //Envio el numero de orden
    write(sock, &num_de_orden, sizeof(num_de_orden));
    
    //El servidor me dice si existe el cliente
    read(sock, &existe_el_cliente, sizeof(int));
    
    memset(datos, 0, sizeof(datos));

    if(existe_el_cliente)
    {
        //Muestro el cliente
        read(sock, datos, sizeof(datos));
        printf("Cliente:\n");
        Mostrar_cadena(datos);
        memset(datos, 0, sizeof(datos));

        //Muestro el equipo
        read(sock, datos, sizeof(datos));
        printf("\nEquipo:\n");
        Mostrar_cadena(datos);
        memset(datos, 0, sizeof(datos));

        //Muestro las reparaciones
        read(sock, datos, sizeof(datos));
        printf("\nReparaciones:\n");
        Mostrar_cadena(datos);
    }
    else 
    {
        printf ("No se encontro el numero de orden\n");
    }
}

void Enviar_WhatsApp(int sock)
{
    int32_t num_de_orden = 0;
    int existe_el_cliente = 0;
    char datos[20];
    char telefono[20] = "549";
    char mensaje[1000];
    char auxNumeroOrden[5] = "";

    printf("Escriba el numero de orden: ");
    scanf("%d", &num_de_orden);
    
    //Envio el numero de orden
    write(sock, &num_de_orden, sizeof(num_de_orden));
    
    //El servidor me dice si existe el cliente
    read(sock, &existe_el_cliente, sizeof(int));

    if(existe_el_cliente)
    {
        read(sock, datos, sizeof(datos));

        if(!strcmp(datos, "NO"))
        {
            printf("No se puede dar aviso de un equipo no reparado\n");
        }
        else
        {
            strcat(mensaje, "Buenas tardes. Su equipo se encuentra reparado, el numero de orden es: ");
            sprintf(auxNumeroOrden, "%d", num_de_orden);
            strcat(mensaje, auxNumeroOrden);

            strcat(telefono, datos);

            SoloDigitos(telefono);

            AbrirWhatsapp(telefono, mensaje);
        }
    }
    else 
    {
        printf ("No se encontro el numero de orden\n");
    }
}

void AbrirWhatsapp(char *telefono, char *mensaje)
{
    char comando[1000] = "";

    strcat(comando, "xdg-open \"https://wa.me/");
    strcat(comando, telefono);
    strcat(comando, "?text=");
    strcat(comando, mensaje);
    strcat(comando, "\""); 

    system(comando);
}

void SoloDigitos(char *telefono)
{
    char *telefonoOriginal = telefono;
    char *telefonoSinGuiones = telefono;

    while(*telefonoOriginal)
    {
        if (isdigit((unsigned char)*telefonoOriginal))
        {
            *telefonoSinGuiones++ = *telefonoOriginal;
        }
        telefonoOriginal++;
    }

    *telefonoSinGuiones = '\0';
}

int SepararPorPuntoComa(char *linea, char campos[][50])
{
    int i;
    int j = 0;
    int k = 0;

    for (i = 0; linea[i] != '\0'; i++)
    {
        if (linea[i] == ';')
        {
            campos[k][j] = '\0';
            k++;
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