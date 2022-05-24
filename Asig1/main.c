#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* reemplazar_espacios(char *string)
{
    printf("Culo");
    int i;
    for (i=0;i<=strlen(string)-2;i++)
    {
        if (string[i] == ' ')
        {
            string[i] = '-';
        }
    }
    return string;
}

void insertar()
{
    /* Gettings vars */

    int DESCRIPCION_LEN = 30;
    char descripcion[DESCRIPCION_LEN];
    float costo, precio;
    int cantidad;
    int codigo;

    /* Getting runtine */

    printf("Insercion de producto:\n");
    printf("Creacion de resgistro:\n");
    printf(" Descripcion del Producto : ");
    fgets(descripcion, sizeof(descripcion), stdin);
    printf(" Costo en Bs : ");
    scanf("%f", &costo);
    printf(" Precio de Venta en Bs : ");
    scanf("%f", &precio);
    printf(" Cantidad Inicial : ");
    scanf("%i", &cantidad);

    /* Data processing */

    // description's depuration
    int i;
    for (i=0;i<=strlen(descripcion)-2;i++)
    {
        if (descripcion[i] == ' ')
        {
            descripcion[i] = '-';
        }
    }
    strtok(descripcion, "\n");

    codigo = 13; // Place holder

    /* File saving:
     * codigo - descripcion - costo - precio - cantidad
     * */
    FILE *archivo = fopen("data.txt","a");
    fprintf(archivo,"%i %s %3.3f %3.3f %i\n",codigo,descripcion,costo,precio,cantidad);
    fclose(archivo);
    

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
        printf(". : Gestion de productos %s : .\n",program_version);
        printf("Operaciones para resgistros:\n");
        printf("i. para Insertar.\n");
        printf("c. para Consultar.\n");
        printf("a. para Actualizar.\n");
        printf("e. para Eliminar.\n");
        printf("q. Salir del programa de gestion.\n");
//        printf("%s",reemplazar_espacios("Puta la wea"));
        printf(" > ");
        
        option = getchar();
        
        while(getchar() != '\n'); // Una cosa kike limpia el buffer y vaina
            printf("^\n");
            switch(option) {
                case 'i': insertar(); break;
                case 'c': consultar(); break;
                case 'a': actualizar(); break;
                case 'e': eliminar(); break;
                case 'q': break;
            }
    }

}


