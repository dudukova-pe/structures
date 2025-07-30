#include <stdio.h>
#include <stdlib.h>
#include "../lines/lines.h"
#include <limits.h>
#include "../entering/entering.h"

typedef struct Matrix {
	int count_lines;
	Line* lines;
} Matrix;

Matrix* create_matrix(int count) {
	Matrix* matrix = (Matrix*)calloc(1, sizeof(Matrix));
	matrix->count_lines = count;
	matrix->lines = (Line*)calloc(count, sizeof(Line));
	return matrix;
}

void print_matrix(const Matrix* matrix) {
	for (int i = 0; i < matrix->count_lines; i++) {
		print_line(&matrix->lines[i]);
	}
}

void delete_matrix(Matrix* matrix) {
	for (int i = 0; i < matrix->count_lines; i++) {
		delete_line(&(matrix->lines[i]));
	}
	free(matrix->lines);
}

int put_matrix(Matrix* matrix) {
	for (int i = 0; i < matrix->count_lines; i++) {
		int count = 0;
		printf("Введите количество элементов в строке: ");
		int check_enter = inputint(&count, 0, INT_MAX);
		if (check_enter == EOF) {
			matrix->count_lines = i;
			delete_matrix(matrix);
			return EOF;
		}
		matrix->lines[i] = create_line(count);
		check_enter = put_line(&matrix->lines[i]);
		if (check_enter == EOF) {
			matrix->count_lines = i;
			delete_matrix(matrix);
			return EOF;
		}
	}
	return 0;
}