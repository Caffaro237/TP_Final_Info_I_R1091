#include "Headers.h"

void Mostrar_cadena (char* cadena);


void Mostrar_cadena (char* cadena)
{
    int i=0;
    while (cadena[i] != '\0')
    {
        if (cadena[i]==',') //Si encuentro una coma, meto enter y paso al siguiente
        {
            printf ("\n");
            i++;
        }
        printf ("%c", cadena[i]);
        
        i++;
    }
    printf("\n");
}