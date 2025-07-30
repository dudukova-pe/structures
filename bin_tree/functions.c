#include <stdio.h>
#include "tree.h"

char* get_key(Leaf* leaf) {
	if (leaf == NULL) {
		return NULL;
	}
	return leaf->key;
}

Leaf* get_left(Leaf* leaf) {
	if (leaf == NULL) {
		return NULL;
	}
	return leaf->left;
}

Leaf* get_right(Leaf* leaf) {
	if (leaf == NULL) {
		return NULL;
	}
	return leaf->right;
}

Leaf* get_next(Leaf* leaf) {
	if (leaf == NULL) {
		return NULL;
	}
	return leaf->next;
}

Item* get_info(Leaf* leaf) {
	if (leaf == NULL) {
		return NULL;
	}
	return leaf->info;
}

char* get_data(Leaf* leaf) {
	if (leaf == NULL) {
		return NULL;
	}
	return leaf->info->data;
}

Leaf* get_root(Tree* tree) {
	if (tree == NULL) {
		return NULL;
	}
	return tree->root;
}

void set_key(Leaf* leaf, char* new_key) {
	if (leaf != NULL) {
		leaf->key = new_key;
	}
}

void set_left(Leaf* leaf, Leaf* new_left) {
	if (leaf != NULL) {
		leaf->left = new_left;
	}
}

void set_right(Leaf* leaf, Leaf* new_right) {
	if (leaf != NULL) {
		leaf->right = new_right;
	}
}

void set_next(Leaf* leaf, Leaf* new_next) {
	if (leaf != NULL) {
		leaf->next = new_next;
	}
}

void set_info(Leaf* leaf, Item* new_info) {
	if (leaf != NULL) {
		leaf->info = new_info;
	}
}

void set_data(Leaf* leaf, char* data) {
	if (leaf != NULL) {
		leaf->info->data = data;
	}
}

void set_root(Tree* tree, Leaf* new_root) {
	if (tree != NULL) {
		tree->root = new_root;
	}
}
