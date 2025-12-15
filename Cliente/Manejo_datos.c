#include "Headers.h"

void Mostrar_cadena (char* cadena)
{
    for (int i = 0; cadena[i] != '\0'; i++)
    {
        if(cadena[i] == ';')
        {
            printf ("%s", "  |  ");
        }
        else
        {
            printf ("%c", cadena[i]);
        }
    }
    
    printf("\n");
}

int verificar_longitud(char* cadena, int tamaño_maximo)
{
    int longitud_cadena = strlen(cadena);

    if (longitud_cadena > 1 && longitud_cadena <=tamaño_maximo)
    {
        return 1;
    }
    else
    {
        printf("Datos invalidos\n");
        return 0;
    }

}

void Pedir_datos_del_cliente(char* datos_crudos)
{

    int i=0;

    char aux [300] = "";
    
    do
    {
        printf("Escriba la fecha de ingreso: ");
        scanf("%299s", aux);

        
    } while (!verificar_longitud(aux, MAX_FECHA_INGRESO));
    
    strcpy(&datos_crudos[i], aux);

    
    i= i + strlen(aux);// Desplazo hasta el final del dato copiado, donde hay un '\0'
    datos_crudos[i]=';';
    i++; //Me muevo despues de la coma

    do
    {
        printf("Escriba el nombre del cliente: ");
        scanf("%299s", aux);

        
    } while (!verificar_longitud(aux, MAX_NOMBRE));
    
    strcpy(&datos_crudos[i], aux);

    i= i + strlen(aux);// Desplazo hasta el final del dato copiado, donde hay un '\0'
    datos_crudos[i]=';';
    i++; //Me muevo despues de la coma

    do
    {
        printf("Escriba el apellido del cliente: ");
        scanf("%299s", aux);

        
    } while (!verificar_longitud(aux, MAX_APELLIDO));
    
    strcpy(&datos_crudos[i], aux);

    i= i + strlen(aux);// Desplazo hasta el final del dato copiado, donde hay un '\0'
    datos_crudos[i]=';';
    i++; //Me muevo despues de la coma

    do
    {
        printf("Escriba la direccion del cliente: ");
        scanf("%299s", aux);

        
    } while (!verificar_longitud(aux, MAX_DIRECCION));
    
    strcpy(&datos_crudos[i], aux);

    i= i + strlen(aux);// Desplazo hasta el final del dato copiado, donde hay un '\0'
    datos_crudos[i]=';';
    i++; //Me muevo despues de la coma

    do
    {
        printf("Escriba telefono del cliente: ");
        scanf("%299s", aux);

        
    } while (!verificar_longitud(aux, MAX_TELEFONO));
    
    strcpy(&datos_crudos[i], aux);

}


void Pedir_datos_del_equipo(char* datos_crudos)
{

    int i=0;

    char aux [300] = "";
    
    do
    {
        printf("Escriba el tipo de maquina: ");
        scanf("%299s", aux);

        
    } while (!verificar_longitud(aux, MAX_TIPO));
    
    strcpy(&datos_crudos[i], aux);

    
    i= i + strlen(aux);// Desplazo hasta el final del dato copiado, donde hay un '\0'
    datos_crudos[i]=';';
    i++; //Me muevo despues de la coma

    do
    {
        printf("Escriba la marca del equipo: ");
        scanf("%299s", aux);

        
    } while (!verificar_longitud(aux, MAX_MARCA));
    
    strcpy(&datos_crudos[i], aux);

    i= i + strlen(aux);// Desplazo hasta el final del dato copiado, donde hay un '\0'
    datos_crudos[i]=';';
    i++; //Me muevo despues de la coma

    do
    {
        printf("Escriba el modelo del equipo: ");
        scanf("%299s", aux);

        
    } while (!verificar_longitud(aux, MAX_MODELO));
    
    strcpy(&datos_crudos[i], aux);

    i= i + strlen(aux);// Desplazo hasta el final del dato copiado, donde hay un '\0'
    datos_crudos[i]=';';
    i++; //Me muevo despues de la coma

    {
        printf("Escriba la falla de la maquina: ");
        scanf("%299s", aux);

        
    } while (!verificar_longitud(aux, MAX_FALLA));
    
    strcpy(&datos_crudos[i], aux);

}

void Pedir_datos_de_reparacion (char* datos_crudos)
{

    int i=0;

    char aux[300] = "";
    
    do
    {
        printf("Escriba la reparacion a efectuar: ");
        scanf("%299s", aux);

        
    } while (!verificar_longitud(aux, MAX_REPARACION));
    
    strcpy(&datos_crudos[i], aux);

    
    i= i + strlen(aux);// Desplazo hasta el final del dato copiado, donde hay un '\0'
    datos_crudos[i]=';';
    i++; //Me muevo despues de la coma

    do
    {
        printf("Indicar el presupuesto: ");
        scanf("%299s", aux);

        
    } while (!verificar_longitud(aux, MAX_PRESUPUESTO));
    
    strcpy(&datos_crudos[i], aux);

    i= i + strlen(aux);// Desplazo hasta el final del dato copiado, donde hay un '\0'
    datos_crudos[i]=';';
    i++; //Me muevo despues de la coma

    do
    {
        printf("Confirmación?: ");
        scanf("%299s", aux);

        
    } while (!verificar_longitud(aux, MAX_CONFIRMACION));
    
    strcpy(&datos_crudos[i], aux);

    i= i + strlen(aux);// Desplazo hasta el final del dato copiado, donde hay un '\0'
    datos_crudos[i]=';';
    i++; //Me muevo despues de la coma

    do
    {
        printf("Escriba si se realizo la reparacion: ");
        scanf("%299s", aux);

        
    } while (!verificar_longitud(aux, MAX_REPARADO));
    
    strcpy(&datos_crudos[i], aux);

    i= i + strlen(aux);// Desplazo hasta el final del dato copiado, donde hay un '\0'
    datos_crudos[i]=';';
    i++; //Me muevo despues de la coma

    do
    {
        printf("Fecha de egreso: ");
        scanf("%299s", aux);

        
    } while (!verificar_longitud(aux, MAX_FECHA_EGRESO));
    
    strcpy(&datos_crudos[i], aux);

}
