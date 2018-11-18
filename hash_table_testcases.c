#include <gtest/gtest.h>
#include "hash_table.h"

/****************************************************************************************************/
TEST(hash, empty) {
    char *str = NULL;
    int hash_value = hash(str);
    EXPECT_EQ(-1, hash_value);
    printf("%d\n", hash_value);
}
/****************************************************************************************************/
TEST(hash, oneCharacter) {
    char str[] = "c";
    int expected_hash = str[0] % HASH_TABLE_LEN;
    int hash_value = hash(str);
    EXPECT_EQ(expected_hash, hash_value);
    printf("%d\n", hash_value);
}

/****************************************************************************************************/
TEST(hash, normalCharacters) {
    char str[] = "character";
    int str_size = strlen(str);
    int expected_hash =  (str[0] +
                        str[1] +
                        str[2] +
                        str[3] +
                        str[4] +
                        str[5] +
                        str[6] +
                        str[7] +
                        str[8]) % HASH_TABLE_LEN;
    int hash_value = hash(str);
    EXPECT_EQ(expected_hash, hash(str));
    printf("%d\n", hash_value);
}

/****************************************************************************************************/
TEST(hash, specialCharacters) {
    char str[] = "$<@.@;}3?";
    int str_size = strlen(str);
    int expected_hash =  (str[0] +
                        str[1] +
                        str[2] +
                        str[3] +
                        str[4] +
                        str[5] +
                        str[6] +
                        str[7] +
                        str[8]) % HASH_TABLE_LEN;
    int hash_value = hash(str);
    EXPECT_EQ(expected_hash, hash(str));
    printf("%d\n", hash_value);
}

/****************************************************************************************************/
// TEST(print_hash_table, empty_hash_table) {
//     char *hash_table[] = {NULL};
//     print_hash_table(hash_table);
// }

/****************************************************************************************************/
TEST(print_hash_table, normal_hash_table) {
    char str_1[] = "character";
    char str_2[] = "$<@.@;}3?";
    char *hash_table[HASH_TABLE_LEN];
    int i;
    for(i = 0; i < HASH_TABLE_LEN; i++) {
        hash_table[i] = NULL;
    }
    hash_table[hash(str_1)] = str_1;
    hash_table[hash(str_2)] = str_2;
    print_hash_table(hash_table);
}

/****************************************************************************************************/
TEST(add_to_hash_table_no_handle_collision, empty_key) {
    char *key = NULL;
    char *hash_table[HASH_TABLE_LEN];
    int i;
    for(i = 0; i < HASH_TABLE_LEN; i++) {
        hash_table[i] = NULL;
    }
    EXPECT_EQ(-1, add_to_hash_table_no_handle_collision(hash_table, key));
}

/****************************************************************************************************/
TEST(add_to_hash_table_no_handle_collision, normal_key) {
    char key1[] = "character";
    char key2[] = "$<@.@;}3?";
    char key3[] = ";'.>(^%(*)";
    char key4[] = "~~~~~~~~~~~~~~~~~~~";
    char *hash_table[HASH_TABLE_LEN];
    int i;
    for(i = 0; i < HASH_TABLE_LEN; i++) {
        hash_table[i] = NULL;
    }
    EXPECT_EQ(1, add_to_hash_table_no_handle_collision(hash_table, key1));
    EXPECT_EQ(8, add_to_hash_table_no_handle_collision(hash_table, key2));
    EXPECT_EQ(0, add_to_hash_table_no_handle_collision(hash_table, key3));
    EXPECT_EQ(4, add_to_hash_table_no_handle_collision(hash_table, key4));
    print_hash_table(hash_table);
}

/****************************************************************************************************/
TEST(add_to_hash_table_no_handle_collision, collided_keys) {
    char key1[] = "$$$$$$$$$$$$$$$$$$$";
    char key2[] = "~~~~~~~~~~~~~~~~~~~";
    char *hash_table[HASH_TABLE_LEN];
    int i;
    for(i = 0; i < HASH_TABLE_LEN; i++) {
        hash_table[i] = NULL;
    }
    EXPECT_EQ(4, add_to_hash_table_no_handle_collision(hash_table, key1));
    EXPECT_EQ(-1, add_to_hash_table_no_handle_collision(hash_table, key2));
    print_hash_table(hash_table);
}

/****************************************************************************************************/
TEST(add_to_hash_table, empty_key) {
    char *key = NULL;
    hash_element *hash_table[HASH_TABLE_LEN];
    int i;
    for(i = 0; i < HASH_TABLE_LEN; i++) {
        hash_table[i] = NULL;
    }
    EXPECT_EQ(-1, add_to_hash_table(hash_table, key));
}

/****************************************************************************************************/
TEST(add_to_hash_table, collided_keys) {
    char key1[] = "$$$$$$$$$$$$$$$$$$$";
    char key2[] = "~~~~~~~~~~~~~~~~~~~";
    hash_element *hash_table[HASH_TABLE_LEN];
    int i;
    for(i = 0; i < HASH_TABLE_LEN; i++) {
        hash_table[i] = NULL;
    }

    EXPECT_EQ(4, add_to_hash_table(hash_table, key1));
    EXPECT_EQ(4, add_to_hash_table(hash_table, key2));
    print_hash_element_table(hash_table);
}

/****************************************************************************************************/
TEST(add_to_hash_table, normal_key) {
    char key1[] = "character";
    char key2[] = "$<@.@;}3?";
    char key3[] = ";'.>(^%(*)";
    char key4[] = "~~~~~~~~~~~~~~~~~~~";
    hash_element *hash_table[HASH_TABLE_LEN];    
    int i;
    for(i = 0; i < HASH_TABLE_LEN; i++) {
        hash_table[i] = NULL;
    }
    EXPECT_EQ(1, add_to_hash_table(hash_table, key1));
    EXPECT_EQ(8, add_to_hash_table(hash_table, key2));
    EXPECT_EQ(0, add_to_hash_table(hash_table, key3));
    EXPECT_EQ(4, add_to_hash_table(hash_table, key4));
    print_hash_element_table(hash_table);
}