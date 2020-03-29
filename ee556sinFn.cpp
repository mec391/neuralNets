#include <iostream>
#include <stdio.h>
#include <cmath>
#include <stdlib.h>
using namespace std;


void run_through_network(double degrees);


int main()
{
	double degrees[91]; //scale from 0 to 90 degrees
	degrees[0] = 0;
	run_through_network(degrees[0]);

	for (int i = 1; i < 91; i++)
	{
		degrees[i] = degrees[i-1] + 1;
		run_through_network(degrees[i]);
	}
	

return 0;
}




void run_through_network(double degrees)
{
	double one = 1;
	double w_weights[2][21]; //bias is row 2 of w matrix
	double z_cells[21];
	double v_weights[21]; //no bias on v matrix
	double y_out;
	
	////////////////////initializing weight matricies//////////
	for (int i = 0; i < 21; i++) //time weight = 1
	{
		w_weights[0][i] = 1;
	}
//activate at inputs 0,1,3,6,10,15,20,25,30,35,40,45,50,55,60
				//   65,70,75,80,85,90 
	w_weights[1][0] = 1;
	w_weights[1][1] = -1;
	w_weights[1][2] = -3;
	w_weights[1][3] = -6;
	w_weights[1][4] = -10;
	for (int i = 5; i < 21; i ++)
	{
		w_weights [1][i] = w_weights[1][i-1] - 5;
	}
	//take sin of the inputs that activate, subtract previous sin value
	//since output is cumulative
	v_weights[0] = 0; //sin0 = 0
	v_weights[1] = .017; //x0 + x1 = sin1
	v_weights[2] = .035; //x0 + x1 + x2 = sin3
	v_weights[3] = .052; //x0 + x1 + x2 + x3 = sin6
	v_weights[4] = .0696;//"   " ... ect.
	v_weights[5] = .0852;
	v_weights[6] = .0832;
	v_weights[7] = .0860;
	v_weights[8] = .072;
	v_weights[9] = .0736;
	v_weights[10]= .0692;
	v_weights[11]= .0643;
	v_weights[12]= .0589;
	v_weights[13]= .0532;
	v_weights[14]= .0468;
	v_weights[15]= .0403;
	v_weights[16]= .0334;
	v_weights[17]= .0262;
	v_weights[18]= .0189;
	v_weights[19]= .0114;
	v_weights[20]= .0038;
	////////////////////////end initialzation////////////
	
	for (int i = 0; i < 21; i++)
	{
			z_cells[i] = degrees * w_weights[0][i] + one * w_weights[1][i]; 
			
			if (z_cells[i] >= 0)//unipolar step AF
			{
			z_cells[i] = 1;	
			}
			else
			{
			z_cells[i] = 0;
			}
	}
	for (int i = 0; i < 21; i++)
	{
		y_out = y_out + z_cells[i] * v_weights[i];
	}
		//no need for unipolar linear AF code since output can only scale from 0 to 1

cout << "\n";
cout << "Input = "; cout << degrees; cout <<"     Output =";
cout << y_out;
cout << "\n";

	return;
}