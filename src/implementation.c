#include "definition.h"

#include <stdio.h>

// Il est important de faire l'implementation de vos fonctions dans un fichier .c
// Si vous le faites dans le fichier "header", chaque fichier qui l'include va compiler l`implementation
// et cela causeras des definitions de symboles multiples.

int monprojet_add(int a, int b){
    return a+b;
}

void monprojet_ditbonjour(void){
    printf("Hello Sailor !\n");
}