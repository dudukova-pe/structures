#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int inputint(int *value, int left, int right) {
	int checkenter = scanf("%d", value);
	while ((checkenter != 1) || (*value < left) || (*value > right)) {
		if (checkenter == -1) {
			printf("\nthe program has stopped\n");
			return EOF;
		}
		printf("incorrect number\nenter again: ");
		scanf("%*[^\n]");
		checkenter = scanf("%d", value);
	}
	return 0;
}

char* txt_readline(FILE* file) {
	char* res = (char*)calloc(1, sizeof(char));
	char buf[81];
	int res_len = 0;
	int check_enter = 1;
	while (check_enter == 1) {
		check_enter = fscanf(file, "%80[^\n]", buf);
		if (check_enter == EOF) {
			free(res);
			return NULL;
		}
		if (check_enter == 0) {
			fscanf(file, "%*c");
		}
		if (check_enter > 0) {
			int buf_len = strlen(buf);
			res_len += buf_len;
			res = (char*)realloc(res, (res_len + 1) * sizeof(char));
			memcpy(res + res_len - buf_len, buf, (buf_len + 1) * sizeof(char));
		}
	}
	return res;
}
