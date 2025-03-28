#include <stdio.h>
#include <string.h>
#include <stdbool.h>;
#include <time.h>;

#include "definition.h"

// Il est important de faire l'implementation de vos fonctions dans un fichier .c
// Si vous le faites dans le fichier "header", chaque fichier qui l'include va compiler l`implementation
// et cela causeras des definitions de symboles multiples.

Node* ajouterItem(Node* head, Item* newData) {


    if (head == NULL)
        return NULL;

    if(head->data == NULL){
        head->data = newData;
        return head;
    }

    Node* nouveau = allocate(sizeof(Node));
    nouveau->data = newData;
    nouveau->next = NULL;

    Node* currentNode = head;
    if (currentNode->next != NULL)
        nouveau->next = currentNode->next;

    currentNode->next = nouveau;

    return nouveau;
}

void afficherInventaire(Node* head) {
    /*Node* node = head;
    while (node != NULL) {
        Item* item = (Item*)node->data;
        printf("%s, %d\n", item->name, item->value);
        node = node->next;
    }*/
    while (head != NULL)
    {
        Item* item = (Item*)head->data;
        printf("%s, %d\n", item->name, item->value);
        head = head->next;
    }
}

int compterItems(Node* head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}

Item* parSonNom(Node* head, char* name) {
    Node* node = head;
    while (node != NULL) {
        Item* item = (Item*)node->data;
        if (strcmp(item->name, name) == 0)
        {
            return item;
        }
        node = node->next;
    }
    return NULL;
}

Item* parSaPosition(Node* head, int index) {
    int i = 0;
    while (head != NULL) {
        if (i == index) {
            return (Item*)head->data;
        }
        head = head->next;
        i++;
    }
    return NULL; 
}

Node* ajouterItemAleatoire(Node inventaire, Node* listeItems) {
    int count = compterItems(listeItems);
    if (count == 0) return &inventaire;

    int randomIndex = rand() % count;
    Item* itemChoisi = parSaPosition(listeItems, randomIndex);
    if (itemChoisi != NULL) {
        Item* itemRandom = allocate(sizeof(Item));
        strcpy(itemRandom->name, itemChoisi->name);
        itemRandom->value = itemChoisi->value;
        return ajouterItem(&inventaire, itemRandom);
    }
}

Node* removeByName(Node* head, char* name)
{
    Node* temp = head;
    Node* last = NULL;

    while (temp != NULL) {
        Item* t = (Item*)temp->data;

        if (strcmp(t->name, name) == 0)
        {
            if (last == NULL) {
                head = temp->next;
                return head;
            }
            else if (temp == head){
                head->data = last->next->data;
                last->next = NULL;
            }
            else {
                last->next = temp->next;
                return head;
            }
        }

        last = temp;
        temp = temp->next;
    }
    return head;
}

void sort(Node* head)
{


    bool echanger = true;

    while (echanger) {

        echanger = false;
        Node* temp = head;

        while (temp->next != NULL) {
            if (((Item*)temp->data)->value > ((Item*)temp->next->data)->value) {
                // �change des valeurs
                void* swap = temp->data;
                temp->data = temp->next->data;
                temp->next->data = swap;

                echanger = true;
            }
            temp = temp->next;
        }
    }
}
