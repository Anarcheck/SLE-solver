
#include "lss_11_09.h"



int main(int argc, char* argv[])
{

    clock_t start_time, stop_time;                   

    int num_of_eq, res;
    double* a, *c, *d, *b, *x;                                

    size_t index = 1;                               

    char* fin_name = "lss_11_09_in.txt";
    char* fout_name = "lss_11_09_out.txt";    

    if ((argc > 1) && (argv[1][0] != '-'))
    {
        fin_name = argv[1];
        index++;
    }

    if ((argc > 2) && (argv[2][0] != '-'))
    {
        fout_name = argv[2];
        index++;
    }
    

    for (size_t i = index; i < argc; ++i)
        switch (argv[i][1])
        {
            case 'd': debug_print = 1; 
            case 'p': matrix_print = 1; break; 
            case 'e': errors_print = 1; break;
            case 't': time_print = 1; break;

            case 'h':
            case '?':
                help_print();
                return 0;

            default:
                if (errors_print)
                    printf("Unknown option!");
                return -2;
        }
    FILE* fin= fopen(fin_name, "r"),
    *fout= fopen(fout_name,"w");

    if (!fin || !fout)
    {
        printf("Files opening error!");
        fclose(fin);
        fclose(fout);

        return -3;
    }

    fscanf(fin, "%d", &num_of_eq);

    a=(double*)calloc(num_of_eq, sizeof(double));
    b=(double*)calloc(num_of_eq, sizeof(double));
    c=(double*)calloc(num_of_eq-1, sizeof(double));
    d=(double*)calloc(num_of_eq-1, sizeof(double));
    x=(double*)calloc(num_of_eq, sizeof(double));

    if ((a == NULL) || (b == NULL) || (x == NULL) || (c==NULL)|| (d==NULL))
    {
        if (errors_print) printf("Memory allocation error!\n");

        free(a); a=NULL;
        free(b); b=NULL;
        free(c); c=NULL;
        free(d); d=NULL;
        free(x); x=NULL;

        fclose(fin);
        fclose(fout);

        return -4;
    }

    fscanf(fin, "%lf %lf", &a[0], &c[0]);
    
    for (int i = 1; i < num_of_eq-1; i++)
    {
        fscanf(fin, "%lf %lf %lf", &d[i-1], &a[i], &c[i]);
    }
    
    fscanf(fin, "%lf %lf", &d[num_of_eq-2], &a[num_of_eq-1]);
    
    for (int i = 0; i < num_of_eq; i++)
    {
        fscanf(fin, "%lf", &b[i]);
    }

    if (time_print) start_time = clock();

    res = lss_11_09(num_of_eq, a, c, d, b, x);

    if (time_print)
    {
        stop_time = clock();
        printf("Working time - %ld ms.\n", stop_time - start_time);
    }

    if (!res)
    {
        fprintf(fout, "%d\n", num_of_eq);

        for (int i = 0; i < num_of_eq; ++i) fprintf(fout, "%.9lf\n", x[i]);
    }
    
    else fprintf(fout, "%d\n", 0);

    
    free(a); a=NULL;
    free(b); b=NULL;
    free(c); c=NULL;
    free(d); d=NULL;
    free(x); x=NULL;

    fclose(fin);
    fclose(fout);

    return res;

}