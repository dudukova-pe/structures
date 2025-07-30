#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "matr.h"

void* get_data(Cell* elem) {
        if (elem == NULL) {
                return NULL;
        }
        return elem->data;
}

void* get_parent(Cell* elem) {
        if (elem == NULL) {
                return NULL;
        }
        return elem->parent;
}

unsigned int get_dist(Cell* elem) {
        if (elem == NULL) {
                return UINT_MAX;
        }
        return elem->dist;
}

Cell** get_elems(Line* line) {
        if (line == NULL) {
                return NULL;
        }
        return line->elems;
}

Cell* get_elem_from_line(Line* line, unsigned int num) {
        if (line == NULL) {
                return NULL;
        }
        if (get_elems(line) == NULL) {
                return NULL;
        }
        return line->elems[num];
}

Line** get_lines(Matr* matr) {
        if (matr == NULL) {
                return NULL;
        }
        return matr->lines;
}

Line* get_line_from_matr(Matr* matr, unsigned int num) {
        if (matr == NULL) {
                return NULL;
        }
        if (get_lines(matr) == NULL) {
                return NULL;
        }
        return matr->lines[num];
}

void* get_ij_elem(Matr* matr, unsigned int i, unsigned int j) {
        Line* line = get_line_from_matr(matr, j);
        if (line == NULL) {
                return NULL;
        }
        Cell** elems = get_elems(line);
        if (elems == NULL) {
                return NULL;
        }
        Cell* elem = elems[i];
        return get_data(elem);
}

void* get_ij_parent(Matr* matr, unsigned i, unsigned int j) {
        Line* line = get_line_from_matr(matr, j);
        if (line == NULL) {
                return NULL;
        }
        Cell** elems = get_elems(line);
        if (elems == NULL) {
                return NULL;
        }
        Cell* elem = elems[i];
        return get_parent(elem);
}

unsigned int get_ij_dist(Matr* matr, unsigned int i, unsigned int j) {
        Line* line = get_line_from_matr(matr, j);
        if (line == NULL) {
                return UINT_MAX;
        }
        Cell** elems = get_elems(line);
        if (elems == NULL) {
                return UINT_MAX;
        }
        Cell* elem = elems[i];
        return get_dist(elem);
}

void set_data(Cell* elem, void* data) {
        if (elem != NULL) {
                elem->data = data;
        }
}

void set_parent(Cell* elem, Cell* parent) {
        if (elem != NULL) {
                elem->parent = parent;
        }
}

void set_dist(Cell* elem, unsigned int dist) {
        if (elem != NULL) {
                elem->dist = dist;
        }
}

void set_elems(Line* line, Cell** elems) {
        if (line != NULL) {
                line->elems = elems;
        }
}

void set_lines(Matr* matr, Line** lines) {
        if (matr != NULL) {
                matr->lines = lines;
        }
}

void set_ij_elem(Matr* matr, void* data, unsigned int i, unsigned int j) {
        if (matr != NULL) {
                Line* line = get_line_from_matr(matr, j);
                if (line != NULL) {
                        Cell** elems = get_elems(line);
                        if (elems != NULL) {
                                Cell* elem = elems[i];
                                set_data(elem, data);
                        }
                }
        }
}

void set_ij_parent(Matr* matr, void* parent, unsigned int i, unsigned int j) {
        if (matr != NULL) {
                Line* line = get_line_from_matr(matr, j);
                if (line != NULL) {
                        Cell** elems = get_elems(line);
                        if (elems != NULL) {
                                Cell* elem = elems[i];
                                set_parent(elem, parent);
                        }
                }
        }
}

void set_ij_dist(Matr* matr, unsigned int dist, unsigned int i, unsigned int j) {
        if (matr != NULL) {
                Line* line = get_line_from_matr(matr, j);
                if (line != NULL) {
                        Cell** elems = get_elems(line);
                        if (elems != NULL) {
                                Cell* elem = elems[i];
                                set_dist(elem, dist);
                        }
                }
        }
}

Cell* create_Cell() {
        Cell* elem = (Cell*)calloc(1, sizeof(Cell));
        set_data(elem, NULL);
        set_parent(elem, NULL);
        set_dist(elem, UINT_MAX);
        return elem;
}

Line* create_Line(unsigned int i) {
        Line* line = (Line*)calloc(1, sizeof(Line));
        Cell** elems = calloc(i, sizeof(Cell*));
        set_elems(line, elems);
        for (unsigned int count = 0; count < i; count++) {
                elems[count] = create_Cell();
        }
        return line;
}

Matr* create_Matr(unsigned int i, unsigned int j) {
        Matr* matr = (Matr*)calloc(1, sizeof(Matr));
        Line** lines = (Line**)calloc(j, sizeof(Line*));
        set_lines(matr, lines);
        for (unsigned int count = 0; count < j; count++) {
                lines[count] = create_Line(i);
        }
        return matr;
}

void delete_Elem(Cell* elem) {
        free(elem);
}

void delete_line(Line* line, unsigned int i) {
        for (int count = 0; count < i; count++) {
                delete_Elem(get_elem_from_line(line, count));
        }
        free(get_elems(line));
        free(line);
}

void delete_Matr(Matr* matr, unsigned int i, unsigned int j) {
        for (unsigned int count = 0; count < j; count++) {
                delete_line(get_line_from_matr(matr, count), i);
        }
        free(get_lines(matr));
        free(matr);
}