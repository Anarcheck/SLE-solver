#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>


#define EPS 1e-8

extern size_t debug_print;              
extern size_t errors_print;                 
extern size_t time_print;
extern size_t matrix_print;


int lss_11_09(int n, double* a, double* c, double* d, double* b, double* x);
void help_print();
