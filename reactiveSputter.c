#include <stdio.h>
#include <math.h>

int main()
  {
    FILE *inputvalues;
    inputvalues = fopen("input.dat", "r");
    int i, n=1; //i...loop variable n...number of iterations
    double Pi = 4.0*atan(1), e = 1.6021766e-19, k_B = 1.38065e-23; //constants
    double p_N, T, M, S_N, J, A_t, A_c, S_M, S, alpha_t, alpha_c; //inputvalues
    double F, theta_one, theta_two, q_t, q_c, q_p, q_zero, R; //outputvalues


    if (inputvalues == NULL) printf ("file input.dat not found\n");
    else fscanf(inputvalues, "%lf %*s %lf %*s %lf %*s %lf %*s %lf %*s %lf %*s %lf %*s %lf %*s %lf %*s %lf %*s %lf %*s", &p_N, &T, &M, &S_N, &J, &A_t, &A_c, &S_M, &S, &alpha_t, &alpha_c);
    
    printf("p_N is set to: %lebar\n", p_N);
    printf("T is set to: %leK\n", T);
    printf("M is set to: %lekg\n", M);
    printf("S_N is set to: %le\n", S_N);
    printf("J is set to: %lemA/cm²\n", J);
    printf("A_t is set to: %lecm²\n", A_t);
    printf("A_c is set to: %lecm²\n", A_c);
    printf("S_M is set to: %le\n", S_M);
    printf("S is set to: %lel/s\n", S);
    printf("alpha_t is set to: %le\n", alpha_t);
    printf("alpha_c is set to: %le\n", alpha_c);

    fclose(inputvalues);

    for(i=1; i==n; i++)
      {
        //equation A5 for flux F of nitrogen molecules:
        F = p_N/sqrt(2.0*Pi*k_B*T*M);         
	
	//equation A1' for target fractional coverage theta_1:
        theta_one = 1.0/(1.0 + J*S_N/(2.0*e*alpha_t*F));         
	
	//equation A2' for chamber wall and substrate fractional coverage theta_2:
        theta_two = (e/J*2.0*alpha_c*F*A_c/A_t + S_N*theta_one)/(e/J*2.0*alpha_c*F*A_c/A_t + S_N*theta_one + S_M*(1 - theta_one));        
	//equation A3 for flow to target:
        q_t = alpha_t*F*(1 - theta_one)*A_t;         
	
	//equation A4 for flow to surface area A_c of the chamber:
        q_c = alpha_c*F*(1 - theta_two)*A_c;       
        
	//equation 2 for flow through pump:
        q_p = p_N*S;        
	
	//equation 1 for incoming reactive gas flow:
        q_zero = q_t + q_c + q_p;         
	
	//equation A6 for total sputtering rate R:
        R = (J/e)*(S_N*theta_one + S_M*(1 - theta_one)); 	
	
	p_N+=0.01;
      }

    printf("values after %d times:\nF=%le\ntheta_1=%le\ntheta_2=%le\nq_t=%le\nq_c=%le\nq_p=%le\nq_zero=%le\nR=%le\n", n, F, theta_one, theta_two, q_t, q_c, q_p, q_zero, R);

    return 0;
  }
