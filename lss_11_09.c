#include "lss_11_09.h"

size_t debug_print = 0;
size_t errors_print = 0;
size_t time_print = 0;
size_t matrix_print = 0;


int lss_11_09(int n, double* a, double* c, double* d, double* b, double* x)
{
    double *l, *lambda, *u, *y;
    l=(double*)calloc(n, sizeof(double));
    lambda=(double*)calloc(n-1, sizeof(double));
    u=(double*)calloc(n-1, sizeof(double));
    y=(double*)calloc(n, sizeof(double));
    
    l[0]=a[0];
    if (fabs(l[0])<EPS)
    {
        if (errors_print) printf("Unsuitable matrix");
        return -1;
    }
    u[0]=c[0]/l[0];
    if (debug_print)
    {
        printf("Step 1\n");
        printf("l[1]=%lf, u[1]=%lf\n\n", l[0], u[0]);
    }
    for (int i = 1; i < n-1; i++)
    {
        lambda[i-1]=d[i-1];
        l[i]=a[i]-lambda[i-1]*u[i-1];
        
        if (fabs(l[i])<EPS)
        {
            if (errors_print) printf("Unsuitable matrix");
            return -1;
        }
        
        u[i]=c[i]/l[i];
        if (debug_print)
        {
            printf("Step %d\n", i+1);
            printf("l[%d]=%lf, u[%d]=%lf, lambda[%d]=%lf\n", i+1, l[i], i+1, u[i], i, lambda[i-1]);
        }
    }

    lambda[n-2]=d[n-2];
    l[n-1]=a[n-1]-lambda[n-2]*u[n-2];
    if (debug_print)
    {
        printf("Step %d\n", n);
        printf("l[%d]=%lf, u[%d]=%lf, lambda[%d]=%lf\n\n", n, l[n-1], n-1, u[n-2], n-1, lambda[n-2]);
    }

    y[0]=b[0]/l[0];

    for (int i = 1; i < n; i++)
    {
        y[i]=(b[i]-lambda[i-1]*y[i-1])/l[i];
    }
    
    x[n-1]=y[n-1];
    for (int i = n-2; i >= 0 ; i--)
    {
        x[i]=y[i]-u[i]*x[i+1];
    }
    
    free(l); l=NULL;
    free(lambda); lambda=NULL;
    free(u); u=NULL;
    free(y); y=NULL;

    return 0;
}

void help_print()
{
    printf("Usage: lss [input_file_name] [output_file_name] [options]\n");
    printf("Where options include:\n");
    printf("\t-d\tprint debug messages [default OFF]\n");
    printf("\t-e\tprint errors [default OFF]\n");
    printf("\t-t\tprint execution time [default OFF]\n");
    printf("\t-h, -?\tprint help and exit\n");
    printf("Default input file name value is \"lss_11_09_in.txt\", default output file name value is \"lss_11_09_out.txt\".\n");
}
