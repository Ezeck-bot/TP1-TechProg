// Vous devez ajouter ce #pragma a tous vos fichiers .h de votre projet.
// Il garantit que le fichier "header" n'est inclus qu'une seule fois par compilation,
// ce qui evite les erreurs de redefinition et les conflits de symboles.
#pragma once
#include <assert.h>

void* allocate(size_t size);

typedef struct Node Node;

struct Node {
	void* data;
	struct Node* next;
};

typedef struct item_t {
	char name[256];
	int value;
} Item;


// Vous devez definir les structures et fonctions que vous voulez exposer dans les "headers"
// Si jamais vous avez des fonctions avec des noms commun, vous devez les prefixer pour eviter des conflits de symboles
// Le prefix peut etre le nom de votre projet, exemple: forhonor_nom_de_fonction
//int monprojet_add(int a, int b);


// Lorsqu'une fonction n'a pas de parametre, mettre void entre les parentheses.
//void monprojet_ditbonjour(void);

Node* ajouterItem(Node* head, Item* newData);

void afficherInventaire(Node* head);

int compterItems(Node* head);

Item* parSonNom(Node* head, char* name);

Item* parSaPosition(Node* liste, int index);

Node* ajouterItemAleatoire(Node* inventaire, Node* listeItems);

Node* removeByName(Node* head, char* name);

void sort(Node* head);