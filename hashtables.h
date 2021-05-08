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

int check_arg(int arg);

HashTable *init_hashtable(int buffer_size);

void remove_hashtable(HashTable *table);

int hash(int key, int buffer_size);

int find_key(int key, HashTable *table);

void rehash(HashTable *table);

void insert_key(int key, HashTable *table);

void remove_key(int key, HashTable *table);


#endif
