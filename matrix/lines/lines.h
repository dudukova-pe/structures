#ifndef LINES_H
#define LINES_H

typedef struct Line {
	int count_elems;
	int* array;
} Line;

Line create_line(int len);
void print_line(Line* line);
void delete_line(Line* line);
int put_line(Line* line);

#endif /*LINES_H*/