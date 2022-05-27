#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int strspace(char *string)
{
    int length = strlen(string), i = 0;
    while(string[i] != ' ' && i < length)
        i++;
    return i == length ? -1 : i;
}

// !! No tiene limitadores
char* strslice(char *string, int inicio, int final)
{
    char* out[100];
    int length = strlen(string), i = 0, j = 0;
    while(i < final && length > final)
    {
        if(i > inicio)
        {
            printf("%c",string[i]);
            out[j] += string[i];
            j++;
        }
        i++;
    }
    return *out;
}

void arreglar_formato(char *cadena)
{
    int length = strlen(cadena), i;

    // Reemplazar espacios
    for (i=0;i<=length-2;i++)
        if (cadena[i] == ' ')
            cadena[i] = '-';
    strtok(cadena, "\n");

    // Reemplazar espacios
    for (i = 0; i < length; i++)
        cadena[i] = tolower(cadena[i]);
}

int es_descripcion(char* cadena, char* linea)
{
    int enc = 0, i;
    
    // Localizacion del primer espacio en formato de registro
    i = 0;
    while(linea[i] != ' ')
        i++;
    i++;

    // Comparacion
    int j = 0;
    while(linea[i] != ' ' && !enc)
    {
        if(linea[i] != cadena[j])
            enc = 1;
        i++;
        j++;
    }
    return !enc;
}

// Retorna el indice donde encontro un espacio.
// Imprime letra a letra hasta encontrar un espacio.
int print_dato(char* linea, int i)
{
    int length = strlen(linea);
    while(linea[i] != ' ' && i < length)
    {
        printf("%c",linea[i]);
        i++;
    }

    i++;
    return i;
}

void print_regitro(char* linea)
{
    // Codigo
    int i = 0;
    printf("\nCodigo de Identidicacion: ");
    i = print_dato(linea,i);
    printf(" ~\nDescripcion del producto: ");
    i = print_dato(linea,i);
    printf(" ~\nCosto: ");
    i = print_dato(linea,i);
    printf(" ~\nPrecio: ");
    i = print_dato(linea,i);
    printf(" ~\nCantidad de unidades: ");
    i = print_dato(linea,i);
}

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

    arreglar_formato(descripcion);

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
        //printf("%s",linea);
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
    char descripcion_user[30], linea[100]; 
    int i, enc = 0, n, index_codigo;

    /* Obtencion de producto */
    printf("Elimnar un registro:\n");
    printf("Inserte la Descripcion del producto:\n");
    fgets(descripcion_user, sizeof(descripcion_user), stdin);
    printf("Buscando dicho producto...\n");
    arreglar_formato(descripcion_user);

    // Obteniendo indices de control
    FILE* aux_archivo = fopen("aux_data.txt","w");
    FILE* archivo = fopen("data.txt","r");
    fscanf(archivo,"%i %i\n",&n, &index_codigo);
    
    // Recorrer los registros y respaldar
    i = 0;
    while(i < n)
    {
        fgets(linea,100,archivo);
        //printf("%s**\n",linea);

        if(es_descripcion(descripcion_user,linea))
            enc = 1;
        else
            fprintf(aux_archivo,"%s",linea);
        i++;
    }

    fclose(archivo);
    fclose(aux_archivo);

    // Salida
    if(enc)
    {
        // Actualizar indices de control y acualizar achivo principal
        FILE* aux_archivo = fopen("aux_data.txt","r");
        FILE* archivo = fopen("data.txt","w");

        n--;
        fprintf(archivo, "%i %i\n", n,index_codigo);

        // Copiar todo los registros
        for(i = 0; i < n; i++)
        {
            fgets(linea,100,aux_archivo);
            //printf("%s*\n",linea);
            fputs(linea,archivo);
            strcpy(linea,"");
        }

        fclose(archivo);
        fclose(aux_archivo);

        printf("El registro \"%s\" ha sido eliminado.", descripcion_user);
    }
    else
    {
        printf("La Descripcion %s no está registrado.", descripcion_user);
    }
}

void consultar()
{
    char descripcion_user[30], linea[100];
    int n, enc = 0, i;

    /* Obtencion de buscando */
    printf("Consulta de producto:\n");
    printf("Inserte la Descripcion del producto:\n");
    fgets(descripcion_user, sizeof(descripcion_user), stdin);
    printf("Buscando dicho producto...\n");

    /* Manipulacion */

    arreglar_formato(descripcion_user);

    // Obteniendo indices de control
    FILE* archivo = fopen("data.txt","r");
    fscanf(archivo,"%i\n",&n);
    
    // Recorrer los registros
    i = 0;
    fseek(archivo,2, SEEK_CUR); // Mover malandristicamente
    while(i < n && !enc)
    {
        fgets(linea,90,archivo);
        if(es_descripcion(descripcion_user,linea))
            enc = 1;
        i++;
    }

    fclose(archivo);

    // Salida
    if(enc)
    {
        printf("Registro encontrado:\n");
        print_regitro(linea);
    }
    else
    {
        printf("\nRegistro No encontrado:\n");
    }

}

void actualizar()
{
    char descripcion_user[30], linea[100]; 
    float costo, precio;
    int i, index_enc = 0, n, index_codigo, cantidad;

    /* Obtencion de producto */
    printf("Actualizar un registro:\n");
    printf("    Inserte la Descripcion del producto:\n");
    printf("         > ");
    fgets(descripcion_user, sizeof(descripcion_user), stdin);
    printf("    Inserte las cantidades de dicho producto a acualizar.\n");
    printf("    Inserte -1 para saltar campo:\n");
    printf("        Costo en Bs:\n");
    printf("                > ");
    scanf("%f", &costo);
    printf("        Precio de Venta en Bs:\n");
    printf("                > ");
    scanf("%f", &precio);
    printf("        Cantidad Nueva:\n");
    printf("                > ");
    scanf("%i", &cantidad);


    /* Buscar registro a acualizar */
    FILE* aux_archivo = fopen("aux_data.txt","w");
    FILE* archivo = fopen("data.txt","r");

    // Indices de control
    fscanf(archivo,"%i\n",&n);

    i = 0;
    fseek(archivo,2, SEEK_CUR); // Mover malandristicamente
    while(i < n)
    {
        fgets(linea,100,archivo);
        fprintf(aux_archivo,"%s",linea);

        if(es_descripcion(descripcion_user,linea))
            index_enc = i;
        i++;
    }

    fclose(archivo);
    fclose(aux_archivo);

    /* Acualizacion de registro */
    if(index_enc > 0)
    {
        char aux_costo[5];
        printf("%s",linea);
        printf("%i ~\n",strspace(linea)); 

        // Copiar todos los registros hasta al anterior al selecionado
        aux_archivo = fopen("aux_data.txt","r");
        //archivo = fopen("data.txt","w");
        
        fseek(aux_archivo,0, SEEK_CUR); // Mover malandristicamente
        printf("%i ~~\n",i);
        while(index_enc > 0)
        {
            fgets(linea,100,aux_archivo);
            printf("%s",linea);
            index_enc--;
        }
        
        // Proceso de reemplazo de linea
        int aux;
        fgets(linea,100,aux_archivo);
        aux = strspace(linea);
        costo = costo != -1 ? costo: -2;
        printf("%f", costo);


        // * Obtener indice del primer espacio (antes del nombre).
        // * Sumar ese indice con la longitud del nombre, obtenemos
        // el segundo espacio.
        // * Si los campos son != a -1, reemplazarlos (float/int -> Cadena)
    }
    else
    {
        printf("qk pelua");
    }
}

int main()
{
    char program_version[] = "v0.4.1";
    char option = 'r';

    
    while(option != 'q')
    { 
        printf("\n. : Gestion de productos %s : .\n",program_version);
        printf("Operaciones para resgistros:\n");
        printf("i. para Insertar.\n");
        printf("c. para Consultar.\n");
        printf("a. para Actualizar.\n");
        printf("e. para Eliminar.\n");
        printf("q. Salir del programa de gestion.\n");
        printf("%s~~~\n",strslice("Machetico",2,5));
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
