//Backpropogation neural network
//Matthew Capuano EE 456


#include <iostream>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
using namespace std;




void calcerr(float *win, float vin[][2], float *xin, float *err, float *z3in, float *z4in, float *y5in, float tin);
void train(float *win, float vin[][2],  float *xin, float alphin, float tin, float z3in, float z4in, float y5in);


int main()
{
  //input xbars
  float x1 [2] = {0, 0};
  float x2 [2] = {0, 1};
  float x3 [2] = {1, 0};
  float x4 [2] = {1, 1};
  
  //desired values
  float t1 = 0;
  float t2 = 1;
  float t3 = 1;
  float t4 = 0;
  
  //alpha, error, z and y values
  float alpha = 0.5;
  float error = 0;
  float totalError = 0;
  float z3 = 0;
  float z4 = 0;
  float y5 = 0;
  
    //V matrix
    float V [3][2] = {
                    {-1.0, 1.0},
                    {2.0, 2.0},
                    {-1.0, -2.0}
                    };
    //W matrix      
    float W [3] = {-1, 2, -2};
  
  
 //apply x1
 calcerr(W, V, x1, &error, &z3, &z4, &y5, t1);
     totalError = totalError + error;
     cout <<  "Error after x1 = " <<error <<endl;
     cout << "Total error = " <<totalError <<endl;
     cout <<"Z3 = " <<z3 <<endl;
     cout <<"Z4 = " <<z4 <<endl;
     cout <<"Y5 = " <<y5 <<endl;
 train(W, V, x1, alpha, t1, z3, z4, y5);
 
//apply x2
calcerr(W, V, x2, &error, &z3, &z4, &y5, t2);
    totalError = totalError + error;
    cout <<  "Error after x2 = " <<error <<endl;
     cout << "Total error = " <<totalError <<endl;
 train(W, V, x2, alpha, t2, z3, z4, y5);
 
//apply x3
 calcerr(W, V, x3, &error, &z3, &z4, &y5, t3);
    totalError = totalError + error;
    cout <<  "Error after x3 = " <<error <<endl;
     cout << "Total error = " <<totalError <<endl;
 train(W, V, x3, alpha, t3, z3, z4, y5);
 
//apply x4
 calcerr(W, V, x4, &error, &z3, &z4, &y5, t4);
    totalError = totalError + error;
    cout <<  "Error after x4 = " <<error <<endl;
     cout << "Total error = " <<totalError <<endl;
 train(W, V, x4, alpha, t4, z3, z4, y5);
 
 
 return 0;
 
}

void calcerr(float *win, float vin[][2], float *xin, float *err, float *z3in, float *z4in, float *y5in, float tin)
{
    float a = vin[1][0] * xin[0] + vin[2][0] * xin[1] + vin[0][0];
    float b = exp( -1 * a);
     *z3in = 1 / (1 + b);
    
    float c = vin[1][1] * xin[0] + vin[2][1] * xin[1] + vin[0][1];
    float d = exp( -1 * c);
    *z4in = 1 / (1 + d);
    
    float e = win[1] * *z3in + win[2] * *z4in + win[0];
    float f = exp(-1 * e);
    *y5in = 1 / (1 + f);
    
    float g = abs(tin - *y5in);
    *err = .5 * g * g;
    return;
}

void train(float *win, float vin[][2],  float *xin, float alphin, float tin, float z3in, float z4in, float y5in)
{
    float delt05 = (tin - y5in) * y5in * (1 - y5in);
    float delt03 = z3in * (1 - z3in) * delt05 * win[1];
    float delt04 = z4in * (1 - z4in) * delt05 * win[2];
    
    vin[0][0] = vin[0][0] + alphin * delt03;
    vin[0][1] = vin[0][1] + alphin * delt04;
    vin[1][0] = vin[1][0] + alphin * delt03 * xin[0];
    vin[1][1] = vin[1][1] + alphin * delt04 * xin[0];
    vin[2][0] = vin[2][0] + alphin * delt03 * xin[1];
    vin[2][1] = vin[2][1] + alphin * delt04 * xin[1];
    
    win[0] = win[0] + alphin * delt05;
    win[1] = win[1] + alphin * delt05 * z3in;
    win[2] = win[2] + alphin * delt05 * z4in;
    return;
}