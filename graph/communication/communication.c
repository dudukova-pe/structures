#include <stdio.h>
#include <limits.h>
#include "../graph/graph.h"
#include "../entering/entering.h"
#include "readline/readline.h"

Graph* create_graph() {
        Graph* graph = create_Graph();
        return graph;
}

Point* input_point() {
        printf("Введите координату x: ");
        uint x = 0;
        int check = inputuint(&x, 1, UINT_MAX);
        if (check == EOF) {
                return NULL;
        }
        printf("Введите координату y: ");
        uint y = 0;
        check = inputuint(&y, 1, UINT_MAX);
        if (check == EOF) {
                return NULL;
        }
        Point* point = create_Point(x, y);
        return point;
}

int insert_vertex(Graph* graph) {
        Point* point = input_point();
        if (point == NULL) {
                return EOF;
        }
        printf("\nВведите тип новой вершины:\n");
        printf("1: Вход в лабиринт\n"); 
        printf("2: Выход из лабиринта\n");
        printf("3: Обычная вершина\n");
        int type = 0;
        int check = inputint(&type, 1, 3);
        if (check == EOF) {
                delete_Point(point);
                return EOF;
        }
        check = insert_Vertex(graph, point, type);
        if (check != 0) {
                if (check == 1) {
                        printf("Граф не инициализирован\n");
                }
                if (check == 2) {
                        printf("Вершина с такими координатами уже есть\n");
                }
                delete_Point(point);
        }
        return check;
}

int insert_edge(Graph* graph) {
        printf("Введите координаты вершин, между которыми будет ребро:\n");
        Point* point1 = input_point();
        if (point1 == NULL) {
                return EOF;
        }
        Point* point2 = input_point();
        if (point2 == NULL) {
                delete_Point(point1);
                return EOF;
        }
        int check = insert_Edge(graph, point1, point2);
        if (check != 0) {
                if (check == 1) {
                        printf("Граф не инициализирован\n");
                }
                if (check == 2) {
                        printf("Вершин с такими координатами не найдено\n");
                }
                if (check == 3) {
                        printf("Вершины слишком далеко друг от друга или совпадают, между ними не может быть ребра\n");
                }
        }
        return check;
}

int change_type(Graph* graph) {
        Point* point = input_point();
        if (point == NULL) {
                return EOF;
        }
        printf("\nВведите новый тип вершины:\n");
        printf("1: Вход в лабиринт\n"); 
        printf("2: Выход из лабиринта\n");
        printf("3: Обычная вершина\n");
        int type = 0;
        int check = inputint(&type, 1, 3);
        if (check == EOF) {
                delete_Point(point);
                return EOF;
        }
        check = change_Type(graph, point, type);
        if (check != 0) {
                if (check == 1) {
                        printf("Граф не инициализирован\n");
                }
                if (check == 2) {
                        printf("Вершины с такими координатами не найдено\n");
                }
        }
        return check;
}

int remove_vertex(Graph* graph) {
        Point* point = input_point();
        if (point == NULL) {
                return EOF;
        }
        int check = remove_Vertex(graph, point);
        if (check != 0) {
                if (check == 1) {
                        printf("Граф не инициализирован\n");
                }
                if (check == 2) {
                        printf("Вершины с такими координатами не найдено\n");
                }
        }
        return check;
}

int remove_edge(Graph* graph) {
        printf("Введите координаты вершин, между которыми находится ребро:\n");
        Point* point1 = input_point();
        if (point1 == NULL) {
                return EOF;
        }
        Point* point2 = input_point();
        if (point2 == NULL) {
                return EOF;
        }
        int check = remove_Edge(graph, point1, point2);
        if (check != 0) {
                if (check == 1) {
                        printf("Граф не инициализирован\n");
                }
                if (check == 2) {
                        printf("Вершин с такими координатами не найдено\n");
                }
                if (check == 3) {
                        printf("Между указанными вершинами нет ребра\n");
                }
        }
        return check;
}

int checking_reachability(Graph* graph) {
        Point* point = input_point();
        if (point == NULL) {
                return EOF;
        }
        int check = checking_Whether(graph, point);
        if (check == 0) {
                printf("Из этой вершины достижим как минимум один выход\n");
        }
        if (check == 1) {
                printf("Граф не инициализирован\n");
        }
        if (check == 2) {
                printf("Вершины с такими координатами не найдено\n");
        }
        if (check == 3) {
                printf("Данная вершина не является входом в лабиринт\n");
        }
        if (check == 4) {
                printf("Из этой вершины не достижим ни один из выходов\n");
        }
        return check;
}

int find_shortest_way(Graph* graph) {
        printf("Введите координаты входа и выхода:\n");
        Point* point1 = input_point();
        if (point1 == NULL) {
                return EOF;
        }
        Point* point2 = input_point();
        if (point2 == NULL) {
                return EOF;
        }
        int check = 0;
        Queue* queue = shortest_way(graph, point1, point2, &check);
        if (check != 0) {
                if (check == 1) {
                        printf("Граф не инициализирован\n");
                }
                if (check == 2) {
                        printf("Вершин с такими координатами не найдено\n");
                }
                if (check == 3) {
                        printf("Указанные точки не являются входом и выходом из лабиринта\n");
                }
                if (check == 4) {
                        printf("Между этими вершинами нет никакого пути\n");
                }
                return check;
        }
        printf("Найденный путь:  ");
        print_Queue(queue);
        delete_Queue(queue);
        return 0;
}

int find_nearest_exit(Graph* graph) {
        Point* point = input_point();
        if (point == NULL) {
                return EOF;
        }
        int check = 0;
        uint dist = 0;
        Queue* queue = nearest_exit(graph, point, &check, &dist);
        if (check == 0) {
                printf("Ближайший выход: ");
                print_Queue(queue);
                printf("Путь до него: ");
                printf("%u\n", dist);
        }
        if (check == 1) {
                printf("Граф не инициализирован\n");
        }
        if (check == 2) {
                printf("Вершины с такими координатами не найдено\n");
        }
        if (check == 3) {
                printf("Указанная точка не является входом в лабиринт\n");
        }
        if (check == 4) {
                printf("Из этой вершины не достижим ни один из выходов\n");
        }
        delete_Queue(queue);
        return 0;
}

int print_graph(Graph* graph) {
        print_Graph_better(graph);
        return 0;
}

int print_graph_with_change(Graph* graph) {
        printf("1: Матрица смежности\n2: Граф\n3: Вывод в файл\n");
        int menu = 0;
        int check = inputint(&menu, 1, 3);
        if (check == EOF) {
                return EOF;
        }
        if (menu == 1) {
                print_Graph(graph);
                return 0;
        }
        if (menu == 2) {
                print_Graph_better(graph);
                return 0;
        }
        printf("Введите имя файла: ");
        char* filename = readline("");
        if (filename == NULL) {
                return EOF;
        }
        print_to_paint(graph, filename);
        if (check == 1) {
                printf("Граф не инициализирован\n");
        }
        if (check == 2) {
                printf("Не удалось открыть файл\n");
        }
        return check;
}

int make_graph_example(Graph* graph) {
        Point* point1 = create_Point(1, 1);
        insert_Vertex(graph, point1, 1);
        Point* point2 = create_Point(1, 2);
        insert_Vertex(graph, point2, 3);
        Point* point3 = create_Point(1, 1);
        Point* point4 = create_Point(1, 2);
        insert_Edge(graph, point3, point4);
        Point* point5 = create_Point(1, 3);
        insert_Vertex(graph, point5, 3);
        Point* point6 = create_Point(1, 2);
        Point* point7 = create_Point(1, 3);
        insert_Edge(graph, point6, point7);
        Point* point8 = create_Point(2, 3);
        insert_Vertex(graph, point8, 2);
        Point* point9 = create_Point(1, 3);
        Point* point10 = create_Point(2, 3);
        insert_Edge(graph, point9, point10);
        Point* point11 = create_Point(3, 3);
        insert_Vertex(graph, point11, 3);
        Point* point12 = create_Point(2, 3);
        Point* point13 = create_Point(3, 3);
        insert_Edge(graph, point12, point13);
        Point* point14 = create_Point(2, 1);
        insert_Vertex(graph, point14, 3);
        Point* point15 = create_Point(1, 1);
        Point* point16 = create_Point(2, 1);
        insert_Edge(graph, point15, point16);
        Point* point17 = create_Point(3, 1);
        insert_Vertex(graph, point17, 3);
        Point* point18 = create_Point(2, 1);
        Point* point19 = create_Point(3, 1);
        insert_Edge(graph, point18, point19);
        Point* point20 = create_Point(3, 2);
        insert_Vertex(graph, point20, 3);
        Point* point21 = create_Point(3, 1);
        Point* point22 = create_Point(3, 2);
        insert_Edge(graph, point21, point22);
        Point* point23 = create_Point(3, 2);
        Point* point24 = create_Point(3, 3);
        insert_Edge(graph, point23, point24);
        Point* point25 = create_Point(4, 2);
        insert_Vertex(graph, point25, 2);
        Point* point26 = create_Point(3, 2);
        Point* point27 = create_Point(4, 2);
        insert_Edge(graph, point26, point27);
        Point* point28 = create_Point(5, 2);
        insert_Vertex(graph, point28, 3);
        Point* point29 = create_Point(4, 2);
        Point* point30 = create_Point(5, 2);
        insert_Edge(graph, point29, point30);
        Point* point31 = create_Point(5, 1);
        insert_Vertex(graph, point31, 3);
        Point* point32 = create_Point(5, 2);
        Point* point33 = create_Point(5, 1);
        insert_Edge(graph, point32, point33);
        Point* point34 = create_Point(8, 2);
        insert_Vertex(graph, point34, 2);
        Point* point35 = create_Point(2, 5);
        insert_Vertex(graph, point35, 1);
        Point* point36 = create_Point(3, 5);
        insert_Vertex(graph, point36, 3);
        Point* point37 = create_Point(2, 5);
        Point* point38 = create_Point(3, 5);
        insert_Edge(graph, point37, point38);
        Point* point39 = create_Point(4, 5);
        insert_Vertex(graph, point39, 3);
        Point* point40 = create_Point(3, 5);
        Point* point41 = create_Point(4, 5);
        insert_Edge(graph, point40, point41);
        return 0;
}

void delete_graph(Graph* graph) {
        delete_Graph(graph);
}