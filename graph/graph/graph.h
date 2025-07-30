#ifndef GRAPH_H
#define GRAPH_H
#include "../queue/queue.h"

typedef unsigned int uint;

typedef struct Point {
        uint x;
        uint y;
} Point;

typedef struct Vertex {
        Point* point;
        int type;
} Vertex;

typedef struct Edge {
        Vertex* adjanced_vertex;
        struct Edge* next;
} Edge;

typedef struct List {
        Vertex* vertex;
        Edge* edges;
} List;

typedef struct Matrix {
        List* list;
        struct Matrix* next;
} Matrix;

typedef struct Graph {
        Matrix* first;
} Graph;

uint get_x(Point* point);
uint get_y(Point* point);
Point* get_point(Vertex* vertex);
int get_type(Vertex* vertex);
Vertex* get_adjanced_vertex(Edge* edge);
Edge* get_next_Edge(Edge* edge);
Vertex* get_vertex(List* list);
Edge* get_edges(List* list);
List* get_list(Matrix* matrix);
Matrix* get_next_Matrix(Matrix* matrix);
Matrix* get_first(Graph* graph);
void set_x(Point* point, uint x);
void set_y(Point* point, uint y);
void set_point(Vertex* vertex, Point* point);
void set_type(Vertex* vertex, int type);
void set_adjanced_vertex(Edge* edge, Vertex* adjancded_vertex);
void set_next_Edge(Edge* edge, Edge* next);
void set_vertex(List* list, Vertex* vertex);
void set_edges(List* list, Edge* edges);
void set_list(Matrix* matrix, List* list);
void set_next_Matrix(Matrix* matrix, Matrix* next);
void set_first(Graph* graph, Matrix* first);

Point* create_Point(uint x, uint y);
Graph* create_Graph();
void print_Graph(Graph* graph);
void print_Graph_better(Graph* graph);
int print_to_paint(Graph* graph, char* filename);
int insert_Vertex(Graph* graph, Point* point, int type);
int insert_Edge(Graph* graph, Point* point1, Point* point2);
int change_Type(Graph* graph, Point* point, int new_type);
int remove_Vertex(Graph* graph, Point* point);
int remove_Edge(Graph* graph, Point* point1, Point* point2);
int checking_Whether(Graph* grpah, Point* point);
Queue* shortest_way(Graph* graph, Point* point1, Point* point2, int* result);
Queue* nearest_exit(Graph* graph, Point* point, int* result, uint* dist);
void delete_Point(Point* point);
void delete_Graph(Graph* graph);
void print_Queue(Queue* queue);

#endif /*GRAPH_H*/