#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define p printf

typedef struct{
    int legajo;
    char nombre[30];
    int nota;
} Alumno;

void linea(int);
void mostrarArchivo(FILE*, char*);
void guardarArchivoB(FILE*, char*, char*);
void mostrar(FILE*);

int main(){
    FILE *file;
    FILE *datFile;
    char *textFileName = "textoParaSeparar.txt";
    char *datFileName = "notas.dat";

    if((datFile = fopen(datFileName, "wrb+")) == NULL){
        printf("\nno se encontro %s, lo vamos a abrir y crear por primera vez\n",datFileName);
        datFile = fopen(datFileName, "wb+");
    } else{
        printf("\nEl archivo: %s, ya existia lo abrimos para lectura escritura\n",datFileName);
    }

    //mostrarArchivo(file, textFileName);
    guardarArchivoB(datFile, datFileName, textFileName);
    mostrar(datFile);
    fclose(file), fclose(datFile);
}

void linea(int x)
{
 int i;
	//p("");
	for(i=1;i<x;i++)
	 p("*");
// p("\n");
}

// Primer ejercicio
void mostrarArchivo(FILE* file, char* fileName){
    int len = 80;
    char *f;
    char texto[len];
    int num_1;
    char *nombre;
    int num_2;

    if((f=fopen(fileName, "r"))==NULL){
        p("Error: El archivo no existe");
    } else{
        while(fgets(texto, len, f)!=NULL){
            num_1 = atoi(strtok(texto, ","));
            nombre = strtok(NULL, ",");
            num_2 = atoi(strtok(NULL, ","));
            p("%i, %s, %i\n", num_1, nombre, num_2);
        }
    }
}

// Cuarto ejercicio = guardar en archivo binario
void guardarArchivoB(FILE* datFile, char* datFileName, char* textFileName){
    Alumno alu;
    int len = 80;
    char* f;
    char texto[len];
    int legajo;
    char* nombre;
    int nota;

    if((f=fopen(textFileName, "r"))==NULL){
        p("Error: El archivo no existe");
    } else{
        while(fgets(texto, len, f)!=NULL){
            legajo = atoi(strtok(texto, ","));
            nombre = strtok(NULL, ",");
            nota = atoi(strtok(NULL, ","));

            alu.legajo = legajo;
            strcpy(alu.nombre, nombre);
            alu.nota = nota;

            fseek(datFile, 0L, SEEK_END);
            fwrite(&alu, sizeof(alu), 1, datFile);
        }
    }
}

void mostrar (FILE *datFile){
    Alumno alu;

    rewind(datFile);
	system("cls");
	linea(80);
    p("\n\t\tDATOS DE LOS ALUMNOS\t\t\n");
    linea(80);
    p("\nLEGAJO\t\tNOMBRE\t\t\tNOTA\n");
    fread(&alu, sizeof(alu), 1, datFile);
    while(!feof(datFile)){
        p("\n%i\t\t%-10s\t\t%i\n", alu.legajo, alu.nombre, alu.nota);
        fread(&alu, sizeof(alu), 1, datFile);
    }
}
