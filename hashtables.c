#include <stdio.h>
#include <stdlib.h>

#include "hashtables.h"

HashTable *init_hashtable(int buffer_size) {

    HashTable *my_table = (HashTable *) malloc(sizeof(HashTable));

    my_table->size = 0;
    my_table->bufferSize = buffer_size;
    my_table->nodes = (Node **) malloc(buffer_size * sizeof(Node *));

    for (int i = 0; i < buffer_size; ++i) {
        my_table->nodes[i] = NULL;
    }
    return my_table;
}

void remove_hashtable(HashTable *table) {

    for (int i = 0; i < table->bufferSize; ++i) {
        if (table->nodes[i] != NULL) {
            free(table->nodes[i]);
        }
    }
    if (table->nodes != NULL) {
        free(table->nodes);
    }
    free(table);
}

int hash(int key, int buffer_size) {
    return abs(key) % buffer_size;
}

int find_key(const int key, HashTable *table) {

    int hashed = hash(key, table->bufferSize);
    int i = 0;
    while (table->nodes[hashed] != NULL && i < table->bufferSize) {
        if (!table->nodes[hashed]->deleted && table->nodes[hashed]->data == key) {
            return 1;
        }
        i++;
        hashed += (i * i + i) / 2;
        hashed %= table->bufferSize;
    }
    return 0;
}


void insert_key(const int key, struct HashTable *table) {


    int hashed = hash(key, table->bufferSize);
    int i = 0;
    while (i < table->bufferSize) {
        if (table->nodes[hashed] == NULL) {
            table->nodes[hashed] = (Node *) malloc(sizeof(Node));


            table->nodes[hashed]->data = key;
            table->nodes[hashed]->deleted = 0;
            table->size++;
            return;
        } else if (table->nodes[hashed]->deleted) {
            table->nodes[hashed]->data = key;
            table->nodes[hashed]->deleted = 0;
            table->size++;
            return;
        }
        i++;
        hashed += (i * i + i) / 2;
        hashed %= table->bufferSize;
    }
}

void remove_key(const int key, struct HashTable *table) {


    int hashed = hash(key, table->bufferSize);
    int i = 0;

    while (i < table->bufferSize) {
        if (!table->nodes[hashed]->deleted && table->nodes[hashed]->data == key) {
            table->nodes[hashed]->deleted = 1;
            table->size--;
            return;
        }
        i++;
        hashed += (i * i + i) / 2;
        hashed %= table->bufferSize;
    }
}
