#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "./entering/entering.h"
#include "./lines/lines.h"
#include "./matrix/matrix.h"

typedef struct Comp {
	int num;
	int* elements;
	int* count_elements;
} Comp;

Comp* create_comp(const Line* line, Comp* comp) {
	comp->num = 0;
	comp->elements = (int*)calloc(line->count_elems, sizeof(int));
	comp->count_elements = (int*)calloc(line->count_elems, sizeof(int));
	return comp;
}

void delete_comp(Comp* comp) {
	free(comp->elements);
	free(comp->count_elements);
	free(comp);
}

int max_num(const Line* line, Comp* comp) {
	comp = create_comp(line, comp);
	for (int j = 0; j < line->count_elems; j++) {
		int check = 0; 
		for (int k = 0; k < comp->num; k++) {
			if (line->array[j] == comp->elements[k]) {
				comp->count_elements[k] += 1;
				check = 1;
			}
			if (check == 1) {
				break;
			}
		}
		if (check == 0) {
			comp->elements[comp->num] = line->array[j];
			comp->count_elements[comp->num] = 1;
			comp->num += 1;
		}
	}
	int num = 0;
	for (int j = 0; j < comp->num; j++) {
		if (comp->count_elements[j] > comp->count_elements[num]) {
			num = j;
		}
	}
	return num;
}

void process(const Matrix* matrix, Line* vector) {
	for (int i = 0; i < matrix->count_lines; i++) {
		Comp* comp = (Comp*)calloc(1, sizeof(Comp));
		int most_common = max_num(&(matrix->lines[i]), comp);
		vector->array[i] = 0;
		if (matrix->lines[i].count_elems > 0) {
			vector->array[i] = comp->elements[most_common];
		}
		delete_comp(comp);
	}
}

int main() {
	int strings = 0;
	printf("Введите количество строк в матрице: ");
	int check_enter = inputint(&strings, 0, INT_MAX);
	if (check_enter == EOF) {
		return EOF;
	}
	Matrix* matrix = create_matrix(strings);
	check_enter = put_matrix(matrix);
	if (check_enter == EOF) {
		free(matrix);
		return EOF;
	}
	printf("\nИсходная матрица:\n");
	print_matrix(matrix);
	Line vector = create_line(matrix->count_lines);
	process(matrix, &vector);
	delete_matrix(matrix);
	free(matrix);
	printf("\nПолученный вектор: ");
	print_line(&vector);
	delete_line(&vector);
	return 0;
}
