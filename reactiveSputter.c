#include <stdio.h>
#include <stdlib.h>//used for function system(onst char *__command) to plot directly
#include <math.h>

int main()
  {
    int i, n; //i...loop variable n...number of iterations
    double Pi = 4.0*atan(1), e = 1.6021766e-19, k_B = 1.38065e-23; //constants
    double m_e = 9.10938356e-31, h = 6.62607004e-34; //constants for thermic correction
    double p_N, T, M, S_N, J, A_t, A_c, S_M, S, alpha_t, alpha_c, dp; //inputvalues
    double w=1e9; //inputvalue(s) for thermic correction
    double F, theta_one, theta_two, q_t, q_c, q_p, q_zero, Y; //outputvalues
    double J_s; //outputvalue(s) for thermic correction

    //read inputvalues and print them:
    FILE *iv;
    iv = fopen("input.dat", "r");
    fscanf(iv, "%d %*s %lf %*s %lf %*s %lf %*s %lf %*s %lf %*s %lf %*s %lf %*s %lf %*s %lf %*s %lf %*s %lf %*s %lf %*s", &n, &dp, &p_N, &T, &M, &S_N, &J, &A_t, &A_c, &S_M, &S, &alpha_t, &alpha_c);
    printf("read values from input.dat:\nn: %d; dp: %.0lePa; p_N: %.0lePa; T: %.0lfK; M: %.lekg; S_N: %.1lf; J: %.1leA/m²; A_t: %.2lem²; A_c: %.2lem²; S_M: %.1lf; S: %.2lem³/s; alpha_t: %.3lf; alpha_c: %.3lf\n", n, dp, p_N, T, M, S_N, J, A_t, A_c, S_M, S, alpha_t, alpha_c);
    fclose(iv);

    //write order of outputvalues to output.dat and do actual calculations:
    FILE *ov = fopen("output.dat","w");
    fprintf(ov, "[p_N]=Pa F theta_1 theta_2 [q_t]=J/s [q_c]=J/s [q_p]=J/s [q_0]=J/s Y\n");
    
    //Schottkyemission:
    J_s = 4*Pi*m_e/pow(h, 3) * pow(e*k_B*T, 2) * exp(-w/(k_B*T));
    
    for(i=0; i<n; i++)
      {
        //equation A5 for flux F of nitrogen molecules:
        F = p_N / sqrt(2.0*k_B*Pi*T*M);         

	//equation A1' for target fractional coverage theta_1:
        //theta_one = 2.0*e*F*alpha_t/(2.0*e*F*alpha_t+J*S_N);
	theta_one = J_s/F;//J_s/F, i would assume the inverse of this and there could be a constant missing in J_s, like J_s = J_s + constant, old function from berg et alii's paper: 1.0 / (1.0 + (J*S_N/e)/(2.0*alpha_t*F));         

	//equation A2' for chamber wall and substrate fractional coverage theta_2:
        //theta_two = (2.0*e*F*alpha_c+J*(A_t/A_c)*theta_one*S_N)/(2.0*e*F*alpha_c+J*(A_t/A_c)*(S_M+S_N*theta_one-S_M*theta_one));
        theta_two = ((e/J)*2.0*alpha_c*F*(A_c/A_t) + S_N*theta_one) / ((e/J)*2.0*alpha_c*F*(A_c/A_t) + S_N*theta_one + S_M*(1.0 - theta_one));       

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
      }

    fclose(ov);
    printf("\ncalculated values for p_N, F, theta_1, theta_2, q_t, q_c, q_p, q_0, Y written to output.dat, plotting to p_NOverq_t.ps, p_NOverq_c.ps, p_NOverq_p.ps, YOverq_0.ps and p_NOverq_0.ps\n");
    system("gnuplot plotYOverq_0.gnu; gnuplot plotp_NOverq_0.gnu; gnuplot plotp_NOverq_t.gnu; gnuplot plotp_NOverq_c.gnu; gnuplot plotp_NOverq_p.gnu");
    return 0;
  }
