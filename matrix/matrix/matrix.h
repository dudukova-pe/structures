#ifndef MATRIX_H
#define MATRIX_H

typedef struct Matrix {
	int count_lines;
	Line* lines;
} Matrix;

Matrix* create_matrix(int count);
void print_matrix(Matrix* matrix);
int put_matrix(Matrix* matrix);
void delete_matrix(Matrix* matrix);

#endif /*MATRIX_H*/