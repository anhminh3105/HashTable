#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HASH_TABLE_LEN 10

struct hash_element {
    char *str;
    struct hash_element *next;
};

int hash(char *key);
void print_hash_table(char *table[]);
void print_hash_element_table(hash_element *table[]);
int add_to_hash_table_no_handle_collision(char *hash_table[], char *key);
int add_to_hash_table(struct hash_element *hash_table[], char *key);