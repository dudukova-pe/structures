#ifndef COMMUNICATION_H
#define COMMUNICATION_H
#include "../scapegoat_tree/scapegoat_tree.h"

Tree* create_tree();
int insert_element(Tree* tree);
int remove_element(Tree* tree);
int find_element(Tree* tree);
int find_max_element(Tree* tree);
int print_tree(Tree* tree);
int check_time(Tree* tree);
void delete_tree(Tree* tree);

#endif /*COMMUNICATION_H*/