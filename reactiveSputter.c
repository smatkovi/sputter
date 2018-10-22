#include <stdio.h>
#include <stdlib.h>//used for function system(onst char *__command) to plot directly
#include <math.h>

int main()
  {
    int i, n; //i...loop variable n...number of iterations
    double Pi = 4.0*atan(1), e = 1.6021766e-19, k_B = 1.38065e-23; //constants
    double p_N, T, M, S_N, J, A_t, A_c, S_M, S, alpha_t, alpha_c, dp; //inputvalues
    double F, theta_one, theta_two, q_t, q_c, q_p, q_zero, Y; //outputvalues

    //read inputvalues and print them:
    FILE *iv;
    iv = fopen("input.dat", "r");
    fscanf(iv, "%d %*s %lf %*s %lf %*s %lf %*s %lf %*s %lf %*s %lf %*s %lf %*s %lf %*s %lf %*s %lf %*s %lf %*s %lf %*s", &n, &dp, &p_N, &T, &M, &S_N, &J, &A_t, &A_c, &S_M, &S, &alpha_t, &alpha_c);
    printf("read values from input.dat:\nn: %d; dp: %.0lePa; p_N: %.0lePa; T: %.0lfK; M: %.lekg; S_N: %.1lf; J: %.1leA/m²; A_t: %.2lem²; A_c: %.2lem²; S_M: %.1lf; S: %.0lfl/s; alpha_t: %.3lf; alpha_c: %.3lf\n", n, dp, p_N, T, M, S_N, J, A_t, A_c, S_M, S, alpha_t, alpha_c);
    fclose(iv);

    //write order of outputvalues to output.dat and do actual calculations:
    FILE *ov = fopen("output.dat","w");
    fprintf(ov, "[p_N]=Pa F theta_1 theta_2 q_ts q_cs q_ps [q_0]=J/s [Y]=m^3\n");
    
    for(i=0; i<n; i++)
      {
        //equation A5 for flux F of nitrogen molecules:
        F = p_N / sqrt(2.0*k_B*Pi*T*M);         
        //alpha_t /= F;//experimental

	//equation A1' for target fractional coverage theta_1:
        theta_one = 2.0*e*F*alpha_t/(2.0*e*F*alpha_t+J*S_N);//1.0 / (1.0 + (J*S_N/e)/(2.0*alpha_t*F));         

	//equation A2' for chamber wall and substrate fractional coverage theta_2:
        theta_two = (2.0*e*F*alpha_c+J*(A_t/A_c)*theta_one*S_N)/(2.0*e*F*alpha_c+J*(A_t/A_c)*(S_M+S_N*theta_one-S_M*theta_two));//((e/J)*2.0*alpha_c*F*(A_c/A_t) + S_N*theta_one) / ((e/J)*2.0*alpha_c*F*(A_c/A_t) + S_N*theta_one + S_M*(1.0 - theta_one));       

	//equation A3 for flow to target:
        q_t = alpha_t*F*(1.0 - theta_one)*A_t;         
	
	//equation A4 for flow to surface area A_c of the chamber:
        q_c = alpha_c*F*(1.0 - theta_two)*A_c;       
        
	//equation 2 for flow through pump:
        q_p = p_N*S;        
	
	//equation 1 for incoming reactive gas flow:
        q_zero = q_t + q_c + q_p;         
	
	//equation A6 for total sputtering rate Y:
        Y = (J/e)*(S_N*theta_one + S_M*(1.0 - theta_one)); 	

	fprintf(ov, "%le %le %le %le %le %le %le %le %le\n", p_N, F, theta_one, theta_two, q_t, q_c, q_p, q_zero, Y);

	p_N += dp;
	//T += n/10.0;//experimental
      }

    fclose(ov);
    printf("\ncalculated values for p_N, F, theta_1, theta_2, q_t, q_c, q_p, q_0, Y written to output.dat, plotting to YOverq_0.ps and p_NOverq_0.ps\n");
    system("gnuplot plotYOverq_0.gnu; gnuplot plotp_NOverq_0.gnu");
    return 0;
  }
