#include <stdio.h>
#include "scapegoat_tree.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/syscall.h>

Item* create_Item() {
        Item* item = (Item*)calloc(1, sizeof(Item));
        set_next_Item(item, NULL);
        return item;
}

Data* create_Data() {
        Data* data = (Data*)calloc(1, sizeof(Data));
        set_head(data, NULL);
        set_tail(data, NULL);
        return data;
}

Node* create_Node() {
        Node* node = (Node*)calloc(1, sizeof(Node));
        set_key(node, 0);
        set_left(node, NULL);
        set_right(node, NULL);
        set_parent(node, NULL);
        Data* data = create_Data();
        set_Data(node, data);
        set_weight(node, 0);
        return node;
}

Tree* create_Tree(float coeff) {
        Tree* tree = (Tree*)calloc(1, sizeof(Tree));
        set_root(tree, NULL);
        set_coeff(tree, coeff);
        set_max_count(tree, 2);
        set_count(tree, 0);
        return tree;
}

void print_finded_Node(Node* node) {
        if (node != NULL) {
                printf("Ключ элемента: %u\nИнформация элемента: ", get_key(node));
                Item* ptr = get_head(get_Info(node));
                while (ptr != NULL) {
                        printf("%s", get_data_Item(ptr));
                        ptr = get_next_Item(ptr);
                        if (ptr != NULL) {
                                printf(", ");
                        }
                }
                printf("\n\n");
        }
}

void print_Node(Node* node) {
        if (node != NULL) {
                Item* ptr = get_head(get_Info(node));
                while (ptr != NULL) {
                        printf("%p %u %u - %s\n", node, get_weight(node), get_key(node), get_data_Item(ptr));
                        printf("left = %p, right = %p, parent = %p\n", get_left(node), get_right(node), get_parent(node));
                        ptr = get_next_Item(ptr);
                }
        }
}

void print_Tree(Node* root) {
        if (root != NULL) {
                print_Tree(get_left(root));
                print_Node(root);
                print_Tree(get_right(root));
        }
}

void print_Node_better(Node* node, uint spaces) {
        if (node != NULL) {
                for (uint i = 0; i < spaces; i++) {
                        printf(" ");
                }
                printf("%u  %u - ", get_weight(node), get_key(node));
                Item* ptr = get_head(get_Info(node));
                while (ptr != NULL) {
                        printf("%s", get_data_Item(ptr));
                        ptr = get_next_Item(ptr);
                        if (ptr != NULL) {
                                printf(", ");
                        }
                }
                printf("\n");
        }
}

void print_Tree_better(Node* root, uint spaces) {
        if (root != NULL) {
                print_Node_better(root, spaces);
                print_Tree_better(get_left(root), spaces + 2);
                print_Tree_better(get_right(root), spaces + 2);
        }
}

void print_Node_to_paint(Node* node, FILE* file) {
        uint node_key = get_key(node);
        uint left_key = get_key(get_left(node));
        uint right_key = get_key(get_right(node));
        if (left_key != EOF) {
                fprintf(file, "\t%u->%u\n", node_key, left_key);
        }
        if (right_key != EOF) {
                fprintf(file, "\t%u->%u\n", node_key, right_key);
        }
}

void print_Tree_to_paint(Node* root, FILE* file) {
        if (root != NULL) {
                print_Tree_to_paint(get_left(root), file);
                print_Node_to_paint(root, file);
                print_Tree_to_paint(get_right(root), file);
        }
}

int print_to_paint(Tree* tree, char* filename) {
        if ((get_root(tree) == NULL) && (filename == NULL)) {
                return 1;
        }
        if (access(filename, 0) != 0) {
                return 4;
        }
        FILE* file = fopen(filename, "w");
        if (file == NULL) {
                return 2;
        }
        fprintf(file, "digraph {\n\trankdir = \"TB\"\n");
        Node* ptr = get_root(tree);
        if (ptr == NULL) {
                return 3;
        }
        print_Tree_to_paint(get_root(tree), file);
        fprintf(file, "}");
        fclose(file);
        return 0;
}

Node* make_Node(uint key, char* data) {
        Node* node = create_Node();
        set_key(node, key);
        Item* item = create_Item();
        set_data_Item(item, data);
        set_head(get_Info(node), item);
        set_weight(node, 1);
        return node;
}

Node* find_elem(Tree* tree, uint key) {
        if (tree == NULL) {
                return NULL;
        }
        Node* ptr = get_root(tree);
        while (ptr != NULL) {
                uint ptr_key = get_key(ptr);
                if (key == ptr_key) {
                        return ptr;
                }
                if (key < ptr_key) {
                        ptr = get_left(ptr);
                }
                if (key > ptr_key) {
                        ptr = get_right(ptr);
                }
        }
        return NULL;
}

Node* find_max_elem(Tree* tree) {
        if (tree == NULL) {
                return NULL;
        }
        Node* ptr = get_root(tree);
        while (get_right(ptr) != NULL) {
                ptr = get_right(ptr);
        }
        return ptr;
}

Node* find_parent(Tree* tree, uint key) {
        if (tree == NULL) {
                return NULL;
        }
        Node* parent = NULL;
        Node* ptr = get_root(tree);
        while (ptr != NULL) {
                parent = ptr;
                uint ptr_key = get_key(ptr);
                if (ptr_key == key) {
                        return ptr;
                }
                if (key < ptr_key) {
                        ptr = get_left(ptr);
                }
                if (key > ptr_key) {
                        ptr = get_right(ptr);
                }
        }
        return parent;
}

void insert_Item(Node* node, char* data) {
        if (node != NULL) {
                Item* item = create_Item();
                set_data_Item(item, data);
                set_head(get_Info(node), item);
        }
}

void add_weight(Node* node) {
        Node* ptr = get_parent(node);
        while (ptr != NULL) {
                set_weight(ptr, get_weight(ptr) + 1);
                ptr = get_parent(ptr);
        }
}

int balance_condition(Node* node, float coeff) {
        if (node == NULL) {
                return 0;
        }
        uint node_weight = get_weight(node);
        uint left_weight = get_weight(get_left(node));
        uint right_weight = get_weight(get_right(node));
        uint weight_diff = (left_weight > right_weight) ? (left_weight - right_weight) : (right_weight - left_weight);
        if (weight_diff < 2) {
                return 0;
        }
        if (left_weight > (node_weight * coeff)) {
                return 1;
        }
        if (right_weight > (node_weight * coeff)) {
                return 1;
        }
        return 0;
}

void add_in_array(Node** array, uint* count_elems, Node* node) {
        if ((node != NULL) && (array[*count_elems] == NULL)) {
                add_in_array(array, count_elems, get_left(node));
                array[*count_elems] = node;
                *count_elems += 1;
                add_in_array(array, count_elems, get_right(node));
        }
}

Node** make_array(Node* scapegoat) {
        Node** array = (Node**)calloc(get_weight(scapegoat), sizeof(Node*));
        uint count_elems = 0;
        add_in_array(array, &count_elems, scapegoat);
        return array;
}

Node* add_in_tree(Node** array, uint start, uint end, uint count_elems, Node* parent) {
        if ((array == NULL) || (start > end)) {
                return NULL;
        }
        uint middle = (start + end) / 2;
        Node* root = array[middle];
        set_parent(root, parent);
        if (middle > 0) {
                set_left(root, add_in_tree(array, start, middle - 1, count_elems, root));
        }
        if (middle < count_elems - 1) {
                set_right(root, add_in_tree(array, middle + 1, end, count_elems, root));
        }
        return root;
}

Node* balance_scapegoat(Node* scapegoat) {
        Node** array = make_array(scapegoat);
        Node* root = add_in_tree(array, 0, get_weight(scapegoat), get_weight(scapegoat), NULL);
        free(array);
        return root;
}

uint count_weight(Node* root) {
        if (root == NULL) {
                return 0;
        }
        uint left_weight = count_weight(get_left(root));
        uint right_weight = count_weight(get_right(root));
        uint root_weight = 1 + left_weight + right_weight;
        set_weight(root, root_weight);
        return root_weight;
} 

void correct_weight(Node* root, uint root_weight) {
        set_weight(root, root_weight);
        count_weight(root);
}

void balance(Tree* tree, Node* node) {
        Node* scapegoat = NULL;
        Node* ptr = node;
        while (ptr != NULL) {
                if (balance_condition(ptr, get_coeff(tree)) != 0) {
                        scapegoat = ptr;
                }
                ptr = get_parent(ptr);
        }
        if (scapegoat != NULL) {
                Node* parent = get_parent(scapegoat);
                Node* root = balance_scapegoat(scapegoat);
                (get_left(parent) == scapegoat) ? set_left(parent, root) : set_right(parent, root);
                set_parent(root, parent);
                if (scapegoat == get_root(tree)) {
                        set_root(tree, root);
                }
                correct_weight(root, get_weight(scapegoat));
        }
}

int insert_elem(Tree* tree, uint key, char* data) {
        if (tree == NULL) {
                return EOF;
        }
        Node* parent = find_parent(tree, key);
        if (parent == NULL) {
                Node* node = make_Node(key, data);
                set_root(tree, node);
                set_count(tree, get_count(tree) + 1);
                return 0;
        }
        uint parent_key = get_key(parent);
        if (parent_key == key) {
                insert_Item(parent, data);
                return 0;
        }
        Node* node = make_Node(key, data);
        (key < parent_key) ? set_left(parent, node) : set_right(parent, node);
        set_parent(node, parent);
        add_weight(node);
        balance(tree, node);
        return 0;
}

Item* delete_Item(Item* item) {
        Item* next = NULL;
        if (item != NULL) {
                next = get_next_Item(item);
                free(get_data_Item(item));
                free(item);
        }
        return next;
}

void delete_Data(Data* data) {
        if (data != NULL) {
                Item* ptr =     get_head(data);
                while (ptr != NULL) {
                        ptr = delete_Item(ptr);
                }
        }
        free(data);
}

void delete_Node(Node* node) {
        if (node != NULL) {
                Data* data = get_Info(node);
                delete_Data(data);
        }
        free(node);
}

void delete_Tree(Node* root) {
        if (root != NULL) {
                Node* left = get_left(root);
                Node* right = get_right(root);
                delete_Tree(left);
                delete_Node(root);
                delete_Tree(right);
        }
}

int count_childs(Node* node) {
        int count = 0;
        if (get_left(node) != NULL) {
                count += 1;
        }
        if (get_right(node) != NULL) {
                count += 1;
        }
        return count;
}

void remove_weight(Node* node) {
        Node* ptr = node;
        while (ptr != NULL) {
                set_weight(ptr, get_weight(ptr) - 1);
                ptr = get_parent(ptr);
        }
}

Node* remove_elem_without_childs(Node* node) {
        Node* parent = get_parent(node);
        if (parent != NULL) {
                (get_left(parent) == node) ? set_left(parent, NULL) : set_right(parent, NULL);
        }
        delete_Node(node);
        return parent;
}

Node* remove_elem_with_child(Node* node) {
        Node* child = (get_left(node) != NULL) ? get_left(node) : get_right(node);
        Node* parent = get_parent(node);
        (get_left(parent) == node) ? set_left(parent, child) : set_right(parent, child);
        set_parent(child, parent);
        delete_Node(node);
        return child;
}

Node* find_new_elem(Node* node) {
        Node* ptr = get_right(node);
        while (get_left(ptr) != NULL) {
                ptr = get_left(ptr);
        }
        return ptr;
}

void move_content(Node* node, Node* new) {
        set_key(node, get_key(new));
        delete_Data(get_Info(node));
        set_Data(node, get_Info(new));
        set_Data(new, NULL);
}

Node* remove_elem_with_childs(Node* node) {
        Node* new = find_new_elem(node);
        move_content(node, new);
        if (count_childs(new) == 0) {
                remove_elem_without_childs(new);
                return node;
        }
        remove_elem_with_child(new);
        return node;
}

Node* find_balance_elem(Node* node, int childs) {
        if (childs < 2) {
                return get_parent(node);
        }
        Node* new = find_new_elem(node);
        return get_parent(new);
}

int remove_elem(Tree* tree, uint key) {
        Node* elem = find_elem(tree, key);
        if (elem == NULL) {
                return 1;
        }
        int childs = count_childs(elem);
        Node* balance_elem = find_balance_elem(elem, childs);
        remove_weight(balance_elem);
        Node* new_root = NULL;
        if (childs == 0) {
                new_root = remove_elem_without_childs(elem);
                if (get_root(tree) == elem) {
                        set_root(tree, new_root);
                }
        }
        if (childs == 1) {
                new_root = remove_elem_with_child(elem);
                if (get_root(tree) == elem) {
                        set_root(tree, new_root);
                }
        }
        if (childs == 2) {
                remove_elem_with_childs(elem);
        }
        balance(tree, balance_elem);
        return 0;
}