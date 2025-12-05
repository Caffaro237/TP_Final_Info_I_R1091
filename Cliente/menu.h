#include "Headers.h"
int32_t menu ();
void pausa ();

int32_t menu()
{
    //Menu principal de opciones

    int32_t opcion;

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

void pausa ()
{
    int c;
    // Limpia cualquier caracter previo (incluye el \n que deja scanf)
    while ((c = getchar()) != '\n' && c != EOF);

    printf("Presiona ENTER para continuar...");
    fflush(stdout);
    getchar();

}