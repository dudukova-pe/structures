#include <stdio.h>
#include "./scapegoat_tree.h"

char* get_data_Item(Item* item) {
        if (item == NULL) {
                return NULL;
        }
        return item->data;
}

Item* get_next_Item(Item* item) {
        if (item == NULL) {
                return NULL;
        }
        return item->next;
}

Item* get_head(Data* data) {
        if (data == NULL) {
                return NULL;
        }
        return data->head;
}

Item* get_tail(Data* data) {
        if (data == NULL) {
                return NULL;
        }
        return data->tail;
}

uint get_key(Node* node) {
        if (node == NULL) {
                return EOF;
        }
        return node->key;
}

Node* get_left(Node* node) {
        if (node == NULL) {
                return NULL;
        }
        return node->left;
}

Node* get_right(Node* node) {
        if (node == NULL) {
                return NULL;
        }
        return node->right;
}

Node* get_parent(Node* node) {
        if (node == NULL) {
                return NULL;
        }
        return node->parent;
}

Data* get_Info(Node* node) {
        if (node == NULL) {
                return NULL;
        }
        return node->info;
}

uint get_weight(Node* node) {
        if (node == NULL) {
                return 0;
        }
        return node->weight;
}

uint get_max_count(Tree* tree) {
        if (tree == NULL) {
                return EOF;
        }
        return tree->max_count;
}

uint get_count(Tree* tree) {
        if (tree == NULL) {
                return EOF;
        }
        return tree->count;
}

float get_coeff(Tree* tree) {
        if (tree == NULL) {
                return EOF;
        }
        return tree->coeff;
}

Node* get_root(Tree* tree) {
        if (tree == NULL) {
                return NULL;
        }
        return tree->root;
}

void set_data_Item(Item* item, char* data) {
        if (item != NULL) {
                item->data = data;
        }
}

void set_next_Item(Item* item, Item* next) {
        if (item != NULL) {
                item->next = next;
        }
}

void set_head(Data* data, Item* head) {
        if (data != NULL) {
                if (head != NULL) {
                        head->next = data->head;
                }
                data->head = head;
        }
}

void set_tail(Data* data, Item* tail) {
        if (data != NULL) {
                data->tail = tail;
        }
}

void set_key(Node* node, uint key) {
        if (node != NULL) {
                node->key = key;
        }
}

void set_left(Node* node, Node* left) {
        if (node != NULL) {
                node->left = left;
        }
}

void set_right(Node* node, Node* right) {
        if (node != NULL) {
                node->right = right;
        }
}

void set_parent(Node* node, Node* parent) {
        if (node != NULL) {
                node->parent = parent;
        }
}

void set_Data(Node* node, Data* data) {
        if (node != NULL) {
                node->info = data;
        }
}

void set_weight(Node* node, uint weight) {
        if (node != NULL) {
                node->weight = weight;
        }
}

void set_max_count(Tree* tree, uint max_count) {
        if (tree != NULL) {
                tree->max_count = max_count;
        }
}

void set_count(Tree* tree, uint count) {
        if (tree != NULL) {
                tree->max_count = count;
        }
}

void set_coeff(Tree* tree, float coeff) {
        if (tree != NULL) {
                tree->coeff = coeff;
        }
}

void set_root(Tree* tree, Node* list) {
        if (tree != NULL) {
                tree->root = list;
        }
}