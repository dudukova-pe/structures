#ifndef COMMUNICATION_H
#define COMMUNICATION_H
#include "../table/table.h"

Table* create_Table();
int insert_element(Table* table);
int remove_element(Table* table);
int print_table(Table* table);
int research_element(Table* table);
int import_table(Table* table);
int export_table(Table* table);

#endif /*COMMUNICATION_H*/