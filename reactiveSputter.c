#include <stdio.h>
#include <math.h>

int main()
  {
    FILE *inputvalues;
    inputvalues = fopen("input.dat", "r");
    int i;
    double Pi=4.0*atan(1);
    double p_N, T, M, e, S_N, J, A_t, A_c, S_M, S, alpha_t, alpha_c;


    if (inputvalues == NULL) printf ("file input.dat not found\n");
    else fscanf(inputvalues, "%lf %*s %lf %*s %lf %*s %lf %*s %lf %*s %lf %*s %lf %*s %lf %*s %lf %*s %lf %*s %lf %*s %lf %*s", &p_N, &T, &M, &e, &S_N, &J, &A_t, &A_c, &S_M, &S, &alpha_t, &alpha_c);
    
    printf("p_N is set to: %lebar\n", p_N);
    printf("T is set to: %leK\n", T);
    printf("M is set to: %lekg\n", M);
    printf("e is set to: %leC\n", e);
    printf("S_N is set to: %le\n", S_N);
    printf("J is set to: %le\n", J);
    printf("A_t is set to: %lem²\n", A_t);
    printf("A_c is set to: %lem²\n", A_c);
    printf("S_M is set to: %le\n", S_M);
    printf("S is set to: %le\n", S);
    printf("alpha_t is set to: %le\n", alpha_t);
    printf("alpha_c is set to: %le\n", alpha_c);

    fclose(inputvalues);

    return 0;
  }
