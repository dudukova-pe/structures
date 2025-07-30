#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "./table.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/syscall.h>

uint get_size(Table* table) {
	if (table == NULL) {
		return 0;
	}
	return table->size;
}

Key** get_keys(Table* table) {
	if (table == NULL) {
		return NULL;
	}
	return table->keys;
}

Key* get_Key(Table* table, uint i) {
	if (table == NULL) {
		return NULL;
	}
	if (i > get_size(table)) {
		return NULL;
	}
	Key** keys = get_keys(table);
	return keys[i];
}

uint get_busy(Table* table, uint i) {
	Key* key = get_Key(table, i);
	if (key == NULL) {
		return EOF;
	}
	return key->busy;
}

uint get_key(Table* table, uint i) {
	Key* key = get_Key(table, i);
	if (key == NULL) {
		return EOF;
	}
	if (get_busy(table, i) != 1) {
		return EOF;
	}
	return key->key;
}

uint get_release(Table* table, uint i) {
	Key* key = get_Key(table, i);
	if (key == NULL) {
		return EOF;
	}
	if (get_busy(table, i) != 1) {
		return EOF;
	}
	return key->release;
}

Item* get_info(Table* table, uint i) {
	Key* key = get_Key(table, i);
	if (key == NULL) {
		return NULL;
	}
	if (get_busy(table, i) != 1) {
		return NULL;
	}
	return key->info;
}

uint get_data(Table* table, uint i) {
	Key* key = get_Key(table, i);
	if (key == NULL) {
		return EOF;
	}
	Item* item = get_info(table, i);
	if (item == NULL) {
		return EOF;
	}
	return item->num;
}


Item* create_Item() {
	Item* item = (Item*)calloc(1, sizeof(Item));
	item->num = 0;
	return item;
}

Key* create_Key() {
	Key* key = (Key*)calloc(1, sizeof(Key));
	key->key = 0;
	key->release = 0;
	key->busy = 0;
	key->info = create_Item();
	return key;
}

Table* create_table(uint size) {
	Table* table = (Table*)calloc(1, sizeof(Table));
	table->size = size;
	table->keys = (Key**)calloc(size, sizeof(Key*));
	for (uint i = 0; i < size; i++) {
		table->keys[i] = create_Key();
	}
	return table;
}

uint hash_function_1(uint key) {
	char* bytes = (char*)calloc(5, sizeof(char));
	for (int i = 0; i < 4; i++) {
		bytes[i] = (char)key;
		key /= 0xFF;
	}
	uint hash = UINT_MAX;
	for (int i = 0; i < 4; i++) {
		hash = 37 * hash + bytes[i];
	}
	free(bytes);
	return (uint)abs((int)hash);
}

uint hash_function_2(uint key) {
	char* bytes = (char*)calloc(5, sizeof(char));
	for (int i = 0; i < 4; i++) {
		bytes[i] = (char)key;
		key /= 0xFF;
	}
	uint hash = 0;
	for (int i = 0; i < 4; i++) {
		hash = 37 * UINT_MAX + i * bytes[i];
	}
	free(bytes);
	return (uint)abs((int)hash);
}

uint count_step(uint table_size, uint hash2) {
	if (table_size < 3) {
		return 1;
	}
	uint step = hash2 % table_size;
	if ((table_size % step == 0) && (step != 1)) {
		step += 1;
		if ((step >= table_size) || (table_size % step == 0)) {
			step = 1;
		}
	}
	if (step == 0) {
		return 1;
	}
	return step;
}

int research_elem(Table* table, Table* research, uint key, uint release) {
	research->size = 0;
	uint table_size = get_size(table);
	uint hash1 = hash_function_1(key);
	uint hash2 = hash_function_2(key);
	for (int i = 0; i < table_size; i++) {
		uint step = count_step(table_size, hash2);
		uint place = (hash1 + i * step) % table_size;
		if ((get_key(table, place) == key) && ((get_release(table, place) == release) || (release == 0))) {
			research->keys[get_size(research)]->key = key;
			research->keys[get_size(research)]->busy = 1;
			research->keys[get_size(research)]->release = get_release(table, place);
			research->keys[get_size(research)]->info->num = get_data(table, place);
			research->size += 1;
		}
	}
	if (get_size(research) == 0) {
		return 1;
	}
	return 0;
}

int select_place(Table* table, unsigned int key) {
	uint table_size = get_size(table);
	uint hash1 = hash_function_1(key);
	uint hash2 = hash_function_2(key);
	uint step = count_step(table_size, hash2);
	for (int i = 0; i < table_size; i++) {
		uint place = (hash1 + i * step) % table_size;
		if (get_busy(table, place) != 1) {
			return place;
		}
	}
	return EOF;
}

/*void extension_table(Table* table) {
	table->size += 1;
	table->keys = (Key**)realloc(table->keys, get_size(table) * sizeof(Key*));
	table->keys[get_size(table) - 1] = create_Key();
}*/

uint last_release(Table* table, uint key) {
	uint table_size = get_size(table);
	uint hash1 = hash_function_1(key);
	uint hash2 = hash_function_2(key);
	uint release = 0;
	uint step = count_step(table_size, hash2);
	uint place = hash1 % table_size;
	for (int i = 0; (i < table_size) && (get_busy(table, place) > 0); i++) {
		place = (hash1 + i * step) % table_size;
		if (get_key(table, place) == key) {
			uint found_release = get_release(table, place);
			if (found_release > release) {
				release = found_release;
			}
		}
	}
	return release;
}

int filling_elem(Table* table, unsigned int key, unsigned int data, unsigned int place) {
	table->keys[place]->busy = 1;
	table->keys[place]->key = key;
	table->keys[place]->info->num = data;
	table->keys[place]->release = last_release(table, key) + 1;
	return 0;
}

int insert_elem(Table* table, unsigned int key, unsigned int data) {
	if (table == NULL) {
		return EOF;
	}
	if (key == 0) {
		return 1;
	}
	uint place = select_place(table, key);
	if (place == EOF) {
//		extension_table(table);
//		place = get_size(table) - 1;
		return 2;
	}
	filling_elem(table, key, data, place);
	return 0;
}

void delete_Item_info(Item* item) {
	if (item != NULL) {
		item->num = 0;
	}
}

void delete_Item(Item* item) {
	free(item);
}

void delete_Key_info(Key* key) {
	if (key != NULL) {
		key->busy = 2;
		key->key = 0;
		key->release = 0;
		delete_Item_info(key->info);
	}
}

void delete_Key(Key* key) {
	if (key != NULL) {
		delete_Item(key->info);
	}
	free(key);
}

int delete_table(Table* table) {
	if (table == NULL) {
		return 0;
	}
	if (get_size(table) == 0) {
		return 0;
	}
	for (uint i = 0; i < get_size(table); i++) {
		delete_Key(get_Key(table, i));
	}
	free(get_keys(table));
	free(table);
	return 0;
}

int remove_elem(Table* table, uint key, uint release) {
	if (table == NULL) {
		return 0;
	}
	if (key < 0) {
		return 1;
	}
	int check = 0;
	uint table_size = get_size(table);
	uint hash1 = hash_function_1(key);
	uint hash2 = hash_function_2(key);
	uint step = count_step(table_size, hash2);
	uint place = hash1 % table_size;
	for (uint i = 0; (i < table_size) && (get_busy(table, place) > 0); i++) {
		place = (hash1 + i * step) % table_size;
		if (get_key(table, place) == key) {
			uint found_release = get_release(table, place);
			if ((release == 0) || (found_release == release)) {
				delete_Key_info(get_Key(table, place));
				if (release != 0) {
					return 0;
				}
				check = 1;
			}
		}
	}
	if (check == 0) {
		return 2;
	}
	return 0;
}

void print_Item(Item* item) {
	printf("%d\n", item->num);
}

void print_Key(Key* key) {
	if (key->busy == 1) {
		printf("%*d  |  %*d  |  %*d  |  ", 10, key->busy, 10, key->key, 10, key->release);
		print_Item(key->info);
	} else {
		printf("%*d  |              |              |\n", 10, key->busy);
	}
}

void print_Table(Table* table) {
	printf("\nTable's size = %d\n", get_size(table));
	printf("Table:\n");
	printf("    Busy    |     Key      |    Release   |  Data:\n");
	for (int i = 0; i < get_size(table); i++) {
		print_Key(get_Key(table, i));
	}
}
char* format_filename(char* filename) {
	int size = strlen(filename);
	if (size == 0) {
		return filename;
	}
	if (filename[size - 1] == ' ') {
		filename[size - 1] = '\0';
	}
	return filename;
}

FILE* open_file(char* filename, const char* format) {
	filename = format_filename(filename);
	if (access(filename, 0) != 0) {
		free(filename);
		return NULL;
	}
	FILE* file = fopen(filename, format);
	free(filename);
	if (file == NULL) {
		printf("Не удалось открыть файл\n");
		return NULL;
	}
	return file;
}

int check_file_format(FILE* file, uint* size_file) {
	char* check_msg = (char*)calloc(8, sizeof(char));
	fread(check_msg, sizeof(char), 7, file);
	if (strcmp(check_msg, "size = ") != 0) {
		free(check_msg);
		return 1;
	}
	free(check_msg);
	fread(size_file, sizeof(uint), 1, file);
	if (*size_file == 0) {
		return 2;
	}
	char space = '\0';
	fread(&space, sizeof(char), 1, file);
	if (space != ' ') {
		return 1;
	}
	return 0;
}

int import_Table(Table* table, FILE* file) {
	if (table == NULL) {
		return EOF;
	}
	if (file == NULL) {
		return EOF;
	}
	uint size_file = 0;
	int check = check_file_format(file, &size_file);
	if (check != 0) {
		return 1;
	}
	int busy;
	uint key, release, data;
	uint table_size = get_size(table);
	uint size = size_file;
	if (table_size < size_file) {
		size = table_size;
		printf("Часть элементов не будет записана, так как их количество превышает размеры таблицы\n");
	}
	for (int i = 0; i < size; i++) {
		fread(&busy, sizeof(int), 1, file);
		fread(&key, sizeof(uint), 1, file);
		fread(&release, sizeof(uint), 1, file);
		fread(&data, sizeof(uint), 1, file);
		if (insert_elem(table, key, data) == EOF) {
			break;
		}
	}
	fclose(file);
	return 0;
}

int export_Table(Table* table, FILE* file) {
	if (table == NULL) {
		return EOF;
	}
	if (file == NULL) {
		return EOF;
	}
	uint size = get_size(table);
	const char* msg = "size = ";
	fwrite(msg, sizeof(const char), strlen(msg), file);
	fwrite(&size, sizeof(uint), 1, file);
	char space = ' ';
	fwrite(&space, sizeof(char), 1, file);
	for (uint i = 0; i < size; i++) {
		int busy = get_busy(table, i);
		uint key = 0;
		uint release = 0;
		uint data = 0;
		if (busy == 1) {
			key = get_key(table, i);
			release = get_release(table, i);
			data = get_data(table, i);
		}
		fwrite(&busy, sizeof(int), 1, file);
		fwrite(&key, sizeof(uint), 1, file);
		fwrite(&release, sizeof(uint), 1, file);
		fwrite(&data, sizeof(uint), 1, file);
	}
	fclose(file);
	return 0;
}