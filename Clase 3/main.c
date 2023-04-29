#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define p printf

void cargarArchivo(FILE*, char*);
void mostrarArchivo(FILE*, char*);
void copiarAOtroArchivo(FILE*, char*, FILE*, char*);

int esPalindromo(char*);
void compararPalabras(FILE*, char*);

void cadenaMayorLongitud(FILE*, char*);

void main(){
    FILE* txt;
    char* txtNombre = "texto99.txt";

    FILE* txt2;
    char* txt2Nombre = "texto2.txt";


       cargarArchivo(txt, txtNombre);
    //mostrarArchivo(txt, txtNombre);
    //copiarAOtroArchivo(txt, txtNombre, txt2, txt2Nombre);
    //compararPalabras(txt, txtNombre); //tiene problemas
    //cadenaMayorLongitud(txt, txtNombre);
    //cadenaMayorLongitud(txt, txtNombre);

    return 0;
}

void cargarArchivo(FILE* txt, char* txtNombre){
    char frase[100];
    if((txt=fopen(txtNombre, "w")) == NULL){
        p("Error: archivo inexistente");

    } else{
        p("\n\n Ingrese un caracter hasta que [Enter] \n\n", txtNombre);
        while(gets(frase)!=NULL){
            fputs(frase, txt);
            fputc('\n', txt);
        }
        fclose(txt);
    }

    return 0;
}

void mostrarArchivo(FILE* txt, char* txtNombre){
    char c;
    if((txt=fopen(txtNombre, "r"))==NULL){
        p("Error: Archivo inexistente");
    } else{
        while((c = fgetc(txt))!=EOF){
            p("%c", c);
        }
        fclose(txt);
    }
}

// no se puede puede abrir un archivo para leer y otro para escribir a la vez?
void copiarAOtroArchivo(FILE* txt, char* txtNombre, FILE* txt2, char* txtNombre2){
    char c;
    if((txt=fopen(txtNombre, "r"))== NULL || (txt2=fopen(txtNombre2, "w"))== NULL){
        p("Error: El archivo a copiar no existe");
    } else{
        while((c = fgetc(txt))!=EOF){
            fputc(c, txt2);
        }
        fclose(txt);
        fclose(txt2);
    }
}

int esPalindromo(char* cadenaDeTexto){
    int i, j;
    int ln = strlen(cadenaDeTexto) - 1;

    for(i = 0, j = ln; i < j; i++, j--){
        while(i<ln && !isalnum(cadenaDeTexto[i])){
            i++;
        }
        while(j>0 && !isalnum(cadenaDeTexto[j])){
            j--;
        }
        //p("\n%c || %c", cadenaDeTexto[i], cadenaDeTexto[j]);
        if(cadenaDeTexto[i]!=cadenaDeTexto[j]){
            return 0;
        }
    }
    return 1;
}

// Opcion 2 para la funcion esPalindromo

//&& !(cadenaDeTexto[i]>='A' && cadenaDeTexto[i]<='Z') && !(cadenaDeTexto[i]>='a' && cadenaDeTexto[i]<='z')
              // && !(cadenaDeTexto[i]>='0' && cadenaDeTexto[i]<='9')

//&& !(cadenaDeTexto[j]>='A' && cadenaDeTexto[j]<='Z') && !(cadenaDeTexto[j]>='a' && cadenaDeTexto[j]<='z')
             // && !(cadenaDeTexto[j]>='0' && cadenaDeTexto[j]<='9'))


// Determinar si una frase es palindroma o no lo es
void compararPalabras(FILE* txt, char* txtNombre){
    int i = 0;
    int len = 100;
    char cadenaDeTexto[len];
    char* f;

    if((txt = fopen(txtNombre, "r"))==NULL){
        p("Error: No se pudo abrir el archivo\n");
    } else{
        while((f = fgets(cadenaDeTexto, len, txt))!=NULL){
            if(esPalindromo(cadenaDeTexto)){
                p("\n%i- La frase '%s' es palindroma",i , f);
            } else{
                p("\%i- nLa frase '%s' no es palindroma",i ,f);
            }
            i++;
        }
    }
    fclose(txt);
}

void cadenaMayorLongitud(FILE* txt, char* txtNombre){
    int i = 0;
    int len = 100;
    char posicion;
    char texto[len];
    char fraseMax[len];
    char* frase;
    int tamanho, ln = 0;
    int tamanhoMax = 0;

    if((txt=fopen(txtNombre, "r")) == NULL){
        p("No se encontro ningun archivo");
    } else{
        while((fgets(texto, len, txt)) != NULL){
            frase = strtok(texto,"\n");
            while(frase!=NULL){
                ln = 0;
                tamanho = strlen(frase);
                for(i=0; i < tamanho; i++){
                    if(frase[i]!=' '){
                        ln++;
                    }
                }
                if(ln > tamanhoMax){
                    tamanhoMax = ln;
                    strcpy(fraseMax, frase);
                }
                frase = strtok(NULL, " ");
            }
        }
        p("'%i- %s' es la frase mas larga\n", ln, fraseMax);
    }
    fclose(txt);
}


