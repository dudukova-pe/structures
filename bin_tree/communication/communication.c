#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "readline/readline.h"
#include "../tree/tree.h"
#include <limits.h>
#include "../entering/entering.h"

int insert_element(Tree* tree) {
	char* key = readline("Введите номер ключа: ");
	if (key == NULL) {
		return EOF;
	}
	char* data = readline("Введите необходимые данные: ");
	if (data == NULL) {
		free(key);
		return EOF;
	}
	int check = insert_elem(tree, key, data);
	if (check != 0) {
		printf("Элемент не был вставлен\n");
	}
	return 0;
}

int remove_element(Tree* tree) {
	char* key = readline("Введите ключ удаляемого элемента: ");
	if (key == NULL) {
		return EOF;
	}
	printf("Введите номер удаляемого элемента: ");
	int place = -1;
	int check = inputint(&place, 1, INT_MAX); 
	if (check == EOF) {
		free(key);
		return EOF;
	}
	check = remove_elem(tree, key, place);
	free(key);
	if (check != 0) {
		if (check == 1) {
			printf("Элемент не найден\n");
		}
		return check;
	}
	return 0;
}

int research_element(Tree* tree) {
	char* key = readline("Введите ключ искомого элемента: ");
	if (key == NULL) {
		return EOF;
	}
	printf("Введите номер искомого элемента: ");
	int place = -1;
	int check = inputint(&place, 1, INT_MAX);
	if (check == EOF) {
		free(key);
		return EOF;
	}
	Leaf* elem = research_elem(tree, key, place);
	print_one_Leaf(elem);
	free(key);
	if (elem == NULL) {
		printf("Элемент не найден\n");
		return 1;
	}
	return 0;
}

int special_research(Tree* tree) {
	char* key = readline("Введите ключ: ");
	if (key == NULL) {
		return EOF;
	}
	Leaf* elem = research_more_than_this(tree, key);
	free(key);
	if (elem == NULL) {
		printf("Такого элемента не найдено\n");
		return 1;
	}
	print_one_Leaf(elem);
	return 0;
}

int print_tree(Tree* tree) {
	printf("Выберите действие:\n");
	printf("1: Вывести в консоль\n");
	printf("2: Вывести в файл в виде картинки\n");
	int menu = 0;
	int check = inputint(&menu, 1, 2);
	if (check == EOF) {
		return EOF;
	}
	if (menu == 1) {
		print_Tree(tree);
		return 0;
	}
	char* filename = readline("Введите имя файла: ");
	if (filename == NULL) {
		return EOF;
	}
	check = print_to_paint(tree, filename);
	free(filename);
	if (check != 0) {
		if (check == 1) {
			printf("Дерева не существует или имя файла некорректно\n");
		}
		if (check == 2) {
			printf("Не удалось открыть файл\n");
		}
		if (check == 3) {
			printf("В дереве один элемент\n");
		}
		if (check == 4) {
			printf("Такого файла не существует\n");
		}
	}
	return check;
}
