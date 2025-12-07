#include "Headers.h"

int main (void)
{
    char path[200] = "./Clientes.csv";
    char seguir = 's';
    int c;

    while(seguir == 's')
    {
        switch(menu()) //Llama a la funcion para mostrar la sopciones principales
        {
            case 1:
                readFile(path);
                break;

            case 6:
                seguir = 'n';
                break;
            
            default:
                printf("Opcion invalida\n");
                break;
        }

        if(seguir == 's')
        {
            // Limpia cualquier caracter previo (incluye el \n que deja scanf)
            while ((c = getchar()) != '\n' && c != EOF);

            printf("Presiona ENTER para continuar...");
            fflush(stdout);
            getchar();
        }
    }
    
    
    printf("Saliendo de la Aplicacion\n");
    printf("\n");

    return 0;
}
