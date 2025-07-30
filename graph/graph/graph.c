#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "./graph.h"
#include "../queue/queue.h"
#include "../matr/matr.h"

Point* create_Point(uint x, uint y) {
        Point* point = (Point*)calloc(1, sizeof(Point));
        set_x(point, x);
        set_y(point, y);
        return point;
}

Vertex* create_Vertex(Point* point, int type) {
        Vertex* vertex = (Vertex*)calloc(1, sizeof(Vertex));
        set_point(vertex, point);
        set_type(vertex, type);
        return vertex;
}

Edge* create_Edge(Vertex* adjanced_vertex) {
        Edge* edge = (Edge*)calloc(1, sizeof(Edge));
        set_adjanced_vertex(edge, adjanced_vertex);
        set_next_Edge(edge, NULL);
        return edge;
}

List* create_List(Vertex* vertex) {
        List* list = (List*)calloc(1, sizeof(List));
        set_vertex(list, vertex);
        set_edges(list, NULL);
        return list;
}

Matrix* create_Matrix(List* list) {
        Matrix* matrix = (Matrix*)calloc(1, sizeof(Matrix));
        set_list(matrix, list);
        set_next_Matrix(matrix, NULL);
        return matrix;
}

Graph* create_Graph() {
        Graph* graph = (Graph*)calloc(1, sizeof(Graph));
        set_first(graph, NULL);
        return graph;
}

uint count_spaces(Point* point) {
        uint x = get_x(point);
        uint y = get_y(point);
        uint count = 4;
        while (x > 0) {
                count += 1;
                x /= 10;
        }
        while (y > 0) {
                count += 1;
                y /= 10;
        }
        return count;
}

void print_vertex(Vertex* vertex) {
        int type = get_type(vertex);
        if (type == 1) {
                printf("\033[0;32m");
        }
        if (type == 2) {
                printf("\033[0;31m");
        }
        Point* point = get_point(vertex);
        printf("(%u, %u)", get_x(point), get_y(point));
        if (type != 3) {
                printf("\033[0;37m");
        }
}

uint print_header(Graph* graph) {
        uint count = 0;
        Matrix* ptr = get_first(graph);
        while (ptr != NULL) {
                List* list = get_list(ptr);
                Vertex* vertex = get_vertex(list);
                uint vertex_count = count_spaces(get_point(vertex));
                if (vertex_count > count) {
                        count = vertex_count;
                }
                ptr = get_next_Matrix(ptr);
        }
        for (int i = 0; i < count; i++) {
                printf(" ");
        }
        ptr = get_first(graph);
        while (ptr != NULL) {
                printf(" ");
                List* list = get_list(ptr);
                Vertex* vertex = get_vertex(list);
                print_vertex(vertex);
                ptr = get_next_Matrix(ptr);
        }
        printf("\n");
        return count;
}

void print_symbol(uint count, char symbol) {
        for (int i = 0; i < (count / 2); i++) {
                printf(" ");
        }
        printf("%c", symbol);
        uint spaces = count / 2;
        if (count % 2 == 0) {
                spaces -= 1;
        }
        for (int i = 0; i < spaces; i++) {
                printf(" ");
        }
}

void print_string(Graph* graph, Matrix* matrix, uint max_count) {
        Vertex* vertex = get_vertex(get_list(matrix));
        print_vertex(vertex);
        uint count = count_spaces(get_point(vertex));
        for (int i = count; i < max_count; i++) {
                printf(" ");
        }
        Matrix* ptr = get_first(graph);
        List* elem = get_list(ptr);
        while (ptr != NULL) {
                printf(" ");
                Edge* edge_ptr = get_edges(get_list(matrix));
                Vertex* vertex_matrix = get_vertex(elem);
                uint spaces = count_spaces(get_point(vertex_matrix));
                int check = 0;
                while (edge_ptr != NULL) {
                        Vertex* vertex_edge = get_adjanced_vertex(edge_ptr);
                        if (vertex_edge == vertex_matrix) {
                                check = 1;
                                break;
                        }
                        edge_ptr = get_next_Edge(edge_ptr);
                }
                (check == 1) ? print_symbol(spaces, '1') : print_symbol(spaces, '0');
                ptr = get_next_Matrix(ptr);
                elem = get_list(ptr);
        }
        printf("\n");
}

void print_Graph(Graph* graph) {
        uint count = print_header(graph);
    Matrix* ptr = get_first(graph);
    while (ptr != NULL) {
        print_string(graph, ptr, count);
        ptr = get_next_Matrix(ptr);
    }
        printf("\n");
}

void delete_Point(Point* point) {
        free(point);
}

void delete_vertex(Vertex* vertex) {
        delete_Point(get_point(vertex));
        free(vertex);
}

Edge* delete_Edge(Edge* edge) {
        Edge* next = get_next_Edge(edge);
        free(edge);
        return next;
}

void delete_Edges(Edge* edge) {
        Edge* ptr = edge;
        while (ptr != NULL) {
                ptr = delete_Edge(ptr);
        }
}

void delete_List(List* list) {
        delete_vertex(get_vertex(list));
        delete_Edges(get_edges(list));
        free(list);
}

Matrix* delete_Matrix(Matrix* matrix) {
        Matrix* next = get_next_Matrix(matrix);
        delete_List(get_list(matrix));
        free(matrix);
        return next;
}

void delete_Graph(Graph* graph) {
        Matrix* ptr = get_first(graph);
        while (ptr != NULL) {
                ptr = delete_Matrix(ptr);
        }
        free(graph);
}

Vertex* find_vertex(Graph* graph, Point* point) {
        uint x = get_x(point);
        uint y = get_y(point);
        Matrix* matrix = get_first(graph);
        Vertex* ptr = get_vertex(get_list(matrix));
        while (ptr != NULL) {
                Point* ptr_point = get_point(ptr);
                if ((get_x(ptr_point) == x) && (get_y(ptr_point) == y)) {
                        return ptr;
                }
                matrix = get_next_Matrix(matrix);
                ptr = get_vertex(get_list(matrix));
        }
        return NULL;
}

Matrix* find_matrix(Graph* graph, Point* point) {
        uint x = get_x(point);
        uint y = get_y(point);
        Matrix* matrix = get_first(graph);
        Vertex* ptr = get_vertex(get_list(matrix));
        while (ptr != NULL) {
                Point* ptr_point = get_point(ptr);
                if ((get_x(ptr_point) == x) && (get_y(ptr_point) == y)) {
                        return matrix;
                }
                matrix = get_next_Matrix(matrix);
                ptr = get_vertex(get_list(matrix));
        }
        return NULL;
}

Matrix* make_Matrix(Point* point, int type) {
        Vertex* vertex = create_Vertex(point, type);
        List* list = create_List(vertex);
        Matrix* matrix = create_Matrix(list);
        return matrix;
}

Matrix* find_place(Graph* graph) {
        Matrix* ptr = get_first(graph);
        while (get_next_Matrix(ptr) != NULL) {
                ptr = get_next_Matrix(ptr);
        }
        return ptr;
}

int insert_Vertex(Graph* graph, Point* point, int type) {
        if (graph == NULL) {
                return 1;
        }
        Vertex* check_copy = find_vertex(graph, point);
        if (check_copy != NULL) {
                return 2;
        }
        Matrix* matrix = make_Matrix(point, type);
        Matrix* place = find_place(graph);
        if (place == NULL) {
                set_next_Matrix(matrix, get_first(graph));
                set_first(graph, matrix);
                return 0;
        }
        set_next_Matrix(matrix, get_next_Matrix(place));
        set_next_Matrix(place, matrix);
        return 0;
}

int edge_conditional(Point* point1, Point* point2) {
        uint x1 = get_x(point1);
        uint y1 = get_y(point1);
        uint x2 = get_x(point2);
        uint y2 = get_y(point2);
        uint x_diff = (x1 > x2) ? (x1 - x2) : (x2 - x1);
        uint y_diff = (y1 > y2) ? (y1 - y2) : (y2 - y1);
        if ((x_diff + y_diff) == 1) {
                return 1;
        }
        return 0;
}

void insert_edge_to_list(Matrix* matrix, Vertex* vertex) {
        if ((matrix != NULL) && (vertex != NULL)) {
                List* list = get_list(matrix);
                Edge* edge = create_Edge(vertex);
                if (get_edges(list) == NULL) {
                        set_edges(list, edge);
                } else {
                        Edge* ptr = get_edges(list);
                        while (get_next_Edge(ptr) != NULL) {
                                ptr = get_next_Edge(ptr);
                        }
                        set_next_Edge(ptr, edge);
                }
        }
}

int insert_Edge(Graph* graph, Point* point1, Point* point2) {
        if (graph == NULL) {
                return 1;
        }
        Matrix* matrix1 = find_matrix(graph, point1);
        if (matrix1 == NULL) {
                return 2;
        }
        Matrix* matrix2 = find_matrix(graph, point2);
        if (matrix2 == NULL) {
                return 2;
        }
        Vertex* vertex1 = get_vertex(get_list(matrix1));
        Vertex* vertex2 = get_vertex(get_list(matrix2));
        int check = edge_conditional(point1, point2);
        delete_Point(point1);
        delete_Point(point2);
        if (check == 0) {
                return 3;
        }
        insert_edge_to_list(matrix1, get_vertex(get_list(matrix2)));
        insert_edge_to_list(matrix2, get_vertex(get_list(matrix1)));
        return 0;
}

int change_Type(Graph* graph, Point* point, int new_type) {
        if (graph == NULL) {
                return 1;
        }
        Matrix* matrix = find_matrix(graph, point);
        delete_Point(point);
        if (matrix == NULL) {
                return 2;
        }
        set_type(get_vertex(get_list(matrix)), new_type);
        return 0;
}

int remove_edge_from_edges(Matrix* matrix, Vertex* vertex) {
        List* list = get_list(matrix);
        Edge* ptr_prev = NULL;
        Edge* ptr = get_edges(list);
        while (ptr != NULL) {
                if (get_adjanced_vertex(ptr) == vertex) {
                        Edge* ptr_next = delete_Edge(ptr);
                        (ptr_prev == NULL) ? set_edges(list, ptr_next) : set_next_Edge(ptr_prev, ptr_next);
                        return 0;
                }
                ptr_prev = ptr;
                ptr = get_next_Edge(ptr);
        }
        return 1;
}

int remove_Edge(Graph* graph, Point* point1, Point* point2) {
        if (graph == NULL) {
                return 1;
        }
        Matrix* matrix1 = find_matrix(graph, point1);
        delete_Point(point1);
        if (matrix1 == NULL) {
                return 2;
        }
        Matrix* matrix2 = find_matrix(graph, point2);
        delete_Point(point2);
        if (matrix2 == NULL) {
                return 2;
        }
        int check = remove_edge_from_edges(matrix1, get_vertex(get_list(matrix2)));
        if (check == 1) {
                return 3;
        }
        check = remove_edge_from_edges(matrix2, get_vertex(get_list(matrix1)));
        if (check == 1) {
                return 3;
        }
        return 0;
}

int remove_Vertex(Graph* graph, Point* point) {
        if (graph == NULL) {
                return 1;
        }
        Matrix* matrix = find_matrix(graph, point);
        delete_Point(point);
        if (matrix == NULL) {
                return 2;
        }
        Matrix* matrix_prev = NULL;
        List* list = get_list(matrix);
        Vertex* vertex = get_vertex(list);
        Matrix* ptr = get_first(graph);
        while (ptr != NULL) {
                if (get_next_Matrix(ptr) == matrix) {
                        matrix_prev = ptr;
                }
                remove_edge_from_edges(ptr, vertex);
                ptr = get_next_Matrix(ptr);
        }
        Matrix* matrix_next = delete_Matrix(matrix);
        if (matrix_prev == NULL) {
                set_first(graph, matrix_next);
                return 0;
        }
        set_next_Matrix(matrix_prev, matrix_next);
        return 0;
}

Matrix* research_matrix(Graph* graph, Vertex* vertex) {
        Matrix* ptr_matrix = get_first(graph);
        while (ptr_matrix != NULL) {
                if (get_vertex(get_list(ptr_matrix)) == vertex) {
                        return ptr_matrix;
                }
                ptr_matrix = get_next_Matrix(ptr_matrix);
        }
        return NULL;
}

int checking_Whether(Graph* graph, Point* point) {
        if (graph == NULL) {
                return 1;
        }
        Matrix* matrix = find_matrix(graph, point);
        delete_Point(point);
        if (matrix == NULL) {
                return 2;
        }
        List* list = get_list(matrix);
        Vertex* vertex = get_vertex(list);
        if (get_type(vertex) != 1) {
                return 3;
        }
        Queue* queue = create_Queue();
        Queue* queue_checked = create_Queue();
        push(queue, matrix);
        while (check_empty(queue) == 0) {
                Matrix* ptr_matrix = (Matrix*)get_elem(queue);
                List* ptr_list = get_list(ptr_matrix);
                Vertex* ptr_vertex = get_vertex(ptr_list);
                if (get_type(ptr_vertex) == 2) {
                        delete_Queue(queue_checked);
                        delete_Queue(queue);
                        return 0;
                }
                Edge* ptr_edge = get_edges(ptr_list);
                while (ptr_edge != NULL) {
                        Vertex* adjanced_vertex = get_adjanced_vertex(ptr_edge);
                        Matrix* adjanced_matrix = research_matrix(graph, adjanced_vertex);
                        if ((check_comp(queue, adjanced_matrix) == 0) && (check_comp(queue_checked, adjanced_matrix) == 0)) {
                                push(queue, adjanced_matrix);
                        }
                        ptr_edge = get_next_Edge(ptr_edge);
                }
                pop(queue, NULL);
                push(queue_checked, ptr_matrix);
        }
        delete_Queue(queue_checked);
        delete_Queue(queue);
        return 4;
}

uint count_vertexes(Graph* graph) {
        Matrix* ptr = get_first(graph);
        uint count = 0;
        while (ptr != NULL) {
                count += 1;
                ptr = get_next_Matrix(ptr);
        }
        return count;
}

uint get_num_matrix(Graph* graph, Matrix* matrix) {
        uint count = 0;
        Matrix* ptr = get_first(graph);
        while (ptr != NULL) {
                if (ptr == matrix) {
                        break;
                }
                count += 1;
                ptr = get_next_Matrix(ptr);
        }
        return count;
}

Matrix* get_i_matrix(Graph* graph, uint i) {
        uint max_i = count_vertexes(graph);
        if (i > max_i) {
                return NULL;
        }
        uint count = 0;
        Matrix* ptr = get_first(graph);
        while (count != i) {
                count += 1;
                ptr = get_next_Matrix(ptr);
        }
        return ptr;
}

int check_adjanced(Matrix* matrix1, Matrix* matrix2) {
        if ((matrix1 == NULL) || (matrix2 == NULL)) {
                return 0;
        }
        Vertex* vertex2 = get_vertex(get_list(matrix2));
        Edge* ptr = get_edges(get_list(matrix1));
        while (ptr != NULL) {
                if (get_adjanced_vertex(ptr) == vertex2) {
                        return 1;
                }
                ptr = get_next_Edge(ptr);
        }
        return 0;
}

void count_dist(Matr* matr, uint count_vertex, uint i, uint j) {
        Matrix* matrix = get_ij_elem(matr, i, j);
        for (int k = 0; k < count_vertex; k++) {
                Matrix* adjanced = get_ij_elem(matr, k, j - 1);
                if ((check_adjanced(matrix, adjanced) == 1) || (matrix == adjanced)) {
                        uint adjanced_dist = get_ij_dist(matr, k, j - 1);
                        if ((matrix != adjanced) && (adjanced_dist != UINT_MAX)) {
                                adjanced_dist += 1;
                        }
                        uint current_dist = get_ij_dist(matr, i, j);
                        if ((adjanced_dist < current_dist) && (adjanced_dist != UINT_MAX)) {
                                set_ij_dist(matr, adjanced_dist, i, j);
                                set_ij_parent(matr, adjanced, i, j);
                        }
                }
        }
}

Queue* shortest_way(Graph* graph, Point* point1, Point* point2, int* result) {
        if (graph == NULL) {
                *result = 1;
                return NULL;
        }
        Matrix* matrix_enter = find_matrix(graph, point1);
        delete_Point(point1);
        if (matrix_enter == NULL) {
                *result = 2;
                return NULL;
        }
        List* list_enter = get_list(matrix_enter);
        Vertex* vertex_enter = get_vertex(list_enter);
        if (get_type(vertex_enter) != 1) {
                *result = 3;
                return NULL;
        }
        Matrix* matrix_exit = find_matrix(graph, point2);
        delete_Point(point2);
        if (matrix_exit == NULL) {
                *result = 2;
                return NULL;
        }
        List* list_exit = get_list(matrix_exit);
        Vertex* vertex_exit = get_vertex(list_exit);
        if (get_type(vertex_exit) != 2) {
                *result = 3;
                return NULL;
        }
        uint count_vertex = count_vertexes(graph);
        Matr* matr = create_Matr(count_vertex, count_vertex);
        for (uint j = 0; j < count_vertex; j++) {
                for (uint i = 0; i < count_vertex; i++) {
                        Matrix* ptr = get_i_matrix(graph, i);
                        set_ij_elem(matr, ptr, i, j);
                }
        }
        set_ij_dist(matr, 0, get_num_matrix(graph, matrix_exit), 0);
        for (uint j = 1; j < count_vertex; j++) {
                for (uint i = 0; i < count_vertex; i++) {
                        count_dist(matr, count_vertex, i, j);
                }
        }
        Matrix* ptr = NULL;
        uint i = 0;
        uint j = count_vertex - 1;
        for (i = 0; i < count_vertex; i++) {
                if (get_ij_elem(matr, i, j) == matrix_enter) {
                        ptr = get_ij_elem(matr, i, j);
                        break;
                }
        }
        Matrix* ptr_prev = NULL;
        if (get_ij_dist(matr, i, j) == UINT_MAX) {
                delete_Matr(matr, count_vertex, count_vertex);
                *result = 4;
                return NULL;
        }
        Queue* queue = create_Queue();
        while (ptr != NULL) {
                if (ptr_prev != ptr) {
                        push(queue, ptr);
                }
                ptr_prev = ptr;
                if ((i != UINT_MAX) || (j != UINT_MAX)) {
                        ptr = get_ij_parent(matr, i, j);
                }
                i = get_num_matrix(graph, ptr);
                j -= 1;
        }
        delete_Matr(matr, count_vertex, count_vertex);
        return queue;
}

uint count_matrix_size_x(Graph* graph) {
        uint max_count = 0;
        Matrix* ptr = get_first(graph);
        while (ptr != NULL) {
                Point* point = get_point(get_vertex(get_list(ptr)));
                uint x = get_x(point);
                if (x > max_count) {
                        max_count = x;
                }
                ptr = get_next_Matrix(ptr);
        }
        if (max_count == 0) {
                return 0;
        }
        return (1 + 2*(max_count - 1));
}

uint count_matrix_size_y(Graph* graph) {
        uint max_count = 0;
        Matrix* ptr = get_first(graph);
        while (ptr != NULL) {
                Point* point = get_point(get_vertex(get_list(ptr)));
                uint y = get_y(point);
                if (y > max_count) {
                        max_count = y;
                }
                ptr = get_next_Matrix(ptr);
        }
        if (max_count == 0) {
                return 0;
        }
        return (1 + 2*(max_count - 1));
}

void print_header_better(uint size_x) {
        printf("\n");
        for (uint i = 1; i <= ((size_x - 1) / 2 + 1); i++) {
                (i < 10) ? printf("%u ", i) : printf("%c ", 'A' + (i - 10));
        }
}

Matr* create_empty_matr(uint size_x, uint size_y, char* space) {
        Matr* matr = create_Matr(size_x, size_y);
        for (uint j = 0; j < size_y; j++) {
                for (uint i = 0; i < size_x; i++) {
                        set_ij_elem(matr, space, i, j);
                }
        }
        return matr;
}

void placement_vertex(Matr* matr, Graph* graph, char* enter, char* exit, char* normal) {
        Matrix* ptr = get_first(graph);
        while (ptr != NULL) {
                Vertex* vertex = get_vertex(get_list(ptr));
                Point* point = get_point(vertex);
                uint i = 2*(get_x(point) - 1);
                uint j = 2*(get_y(point) - 1);
                int type = get_type(vertex);
                if (type == 1) {
                        set_ij_elem(matr, enter, i, j);
                }
                if (type == 2) {
                        set_ij_elem(matr, exit, i, j);
                }
                if (type == 3) {
                        set_ij_elem(matr, normal, i, j);
                }
                ptr = get_next_Matrix(ptr);
        }
}


void placement_horizontal(Matr* matr, Graph* graph, uint size_x, uint size_y, char* horizontal) {
        for (uint j = 0; j < size_y; j += 2) {
                for (uint i = 1; i < size_x; i += 2) {
                        if ((*(char*)get_ij_elem(matr, i - 1, j) != ' ') && (*(char*)get_ij_elem(matr, i + 1, j) != ' ')) {
                                Point* point1 = create_Point(1 + (i - 1)/2, 1 + j/2);
                                Matrix* matrix1 = find_matrix(graph, point1);
                                delete_Point(point1);
                                Point* point2 = create_Point(1 + (i + 1)/2, 1 + j/2);
                                Matrix* matrix2 = find_matrix(graph, point2);
                                delete_Point(point2);
                                if (check_adjanced(matrix1, matrix2) == 1) {
                                        set_ij_elem(matr, horizontal, i, j);
                                }
                        }
                }
        }
}

void placement_vertical(Matr* matr, Graph* graph, uint size_x, uint size_y, char* vertical) {
        for (uint j = 1; j < size_y; j+= 2) {
                for (uint i = 0; i < size_x; i += 2) {
                        if ((*(char*)get_ij_elem(matr, i, j - 1) != ' ') && (*(char*)get_ij_elem(matr, i, j + 1) != ' ')) {
                                Point* point1 = create_Point(1 + i/2, 1 + (j - 1)/2);
                                Matrix* matrix1 = find_matrix(graph, point1);
                                delete_Point(point1);
                                Point* point2 = create_Point(1 + i/2, 1 + (j + 1)/2);
                                Matrix* matrix2 = find_matrix(graph, point2);
                                delete_Point(point2);
                                if (check_adjanced(matrix1, matrix2) == 1) {
                                        set_ij_elem(matr, vertical, i, j);
                                }
                        }
                }
        }
}

void print_matr(Matr* matr, uint size_x, uint size_y) {
        printf("\n");
        for (uint j = 0; j < size_y; j++) {
                for (uint i = 0; i < size_x; i++) {
                        char symbol = *(char*)(get_ij_elem(matr, i, j));
                        if (symbol == '1') {
                                printf("\033[0;32m");
                                printf("%c", 'O');
                                printf("\033[0;37m");
                        }
                        if (symbol == '2') {
                                printf("\033[0;31m");
                                printf("%c", 'O');
                                printf("\033[0;37m");
                        }
                        if ((symbol != '1') && (symbol != '2')) {
                                printf("%c", symbol);
                        }
                }
                printf("\n");
        }
        printf("\n");
}

void print_Graph_better(Graph* graph) {
        char space = ' ';
        char enter = '1';
        char exit = '2';
        char normal = 'O';
        char horizontal = '-';
        char vertical = '|';
        uint matr_size_x = count_matrix_size_x(graph);
        uint matr_size_y = count_matrix_size_y(graph);
        if ((matr_size_x > 0) && (matr_size_y)) {
                print_header_better(matr_size_x);
                Matr* matr = create_empty_matr(matr_size_x, matr_size_y, &space);
                placement_vertex(matr, graph, &enter, &exit, &normal);
                placement_horizontal(matr, graph, matr_size_x, matr_size_y, &horizontal);
                placement_vertical(matr, graph, matr_size_x, matr_size_y, &vertical);
                print_matr(matr, matr_size_x, matr_size_y);
                delete_Matr(matr, matr_size_x, matr_size_y);
        }
}

void correct_filename(char* filename) {
        while (filename[strlen(filename) - 1] == ' ') {
                filename[strlen(filename) - 1] = '\0';
        }
}

void print_to_paint_vertex(Vertex* vertex, FILE* file) {
        Point* point = get_point(vertex);
        fprintf(file, "\"(%u, %u)\"", get_x(point), get_y(point));
}

void print_to_paint_for_matrix(Graph* graph, Matrix* matrix, FILE* file) {
        uint matrix_num = get_num_matrix(graph, matrix) + 1;
        List* list = get_list(matrix);
        Vertex* vertex = get_vertex(list);
        if (get_type(vertex) == 1) {
                fprintf(file, "\t");
                print_to_paint_vertex(vertex, file);
                fprintf(file, " [color = \"green\"]\n");
        }
        if (get_type(vertex) == 2) {
                fprintf(file, "\t");
                print_to_paint_vertex(vertex, file);
                fprintf(file, " [color = \"red\"]\n");
        }
        Edge* ptr = get_edges(list);
        if (ptr == NULL) {
                print_to_paint_vertex(vertex, file);
                printf("\n");
        }
        while (ptr != NULL) {
                Matrix* adjanced = research_matrix(graph, get_adjanced_vertex(ptr));
                if ((get_num_matrix(graph, adjanced) + 1) > matrix_num) {
                        fprintf(file, "\t");
                        print_to_paint_vertex(vertex, file);
                        fprintf(file, "--");
                        print_to_paint_vertex(get_adjanced_vertex(ptr), file);
                        fprintf(file, "\n");
                }
                ptr = get_next_Edge(ptr);
        }
}

int print_to_paint(Graph* graph, char* filename) {
        if (graph == NULL) {
                return 1;
        }
        correct_filename(filename);
        FILE* file = fopen(filename, "w");
        if (file == NULL) {
                return 2;
        }
        fprintf(file, "graph {\n");
        Matrix* ptr = get_first(graph);
        while (ptr != NULL) {
                print_to_paint_for_matrix(graph, ptr, file);
                ptr = get_next_Matrix(ptr);
        }
        free(filename);
        fprintf(file, "}");
        return 0;
}

Queue* nearest_exit(Graph* graph, Point* point, int* result, uint* dist) {
        if (graph == NULL) {
                *result = 1;
                delete_Point(point);
                return NULL;
        }
        Matrix* enter = find_matrix(graph, point);
        delete_Point(point);
        if (enter == NULL) {
                *result = 2;
                return NULL;
        }
        if (get_type(get_vertex(get_list(enter))) != 1) {
                *result = 3;
                return NULL;
        }
        uint count_vertex = count_vertexes(graph);
        Matr* matr = create_Matr(count_vertex, count_vertex);
        for (uint i = 0; i < count_vertex; i++) {
                set_ij_dist(matr, 0, i, i);
        }
        for (uint j = 0; j < count_vertex; j++) {
                Matrix* matrix_j = get_i_matrix(graph, j);
                for (uint i = 0; i < count_vertex; i++) {
                        Matrix* matrix_i = get_i_matrix(graph, i);
                        if (check_adjanced(matrix_i, matrix_j) == 1) {
                                set_ij_dist(matr, 1, i, j);
                        }
                }
        }
        for (uint k = 0; k < count_vertex; k++) {
                for (uint j = 0; j < count_vertex; j++) {
                        uint dist_kj = get_ij_dist(matr, k, j);
                        for (uint i = 0; i < count_vertex; i++) {
                                uint dist_ik = get_ij_dist(matr, i, k);
                                uint dist_ij = get_ij_dist(matr, i, j);
                                if ((dist_ik != UINT_MAX) && (dist_kj != UINT_MAX)) {
                                        if ((dist_ik + dist_kj) < dist_ij) {
                                                set_ij_dist(matr, dist_ik + dist_kj, i, j);
                                        }
                                }
                        }
                }
        }
        uint j = get_num_matrix(graph, enter);
        uint min_dist = UINT_MAX;
        Matrix* exit = NULL;
        for (uint i = 0; i < count_vertex; i++) {
                Matrix* ptr = get_i_matrix(graph, i);
                if (get_type(get_vertex(get_list(ptr))) == 2) {
                        uint ptr_dist = get_ij_dist(matr, i, j);
                        if (ptr_dist < min_dist) {
                                min_dist = ptr_dist;
                                exit = ptr;
                        }
                }
        }
        Queue* queue = create_Queue();
        if (exit != NULL) {
                push(queue, exit);
        }
        *dist = min_dist;
        if (check_empty(queue) == 1) {
                *result = 4;
                delete_Matr(matr, count_vertex, count_vertex);
                delete_Queue(queue);
                return NULL;
        }
        delete_Matr(matr, count_vertex, count_vertex);
        return queue;
}

void print_Queue(Queue* queue) {
        void* result = NULL;
        while (check_empty(queue) == 0) {
                pop(queue, &result);
                print_vertex(get_vertex(get_list((Matrix*)result)));
                printf(" ");
        }
        printf("\n");
}