#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../entering/entering.h"

typedef struct Line {
	int count_elems;
	int* array;
} Line;

Line create_line(int len) {
	Line line;
	line.count_elems = len;
	line.array = (int*)calloc(len, sizeof(int));
	return line;
}

void print_line(Line* line) {
	for (int i = 0; i < line->count_elems; i++) {
		printf("%d ", (line->array)[i]);
	}
	printf("\n");
}

void delete_line(Line* line) {
	free(line->array);
}

int put_line(Line* line) {
	for (int i = 0; i < line->count_elems; i++) {
		int check_enter = inputint(&((line->array)[i]), INT_MIN, INT_MAX);
		if (check_enter == EOF) {
			line->count_elems = i;
			delete_line(line);
			return EOF;
		}
	}
	return 0;
}