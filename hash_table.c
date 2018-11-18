#include "hash_table.h"

int hash(char *key) {
    if (!key) {
        printf("Error code 0: key must not be NULL.\n");
        return -1;
    }

    int c;
    int hash = 0;
    // int keySize = strlen(key);
    while(c = *key++) hash += c;
    return hash % HASH_TABLE_LEN;
}

void print_hash_table(char *table[]) {
    int i = 0;
    while(i != HASH_TABLE_LEN) {
        if(table[i] != NULL) printf("hash index: \"%d\" - key value: \"%s\"\n", i, table[i]);
        i++;
    }
}

void print_hash_element_table(hash_element *table[]) {
    int i = 0;
    while(i != HASH_TABLE_LEN) {
        if(table[i] != NULL) {
            hash_element *current_elem = table[i];
            while(current_elem) {
                printf("hash index: \"%d\" - key value: \"%s\"\n", i, current_elem->str);
                current_elem = current_elem->next;
            }
        }
        i++;
    }
}

int add_to_hash_table_no_handle_collision(char *hash_table[], char *key) {
    if (!key) {
        printf("Error code 0: key must not be NULL.\n");
        return -1;
    }

    int hash_val = hash(key);
    if (hash_table[hash_val]) {
        printf("Error code 1: key - %s generates hash collision!! did not add key to hash table.\n", key);
        return -1;
    }

    else {
        hash_table[hash_val] = key;
        return hash_val;
    }
}

int add_to_hash_table(struct hash_element *hash_table[], char *key) {
    if (!key) {
        printf("Error code 0: key must not be NULL.\n");
        return -1;
    }

    int hash_val = hash(key);
    hash_element *new_elem = (struct hash_element*)malloc(sizeof(hash_element));
    new_elem->str = key;
    new_elem->next = NULL;
    
    if (hash_table[hash_val]) {
        hash_element *current_elem = hash_table[hash_val];
        while (current_elem->next) current_elem = current_elem->next;
        current_elem->next = new_elem;
    }
    else {
        hash_table[hash_val] = new_elem;
    }
    return hash_val;
}

