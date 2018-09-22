#include <stdio.h>
#include <math.h>

int main()
  {
    int i, n=1000; //i...loop variable n...number of iterations
    double Pi = 4.0*atan(1), e = 1.6021766e-19, k_B = 1.38065e-23; //constants
    double p_N, T, M, S_N, J, A_t, A_c, S_M, S, alpha_t, alpha_c; //inputvalues
    double F, theta_one, theta_two, q_t, q_c, q_p, q_zero, R; //outputvalues

    //read inputvalues and print them:
    FILE *iv;
    iv = fopen("input.dat", "r");
    fscanf(iv, "%lf %*s %lf %*s %lf %*s %lf %*s %lf %*s %lf %*s %lf %*s %lf %*s %lf %*s %lf %*s %lf %*s", &p_N, &T, &M, &S_N, &J, &A_t, &A_c, &S_M, &S, &alpha_t, &alpha_c);
    printf("read values from input.dat:\np_N: %.1lfbar; T: %.0lfK; M: %.4lekg; S_N: %.1lf; J: %.1lfmA/cm²;\nA_t: %.0lfcm²; A_c: %.0lfcm²; S_M: %.1lf; S: %.0lfl/s; alpha_t: %.3lf; alpha_c: %.3lf\n", p_N, T, M, S_N, J, A_t, A_c, S_M, S, alpha_t, alpha_c);
    fclose(iv);

    //write order of outputvalues to output.dat and do actual calculations:
    FILE *ov = fopen("output.dat","w");
    fprintf(ov, "p_N F theta_1 theta_2 q_ts q_cs q_ps q_zero R\n");

    for(i=0; i<2*n; i++)
      {
        //equation A5 for flux F of nitrogen molecules:
        F = p_N/sqrt(2.0*Pi*k_B*T*M);         
	
	//equation A1' for target fractional coverage theta_1:
        theta_one = 1.0/(1.0 + J*S_N/(2.0*e*alpha_t*F));         
	
	//equation A2' for chamber wall and substrate fractional coverage theta_2:
        theta_two = (e/J*2.0*alpha_c*F*A_c/A_t + S_N*theta_one)/(e/J*2.0*alpha_c*F*A_c/A_t + S_N*theta_one + S_M*(1.0 - theta_one));       

	//equation A3 for flow to target:
        q_t = alpha_t*F*(1.0 - theta_one)*A_t;         
	
	//equation A4 for flow to surface area A_c of the chamber:
        q_c = alpha_c*F*(1.0 - theta_two)*A_c;       
        
	//equation 2 for flow through pump:
        q_p = p_N*S;        
	
	//equation 1 for incoming reactive gas flow:
        q_zero = q_t + q_c + q_p;         
	
	//equation A6 for total sputtering rate R:
        R = (J/e)*(S_N*theta_one + S_M*(1 - theta_one)); 	

	fprintf(ov, "%le %le %le %le %le %le %le %le %le\n", p_N, F, theta_one, theta_two, q_t, q_c, q_p, q_zero, R);

	if(i<n) p_N+=0.1;
	else p_N-=0.1;
      }

    fclose(ov);
    printf("\ncalculated values written to output.dat\n");
    return 0;
  }
