//Bonne pratique, pour les includes systemes toujours utiliser <> et "" pour les includes de votre projet.
#include <stdio.h>
#include "definition.h"


int main(int argc, char** argv){
    printf("Bienvenue dans mon application nommer monprojet !\n");
    printf("20 plus 22 donne: %d\n", monprojet_add(20,22));
    monprojet_ditbonjour();
}