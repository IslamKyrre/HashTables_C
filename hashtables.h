#ifndef _HASHTABLES_H_
#define _HASHTABLES_H_

typedef struct Node {
    int data;
    int deleted;
} Node;

typedef struct HashTable {
    int bufferSize;
    int size;
    Node **nodes;
} HashTable;

typedef enum {
    ESUCCESS = 0,
    EMALLOC,
    EINSERT,
    EREMOVE,
    EINVARG
} HASHTABLES_ERR;

int check_arg(int arg);

HashTable *init_hashtable(int buffer_size, HASHTABLES_ERR *err);

void remove_hashtable(HashTable *table, HASHTABLES_ERR *err);

int hash(int key, int buffer_size);

int find_key(int key, HashTable *table, HASHTABLES_ERR *err);

void rehash(HashTable *table, HASHTABLES_ERR *err);

void insert_key(int key, HashTable *table, HASHTABLES_ERR *err);

void remove_key(int key, HashTable *table, HASHTABLES_ERR *err);


#endif
