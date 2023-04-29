/*
Dado un lote de numeros generados al azar entre 1 y 200 ,se necesitan generar 20 numeros primos
al llegar a ese limite de 20 se debera frenar esa generacion .
Al momento que vamos genrando los numeros primos ,los vamos guardanado en un archivo binario, para luego mostrar
la generacion de 2 archivos .
Los numeros primos generados no pueden repetirse en el archivo .
Luego  generar un archivo binario ordenado utilizando el siguiente struct

typedef struct
{ int cod;
  int np;
 } registro;

 ej  1-17      	5-11
    2-47		1-17
    3-53		4-19
    4-19       2-47
    5-11       3-53
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
#define p printf

typedef struct
{ int cod;
  int np;
 } Registro;

void generarNumerosPrimos(int, int[]);
void grabarArchivo(char*, int, int[], Registro[], int);
void sortVect(int, Registro[]);
void setPrimos(int, int[], int[]);
void leerArchivo(char*, int);

void linea(int);

void main(){
    char* nombreArchivo_primosUnicos = "primosUnicos.dat";
    char* nombreArchivo_primosUnicos_struc = "primosUnicos_struct.dat";
    int lenVector = 20;
    int numerosPrimos[lenVector];
    int setNumerosPrimos[lenVector];
    Registro setPrimosStruct[20];
    int i;
    int j = 1; //Indica la posicion del numero en el vector

    //Genera numeros primos y se escriben en un archivo sin repetir
    linea(80);
    linea(80);
    generarNumerosPrimos(lenVector, numerosPrimos);
    setPrimos(lenVector, numerosPrimos, setNumerosPrimos);
    grabarArchivo(nombreArchivo_primosUnicos, lenVector, setNumerosPrimos, setPrimosStruct, 1);
    leerArchivo(nombreArchivo_primosUnicos, 1);
    linea(80);
    linea(80);


    //Cargar vector de struct
    for(i=0; i<lenVector; i++){
        if(setNumerosPrimos[i]!=0){
            setPrimosStruct[i].np = setNumerosPrimos[i];
            setPrimosStruct[i].cod = j;
            j++;
        } else{
            setPrimosStruct[i].np = 0;
            setPrimosStruct[i].cod = 0;
        }
    }

    //Grabar en archivo binario un vector de estructuras con un set de numeros primos
    sortVect(lenVector, setPrimosStruct);
    grabarArchivo(nombreArchivo_primosUnicos_struc, lenVector, setNumerosPrimos, setPrimosStruct, 2);
    leerArchivo(nombreArchivo_primosUnicos_struc, 2);

}

void leerArchivo(char* nombre, int option){
    FILE* file;
    Registro reg;
    int registro;
    int i = 0;

    switch(option){
        //Leer archivo que no contiene estructuras
        case 1:
            if((file=fopen(nombre, "rb+"))!= NULL){
                rewind(file);
                fread(&registro, sizeof(int), 1, file);
                while(!feof(file)){
                    p("\n-- %i", registro);
                    fread(&registro, sizeof(int), 1, file);
                    i++;
                }
                fclose(file);

            } else{
                p("El archivo %s no existe", nombre);
            }
            break;

        //Leer archivo con estructura
        case 2:
            if((file=fopen(nombre, "rb+"))!= NULL){
                rewind(file);
                fread(&reg, sizeof(Registro), 1, file);
                while(!feof(file)){
                    p("\n## %i || %i", reg.cod, reg.np);
                    fread(&reg, sizeof(Registro), 1, file);
                    i++;
                }
                fclose(file);

            } else{
                p("El archivo %s no existe", nombre);
            }
            break;

        default:
            p("Error: Opcion equivocada");
    }


}

void grabarArchivo(char* nombre, int len, int vec[len], Registro vec_reg[len], int opcion){
    FILE* file;
    int registro;
    int i=0;

    switch(opcion){
        //Grabar archivo que no contiene estructuras
        case 1:
            p("Se ha contruido el archivo %s", nombre);
            file = fopen(nombre, "wb+");

            rewind(file);
            for(i = 0; i < len; i++){
                if(vec[i] > 0){
                    fseek(file, 0L, SEEK_END);
                    fwrite(&vec[i], sizeof(int), 1, file);
                }
            }
            fclose(file);
            break;

        //Grabar archivo que si contiene estructura
        case 2:
             p("Se ha contruido el archivo %s", nombre);
            file = fopen(nombre, "wb+");

            rewind(file);
            for(i = 0; i < len; i++){
                if(vec_reg[i].np > 0){
                    fseek(file, 0L, SEEK_END);
                    fwrite(&vec_reg[i], sizeof(Registro), 1, file);
                }
            }
            fclose(file);
            break;

        default:
            p("Error: Opcion equivocada");
    }
}

void sortVect(int n, Registro arr[n]){
    int m, i;
    Registro k;
        for (m = 1; m < n; m++) {
            k = arr[m];
            i = m - 1;

            //Ordenamiento a partir de los numeros primos en la estructura
            while (i >= 0 && arr[i].np > k.np) {
                arr[i + 1] = arr[i];
                i = i - 1;
            }
        arr[i + 1] = k;
    }
}

void setPrimos(int len, int vec_contaminado[len], int vec_limpio[len]){
    int i, j, t;
    int cleanLen = 0;
    int flag;

    for( t = 0; t < len; t++){
        vec_limpio[t] = 0;
    }

    vec_limpio[0] = vec_contaminado[0];
    for(i = 1; i < len; i++){
        flag = 0;
        for(j = 0; j < i; j++){
            if(vec_contaminado[i] == vec_limpio[j]){
                flag = 1;
            }
        }
        if(!flag){
            vec_limpio[i] = vec_contaminado[i];
        }
    }
}

void generarNumerosPrimos(int cantidad, int numerosPrimos[]){
    int i;
    int numero;
    srand(time(NULL));
    for(i = 0; i < cantidad; i++){
        numero = (rand() % (200 - 1 + 1));
        if(esPrimo(numero)){
            numerosPrimos[i] = numero;
        } else{
            i--;
        }
    }
}

int esPrimo(int numero){
    int j;

    switch(numero){
    case 0:
        return 0;
        break;
    case 1:
        return 0;
        break;
    case 2:
        return 1;
        break;
    case 4:
        return 0;
        break;
    default:
        for(j = 2; j < numero/2; j++){
            if(numero % j == 0){
                return 0;
            }
        }
        return 1;
        break;
    }
}

void linea(int x)
{
 int i;
	//p("");
	p("\n");
	for(i=1;i<x;i++)
    p("*");
    p("\n");
}


