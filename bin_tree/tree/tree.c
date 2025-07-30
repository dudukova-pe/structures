#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/syscall.h>

Item* create_Item() {
	Item* item = (Item*)calloc(1, sizeof(Item));
	item->data = NULL;
	return item;
}

Leaf* create_Leaf() {
	Leaf* leaf = (Leaf*)calloc(1, sizeof(Leaf));
	set_key(leaf, NULL);
	set_left(leaf, NULL);
	set_right(leaf, NULL);
	set_next(leaf, NULL);
	Item* info = create_Item();
	set_info(leaf, info);
	return leaf;
}

Tree* create_Tree() {
	Tree* tree = (Tree*)calloc(1, sizeof(Tree));
	set_root(tree, NULL);
	return tree;
}

void print_one_Leaf(Leaf* leaf) {
	if (leaf != NULL) {
		printf("%s - %s\n", get_key(leaf), get_data(leaf));
	}
}

void print_Tree(Tree* tree) {
	Leaf* ptr = get_root(tree);
	while (ptr != NULL) {
		print_one_Leaf(ptr);
		ptr = get_next(ptr);
	}
}

void delete_Item(Item* item) {
	if (item != NULL) {
		free(item->data);
	}
	free(item);
}

Leaf* delete_Leaf(Leaf* leaf) {
	if (leaf == NULL) {
		return NULL;
	}
	Item* item = get_info(leaf);
	if (item != NULL) {
		delete_Item(item);
		item = NULL;
	}
	Leaf* next = get_next(leaf);
	free(get_key(leaf));
	free(leaf);
	return next;
}

int delete_Tree(Tree* tree) {
	Leaf* ptr = get_root(tree);
	while (ptr != NULL) {
		ptr = delete_Leaf(ptr);
	}
	free(tree);
	return 0;
}

Leaf* make_elem(char* key, char* data) {
	if ((key == NULL) || (data == NULL)) {
		return NULL;
	}
	Leaf* elem = create_Leaf();
	set_key(elem, key);
	set_data(elem, data);
	set_left(elem, NULL);
	set_right(elem, NULL);
	set_next(elem, NULL);
	return elem;
}

Leaf* find_parent(Tree* tree, Leaf* elem) {
	char* key = get_key(elem);
	Leaf* parent = NULL;
	Leaf* ptr = get_root(tree);
	while (ptr != NULL) {
		parent = ptr;
		ptr = (strcmp(key, get_key(ptr)) > -1) ? get_right(ptr) : get_left(ptr);
		if (ptr == NULL) {
			return parent;
		}
	}
	return NULL;
}

Leaf* find_last_in_left(Leaf* parent) {
	Leaf* left = get_left(parent);
	if (left == NULL) {
		return parent;
	}
	Leaf* ptr = left;
	while (ptr != NULL) {
		Leaf* right = get_right(ptr);
		if (right != NULL) {
			ptr = right;
		} else {
			Leaf* left = get_left(ptr);
			if (left != NULL) {
				ptr = left;
			} else {
				return ptr;
			}
		}
	}
	return NULL;
}

int insert_elem(Tree* tree, char* key, char* data) {
	Leaf* elem = make_elem(key, data);
	if (elem == NULL) {
		return EOF;
	}
	if (get_root(tree) == NULL) {
		set_root(tree, elem);
		return 0;
	}
	Leaf* parent = find_parent(tree, elem);
	int check = strcmp(get_key(parent), key);
	if (check == 1) {
		set_left(parent, elem);
		set_next(elem, get_next(parent));
		set_next(parent, elem);
	} else {
		set_right(parent, elem);
		Leaf* prev = find_last_in_left(parent);
		set_next(elem, get_next(prev));
		set_next(prev, elem);
	}
	return 0;
}

Leaf* find_new_elem(Leaf* elem) {
	Leaf* ptr = get_right(elem);
	if (ptr == NULL) {
		return NULL;
	}
	while (get_left(ptr) != NULL) {
		ptr = get_left(ptr);
	}
	return ptr;
}

Leaf* prev_elem(Tree* tree, Leaf* elem) {
	Leaf* ptr = get_root(tree);
	if ((ptr == elem) || (ptr == NULL)) {
		return NULL;
	}
	while (get_next(ptr) != elem) {
		ptr = get_next(ptr);
	}
	return ptr;
}

Leaf* find_parent_for_elem(Tree* tree, Leaf* elem) {
	if ((get_root(tree) == NULL) || (elem == get_root(tree))) {
		return NULL;
	}
	char* key = get_key(elem);
	Leaf* ptr = get_root(tree);
	while ((get_left(ptr) != elem) && (get_right(ptr) != elem)) {
		if (strcmp(key, get_key(ptr)) > -1) {
			ptr = get_right(ptr);
		} else {
			ptr = get_left(ptr);
		}
	}
	return ptr;
}

int count_childs(Leaf* elem) {
	Leaf* right = get_right(elem);
	Leaf* left = get_left(elem);
	if ((right != NULL) && (left != NULL)) {
		return 2;
	}
	if ((right != NULL) || (left != NULL)) {
		return 1;
	}
	return 0;
}

void remove_elem_without_childs(Tree* tree, Leaf* elem) {
	Leaf* parent = find_parent_for_elem(tree, elem);
	Leaf* prev_for_elem = prev_elem(tree, elem);
	Leaf* next_for_elem = get_next(elem);
	set_next(prev_for_elem, next_for_elem);
	if (get_left(parent) == NULL) {
		set_right(parent, NULL);
	} else {
		set_left(parent, NULL);
	}
	delete_Leaf(elem);
}

void remove_elem_with_child(Tree* tree, Leaf* elem) {
	Leaf* parent = find_parent_for_elem(tree, elem);
	Leaf* next_for_elem = get_next(elem);
	set_next(parent, next_for_elem);
	if (get_left(parent) == NULL) {
		set_right(parent, next_for_elem);
	} else {
		set_left(parent, next_for_elem);
	}
	delete_Leaf(elem);
}

int move_content(Leaf* elem, Leaf* new_elem) {
	free(get_key(elem));
	char* new_key = strdup(get_key(new_elem));
	set_key(elem, new_key);
	delete_Item(get_info(elem));
	Item* new_info = create_Item();
	set_info(elem, new_info);
	char* new_data = strdup(get_data(new_elem));
	set_data(elem, new_data);
	return 0;
}

int remove_elem_with_childs(Tree* tree, Leaf* elem) {
	Leaf* new_elem = find_new_elem(elem);
	move_content(elem, new_elem);
	if (count_childs(new_elem) == 0) {
		remove_elem_without_childs(tree, new_elem);
		return 0;
	}
	remove_elem_with_child(tree, new_elem);
	return 0;
}

int remove_elem(Tree* tree, char* key, int place) {
	Leaf* elem = research_elem(tree, key, place);
	if (elem == NULL) {
		return 1;
	}
	int count = count_childs(elem);
	if (count == 2) {
		remove_elem_with_childs(tree, elem);
	}
	if (count == 1) {
		if (elem == get_root(tree)) {
			set_root(tree, get_next(elem));
		}
		remove_elem_with_child(tree, elem);
	}
	if (count == 0) {
		if (elem == get_root(tree)) {
			set_root(tree, NULL);
		}
		remove_elem_without_childs(tree, elem);
	}
	return 0;
}

Leaf* research_elem(Tree* tree, char* key, int place) {
	Leaf* ptr = get_root(tree);
	int num = 0;
	while (ptr != NULL) {
		if (strcmp(get_key(ptr), key) == 0) {
			num += 1;
			if (num == place) {
				return ptr;
			}
		}
		ptr = get_next(ptr);
	}
	return NULL;
}

Leaf* research_more_than_this(Tree* tree, char* key) {
	Leaf* ptr = get_root(tree);
	Leaf* min_elem = NULL;
	char* min_key = NULL;
	while (ptr != NULL) {
		print_one_Leaf(ptr); //
		char* ptr_key = get_key(ptr);
		if (strcmp(ptr_key, key) > 0) {
			if (min_key == NULL) {
				min_elem = ptr;
				min_key = ptr_key;
			} else {
				if (strcmp(ptr_key, min_key) < 0) {
					min_elem = ptr;
					min_key = ptr_key;
				}
			}
		}
		ptr = get_next(ptr);
	}
	if (strcmp(min_key, key) < 1) {
		return NULL;
	}
	return min_elem;
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
	Leaf* ptr = get_root(tree);
	if (ptr == NULL) {
		return 3;
	}
	while (ptr != NULL) {
		if (get_left(ptr) != NULL) {
			Leaf* left = get_left(ptr);
			fprintf(file, "\t%s->%s\n", get_key(ptr), get_key(left));
		}
		if (get_right(ptr) != NULL) {
			Leaf* right = get_right(ptr);
			fprintf(file, "\t%s->%s\n", get_key(ptr), get_key(right));
		}
		ptr = get_next(ptr);
	}
	fprintf(file, "}");
	fclose(file);
	return 0;
}