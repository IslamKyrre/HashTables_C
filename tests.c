#include <stdio.h>
#include <stdlib.h>

#include "hashtables.h"


int main() {
    HASHTABLES_ERR err;
    HashTable *table = NULL;

    remove_hashtable(NULL, &err); //1
    if (err != EINVARG)
        fprintf(stdout, "Test_1\t->\tFAILED\n");
    else
        fprintf(stdout, "Test_1\t->\tPASSED\n");


    table = init_hashtable(-8, &err); //2
    if (err != EINVARG)
        fprintf(stdout, "Test_2\t->\tFAILED\n");
    else
        fprintf(stdout, "Test_2\t->\tPASSED\n");

    table = init_hashtable(36, &err); //3
    if (err != EINVARG)
        fprintf(stdout, "Test_3\t->\tFAILED\n");
    else
        fprintf(stdout, "Test_3\t->\tPASSED\n");

    table = init_hashtable(4, &err); //4
    if (err != ESUCCESS)
        fprintf(stdout, "Test_4\t->\tFAILED\n");
    else
        fprintf(stdout, "Test_4\t->\tPASSED\n");

    print_table(table, &err); //5
    if (err != ESUCCESS)
        fprintf(stdout, "Test_5\t->\tFAILED\n");
    else
        fprintf(stdout, "Test_5\t->\tPASSED\n");

    insert_key(1, table, &err); //6
    if (err != ESUCCESS)
        fprintf(stdout, "Test_6\t->\tFAILED\n");
    else
        fprintf(stdout, "Test_6\t->\tPASSED\n");

    //print_table(table, &err); //5

    find_key(3, NULL, &err); //7
    if (err != EINVARG)
        fprintf(stdout, "Test_7\t->\tFAILED\n");
    else
        fprintf(stdout, "Test_7\t->\tPASSED\n");

    int find_res = find_key(1, table, &err); //8
    if (!find_res || err != ESUCCESS)
        fprintf(stdout, "Test_8\t->\tFAILED\n");
    else
        fprintf(stdout, "Test_8\t->\tPASSED\n");


    find_res = find_key(2, table, &err); //9
    if (find_res || err != ESUCCESS)
        fprintf(stdout, "Test_9\t->\tFAILED\n");
    else
        fprintf(stdout, "Test_9\t->\tPASSED\n");


    insert_key(10, NULL, &err); //10
    if (err != EINVARG)
        fprintf(stdout, "Test_10\t->\tFAILED\n");
    else
        fprintf(stdout, "Test_10\t->\tPASSED\n");


    insert_key(9, table, &err); //11
    if (err != ESUCCESS)
        fprintf(stdout, "Test_11\t->\tFAILED\n");
    else
        fprintf(stdout, "Test_11\t->\tPASSED\n");

    //print_table(table, &err); //5

    insert_key(2, table, &err); //12
    if (err != ESUCCESS)
        fprintf(stdout, "Test_12\t->\tFAILED\n");
    else
        fprintf(stdout, "Test_12\t->\tPASSED\n");

    //print_table(table, &err); //5

    insert_key(2, table, &err); //13
    if (err != EINSERT)
        fprintf(stdout, "Test_13\t->\tFAILED\n");
    else
        fprintf(stdout, "Test_13\t->\tPASSED\n");

    //print_table(table, &err);

    remove_key(2, table, &err); //14
    if (err != ESUCCESS)
        fprintf(stdout, "Test_14\t->\tFAILED\n");
    else
        fprintf(stdout, "Test_14\t->\tPASSED\n");

    insert_key(2, table, &err); //15
    if (err != ESUCCESS)
        fprintf(stdout, "Test_15\t->\tFAILED\n");
    else
        fprintf(stdout, "Test_15\t->\tPASSED\n");

    remove_key(3, table, &err); //16
    if (err != EREMOVE)
        fprintf(stdout, "Test_16\t->\tFAILED\n");
    else
        fprintf(stdout, "Test_16\t->\tPASSED\n");

    //print_table(table, &err);

    remove_key(9, table, &err); //17
    if (err != ESUCCESS)
        fprintf(stdout, "Test_17\t->\tFAILED\n");
    else
        fprintf(stdout, "Test_17\t->\tPASSED\n");

    //print_table(table, &err);

    remove_key(2, NULL, &err); //18
    if (err != EINVARG)
        fprintf(stdout, "Test_18\t->\tFAILED\n");
    else
        fprintf(stdout, "Test_18\t->\tPASSED\n");

    //rehash test
    for (int i = 1; i <= 100; ++i) {
        insert_key(i * i, table, &err); //19
    }
    if (table->bufferSize <= 4 || err != ESUCCESS)
        fprintf(stdout, "Test_19\t->\tFAILED\n");
    else
        fprintf(stdout, "Test_19\t->\tPASSED\n");

    //print_table(table, &err);

    rehash(NULL, &err); //20
    if (err != EINVARG)
        fprintf(stdout, "Test_20\t->\tFAILED\n");
    else
        fprintf(stdout, "Test_20\t->\tPASSED\n");

    print_table(table, &err); //21
    if (err != ESUCCESS)
        fprintf(stdout, "Test_21\t->\tFAILED\n");
    else
        fprintf(stdout, "Test_21\t->\tPASSED\n");


    print_table(NULL, &err);//22
    if (err != EINVARG)
        fprintf(stdout, "Test_22\t->\tFAILED\n");
    else
        fprintf(stdout, "Test_22\t->\tPASSED\n");

    remove_hashtable(table, &err); //23
    if (err != ESUCCESS)
        fprintf(stdout, "Test_23\t->\tFAILED\n");
    else
        fprintf(stdout, "Test_23\t->\tPASSED\n");


    return 0;
}
