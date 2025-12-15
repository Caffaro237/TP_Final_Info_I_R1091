#include "Headers.h"

void CierreCliente(int signal)
{
    (void)signal;
    char msg[] = "Cliente desconectado\n";
    write(1, msg, sizeof(msg) - 1); // stdout
}