#include <stdio.h>
#include <stdlib.h>

#include "hashtables.h"

int check_arg(int arg) {
    if (arg < 0) return 0;
    while (arg > 1) {
        if (arg % 2) return 0;
        arg /= 2;
    }
    return 1;
}

HashTable *init_hashtable(int buffer_size, HASHTABLES_ERR *err) {

    if (!check_arg(buffer_size)) {
        fprintf(stderr, "Invalig argument: buffer_size\n"
                        "Consider that buffer_size should be a pow of 2\n");
        if (err != NULL)
            *err = EINVARG;
        return NULL;
    }

    HashTable *my_table = (HashTable *) malloc(sizeof(HashTable));

    if (my_table == NULL) {
        fprintf(stderr, "Not enough memory\n");
        if (err != NULL)
            *err = EMALLOC;
        return NULL;
    }

    my_table->size = 0;
    my_table->bufferSize = buffer_size;
    my_table->nodes = (Node **) malloc(buffer_size * sizeof(Node *));

    if (my_table->nodes == NULL) {
        fprintf(stderr, "Not enough memory\n");
        if (err != NULL)
            *err = EMALLOC;
        return NULL;
    }


    for (int i = 0; i < buffer_size; ++i) {
        my_table->nodes[i] = NULL;
    }
    *err = ESUCCESS;
    return my_table;
}

void remove_hashtable(HashTable *table, HASHTABLES_ERR *err) {
    if (table == NULL) {
        fprintf(stderr, "Invalig argument: hashtable\n");
        if (err != NULL)
            *err = EINVARG;
        return;
    }

    for (int i = 0; i < table->bufferSize; ++i) {
        if (table->nodes[i] != NULL) {
            free(table->nodes[i]);
        }
    }
    if (table->nodes != NULL) {
        free(table->nodes);
    }
    free(table);
    *err = ESUCCESS;
}

int hash(int key, int buffer_size) {
    return abs(key) % buffer_size;
}

int find_key(const int key, HashTable *table, HASHTABLES_ERR *err) {

    if (table == NULL) {
        fprintf(stderr, "Invalig argument: hashtable\n");
        if (err != NULL)
            *err = EINVARG;
        return 0;
    }

    int hashed = hash(key, table->bufferSize);
    int i = 0;
    while (table->nodes[hashed] != NULL && i < table->bufferSize) {
        if (!table->nodes[hashed]->deleted && table->nodes[hashed]->data == key) {
            *err = ESUCCESS;
            return 1;
        }
        i++;
        hashed += (i * i + i) / 2;
        hashed %= table->bufferSize;
    }

    *err = ESUCCESS;
    return 0;
}


void rehash(HashTable *table, HASHTABLES_ERR *err) {

    if (table == NULL) {
        fprintf(stderr, "Invalig argument: hashtable\n");
        if (err != NULL)
            *err = EINVARG;
        return;
    }

    Node **tmp = table->nodes;
    table->bufferSize *= 2;
    table->size = 0;
    table->nodes = (Node **) malloc(table->bufferSize * sizeof(Node *));

    if (table->nodes == NULL) {
        fprintf(stderr, "Not enough memory\n");
        if (err != NULL)
            *err = EMALLOC;
        return;
    }

    for (int i = 0; i < table->bufferSize; ++i) {
        table->nodes[i] = NULL;
    }

    for (int i = 0; i < table->bufferSize / 2; ++i) {
        if (tmp[i] != NULL) {
            if (!tmp[i]->deleted)
                insert_key(tmp[i]->data, table, err);
            free(tmp[i]);
        }
    }
    free(tmp);
    *err = ESUCCESS;
}

void insert_key(const int key, struct HashTable *table, HASHTABLES_ERR *err) {

    if (table == NULL) {
        fprintf(stderr, "Invalig argument: hashtable\n");
        if (err != NULL)
            *err = EINVARG;
        return;
    }

    if (find_key(key, table, err)) {
        fprintf(stderr, "The key found in hashtable already\n");
        if (err != NULL)
            *err = EINSERT;
        return;
    }

    if (3 * table->bufferSize <= 4 * (table->size + 1))
        rehash(table, err);

    int hashed = hash(key, table->bufferSize);
    int i = 0;
    while (i < table->bufferSize) {
        if (table->nodes[hashed] == NULL) {
            table->nodes[hashed] = (Node *) malloc(sizeof(Node));

            if (table->nodes == NULL) {
                fprintf(stderr, "Not enough memory\n");
                if (err != NULL)
                    *err = EMALLOC;
                return;
            }

            table->nodes[hashed]->data = key;
            table->nodes[hashed]->deleted = 0;
            table->size++;
            *err = ESUCCESS;
            return;
        } else if (table->nodes[hashed]->deleted) {
            table->nodes[hashed]->data = key;
            table->nodes[hashed]->deleted = 0;
            table->size++;
            *err = ESUCCESS;
            return;
        }
        i++;
        hashed += (i * i + i) / 2;
        hashed %= table->bufferSize;
    }
}

void remove_key(const int key, struct HashTable *table, HASHTABLES_ERR *err) {

    if (table == NULL) {
        fprintf(stderr, "Invalig argument: hashtable\n");
        if (err != NULL)
            *err = EINVARG;
        return;
    }

    if (!find_key(key, table, err)) {
        fprintf(stderr, "The key was not found in hashtable\n");
        if (err != NULL)
            *err = EREMOVE;
        return;
    }

    int hashed = hash(key, table->bufferSize);
    int i = 0;

    while (i < table->bufferSize) {
        if (!table->nodes[hashed]->deleted && table->nodes[hashed]->data == key) {
            table->nodes[hashed]->deleted = 1;
            table->size--;
            *err = ESUCCESS;
            return;
        }
        i++;
        hashed += (i * i + i) / 2;
        hashed %= table->bufferSize;
    }
}

void print_table(HashTable *table, HASHTABLES_ERR *err) {
    if (table == NULL) {
        fprintf(stderr, "Invalig argument: hashtable\n");
        if (err != NULL)
            *err = EINVARG;
        return;
    }

    if (table->size == 0) {
        printf("No elements in hashtable\n");
        return;
    }

    for (int i = 0; i < table->bufferSize; ++i) {
        if (table->nodes[i] != NULL && !table->nodes[i]->deleted) {
            printf("%d ", table->nodes[i]->data);
        }
    }
    printf("\n");
    *err = ESUCCESS;
}
