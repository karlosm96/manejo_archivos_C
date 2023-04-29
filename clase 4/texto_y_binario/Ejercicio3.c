#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define p printf

typedef struct
{
	int cod_chof;
	char nom_chof[30];
	int km;
	int rec;
} registro;

void cargar(FILE *);
void mostrar(FILE *);
void linea(int);

int main(){
	FILE *binario;
	char *nombin = "choferes.dat";
	if((binario=fopen(nombin,"rb+"))==NULL)
    {
        printf("\nno se encontro %s, lo vamos a abrir y crear por primera vez\n",nombin);
        binario=fopen(nombin,"wb+");
    }
	else
    {
         printf("\nno El archivo: %s, ya existia lo abrimos para lectura escritura\n",nombin);
    }

	cargar(binario);
	mostrar(binario);
	fclose(binario);
	return 0;
}

void linea(int x){
 int i;
	//p("");
	for(i=1;i<x;i++)
	 p("*");
// p("\n");
}

void cargar(FILE *x){
    registro reg;
    int ignite = 1;
    int codChofer;
    char* nomChofer;
    int km;
    int rec;

    while(ignite){
        p("\n");
        linea(80);
        p("\nPorfavor ingrese el codigo del chofer\n");
        scanf("%i", &codChofer);

        if(codChofer==0){
            break;
        }

        fflush(stdin);
        p("Porfavor ingrese el nombre del chofer\n");
        gets(nomChofer);
        p("Porfavor ingrese la cantidad de Kilometros recorridos\n");
        scanf("%i", &km);
        fflush(stdin);
        p("\nPara finalizar la carga de datos ingrese ['0'] en codigo de chofer\n");

        reg.cod_chof = codChofer;
        strcpy(reg.nom_chof, nomChofer);
        reg.km = km;
        reg.rec = km * 200;

        fseek(x, 0L, SEEK_END);
        fwrite(&reg, sizeof(reg), 1, x);
    }

}

void mostrar (FILE *x){
    registro reg;

    rewind(x);
    system("cls");
    p("\n\t\tDATOS DE LOS CHOFERES\t\t\n");
    linea(80);
    p("\nCODIGO\t\tNOMBRE\t\tKM RECORRIDOS\t\tDINERO RECOLECTADO\n");
    fread(&reg, sizeof(reg), 1, x);
    while(!feof(x)){
        p("\n\t%i\t\%-10s\t\t%i\t\t%i\n", reg.cod_chof, reg.nom_chof, reg.km, reg.rec);
        fread(&reg, sizeof(reg), 1, x);
    }
}
