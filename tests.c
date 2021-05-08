#include <stdio.h>
#include <stdlib.h>

#include "hashtables.h"


int main() {
    HASHTABLES_ERR err;
    HashTable *table = NULL;



    table = init_hashtable(4, &err);
    if (err != ESUCCESS)
        fprintf(stdout, "Test\t->\tFAILED\n");
    else
        fprintf(stdout, "Test\t->\tPASSED\n");


    insert_key(1, table, &err);
    if (err != ESUCCESS)
        fprintf(stdout, "Test\t->\tFAILED\n");
    else
        fprintf(stdout, "Test\t->\tPASSED\n");


    int find_res = find_key(1, table, &err);
    if (!find_res || err != ESUCCESS)
        fprintf(stdout, "Test\t->\tFAILED\n");
    else
        fprintf(stdout, "Test\t->\tPASSED\n");


    find_res = find_key(2, table, &err);
    if (find_res || err != ESUCCESS)
        fprintf(stdout, "Test\t->\tFAILED\n");
    else
        fprintf(stdout, "Test\t->\tPASSED\n");


    insert_key(10, NULL, &err);
    if (err != EINVARG)
        fprintf(stdout, "Test\t->\tFAILED\n");
    else
        fprintf(stdout, "Test\t->\tPASSED\n");


    insert_key(9, table, &err);
    if (err != ESUCCESS)
        fprintf(stdout, "Test\t->\tFAILED\n");
    else
        fprintf(stdout, "Test\t->\tPASSED\n");


    insert_key(2, table, &err);
    if (err != ESUCCESS)
        fprintf(stdout, "Test\t->\tFAILED\n");
    else
        fprintf(stdout, "Test\t->\tPASSED\n");



    remove_key(3, table, &err);
    if (err != EREMOVE)
        fprintf(stdout, "Test\t->\tFAILED\n");
    else
        fprintf(stdout, "Test\t->\tPASSED\n");


    remove_key(9, table, &err);
    if (err != ESUCCESS)
        fprintf(stdout, "Test\t->\tFAILED\n");
    else
        fprintf(stdout, "Test\t->\tPASSED\n");



    remove_hashtable(table, &err);
    if (err != ESUCCESS)
        fprintf(stdout, "Test\t->\tFAILED\n");
    else
        fprintf(stdout, "Test\t->\tPASSED\n");


    return 0;
}

