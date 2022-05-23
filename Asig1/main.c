#include <stdio.h>
#include <stdlib.h>

void insertar()
{
    printf("Proceso de insercion...\n");
}

void eliminar()
{
    printf("Proceso de eliminacion...\n");
}

void consultar()
{
    printf("Proceso de consulta...\n");
}

void actualizar()
{
    printf("Proceso de actualizacion...\n");
}

int main()
{
    char program_version[] = "v0.1";
    char option = 'r';
    while(option != 'q')
    { 
        system("clear");
        printf(". : Gestion de productos %s : .\n",program_version);
        printf("Operaciones para resgistros:\n");
        printf("i. para Insertar.\n");
        printf("c. para Consultar.\n");
        printf("a. para Actualizar.\n");
        printf("e. para Eliminar.\n");
        printf("q. Salir del programa de gestion.\n");
        printf(" > ");
        
        option = getchar();
        
        while(getchar() != '\n');
            switch(option) {
                case 'i': insertar(); break;
                case 'c': consultar(); break;
                case 'a': actualizar(); break;
                case 'e': eliminar(); break;
                case 'q': break;
            }
    }

}


