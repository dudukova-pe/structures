#ifndef COMMUNICATION_H
#define COMMUNICATION_H
#include "../table/table.h"

Table* create_empty_table();
int insert_element(Table* table);
int remove_element(Table* table);
int import_table();
int research_element(Table* table);
int print_table(Table* table);
int garbage_collection(Table* table);

#endif /*COMMUNICATION_H*/