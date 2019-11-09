//Matthew Capuano
//EE 456
//Function Approximation

#include <iostream>
#include <stdio.h>
#include <cmath>
#include <stdlib.h>
using namespace std;

int main()
{
  double t [10] = {.1, .2, .3, .4, .5, .6, .7, .8, .9};
  double bias [10] = {.01, .04, .09, .160, .250, .360, .490, .640, .810};
  
  
  double v[2][10] = {{1,1,1,1,1,1,1,1,1,1}, {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}} ;
  double z [10];
  double w [10] = {.1, .1, .1, .1, .1, .1, .1, .1, .1, .1};
  
  for(int i = 0; i < 10; i ++)
  {
        for(int j = 0; j <10; j ++ )
        {
            z[j] = v[0][j] * t[i] + bias[j] * v[1][j];
           // double p = exp(-1 * z[j]);
            //z[j] = 1 / (1 + p);
            if (z[j] > 0)
            {
                z[j] = 1;
            }
            else
            {
                z[j] = z[j];
            }
        }
      
        double a = 0;      
        for(int k = 0; k <10; k++)
        {
            a = a + z[k]*w[k];
        }
        
        //double q = exp(-1 * a);
        //double y = 1 / (1 + q);
        
        double y = 0;
        if (a < 0)
        {
            y = 0;
        }
        else if (a > 1)
        {
            y = 1;
        }
        else 
        {
            y = a;
        }
        
        cout << y <<endl;

  }

  
  
}
