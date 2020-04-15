//Matthew Capuano
//EE 556 Convolution Kernel

#include <iostream>
#include <stdio.h>
#include <cmath>
#include <stdlib.h>
using namespace std;

void convolve(double insignal[]);
void display(double insignal[]);

int main()
{

double ramp[9] = {0, .1, .2, .3, .4, .5, .6, .7, .8 };
double pulse[9]= {.2, .2, .2, .8, .8, .8, .2, .2, .2};

double counter = 0;

convolve(ramp);
convolve(pulse);
counter = counter + 1;
cout << "Data Type: Ramp     Iterations: 1 \n";
display(ramp);
cout <<"Data Type:  Pulse     Iterations: 1 \n";
display(pulse);

while (counter < 10)
{
	convolve(ramp);
	convolve(pulse);
	counter = counter + 1;
}
cout <<"Data Type: Ramp     Iterations: 10 \n";
display(ramp);
cout <<"Data Type: Pulse    Iterations: 10 \n";
display(pulse);

while (counter < 1000)
{
	convolve(ramp);
	convolve(pulse);
	counter = counter + 1;
}
cout <<"Data Type: Ramp     Iterations: 1000 \n";
display(ramp);
cout <<"Data Type: Pulse    Iterations: 1000 \n";
display(pulse);



	return 0;
}

void convolve(double insignal[])
{
double r1 = 1;
double r2 = 4;
double alpha = .6;
double epsilon= -.2;

double placehold[9];

placehold[0] = alpha * (insignal[0] + insignal[1]) + epsilon * (insignal[2] + insignal[3] + insignal[4]); 
placehold[1] = alpha * (insignal[0] + insignal[1] + insignal[2]) + epsilon * (insignal[3] + insignal[4] + insignal[5]);
placehold[2] = epsilon * insignal[0] + alpha * (insignal[1] + insignal[2] + insignal[3]) + epsilon * (insignal [4] + insignal[5] + insignal[6]);
placehold[3] = epsilon * (insignal[0] + insignal[1]) + alpha * (insignal[2] + insignal[3]+ insignal[4]) + epsilon*(insignal[5] + insignal[6] + insignal[7]);
placehold[4] = epsilon * (insignal[0] + insignal[1] + insignal[2]) + alpha * (insignal[3] + insignal[4] + insignal[5]) + epsilon * (insignal[6] + insignal[7] + insignal[8]);
placehold[5] = epsilon * (insignal[1] + insignal[2] + insignal[3]) + alpha * (insignal[4] + insignal[5] + insignal[6]) + epsilon * (insignal[7] + insignal[8]);
placehold[6] = epsilon * (insignal[2] + insignal[3] + insignal[4]) + alpha * (insignal[5] + insignal[6] + insignal[7]) + epsilon * (insignal[8]);
placehold[7] = epsilon * (insignal[3] + insignal[4] + insignal[5]) + alpha * (insignal[6] + insignal[7] + insignal[8]);
placehold[8] = epsilon * (insignal[4] + insignal[5] + insignal[6]) + alpha * (insignal[7] + insignal[8]);

for (int i = 0; i < 9; i++)
{
 	insignal[i] = placehold[i];
}
	return;
}



void display(double insignal[])
{
	for(int i = 0; i < 10; i++)
	{
		cout << insignal[i];
		cout << " ";
	}

cout << "\n";


	return;
}