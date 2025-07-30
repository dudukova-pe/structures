#ifndef SCAPEGOAT_TREE_H
#define SCAPEGOAT_TREE_H

typedef struct Item {
        char* data;
        struct Item* next;
} Item;

typedef unsigned int uint;

typedef struct Data {
        Item* head;
        Item* tail;
} Data;

typedef struct Node {
        uint key;
        struct Node* left;
        struct Node* right;
        struct Node* parent;
        Data* info;
        uint weight;
} Node;

typedef struct Tree {
        uint max_count;
        uint count;
        float coeff;
        Node* root;
} Tree;

char* get_data_Item(Item* item);
Item* get_next_Item(Item* item);
Item* get_head(Data* data);
Item* get_tail(Data* data);
uint get_key(Node* node);
Node* get_left(Node* node);
Node* get_right(Node* node);
Node* get_parent(Node* node);
Data* get_Info(Node* node);
uint get_weight(Node* node);
uint get_max_count(Tree* tree);
uint get_count(Tree* tree);
float get_coeff(Tree* tree);
Node* get_root(Tree* tree);
void set_data_Item(Item* item, char* data);
void set_next_Item(Item* item, Item* next);
void set_head(Data* data, Item* head);
void set_tail(Data* data, Item* tail);
void set_key(Node* node, uint key);
void set_left(Node* node, Node* left);
void set_right(Node* node, Node* right);
void set_parent(Node* node, Node* parent);
void set_Data(Node* node, Data* data);
void set_weight(Node* node, uint weight);
void set_max_count(Tree* tree, uint max_count);
void set_count(Tree* tree, uint count);
void set_coeff(Tree* tree, float coeff);
void set_root(Tree* tree, Node* list);

Tree* create_Tree(float coeff);
int insert_elem(Tree* tree, uint key, char* data);
int remove_elem(Tree* tree, uint key);
Node* find_elem(Tree* tree, uint key);
Node* find_max_elem(Tree* tree);
void print_finded_Node(Node* node);
void print_Tree(Node* root);
void print_Tree_better(Node* root, uint spaces);
int print_to_paint(Tree* tree, char* filename);
void delete_Tree(Node* node);

#endif /*SCAPEGOAT_TREE_H*/