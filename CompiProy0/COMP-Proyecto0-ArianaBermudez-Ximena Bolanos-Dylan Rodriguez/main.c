#include <stdio.h>
#include <stdlib.h>

int parada;
int main()
{

    /*FILE *file;
    printf("Ruta del archivo:\n");
    char NombreArchivo[50];
    gets(NombreArchivo);
    file = fopen(NombreArchivo, "r");

    if (file) {
        //system_goal();
        while (parada==0)
            scanner(file);
        fclose(file);

    }else{
    printf("No se pudo leer el nombre del archivo.");
    }*/


/* pruebas ari
  printf("***");
  enter("null");
  printf("***");

  enter("holi");
  enter("holi");
  verSymbol_table();
*/
    leerArchivo();
    if(seLeyoArchivo()){

        system_goal();
        //while (parada==0)
        //    scanner();
        //scanner();
        cerrarArchivo();
    }
    else{
        printf("No se pudo leer el archivo.");
    }










    return 0;
}
