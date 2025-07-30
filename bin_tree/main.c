#include <stdio.h>
#include <stdlib.h>
#include "../3b/entering/entering.h"
#include "./tree/tree.h"
#include "./communication/communication.h"

void print_menu(const char* msgs[], const int count_msgs) {
	printf("\nВыберите действие:\n");
	for (int i = 0; i < count_msgs; i++) {
		printf("%s\n", msgs[i]);
	}
}

int main() {
	Tree* tree = create_Tree();
	const char *msgs[] = {"0: Завершить работу", "1: Вставить новый элемент", "2: Удалить элемент по номеру ключа", "3: Поиск элемента по значению ключа", "4: Поиск минимальгого элемента, большего заданного", "5: Вывод содержимого"};
	const int count_msgs = sizeof(msgs) / sizeof(msgs[0]);
	print_menu(msgs, count_msgs);
	int (*func[])(Tree*) = {NULL, insert_element, remove_element, research_element, special_research, print_tree};
	int menu = -1;
	int check = inputint(&menu, 0, 5);
	while (check != EOF) {
		if (menu == 0) {
			break;
		}
		check = func[menu](tree);
		if (check == EOF) {
			delete_Tree(tree);
			return EOF;
		}
		print_Tree(tree);
		print_menu(msgs, count_msgs);
		check = inputint(&menu, 0, 5);
	}
	delete_Tree(tree);
	return 0;
}