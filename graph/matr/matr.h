#ifndef MATR_H
#define MATR_H

typedef struct Cell {
        void* data;
        void* parent;
        unsigned int dist;
} Cell;

typedef struct Line {
        Cell** elems;
} Line;

typedef struct Matr {
        Line** lines;
} Matr;

Matr* create_Matr(unsigned int i, unsigned int j);
void delete_Matr(Matr* matr, unsigned int i, unsigned int j);
void* get_ij_elem(Matr* matr, unsigned int i, unsigned int j);
void* get_ij_parent(Matr* matr, unsigned i, unsigned int j);
unsigned int get_ij_dist(Matr* matr, unsigned int i, unsigned int j);
void set_ij_elem(Matr* matr, void* data, unsigned int i, unsigned int j);
void set_ij_parent(Matr* matr, void* parent, unsigned int i, unsigned int j);
void set_ij_dist(Matr* matr, unsigned int dist, unsigned int i, unsigned int j);

#endif /*MATR_H*/