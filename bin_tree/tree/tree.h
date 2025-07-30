#ifndef TREE_H
#define TREE_H

typedef struct Item {
	char* data;
} Item;

typedef struct Leaf {
	char* key;
	struct Leaf* left;
	struct Leaf* right;
	struct Leaf* next;
	Item* info;
} Leaf;

typedef struct Tree {
	Leaf* root;
} Tree;

char* get_key(Leaf* leaf);
Leaf* get_left(Leaf* leaf);
Leaf* get_right(Leaf* leaf);
Leaf* get_next(Leaf* leaf);
Item* get_info(Leaf* leaf);
char* get_data(Leaf* leaf);
Leaf* get_root(Tree* tree);
void set_key(Leaf* leaf, char* new_key);
void set_left(Leaf* leaf, Leaf* new_left);
void set_right(Leaf* leaf, Leaf* new_right);
void set_next(Leaf* leaf, Leaf* new_next);
void set_info(Leaf* leaf, Item* new_info);
void set_data(Leaf* leaf, char* data);
void set_root(Tree* tree, Leaf* new_root);

Leaf* create_Leaf();
Tree* create_Tree();
void print_Tree(Tree* root);
void print_one_Leaf(Leaf* leaf);
int insert_elem(Tree* leaf, char* key, char* data);
int remove_elem(Tree* root, char* key, int place);
Leaf* research_elem(Tree* root, char* key, int place);
Leaf* research_more_than_this(Tree* tree, char* key);
Leaf* delete_Leaf(Leaf* leaf);
int delete_Tree(Tree* root);
int print_to_paint(Tree* tree, char* filename);

#endif /*TREE_H*/