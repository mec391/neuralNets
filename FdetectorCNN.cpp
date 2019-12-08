//Matthew Capuano
//EE 456 Convolution Neural Network
//no mapping, 3 kernels used for capital F detection, compares to fixed value on output
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <stdlib.h>
using namespace std;

void kernalRun(double input[][6], double kernal[][2], double subarray[][5]);
void Comparator(double subarray1[][5], double subarray2[][5], double subarray3[][5], double *isitF);

int main()
{
    double testInputCapF [8][6] = {{1,1,1,1,1,1}, {1,0,0,0,0,0},{1,0,0,0,0,0},{1,1,1,1,0,0},{1,0,0,0,0,0},{1,0,0,0,0,0},{1,0,0,0,0,0},{1,0,0,0,0,0}};
    double testInputLowF [8][6] = {{0,0,1,1,0,0},{0,1,0,0,0,0},{0,1,0,0,0,0},{1,1,1,0,0,0},{0,1,0,0,0,0},{0,1,0,0,0,0},{0,1,0,0,0,0},{0,1,0,0,0,0}};
    double testInputLowX [8][6] = {{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{1,0,0,0,1,0},{0,1,0,1,0,0}, {0,0,1,0,0,0},{0,1,0,1,0,0},{1,0,0,0,1,0}};
    
    
    
    double kernalVert [2][2] = {{1, 0}, {1,0}};
    double kernalHoriz[2][2] = {{1, 1}, {0,0}};
    double kernalCurve[2][2] = {{1,1}, {1,0}};
    
    double subArrayVert[7][5];
    double subArrayHoriz[7][5]; 
    double subArrayCurve[7][5];
    
    double isF = 0;
    
    //test capital F
    kernalRun(testInputCapF, kernalVert, subArrayVert);
    kernalRun(testInputCapF, kernalHoriz, subArrayHoriz);
    kernalRun(testInputCapF, kernalCurve, subArrayCurve);
    Comparator(subArrayVert, subArrayHoriz, subArrayCurve, &isF);
    if(isF == 1)
    {
     cout << "input is capital F, output is Capital F" <<endl;
    }
    else
    {
    cout <<"input is capital F, output is not Capital F" <<endl;  
    }
    
    //test lowercase F
     kernalRun(testInputLowF, kernalVert, subArrayVert);
    kernalRun(testInputLowF, kernalHoriz, subArrayHoriz);
    kernalRun(testInputLowF, kernalCurve, subArrayCurve);
    Comparator(subArrayVert, subArrayHoriz, subArrayCurve, &isF);
     if(isF == 1)
    {
     cout << "input is lowercase F, output is Capital F" <<endl;
    }
    else
    {
    cout <<"input is lowercase F, output is not Capital F" <<endl;  
    }
    //test lowercase X
     kernalRun(testInputLowX, kernalVert, subArrayVert);
    kernalRun(testInputLowX, kernalHoriz, subArrayHoriz);
    kernalRun(testInputLowX, kernalCurve, subArrayCurve);
    Comparator(subArrayVert, subArrayHoriz, subArrayCurve, &isF);
     if(isF == 1)
    {
     cout << "input is lowercase X, output is Capital F" <<endl;
    }
    else
    {
    cout <<"input is lowercase X, output is not Capital F" <<endl;  
    }
  return 0;

}
//compare 3 subarrays to 3 fixed values, if over 50% matching, return true for F detected
void Comparator(double subarray1[][5], double subarray2[][5], double subarray3[][5], double *isitF)
{
 double Ftest[7][5] ={{3, 3, 3, 3}, {3, 0, 0, 0}, {3, 3, 3, 3}, {1, 0, 0, 0}, {1,0,0,0},{1,0,0,0},{1,0,0,0}};
 double placeholder[7][5];
 
 for(int i = 0; i < 7; i++)
 {
    for(int j = 0; j < 5; j++) //add up subarrays
        {
        placeholder[i][j] = subarray1[i][j] + subarray2[i][j] + subarray3[i][j];   
        }
 }
 
 double counter = 0;
 for(int i = 0; i <7; i++) //compare added up subarrays to fixed value
 {
    for(int j = 0; j <5; j++)
        {
            if (Ftest[i][j] == 3)
              {
                    if(placeholder[i][j] > 1.5)
                        {
                         counter = counter + 1;   
                        }
                    else
                        {
                            counter = counter;
                        }
              }
            else
                {
                   if(placeholder[i][j] < 1.5)
                    {
                        counter = counter + 1;   
                    }
                    else
                    {
                     counter = counter;   
                    }
                }
            
         
        }
 }
 
 cout <<"%Matching is " << counter << "/35"<<endl;
 
 if (counter > 17)
 {
    *isitF = 1;
 }
 else
 {
    *isitF = 0;   
 }
 
 return;   
}




//map 8x6 to 4x3 //not being used
/*
void map(double input[][6], double output[][3])
{
    
    double counter = 0;
    double counterCol = 0;
    double counterRow = 0;
    
    for (int i = 0; i < 8; i = i + 2)
        {
            counterCol = 0;
         for(int j = 0; j <6; j = j + 2)
            {   
                counter = 0;
                if(input[i][j] == 1)        //determine how many of the 4 blocks are 1
                {
                    counter = counter + 1;
                }
                else
                {
                    counter = counter;
                }
                
                if (input[i+1][j] == 1)
                {
                    counter = counter + 1;   
                }
                else
                {
                    counter = counter;   
                }    
                if (input[i][j+1] == 1)
                {
                    counter = counter + 1;   
                }
                else
                {
                    counter = counter;
                }
                if (input[i+1][j+1] == 1)
                {
                    counter = counter + 1;   
                }
                else 
                {
                    counter = counter;   
                }
                
                
                
                if(counter > 1 ) //assign value to mapped block based on total weight
                    {
                       output[counterCol][counterRow] = 1;
                    }
                else
                    {
                       output[counterCol][counterRow] = 0;   
                    }
                
                counterCol = counterCol + 1;
            }
            
          counterRow = counterRow + 1;  
        }
    
    
    
    
 return;   
}

*/





//run a 2x2 kernal through an 8x6 image, output a 7x5 subarray
void kernalRun(double input[][6], double kernal[][2], double subarray[][5])
{
    double counter = 0;
    
    
    for (int i = 0; i < 7; i++)
    {
        
     for (int j = 0; j < 5; j++)
        {
            counter = 0;
            if(kernal[0][0] == input[i][j])
                {
                    counter = counter + 0.25;
                }
            else
            {
                counter = counter;   
            }
            if(kernal[0][1] == input[i][j+1])
            {
              counter = counter + 0.25;   
            }
            else
            {
                counter = counter;
            }
            if(kernal[1][0] == input[i+1][j])
            {
                counter = counter + 0.25;
            }
            else
            {
                counter = counter;
            }
            if(kernal[1][1] == input[i+1][j+1])
            {
             counter = counter + 0.25;   
            }
            else
            {
             counter = counter; 
            }
            
            subarray[i][j] = counter;
            
        }
        
    }
    
return;
}

