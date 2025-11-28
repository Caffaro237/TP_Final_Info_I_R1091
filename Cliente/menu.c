#include "Headers.h"

int menu(void)
{
    //Menu principal de opciones

    int opcion;

    system("clear"); //Limpia la consola
   //system("color 0F"); //Cambia a color negro de la consola y las letras a blanco brillante

    printf("*****Menu de opciones*****\n");
    printf("1 - Listar clientes\n");
    printf("2 - Alta de cliente\n");
    printf("3 - Modificar datos de cliente\n");
    printf("4 - Modificar datos de equipo\n");
    printf("5 - Buscar cliente\n");
    printf("6 - Salir\n");

    printf("Indique su opcion: ");
    scanf("%d", &opcion); //Ingresa la opcion

    return opcion;
}