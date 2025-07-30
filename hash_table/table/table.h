#ifndef TABLE_H
#define TABLE_H
#include <stdio.h>

typedef unsigned int uint;

typedef struct Item {
	uint num;
} Item;

typedef struct Key {
	int busy; // char?
	uint key;
	uint release;
	Item* info;
} Key;

typedef struct Table {
	Key** keys;
	uint size;
} Table;

uint get_size(Table* table);
Table* create_table(uint size);
int insert_elem(Table* table, uint key, uint data);
int remove_elem(Table* table, uint num, uint release);
int research_elem(Table* table, Table* research, uint key, uint release);
void print_Table(Table* table);
FILE* open_file(char* filename, const char* format);
int import_Table(Table* table, FILE* file);
int export_Table(Table* table, FILE* file);
int delete_table(Table* table);

#endif /*TABLE_H*/
