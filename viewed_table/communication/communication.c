#include <stdio.h>
#include <stdlib.h>
#include "readline/readline.h"
#include <limits.h>
#include "../entering/entering.h"
#include "../table/table.h"
#include <unistd.h>

Table* create_empty_table() {
	printf("Введите размер таблицы: ");
	int size = -1;
	int check = inputint(&size, 0, INT_MAX);
	if (check == EOF) {
		return NULL;
	}
	if (size == 0) {
		printf("Завершение работы программы\n");
		return NULL;
	}
	Table* table = create_table(size);
	return table;
}

int insert_element(Table* table) {
	printf("Введите ключ вставляемого элемента: ");
	int key = -1;
	int check = inputint(&key, 1, INT_MAX);
	if (check == EOF) {
		return EOF;
	}
	printf("Введите родительский ключ вставляемого элемента: ");
	int par = -1;
	check = inputint(&par, 0, INT_MAX);
	if (check == EOF) {
		return EOF;
	}
	printf("Введите необходимую информацию: ");
	char* str = readline("");
	if (str == NULL) {
		return EOF;
	}
	check = ins_elem(table, key, par, str);
	if (check == EOF) {
		printf("check = EOF\n");
		return EOF;
	}
	if (check == 1) {
		garbage_clean(table);
		print_Table(table);
		printf("Таблица сжата до минимально возможного размера для ещё одной попытки вставки элемента\n");
		check = ins_elem(table, key, par, str);
		if (check == 1) {
			printf("Элемент не может быть вставлен, так как таблица заполнена\n");
			return 1;
		}
	}		
	if (check == 2) {
		printf("Введены некорректные или неполные данные\n");
		return 2;
	}
	check_keys(table);
	check_parents(table);
	return 0;
}

int remove_element(Table* table) {
	printf("Введите ключ удаляемого элемента: ");
	int num = -1;
	int check_enter = inputint(&num, 1, INT_MAX);
	if (check_enter == EOF) {
		return EOF;
	}
	if (remove_elem(table, num) == 1) {
		printf("Элемента с указанным ключом не найдено\n");
		return 1;
	}
	for (int i = 0; i < table->size; i++) {
		if (table->keys[i]->par == num) {
			remove_elem(table, table->keys[i]->key);
		}
	}
	return 0;
}

int print_table(Table* table) {
	print_Table(table);
	return 0;
}

int import_table(Table* table) {
	printf("Введите имя файла: ");
	char* filename = readline("");
	if (filename == NULL) {
		return EOF;
	}
	FILE* file = open_file(filename);
	if (file == NULL) {
		return 2;
	}
	if (table_import(file, table) == EOF) {
		return EOF;
	}
	check_keys(table);
	check_parents(table);
	return 0;
}

int research_element(Table* table) {
	printf("Введите ключ искомого элемента: ");
	int key = -1;
	int check = inputint(&key, 1, INT_MAX);
	if (check == EOF) {
		return EOF;
	}
	check = research_elem(table, key);
	if (check == 2) {
		printf("Не удалось найти данный элемент в таблице\n");
	}
	if (check == 1) {
		printf("Номер ключа должен быть положительным\n");
	}
	return 0;
}

int garbage_collection(Table* table) {
	garbage_clean(table);
	return 0;
}
