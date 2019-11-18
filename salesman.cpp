//Matthew Capuano
//EE 456 -- Constrained Optimization (Evolutionary Algorithm) -- Traveling Salesman
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <ctime>
using namespace std;

//Locations...Start at Harrisburg on day 0, travel to 1 location per day for next 9 days, then return to HBG on 10th day.  Optimize to reduce traveling distance, incur penalties if...
// -skip city -skip day -duplicate city - duplicate day -distance penalty

/*  Locations and Associated Coordinates 
0 HBG  (40.203, -76.742)
1 UP    (40.798, -77.867)
2 Behrend (42.119, -79.984)
3 Beaver   (40.678, -80.297)
4 York     (39.950, -76.704)
5 Altoona   (40.541, -78.412)
6 Abington  (40.116, -75.111)
7 Wilkes-Barre (41.307, -76.015)
8 Williamsport  (41.234, -77.022)
9 Pittsburg  (40.444, -79.989)
*/ 


void cycle(double cityXday1[][11],double *temp, double *constrain);
void computeDistance(int firstcity, int secondcity, double *distances);



int main()
{
     srand((unsigned)time(0)); 
     //city X day matrix that will contain 1's and zeros
double cityXday[10][11] = {0};
    cityXday[0][0] = 1;
    cityXday[0][10] = 1;
    

double temperature = .693 * 5.268;
//initialize cityXday with 50% 1's and 0's randomly, excluding the starting point of harrisburg
     double counter = 0;
     
     while(counter < 50)
     {
         // Initialize random number generator
     
    
     int randRow = (rand() % 9) + 1; //make sure this includes 1 and 9 double check this is right
     int randCol = (rand() % 9) + 1;
     
    
     
    if(cityXday[randRow][randCol] == 0)
        {
            cityXday[randRow][randCol] = 1;
            counter = counter + 1;
        }
    else
        {
            cityXday[randRow][randCol] = 0;
            counter = counter;
        }
     }
     
double counter00 = 0;     
double totalhoriz = 99;
double constraint = 0;
///perform cycling
while (temperature > .365 || constraint != 9)
{
cycle(cityXday, &temperature, &constraint);
temperature = .99 * temperature;
/*
counter00 = 0;
double newcounter = 0;
newcounter = 0;
 for (int i = 1; i < 10; i++)
    {
        counter00 = 0;
            for (int j = 0; j < 11; j++)  
            {
                if(cityXday[i][j] == 1)
                    {
                        counter00 = counter00 + 1;
                    }
                   
            }
            if (counter00 > 1)
                {
                    newcounter = newcounter + 1;
                }
                else
                {
                    newcounter = newcounter;
                }
                
    }
    
totalhoriz = newcounter;
*/


}



    


for (int i = 0; i < 10; i++) 
{ 
   for (int j = 0; j < 11; j++) 
   { 
      cout << cityXday[i][j] << " "; 
   } 
     
   // Newline for new row 
   cout << endl; 
   
}

      
cout << "   0 HBG  (40.203, -76.742) "; cout << endl;
cout << "  1 UP    (40.798, -77.867) "; cout << endl;
cout << "  2 Behrend (42.119, -79.984) ";cout << endl;
cout << "  3 Beaver   (40.678, -80.297)";cout << endl;
cout << "  4 York     (39.950, -76.704)";cout << endl;
cout << "  5 Altoona   (40.541, -78.412)";cout << endl;
cout << "  6 Abington  (40.116, -75.111)";cout << endl;
cout << "  7 Wilkes-Barre (41.307, -76.015)";cout << endl;
cout << "  8 Williamsport  (41.234, -77.022)";cout << endl;
cout << "  9 Pittsburg  (40.444, -79.989)   ";cout << endl;
return 0;
}




void cycle(double cityXday1[][11], double *temp, double *constrain)
{
    double cyclecounter = 0;
    double prevDistance = 0;
    double totalDistance = 0;
    double first[10];
    double second[10];
    int countr = 0;
    double distBetween2values = 0;
    int a;
    int b;
    double totalFirst;
    double totalSecond;
    //find initial distance
        for (int i = 0; i < 10; i++)
    {
            for (int j = 0; j < 10; j++)  //first location
            {
                if(cityXday1[j][i] == 1)
                    {
                        first[countr] = j;
                        countr = countr + 1;
                    }
            }
            totalFirst = countr;
            countr = 0;
            for (int j = 0; j< 10; j++) //second location
            {
                if(cityXday1[j][i+1] == 1)
                    {
                        second[countr] = j;
                        countr = countr + 1;
                    }  
            }    
            totalSecond = countr;
            countr = 0;
  
    for (int k = 0; k < totalFirst; k++)
        {
            for(int z = 0; z<totalSecond; z++)
                {
                    a = first[k];
                    b = second[z];
                 computeDistance(a, b, &distBetween2values);   
                 totalDistance = totalDistance + distBetween2values;
                }
            
        }
    
    }
    prevDistance = totalDistance;
    
    //begin the cycle
   while  (cyclecounter < 100)
   {
    //code for function that flips bit
    int randrow1 =  (rand() % 9) + 1;
    int randcol1 =  (rand() % 9) + 1;
    double prev;
    
    double multipleOld = 0;

            for (int j = 0; j < 10; j++) 
            {
                if(cityXday1[j][randcol1] == 1)
                    {
                        multipleOld = multipleOld + 1;
                        
                    }
                
                    
            }
    
    double horiz = 0;

            for (int j = 0; j < 11; j++) 
            {
                if(cityXday1[randrow1][j] == 1)
                    {
                        horiz = horiz + 1;
                        
                    }
                
                    
            }    
    
    if(cityXday1[randrow1][randcol1] == 0)
        {
            cityXday1[randrow1][randcol1] = 1;
            prev = 0;
        }
    else
        {
            cityXday1[randrow1][randcol1] = 0;   
            prev = 1;
        }
    


//code that calculates total distance

totalDistance = 0;
for (int i = 0; i < 10; i++)
    {
            for (int j = 0; j < 10; j++)  //first location
            {
                if(cityXday1[j][i] == 1)
                    {
                        first[countr] = j;
                        countr = countr + 1;
                    }
            }
            totalFirst = countr;
            countr = 0;
            for (int j = 0; j< 10; j++) //second location
            {
                if(cityXday1[j][i+1] == 1)
                    {
                        second[countr] = j;
                        countr = countr + 1;
                    }  
            }    
            totalSecond = countr;
            countr = 0;
  
    for (int k = 0; k < totalFirst; k++)
        {
          
            for(int z = 0; z<totalSecond; z++)
                {
                    a = first[k];
                    b = second[z];
                 computeDistance(a, b, &distBetween2values);   
                 totalDistance = totalDistance + distBetween2values;
                }
            
        }
    
    }


double deltaC = (1-2*prev) * (totalDistance * prevDistance);
//5.268 is distance from abington to berend
double ex = exp(-1*deltaC / *temp);
double AofT = 1 / (1 + ex);

//calculate repeat constrain
double newcount = 0;
*constrain = 0;
for (int i = 0; i < 10; i++)
    {
            for (int j = 0; j < 10; j++) 
            {
                if(cityXday1[j][i] == 1)
                    {
                        newcount = newcount + 1;
                        j = 99;
                    }
                if(newcount != 0)
                    {
                        *constrain = *constrain + 1;
                    }
                    newcount = 0;
            }
    }
    
//calculate multiple days twice penalty

double multiple = 0;

            for (int j = 0; j < 10; j++) 
            {
                if(cityXday1[j][randcol1] == 1)
                    {
                        multiple = multiple + 1;
                        
                    }
                
                    
            }
    
    
double newhoriz = 0;

            for (int j = 0; j < 11; j++) 
            {
                if(cityXday1[randrow1][j] == 1)
                    {
                        newhoriz = newhoriz + 1;
                        
                    }
                
                    
            }    


float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

//conditions for reverting switch
if (r < AofT || *constrain < 10 || multiple > multipleOld || newhoriz > horiz)

    {
         if(cityXday1[randrow1][randcol1] == 0)
        {
            cityXday1[randrow1][randcol1] = 1;
        }
    else
        {
            cityXday1[randrow1][randcol1] = 0;   
        }
    }
    
cyclecounter = cyclecounter + 1;
prevDistance = totalDistance;
}





return;
}


///compute distance function
void computeDistance(int firstcity, int secondcity, double *distances)
{
double xCoords[10] = {40.203, 40.798, 42.119, 40.678, 39.950, 40.541, 40.116, 41.307, 41.234, 40.444};    
double yCoords[10] = {-76.742, -77.867, -79.984, -80.297, -76.704, -78.412, -75.111, -76.015, -77.022, -79.989};

double x = xCoords[secondcity] - xCoords[firstcity];
double y = yCoords[secondcity] - yCoords[firstcity];
double z = abs(y * y - x * x);
*distances = sqrt(z);

return;
}


