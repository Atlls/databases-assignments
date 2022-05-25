#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// tolower
/*
 *  size_t len = strlen(str);
    char *lower = calloc(len+1, sizeof(char));

    for (size_t i = 0; i < len; ++i) {
        lower[i] = tolower((unsigned char)str[i]);
    }
 *
 * */

void insertar()
{

    int DESCRIPCION_LEN = 30; // ?
    char descripcion[DESCRIPCION_LEN];
    float costo, precio;
    int cantidad;
    int codigo, i;

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
    //| Setear descripcion todo en mayusculas
    for (i=0;i<=strlen(descripcion)-2;i++)
    {
        if (descripcion[i] == ' ')
        {
            descripcion[i] = '-';
        }
    }
    strtok(descripcion, "\n");

    /* File saving */
    /* cant_registros codigo_registos
     * n              0 ... 9999
     *
     * codigo - descripcion - costo - precio - cantidad
     * */

    int n = 0, index_codigo = 0;
    char linea[100];

    /* Copiar data.txt -> aux_data.txt */

    FILE* aux_archivo = fopen("aux_data.txt","w");
    FILE* archivo = fopen("data.txt","r+");

    fscanf(archivo,"%i %i\n",&n,&index_codigo);

    for(i = 0; i < n; i++)
    {
        //| Si linea[descripcion] == descripcion No Insertes
        fgets(linea,90,archivo);
        printf("%s",linea);
        fprintf(aux_archivo,"%s",linea);
        strcpy(linea,"");
    }

    fclose(archivo);
    fclose(aux_archivo);

    /* Abrir data.txt en Write y aplicar el control de indice y la insercion */

    archivo = fopen("data.txt","w"); // Reset
    aux_archivo = fopen("aux_data.txt","r+");

    // Indices de control
    n++;
    index_codigo++;
    fprintf(archivo, "%i %i\n", n,index_codigo);
    
    // Copiar todo los registros
    for(i = 0; i < n-1; i++)
    {
        fgets(linea,100,aux_archivo);
        fputs(linea,archivo);
        strcpy(linea,"");
    }

    // Insertando nuevo resgistro
    codigo = index_codigo;
    fprintf(archivo,"%i %s %3.3f %3.3f %i\n",codigo,descripcion,costo,precio,cantidad);

    fclose(archivo);
    fclose(aux_archivo);

}

void eliminar()
{
    printf("Proceso de eliminacion...\n");
}

void consultar()
{
    char descripcion_user[30], linea[100];
    int n, enc = 0, i;

    /* Obtencion de buscando */
    printf("Consulta de producto:\n");
    printf("Inserte la Descripcion del producto:\n");
    fgets(descripcion_user, sizeof(descripcion_user), stdin);

    /* Manipulacion */

    // Obteniendo indices de control
    FILE* archivo = fopen("data.txt","r");
    fscanf(archivo,"%i\n",&n);
    
    // Recorrer los registros
    i = 0;
    fseek(archivo,1, SEEK_CUR);
    while(i < n && !enc)
    {
        strcpy(linea,"");
        fgets(linea,90,archivo);
        printf("%s",linea);
        i++;
    }

}

void actualizar()
{
    printf("Proceso de actualizacion...\n");
}

int main()
{
    char program_version[] = "v0.2";
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
