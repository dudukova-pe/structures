#include <stdio.h>
#include <stdlib.h>
#include "entering/entering.h"
#include "communication/communication.h"
#include "scapegoat_tree/scapegoat_tree.h"

void print_menu(const char* msgs[], const int count_msgs) {
        printf("\nВыберите действие:\n");
        for (int i = 0; i < count_msgs; i++) {
                printf("%s\n", msgs[i]);
        }
}

int main() {
        Tree* tree = create_tree();
        const char *msgs[] = {"0: Завершить работу", "1: Вставить новый элемент", "2: Удалить элемент по номеру ключа", "3: Поиск элемента по значению ключа", "4: Поиск максимального элемента в дереве", "5: Таймирование", "6: Вывод содержимого"};
        const int count_msgs = sizeof(msgs) / sizeof(msgs[0]);
        print_menu(msgs, count_msgs);
        int (*func[])(Tree*) = {NULL, insert_element, remove_element, find_element, find_max_element, NULL, print_tree};
        int menu = -1;
        int check = inputint(&menu, 0, 6);
        while (check != EOF) {
                if (menu == 0) {
                        break;
                }
                if (menu == 5) {
                        check = check_time(tree);
                } else {
                        check = func[menu](tree);
                        if (check == EOF) {
                                delete_tree(tree);
                                return EOF;
                        }
                }
                print_Tree_better(get_root(tree), 0);
                print_menu(msgs, count_msgs);
                check = inputint(&menu, 0, count_msgs);
        }
        delete_tree(tree);
        return 0;
}