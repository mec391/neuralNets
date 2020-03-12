// Matthew Capuano EE 556 -- Adeline / Perceptron


#include <iostream>
#include <stdio.h>
#include <cmath>
#include <stdlib.h>
using namespace std;

void error_and_train(double input[], double weights[], double desired, double *error, double final_run);


int main()
{
    double x1[4] = {1, -2, 0, -1};
    double t1 = -1;
    double x2[4] = {0, 1.5, -.5, -1};
    double t2 = -1;
    double x3[4] = {-1, 1,.5, -1};
    double t3 = 1;
    
    double weights[4] = {1,-1,0,.5};
    
    double er = 0;
    double error_each = 0;
    double error_total = 9999;
    double final_run = 0; //set high when error reaches threshold
    
    while (er == 0)                                                                       //training cycle
        {
            error_and_train(x1, weights, t1, &error_each, final_run);
            error_total = error_total + error_each;
            error_and_train(x2, weights, t2, &error_each, final_run);
            error_total = error_total + error_each;
            error_and_train(x3, weights, t3, &error_each, final_run);
            error_total = error_total + error_each;
            
            
            cout << "Error total = "; 
            cout <<error_total; 
            cout <<"\n";
            if(error_total < .001)
            {
                er = 1;
            }
            error_total = 0;
        }
        
        cout << "Training complete, the following shows the final values: \n";                   // Training Finished
        final_run = 1;
         error_and_train(x1, weights, t1, &error_each, final_run);
         error_and_train(x2, weights, t2, &error_each, final_run);
         error_and_train(x3, weights, t3, &error_each, final_run);
            
    
    
    
    
    return 0;
}


void error_and_train(double input[], double weights[], double desired, double *error, double final_run)
{
    double alpha = .2;
    double yin = input[0]*weights[0] + input[1]*weights[1] + input[2]*weights[2] + input[3]*weights[3];     //calc output
    double yin1 = exp(-1 * yin);
    double f = (2 / (1 + yin1)) - 1; 
 
    for (int i = 0; i <4; i++)                                                                      //train
    {
        weights[i] = weights[i] + alpha * input[i] * (desired - f);    
    }
    
    *error = (desired - f) * (desired - f);                                                     //calc error
 
 if (final_run == 1)
    {
        cout << "Input is ";
        cout << input[0]; cout << " ";
        cout << input[1]; cout << " ";
        cout <<input [2]; cout << " ";
        cout <<input [3]; cout << " ";
        cout <<"\n weight matrix is ";
        cout << weights[0]; cout << " ";
        cout << weights[1]; cout << " ";
        cout << weights[2]; cout << " ";
        cout << weights[3]; cout << " ";
        cout <<"\n desired output is ";
        cout << desired;
        cout <<"\n actual output is ";
        cout <<f;
        cout << "\n \n";
    }
 
 return;   
}
