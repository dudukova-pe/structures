#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include </home/students/d/dudukova.pe/files/entering/entering.h>

int memory_N(int **array, int size_array, int *capacity_array, int N) {
        if (((*capacity_array - size_array) < 0) || ((*capacity_array - size_array) >= N)) {
                *capacity_array = ((size_array / N) + (size_array % N == 0 ? 0 : 1)) * N;
                int *tmp = (int *)realloc(*array, *capacity_array * sizeof(int));
                if (tmp == NULL) {
                        return -1;
                }
                *array = tmp;
                return 1;
        }

        if (size_array == 0) {
                *capacity_array = 0;
                free(*array);
                return 2;
        }

        return 0;
}

void print_int_array(int *array, int size_array, int capacity_array, const char *msg) {
        printf("%s", msg);
        for (int i = 0; i < size_array; i++) {
                printf("%d ", array[i]);
        }
        for (int i = size_array; i < capacity_array; i++) {
                printf("%c ", 'x');
        }
        printf("\n");
}

void print_arrays(int *A, int *B, int size_A, int size_B, int capacity_A, int capacity_B, const char *msg_A, const char *msg_B) {
        print_int_array(A, size_A, capacity_A, msg_A);
        print_int_array(B, size_B, capacity_B, msg_B);
}

int initialization(int **array, int *size_array, int *capacity_array, int N) {

        if (size_array == 0) {
                return 0;
        }

        if (memory_N(array, *size_array, capacity_array, N) == -1) {
                return 1;
        }

        for (int i = 0; i < *size_array; i++) {
                printf("array[%d] = ", i);
                if (inputint(&(*array)[i], INT_MIN, INT_MAX) == EOF) {
                        return EOF;
                }
        }
        printf("\n");
        return 0;
}

int insert_elem(int **array, int *size_array, int *capacity_array, int N, int num_elem, int elem) {

        if (num_elem < 0) {
                return 2;
        }

        if (num_elem > *size_array) {
                num_elem = *size_array;
        }

        *size_array += 1;
        if (memory_N(array, *size_array, capacity_array, N) == -1) {
                return 1;
        }

        for (int i = *size_array - 1; i > num_elem; i--) {
                (*array)[i] = (*array)[i - 1];
        }
        (*array)[num_elem] = elem;

        return 0;
}

int remove_elem(int **array, int *size_array, int *capacity_array, int N, int num_elem) {

        if (*size_array <= 0) {
                return 3;
        }

        if ((num_elem < 0) || (num_elem >= (*size_array))) {
                return 2;
        }

        if ((*size_array == 1) && (num_elem == 0)) {
                free(*array);
                return 0;
        }

        for (int i = num_elem; i < (*size_array - 1); i++) {
                (*array)[i] = (*array)[i + 1];
        }

        *size_array -= 1;
        if (memory_N(array, *size_array, capacity_array, N) == -1) {
                return 1;
        }

        return 0;
}

int make_odd_even(int **array, int **C, int *size_array, int *size_C, int *capacity_array, int *capacity_C, int N, int marker) {
        for (int i = 0; i < *size_array; i++) {
                if ((*array)[i] % 2 == marker) {
                        if (insert_elem(C, size_C, capacity_C, N, *size_C + 1, (*array)[i]) == 1) {
                                return 1;
                        }
                        if (remove_elem(array, size_array, capacity_array, N, i) == 1) {
                                return 1;
                        }

                        i -= 1;
                }
        }
        return 0;
}