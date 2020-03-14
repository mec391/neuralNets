#include <iostream>
#include <stdio.h>
#include <cmath>
#include <stdlib.h>
using namespace std;


void createweights(double inweights[][7],double inbcd[],double in7seg[]);
void run_and_train(double inweights[][7],double inbcd[],double in7seg[], double *error);
void displayweights(double inweights[][7]);


int main()
{
	double bcd0[3] = {-1,-1,-1};
	double bcd1[3] = {-1,-1,1};
	double bcd2[3] = {-1,1,-1};
	double bcd3[3] = {-1,1,1};
	double bcd4[3] = {1,-1,-1};
	double bcd5[3] = {1,-1,1};
	double bcd6[3] = {1,1,-1};
	double bcd7[3] = {1,1,1};

	double seg0[7] = {1,1,1,1,1,1,-1};
	double seg1[7] = {-1,1,1,-1,-1,-1,-1};
	double seg2[7] = {1,1,-1,1,1,-1,1};
	double seg3[7] = {1,1,1,1,-1,-1,1};
	double seg4[7] = {-1,1,1,-1,-1,1,1};
	double seg5[7] = {1,-1,1,1,-1,1,1};
	double seg6[7] = {1,-1,1,1,1,1,1};
	double seg7[7] = {1,1,1,-1,-1,-1,-1};

	double weights[3][7];

	createweights(weights, bcd0, seg0); //create weight matrix
	createweights(weights, bcd1, seg1);
	createweights(weights, bcd2, seg2);
	createweights(weights, bcd3, seg3);
	createweights(weights, bcd4, seg4);
	createweights(weights, bcd5, seg5);
	createweights(weights, bcd6, seg6);
	createweights(weights, bcd7, seg7);

	cout << "initial weight matrix: ";
	displayweights(weights);
	
	double error = 9999;
	while (error > 3) //train until 4 outputs match
	{
	run_and_train(weights, bcd0, seg0, &error);
	run_and_train(weights, bcd1, seg1, &error);
	run_and_train(weights, bcd2, seg2, &error);
	run_and_train(weights, bcd3, seg3, &error);
	run_and_train(weights, bcd4, seg4, &error);
	run_and_train(weights, bcd5, seg5, &error);
	run_and_train(weights, bcd6, seg6, &error);
	run_and_train(weights, bcd7, seg7, &error);
	displayweights(weights);
	}

	return 0;
}





void createweights(double inweights[][7], double inbcd[], double in7seg[])
{
	for (int i=0; i < 3; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			inweights[i][j] = inweights[i][j] + inbcd[i] * in7seg[j];
		}
	}
return;
}




void run_and_train(double inweights[][7], double inbcd[], double in7seg[], double *error)
{
	double actual7seg[7];

	for(int i = 0; i < 7; i++)
		{
			actual7seg[i] = inbcd[0] * inweights[0][i] + inbcd[1] * inweights[1][i] + inbcd[2] * inweights[2][i];
			if (actual7seg[i] > 0)
				actual7seg[i] = 1;
			else
				actual7seg[i] = -1;
		}


			

	cout <<"desired output is ";
		for (int i = 0; i < 7; i ++)
		{
			cout << in7seg[i];
			cout << " ";
		}
	cout << "\n";
	cout << "actual output is ";
		for (int i = 0; i < 7; i ++)
		{
			cout << actual7seg[i];
			cout << " ";

		}
		cout <<"\n";
		cout <<"training if necessary...\n"; //add 'emphasis'
double errorcounter = 0;
		for (int i = 0; i < 7; i++)
		{
			if (actual7seg[i] != in7seg[i]);
				{
					errorcounter = errorcounter + 1;
					double dummy[3][7];
					createweights(dummy, inbcd, in7seg);
					for (int j = 0; j <3; j++)
					{
						inweights[j][i] = inweights[j][i] + dummy[j][i];
					}
				}

		}
*error = errorcounter;

return;
}





void displayweights(double inweights[][7])
{
	cout << "\n";
	for (int i = 0; i < 3; i++ )
	{
		for (int j = 0; j <7; j++)
		{
			cout <<inweights[i][j];
			cout << " ";
		}
		cout <<"\n";
	}

	cout <<"\n";

return;
}