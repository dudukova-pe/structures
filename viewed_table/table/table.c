#include "./table.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <string.h>
#include <limits.h>
#include "../entering/entering.h"

void print_Item(Item* item) {
	printf("%s\n", item->string);
}

void print_Key(Key* key) {
	if (key->busy == 1) {
		printf("%*d  |  %*d  |  %*d  |  ", 10, key->busy, 10, key->key, 10, key->par);
		print_Item(key->info);
	} else {
		printf("%*d  |              |              |\n", 10, 0);
	}
}

void print_Table(Table* table) {
	printf("\nTable's size = %d\n", table->size);
	printf("Table:\n");
	printf("    Busy    |     Key      |    Parent    |  Data:\n");
	for (int i = 0; i < table->max_size; i++) {
		print_Key(table->keys[i]);
	}
}

int delete_Item_info(Item* item) {
	if (item == NULL) {
		return 0;
	}
	if (item->string == NULL) {
		return 0;
	}
	free(item->string);
	item->string = NULL;
	return 0;
}

int delete_Item(Item* item) {
	delete_Item_info(item);
	free(item);
	return 0;
}

int delete_Key_info(Key* key) {
	if (key == NULL) {
		return 0;
	}
	if (key->busy == 0) {
		return 0;
	}
	if (key->info == NULL) {
		return 0;
	}
	delete_Item_info(key->info);
	key->busy = 0;
	return 0;
}

int delete_Key(Key* key) {
	if (key == NULL) {
		return 0;
	}
	delete_Item(key->info);
	free(key);
	return 0;
} 

void delete_table(Table* table) {
	for (int i = 0; i < table->max_size; i++) {
		delete_Key(table->keys[i]);
	}
	free(table->keys);
	free(table);
}

int replace_data(Key* old_key, int key, int par, char* data) {
	if (data == NULL) {
		return EOF;
	}
	if ((key < 1) || (par < 0)) {
		return 2;
	}
	old_key->busy = 1;
	old_key->key = key;
	old_key->par = par;
	old_key->info->string = data;
	return 0;
}

int ins_elem(Table* table, int key, int par, char* data) {
	if (table == NULL) {
		return EOF;
	}
	if (data == NULL) {
		return EOF;
	}
	if (table->size == table->max_size) {
		return 1;
	}
	int check = replace_data(table->keys[table->size], key, par, data);
	if (check != 0) {
		return check;
	}
	table->size += 1;
	return 0;
}

char* format_filename(char* filename) {
	int size = strlen(filename);
	if (filename[size - 1] == ' ') {
		filename[size - 1] = '\0';
	}
	return filename;
}

FILE* open_file(char* filename) {
	filename = format_filename(filename);
	if (access(filename, 0) != 0) {
		printf("Не удалось найти файл\n");
		free(filename);
		return NULL;
	}
	FILE* file = fopen(filename, "r");
	free(filename);
	if (file == NULL) {
		printf("Не удалось открыть файл\n");
		fclose(file);
		return NULL;
	}
	return file;
}

Table* create_table(int size) {
	Table* table = (Table*)calloc(1, sizeof(Table));
	table->max_size = size;
	table->size = 0;
	table->keys = (Key**)calloc(table->max_size, sizeof(Key*));
	for (int i = 0; i < table->max_size; i++) {
		table->keys[i] = (Key*)calloc(1, sizeof(Key));
		table->keys[i]->info = (Item*)calloc(1, sizeof(Item));
		table->keys[i]->busy = 0;
	}
	return table;
}
	
int table_import(FILE* file, Table* table) {
	if (file == NULL) {
		return EOF;
	}
	while (table->size < table->max_size) {
		char* str = txt_readline(file);
		if (str == NULL) {
			break;
		}	

		char* key_word = strtok(str, " \t");
		if (key_word == NULL) {
			free(str);
			return 1;
		}
		char* read_key = strdup(key_word);
		int	key = atoi(read_key);
		free(read_key);
		char* par_word = strtok(NULL, " \t");
		if (par_word == NULL) {
			free(str);
			return 1;
		}
		char* read_par = strdup(par_word);
		int par = atoi(read_par);
		free(read_par);
		char* data_word = strtok(NULL, "");	
		if (data_word == NULL) {
			free(str);
			return 1;
		}
		char* data = strdup(data_word);
		free(str);
		if (ins_elem(table, key, par, data) == EOF) {
			break;
		}
	}
	fclose(file);
	return 0;
}

int check_keys(Table* table) {
	int check = 0;
	if (table->size == 1) {
		if (table->keys[0]->key == 0) {
			delete_Key_info(table->keys[0]);
			printf("Ключ из строки 1 удалён, так как значение ключа не может быть равно нулю\n");
		}
		return 0;
	}
	for (int i = 0; i < table->size - 1; i++) {
		while (table->keys[i]->busy == 0) {
			i++;
			if (i >= table->size) {
				return 0;
			}
		}
		if (table->keys[i]->key == 0) {
			delete_Key_info(table->keys[i]);
			printf("Ключ из строки %d удалён, так как значение ключа не может быть равно нулю\n", i + 1);
		}
		for (int j = i + 1; j < table->size; j++) {		
			if (i == j) {
				j++;
			}
			while ((table->keys[j]->busy == 0) && (j < table->size)) {
				j++;
				if (j >= table->size) {
					break;
				}
			}
			if (j >= table->size) {
				break;
			}
			if (table->keys[i]->key == table->keys[j]->key) {
				delete_Key_info(table->keys[j]);
				printf("Ключ из %d строки удалён, так как значения ключей не могут совпадать\n", j + 1);
			}
		}
	}
	return 0;
}

int check_parents(Table* table) {
	for (int i = 0; i < table->size; i++) {
		while (table->keys[i]->busy == 0) {
			i++;
			if (i == table->size) {
				return 0;
			}
		}
		if (table->keys[i]->par == table->keys[i]->key) {
			table->keys[i]->par = 0;
			printf("Исправлена ошибка в родительском ключе (%d строка)\n", i + 1);
		}
		int check = 0;
		if (table->keys[i]->par != 0) {
			for (int j = 0; j < table->size; j++) {
				if (i == j) {
					j++;
				}
				while ((j < table->size) && (table->keys[j]->busy == 0)) {
					j++;
					if (j >= table->size) {
						break;
					}
				}
				if (j >= table->size) {
					break;
				}
				if (table->keys[i]->par == table->keys[j]->key) {
					check += 1;
				}
			}
			if (check == 0) {
				table->keys[i]->par = 0;
				printf("Исправлена ошибка в родительском ключе (%d строка)\n", i + 1);
			}
		}
	}
	return 0;
}

int garbage_clean(Table* table) {
	if (table == NULL) {
		return 0;
	}
	int empty = -1;
	for (int i = 0; i < table->size; i++) {
		if (table->keys[i]->busy == 0) {
			empty = i;
			break;
		}
	}
	if (empty == -1) {
		return 0;
	}
	int full = -1;
	for (int i = table->size - 1; i >= 0; i--) {
		if (table->keys[i]->busy == 1) {
			full = i;
			break;
		}
	}
	while (full > empty) {
		Key* memory = table->keys[empty];
		table->keys[empty] = table->keys[full];
		table->keys[full] = memory;
		table->size--;
		while (table->keys[full]->busy == 0) {
			full--;
			table->size--;
		}
		while (table->keys[empty]->busy == 1) {
			empty++;
		}
	}
	table->size = empty;
	return 0;
}

int remove_elem(Table* table, int num) {
	if (table == NULL) {
		return 0;
	}
	if (num < 1) {
		return 0;
	}
	int dep = -1;
	for (int i = 0; i < table->size; i++) {
		if (table->keys[i]->busy == 1) {
			if (table->keys[i]->key == num) {
				delete_Key_info(table->keys[i]);
				break;
			}
		}
	}
	for (int i = 0; i < table->size; i++) {
		if (table->keys[i]->busy == 1) {
			if (table->keys[i]->par == num) {
				remove_elem(table, table->keys[i]->key);
			}
		}
	}
	return 0;
}

int research_elem(Table* table, int num) {
	if (table == NULL) {
		return EOF;
	}
	if (num < 1) {
		return 1;
	}
	for (int i = 0; i < table->size; i++) {
		if (table->keys[i]->busy == 1) {
			if (table->keys[i]->key == num) {
				print_Key(table->keys[i]);
				return 0;
			}
		}
	}
	return 2;
}
