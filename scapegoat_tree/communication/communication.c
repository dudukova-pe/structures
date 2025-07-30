#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include "communication.h"
#include "../entering/entering.h"
#include "readline/readline.h"
#include "../scapegoat_tree/scapegoat_tree.h"

Tree* create_tree() {
        printf("Введите коэффициент для балансировки дерева: ");
        float coeff = 0;
        int check = inputfloat(&coeff, 0.5, 1.0);
        if (check == EOF) {
                return NULL;
        }
        Tree* tree = create_Tree(coeff);
        return tree;
}

int insert_element(Tree* tree) {
        printf("Введите значение ключа: ");
        uint key = 0;
        int check = inputuint(&key, 0, UINT_MAX);
        if (check == EOF) {
                return EOF;
        }
        char* data = readline("Введите необходимую информацию: ");
        if (data == NULL) {
                return EOF;
        }
        check = insert_elem(tree, key, data);
        if (check == EOF) {
                return EOF;
        }
        return 0;
}

int remove_element(Tree* tree) {
        printf("Введите ключ удаляемого элемента: ");
        uint key = 0;
        int check = inputuint(&key, 0, UINT_MAX);
        if (check == EOF) {
                return EOF;
        }
        check = remove_elem(tree, key);
        if (check == 1) {
                printf("Элемента с таким ключом не найдено\n");
                return 1;
        }
        return 0;
}

int find_element(Tree* tree) {
        printf("Введите ключ искомого элемента: ");
        uint key = 0;
        int check = inputuint(&key, 0, UINT_MAX);
        if (check == EOF) {
                return EOF;
        }
        Node* finded_elem = find_elem(tree, key);
        if (finded_elem == NULL) {
                printf("Элемент не найден\n");
                return 1;
        }
        print_finded_Node(finded_elem);
        return 0;
}

int find_max_element(Tree* tree) {
        Node* max_element = find_max_elem(tree);
        if (max_element == NULL) {
                printf("Дерево пусто, поиск максимального элемента невозможен\n");
                return 1;
        }
        print_finded_Node(max_element);
        return 0;
}

int print_tree(Tree* tree) {
        printf("1: В консоль с указанием веса вершины\n");
        printf("2: В консоль с наглядной иерархией\n");
        printf("3: В файл\n");
        int select = 0;
        int check = inputint(&select, 1, 3);
        if (check == EOF) {
                return 0;
        }
        if (select == 1) {
                print_Tree(get_root(tree));
                return 0;
        }
        if (select == 2) {
                print_Tree_better(get_root(tree), 0);
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
        return 0;
}

int check_insert(Tree* tree) {
        int count_tests = 0;
        printf("Введите количество тестов: ");
        int check = inputint(&count_tests, 0, INT_MAX);
        if (check == EOF) {
                return EOF;
        }
        int count_elements = 0;
        printf("Введите количество элементов в дереве: ");
        check = inputint(&count_elements, 0, INT_MAX);
        if (check == EOF) {
                return EOF;
        }
        int count_inserted_elements = 0;
        printf("Введите количество вставляемых элементов: ");
        check = inputint(&count_inserted_elements, 0, INT_MAX);
        if (check == EOF) {
                return EOF;
        }
        srand(time(NULL));
        for (int i = 0; i < count_tests; i++) {
                Tree* test_tree = create_Tree(get_coeff(tree));
                while (get_weight(get_root(test_tree)) < count_elements) {
                        uint key = (uint)(rand() % ((i + 1) * count_elements) + 1);
                        char* data = (char*)calloc(1, sizeof(char));
                        insert_elem(test_tree, key, data);
                }
                uint array_keys[count_inserted_elements];
                for (int count_inserted_elems = 0; count_inserted_elems < count_inserted_elements; count_inserted_elems++) {
                        array_keys[count_inserted_elems] = (uint)(rand() % ((i + 1) * count_elements) + 1);
                }
                char* array_data[count_inserted_elements];
                for (int count_inserted_elems = 0; count_inserted_elems < count_inserted_elements; count_inserted_elems++) {
                        array_data[count_inserted_elems] = (char*)calloc(1, sizeof(char));
                }
                clock_t start = clock();
                for (int inserting = 0; inserting < count_inserted_elements; inserting++) {
                        insert_elem(test_tree, array_keys[inserting], array_data[inserting]);
                }
                clock_t finish = clock();
                printf("%ld\n", finish - start);
                delete_tree(test_tree);
        }
        return 0;
}

int check_remove(Tree* tree) {
        int count_tests = 0;
        printf("Введите количество тестов: ");
        int check = inputint(&count_tests, 0, INT_MAX);
        if (check == EOF) {
                return EOF;
        }
        int count_elements = 0;
        printf("Введите количество элементов в дереве: ");
        check = inputint(&count_elements, 0, INT_MAX);
        if (check == EOF) {
                return EOF;
        }
        int count_removed_elements = 0;
        printf("Введите количество удаляемых элементов: ");
        check = inputint(&count_removed_elements, 0, INT_MAX);
        if (check == EOF) {
                return EOF;
        }
        srand(time(NULL));
        for (int i = 0; i < count_tests; i++) {
                Tree* test_tree = create_Tree(get_coeff(tree));
                while (get_weight(get_root(test_tree)) < count_elements) {
                        uint key = (uint)(rand() % ((i + 1) * count_elements) + 1);
                        char* data = (char*)calloc(1, sizeof(char));
                        insert_elem(test_tree, key, data);
                }
                uint array_keys[count_removed_elements];
                for (int count_inserted_elems = 0; count_inserted_elems < count_removed_elements; count_inserted_elems++) {
                        array_keys[count_inserted_elems] = (uint)(rand() % ((i + 1) * count_elements) + 1);
                }
                clock_t start = clock();
                for (int inserting = 0; inserting < count_removed_elements; inserting++) {
                        remove_elem(test_tree, array_keys[inserting]);
                }
                clock_t finish = clock();
                printf("test %d: %ld\n", i + 1, finish - start);
                delete_tree(test_tree);
        }
        return 0;
}

int check_find(Tree* tree) {
        int count_tests = 0;
        printf("Введите количество тестов: ");
        int check = inputint(&count_tests, 0, INT_MAX);
        if (check == EOF) {
                return EOF;
        }
        int count_elements = 0;
        printf("Введите количество элементов в дереве: ");
        check = inputint(&count_elements, 0, INT_MAX);
        if (check == EOF) {
                return EOF;
        }
        int count_finded_elements = 0;
        printf("Введите количество искомых элементов: ");
        check = inputint(&count_finded_elements, 0, INT_MAX);
        if (check == EOF) {
                return EOF;
        }
        srand(time(NULL));
        for (int i = 0; i < count_tests; i++) {
                Tree* test_tree = create_Tree(get_coeff(tree));
                while (get_weight(get_root(test_tree)) < count_elements) {
                        uint key = (uint)(rand() % ((i + 1) * count_elements) + 1);
                        char* data = (char*)calloc(1, sizeof(char));
                        insert_elem(test_tree, key, data);
                }
                uint array_keys[count_finded_elements];
                for (int count_inserted_elems = 0; count_inserted_elems < count_finded_elements; count_inserted_elems++) {
                        array_keys[count_inserted_elems] = (uint)(rand() % ((i + 1) * count_elements) + 1);
                }
                clock_t start = clock();
                for (int inserting = 0; inserting < count_finded_elements; inserting++) {
                        find_elem(test_tree, array_keys[inserting]);
                }
                clock_t finish = clock();
                printf("test %d: %ld\n", i + 1, finish - start);
                delete_tree(test_tree);
        }

        return 0;
}

int check_time(Tree* tree) {
        printf("Выберите функцию, работу которой вы хотите проверить:\n");
        printf("1: Вставка\n");
        printf("2: Удаление\n");
        printf("3: Поиск\n");
        int menu = 0;
        int check = inputint(&menu, 1, 3);
        if (check == EOF) {
                return EOF;
        }
        if (menu == 1) {
                check = check_insert(tree);
        }
        if (menu == 2) {
                check = check_remove(tree);
        }
        if (menu == 3) {
                check = check_find(tree);
        }
        return check;
}

void delete_tree(Tree* tree) {
        delete_Tree(get_root(tree));
        free(tree);
}