#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "./entering/entering.h"
#include "./table/table.h"
#include "./communication/communication.h"

void print_menu(const char* msgs[], const int count_msgs) {
	printf("\nВыберите действие:\n");
	for (int i = 0; i < count_msgs; i++) {
		printf("%s\n", msgs[i]);
	}
}

int main() {
	Table* table = create_empty_table();
	if (table == NULL) {
		return EOF;
	}
	const char *msgs[] = {"0: Завершить работу", "1: Вставить в таблицу новый элемент", "2: Удалить элемент из таблицы по номеру ключа", "3: Поиск элемента по значению ключа", "4: Вывод содержимого на экран", "5: Инициализировать таблицу из файла", "6: Сжать табллицу (удалить пустые строки)"};
	const int count_msgs = sizeof(msgs) / sizeof(msgs[5]);
	print_menu(msgs, count_msgs);
	int (*func[])(Table*) = {NULL, &insert_element, remove_element, research_element, print_table, import_table, garbage_collection};
	int menu = -1;
	int check = inputint(&menu, 0, 6);
	while (check != EOF) {
		if (menu == 0) {
			break;
		}
		check = func[menu](table);
		if (check == EOF) {
			delete_table(table);
			return EOF;
		}
		print_table(table);
		print_menu(msgs, count_msgs);
		check = inputint(&menu, 0, 6);
	}
	delete_table(table);
	return 0;
}