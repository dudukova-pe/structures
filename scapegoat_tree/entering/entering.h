#ifndef ENTERING_H
#define ENTERING_H
#include <stdio.h>

int inputint(int* value, int left, int right);
int inputuint(unsigned int* value, unsigned int left, unsigned int right);
int inputfloat(float* value, float left, float right);
char* txt_readline(FILE* file);
char* my_readline(const char* msg);

#endif /*ENTERING_H*/