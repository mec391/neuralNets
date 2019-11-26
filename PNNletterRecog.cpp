 
//Matthew Capuano
//EE 456 -- Probabilistic Neural Network -- Letter Recognition Using Feature Extraction
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <stdlib.h>
using namespace std;

/*  
Features:
LetterArray = [endpoints] [diagonal connections] [curves] [connection points]

straight lines = number of straight segments with 3 or more blocks
connection points = number of locations where 3 or more pixels are touching to 1 pixel
diagonal connections = any amount of connections that are formed diagonally
curves = can make a c shape out of the outline
Letters:
[C]
[D]
[F]
[I]
[X]
[Y]
[H]
[J]
[K]
*/

void determineOutput(double outputvalue);
void networkRun(double input[], double *output);

int main()
{
     //z values
    /*
    double C [4] = {2, 4, 2, 0};
    double D [4] = {0, 2, 1, 0};
    double F [4] = {3, 0, 1, 1};
    double I [4] = {4, 0, 2, 2};
    double X [4] = {4, 4, 4, 2};
    double Y [4] = {3, 3, 2, 1};
    double H [4] = {4, 0, 2, 2};
    double J [4] = {3, 0, 1, 1};
    double K [4] = {4, 2, 3, 4};
    */
    
    //inputs
    double inC [4] = {2, 4, 2, 0};
    double inD [4] = {1, 2, 1, 1};
    double inF [4] = {4, 1, 1, 1};
    double inI [4] = {2, 0, 0, 0};
    double inX [4] = {4, 4, 4, 1};
    double inY [4] = {3, 3, 2, 1};
    double inH [4] = {3, 0, 1, 1};
    double inJ [4] = {2, 0, 1, 0};
    double inK [4] = {4, 2, 3, 4};
    
    
    double output;
    double inputvector[4];
    
    
    

for(int i = 0; i < 4; i++)
{
    inputvector[i] = inC[i];
}
cout << "Input is lowercase C" <<endl;
networkRun(inputvector, &output);  
determineOutput(output);
    
for(int i = 0; i < 4; i++)
{
    inputvector[i] = inD[i];
}
cout << "Input is lowercase D" <<endl;
networkRun(inputvector, &output);  
determineOutput(output);    
    
for(int i = 0; i < 4; i++)
{
    inputvector[i] = inF[i];
}
cout << "Input is lowercase F" <<endl;
networkRun(inputvector, &output);  
determineOutput(output);      

for(int i = 0; i < 4; i++)
{
    inputvector[i] = inI[i];
}
cout << "Input is lowercase I" <<endl;
networkRun(inputvector, &output);  
determineOutput(output);   
 
for(int i = 0; i < 4; i++)
{
    inputvector[i] = inX[i];
}
cout << "Input is lowercase X" <<endl;
networkRun(inputvector, &output);  
determineOutput(output);    

 for(int i = 0; i < 4; i++)
{
    inputvector[i] = inY[i];
}
cout << "Input is lowercase Y" <<endl;
networkRun(inputvector, &output);  
determineOutput(output);  

for(int i = 0; i < 4; i++)
{
    inputvector[i] = inH[i];
}
cout << "Input is lowercase H" <<endl;
networkRun(inputvector, &output);  
determineOutput(output);  

for(int i = 0; i < 4; i++)
{
    inputvector[i] = inJ[i];
}
cout << "Input is lowercase J" <<endl;
networkRun(inputvector, &output);  
determineOutput(output);  

for(int i = 0; i < 4; i++)
{
    inputvector[i] = inK[i];
}
cout << "Input is lowercase K" <<endl;
networkRun(inputvector, &output);  
determineOutput(output);  

 return 0;   
}

void networkRun(double input[], double *output)
{
    
    //z values
    /*
    double C [4] = {2, 4, 2, 0};
    double D [4] = {0, 2, 1, 0};
    double F [4] = {3, 0, 1, 1};
    double I [4] = {4, 0, 2, 2};
    double X [4] = {4, 4, 4, 2};
    double Y [4] = {3, 3, 2, 1};
    double H [4] = {4, 0, 2, 2};
    double J [4] = {3, 0, 1, 1};
    double K [4] = {4, 2, 3, 4};
    */
double zvalues[9][4] = {{2, 4, 2, 0}, {0, 2, 1, 0}, {3, 0, 1, 1},{4, 0, 2, 2},{4, 4, 4, 2}, {3, 3, 2, 1}, {4, 0, 2, 2}, {3, 0, 1, 1}, {4, 2, 3, 4}};
double zarray[9];
int counter1 = 0;

//compute z values
for (int i = 0; i < 9; i++)
    {
        double b = 0;
        double c = 0;
        
        for (int j = 0; j < 4; j++)
            {
                double xyz = (-1) * ((input[j] - zvalues[i][j])*(input[j] - zvalues[i][j])) / 2 ;
                double a = (1 / 6.28) * exp(xyz);
                b = b + a;
            }
        c = .25 * b;
        zarray[counter1] = c;
        counter1 = counter1 + 1;
        
    }

//compute zbar values
double bias = 0;
for(int i = 0; i < 9; i++)
    {
        bias = bias + zarray[i];
    }
    
    bias = bias / 9;
    
    
for(int i = 0; i < 9; i++)
    {
        zarray[i] = zarray[i] - bias;   
    }



//compute WTA
double outputbuffer = 0;
double zlocation = 0;
 if(zarray[1] > zarray[0])
    {
        outputbuffer = zarray[1];
        zlocation = 1;
    }
    else
    {
        outputbuffer = zarray[0]; 
        zlocation = 0;
    }

for(int i = 2; i < 9; i++)
    {
          if(zarray[i] > outputbuffer)
          {
            outputbuffer = zarray[i]; 
            zlocation = i;
          }
          else
          {
           outputbuffer = outputbuffer;  
           zlocation = zlocation;
          }
    }

*output = zlocation;
return;
}


void determineOutput(double outputvalue)
{
    
 if (outputvalue == 0)
    {
     cout << "Output is C" << endl;
    }
    else if (outputvalue == 1)
    {
    cout << "Output is D" <<endl;
    }
    else if (outputvalue ==2)
    {
     cout << "Output is F" << endl;
    }
    else if (outputvalue == 3)
    {
    cout << "Output is I" <<endl;
    }
    else if (outputvalue ==4)
    {
    cout <<"Output is X" <<endl;
    }
    else if (outputvalue == 5)
    {
     cout <<"Output is Y" <<endl;   
    }
    else if (outputvalue == 6)
    {
     cout <<"Output is H" <<endl;   
    }
    else if (outputvalue == 7)
    {
     cout <<"Output is J" <<endl;   
    }
    else if(outputvalue == 8)
    {
     cout <<"Output is K" <<endl;   
    }
    
return;
}
