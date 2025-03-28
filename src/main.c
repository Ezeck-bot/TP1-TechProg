//Bonne pratique, pour les includes systemes toujours utiliser <> et "" pour les includes de votre projet.
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "definition.h"

int garbage = 69;
static size_t getline(char** lineptr, size_t* n, FILE* stream) {
	char* bufptr = NULL;
	char* p = bufptr;
	size_t size;
	int c;

	if (lineptr == NULL) {
		return -1;
	}
	if (stream == NULL) {
		return -1;
	}
	if (n == NULL) {
		return -1;
	}
	bufptr = *lineptr;
	size = *n;

	c = fgetc(stream);
	if (c == EOF) {
		return -1;
	}
	if (bufptr == NULL) {
		bufptr = malloc(128);
		if (bufptr == NULL) {
			return -1;
		}
		size = 128;
	}
	p = bufptr;
	while (c != EOF) {
		if ((p - bufptr) > (size - 1)) {
			size = size + 128;
			bufptr = realloc(bufptr, size);
			if (bufptr == NULL) {
				return -1;
			}
		}
		*p++ = c;
		if (c == '\n') {
			break;
		}
		c = fgetc(stream);
	}

	*p++ = '\0';
	*lineptr = bufptr;
	*n = size;

	return p - bufptr - 1;
}

Node* enregistrer_dans_struct(FILE* f) {
	char* ligne = NULL;
	size_t len = 0;
	Node* liste = allocate(sizeof(Node));
	memset(liste, 0, sizeof(Node));

	while (getline(&ligne, &len, f) != -1) {

		char label1[512] = { 0 };
		char name[512] = { 0 };
		char label2[512] = { 0 };
		int value = 0;

		garbage = sscanf(ligne, "%[^,],%[^,],%[^,],%d", label1, name, label2, &value);

		int i = 0, j = 0;
		while (name[i]) {
			if (name[i] != ' ') {
				name[j++] = name[i];
			}
			i++;
		}
		name[j] = '\0';

		Item* item = allocate(sizeof(Item));
		strcpy(item->name, name);
		item->value = value;

		ajouterItem(liste, item);
	}
	return liste;
}

#define HEAP_SIZE 2048 * 2048 * 4
static uint8_t* heap = NULL;
static size_t heap_top = 0;
void* allocate(size_t size) {
	size_t old_top = heap_top;
	heap_top += size;
	assert(heap_top <= HEAP_SIZE);
	return &heap[old_top];
}
int main(int argc, char** argv) {
	heap = (uint8_t*)malloc(HEAP_SIZE);
	assert(heap != NULL);

	FILE* input = fopen("tp1_data.csv", "r");
	/*if (input != NULL) {*/

	Node* listeItems = enregistrer_dans_struct(input);
	fclose(input);

	printf("Bienvenue dans Dave's World\n");

	Node inventaire = { 0 };


	//Aléatoire
	// Ajouter la fiole
	Item fiole = { "Fiole", 50 };
	ajouterItem(&inventaire, &fiole);

	srand(time(NULL));
	for (int i = 0; i < 3; i++) {
		ajouterItemAleatoire(&inventaire, listeItems);
	}

	int end = 0;
	while (!end)
	{
		printf("\nAppuyer sur : \n1 - pour voir l'inventaire\n2 - Pour ajouter un item dans l'inventaire\n3 - Pour enlever un item dans l'inventaire\n4 - Pour trier iventaire\n5 - Pour trouver un item relatif a son nom\n6 - Pour trouver un item relatif a sa position\n7 - Pour avoir la quantite d'items\n0 - Pour quitter\n");

		int choix;
		garbage = scanf("%d", &choix);
		if (choix == 0) {
			end = 1;
		}
		else if (choix == 1)
		{
			printf("\n**************\nINVENTAIRE :\n");
			afficherInventaire(&inventaire);
			printf("**************\n");
		}
		else if (choix == 2)
		{
			printf("Saisissez le nom de votre item : ");
			char nom_item[50] = { 0 };
			garbage = scanf("%s", &nom_item);

			printf("Saisissez la valeur de votre item : ");
			int valeur_item;
			garbage = scanf("%d", &valeur_item);

			Item* newItem = allocate(sizeof(Item));
			strcpy(newItem->name, nom_item);
			newItem->value = valeur_item;
			ajouterItem(&inventaire, newItem);
		}
		else if (choix == 3)
		{
			printf("\n**************\nSaisissez le nom de votre item : ");
			char nom_item[50] = { 0 };
			garbage = scanf("%s", &nom_item);

			removeByName(&inventaire, nom_item);

			printf("\n**************\nINVENTAIRE :\n");
			afficherInventaire(&inventaire);
			printf("**************\n");
		}
		else if (choix == 4)
		{
			sort(&inventaire);
			printf("\n**************\nINVENTAIRE TRIEE :\n");
			afficherInventaire(&inventaire);
			printf("**************\n");
		}
		else if (choix == 5)
		{
			printf("Saisissez le nom de votre item : ");
			char nom_item[50] = { 0 };
			garbage = scanf("%s", &nom_item);

			Item* itemTrouvee = parSonNom(&inventaire, nom_item);

			printf("%s, %d\n", itemTrouvee->name, itemTrouvee->value);
		}
		else if (choix == 6)
		{
			printf("Saisissez la position de l'item : ");
			int position_item;
			garbage = scanf("%d", &position_item);

			Item* itemTrouvee = parSaPosition(&inventaire, position_item - 1);

			printf("%s, %d\n", itemTrouvee->name, itemTrouvee->value);
		}
		else if (choix == 7)
		{
			printf("\n**************\nIl y'a %d dans l'inventaire.\n**************\n", compterItems(&inventaire));
		}
	}

	free(heap);
	return 0;
}