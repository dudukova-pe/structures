#include <stdio.h>
#include "./graph.h"

uint get_x(Point* point) {
        if (point == NULL) {
                return 0;
        }
        return point->x;
}

uint get_y(Point* point) {
        if (point == NULL) {
                return 0;
        }
        return point->y;
}

Point* get_point(Vertex* vertex) {
        if (vertex == NULL) {
                return NULL;
        }
        return vertex->point;
}

int get_type(Vertex* vertex) {
        if (vertex == NULL) {
                return 0;
        }
        return vertex->type;
}

Vertex* get_adjanced_vertex(Edge* edge) {
        if (edge == NULL) {
                return NULL;
        }
        return edge->adjanced_vertex;
}

Edge* get_next_Edge(Edge* edge) {
        if (edge == NULL) {
                return NULL;
        }
        return edge->next;
}

Vertex* get_vertex(List* list) {
        if (list == NULL) {
                return NULL;
        }
        return list->vertex;
}

Edge* get_edges(List* list) {
        if (list == NULL) {
                return NULL;
        }
        return list->edges;
}

List* get_list(Matrix* matrix) {
        if (matrix == NULL) {
                return NULL;
        }
        return matrix->list;
}

Matrix* get_next_Matrix(Matrix* matrix) {
        if (matrix == NULL) {
                return NULL;
        }
        return matrix->next;
}

Matrix* get_first(Graph* graph) {
        if (graph == NULL) {
                return NULL;
        }
        return graph->first;
}

void set_x(Point* point, uint x) {
        if (point != NULL) {
                point->x = x;
        }
}

void set_y(Point* point, uint y) {
        if (point != NULL) {
                point->y = y;
        }
}

void set_point(Vertex* vertex, Point* point) {
        if (vertex != NULL) {
                vertex->point = point;
        }
}

void set_type(Vertex* vertex, int type) {
        if (vertex != NULL) {
                vertex->type = type;
        }
}

void set_adjanced_vertex(Edge* edge, Vertex* adjancded_vertex) {
        if (edge != NULL) {
                edge->adjanced_vertex = adjancded_vertex;
        }
}

void set_next_Edge(Edge* edge, Edge* next) {
        if (edge != NULL) {
                edge->next = next;
        }
}

void set_vertex(List* list, Vertex* vertex) {
        if (list != NULL) {
                list->vertex = vertex;
        }
}

void set_edges(List* list, Edge* edges) {
        if (list != NULL) {
                list->edges = edges;
        }
}

void set_list(Matrix* matrix, List* list) {
        if (matrix != NULL) {
                matrix->list = list;
        }
}

void set_next_Matrix(Matrix* matrix, Matrix* next) {
        if (matrix != NULL) {
                matrix->next = next;
        }
}

void set_first(Graph* graph, Matrix* first) {
        if (graph != NULL) {
                graph->first = first;
        }
}