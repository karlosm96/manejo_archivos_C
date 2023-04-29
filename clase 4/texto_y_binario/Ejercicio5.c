#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define p printf

typedef struct{
    int legajo;
    char nombre[30];
    int nota_1;
    int nota_2;
} Alumno;

void linea(int);
FILE* abrirArchivo(char*, char*);
FILE* crearArchivo(char*, char*);
void aprovadorYdesaprovadosDat(FILE*, FILE*, FILE*);
void mostratArchivo(FILE*, int);

void main(){
    FILE *txtFile;
    char *action = "r+";
    char *txtFileName = "notas.txt";
    FILE *binAprobados = "aprobados.dat";
    FILE *binDesaprovados = "desaprovados.dat";

    txtFile = abrirArchivo(txtFileName, action);
    binAprobados = crearArchivo("aprovados.dat", "wb+");
    binDesaprovados = crearArchivo("desaprovados.doat", "wb+");
    aprovadorYdesaprovadosDat(txtFile, binAprobados, binDesaprovados);

    mostratArchivo(binAprobados, 1);
    mostratArchivo(binDesaprovados, 0);

    fclose(txtFile);
}

void linea(int x)
{
 int i;
	//p("");
	for(i=1;i<x;i++)
	 p("*");
// p("\n");
}


FILE* abrirArchivo(char* fileName, char* action){
    FILE *f;
    if((f=fopen(fileName, action))==NULL){
        p("\nError: el archivo no se pudo abrir");
    } else{
        return f;
    }
}

FILE* crearArchivo(char* fileName, char* action){
    FILE *f;
    printf("\nno se encontro '%s', lo vamos a abrir y crear por primera vez\n",fileName);
    f = fopen(fileName, action);
    return f;
}

void aprovadorYdesaprovadosDat(FILE* txtFile, FILE* binFileAprovado, FILE* binFileDesaprovado){
    Alumno alu;
    int len = 80;
    char texto[len];
    char *linea;
    int legajo;
    int nota_1;
    int nota_2;
    float promedio;
    char *nombreAlu;

    rewind(txtFile);
    system("cls");
    while((linea = fgets(texto,len,txtFile))!=NULL){
        legajo = atoi(strtok(linea, ","));
        nombreAlu = strtok(NULL, ",");
        nota_1 = atoi(strtok(NULL, ","));
        nota_2 = atoi(strtok(NULL, ","));
        promedio = (nota_1 + nota_2)/2;

        //Cargar struct alumno
        alu.legajo = legajo;
        strcpy(alu.nombre, nombreAlu);
        alu.nota_1 = nota_1;
        alu.nota_2 = nota_2;

        if(nota_1>=6 && nota_2>=6){
            fseek(binFileAprovado, 0L, SEEK_END);
            fwrite(&alu, sizeof(alu), 1, binFileAprovado);
        } else{
            fseek(binFileDesaprovado, 0L, SEEK_END);
            fwrite(&alu, sizeof(alu), 1, binFileDesaprovado);
        }
    }
}

void mostratArchivo(FILE* file, int aprobado){
    Alumno alu;
    char* titulo;

    if(aprobado){
        titulo = "APROBADOS";
    } else{
        titulo = "DESAPROVADOS";
    }

    rewind(file);
    linea(80);
    p("\n\n\t\t\tESTUDIANTES %s\n\n", titulo);
    linea(80);
    p("\nLEGAJO\t\tNOMBRE\t\t\t\tNOTA 1\t\tNOTA 2\t\n");
    fread(&alu,sizeof(alu),1,file);
    while(!feof(file))
    {
        p("\n%i\t\t%-20s\t\t%i\t\t%i\t\n",alu.legajo, alu.nombre, alu.nota_1, alu.nota_2);
        fread(&alu,sizeof(alu),1,file);
    }
}
