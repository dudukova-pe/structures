#ifndef TABLE_H
#define TABLE_H
#include <stdio.h>

typedef struct Item {
	char* string;
} Item;

typedef struct Key {
	int busy;
	unsigned int key;
	int par;
	Item* info;
} Key;

typedef struct Table {
	Key** keys;
	int max_size;
	int size;
} Table;

void print_Table(Table* table);
FILE* open_file(char* filename);
int ins_elem(Table* table, int key, int par, char* data);
Table* create_table(int size);
int table_import(FILE* file, Table* table);
void delete_table(Table* table);
int check_parents(Table* table);
int check_keys(Table* table);
int garbage_clean(Table* table);
int remove_elem(Table* table, int num);
int research_elem(Table* table, int num);

#endif /*TABLE_H*/
