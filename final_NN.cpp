//Matthew Capuano EE 556 - CNN
//I assume that normally you would perform a training and testing sequence
//where with training you would apply an image knowing the name of shape, 
//then see what kernels intensities associate with it,
//then train the network to associate those kernel intensities with the name of the shape provided.

//for this application, I am basically skipping the training and saying that certain kernel intensities correllate
// with certain shape names(since it is obvious which kernels will pick up parts of which shapes, IE the the diagonal kernals line up with the diagonals of a triangle)
// and outputing a shape name based on what intensities I get.
//Essentially, the weight that the kernel intensities in association with name of shape have will be predetermined and fixed instead of trained.

#include <iostream>
#include <stdio.h>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
using namespace std;

//TRY PLAYING WITH INPUT SIZE OF CELLS OR TRAINING PARAMETER, TRY PLAYING WITH NORMALIZATION OF INPUT VALUES, DOUBLE CHECK HOW NN IS SET UP
void pooling(int shape[][9][9], double *k0, double *k1, double *k2, double *k3, double *k4); 
int apply_kernel(int shape[][9][9], int kernel[][3]);
void feed_forward_network(double k0, double k1, double k2, double k3, double k4, int train, int desired[], double w_matrix[][100], double v_matrix[][4], double *error);


int main()
{

double w_matrix[5][100];
for (int i = 0; i < 5; i++)
{
	for (int j = 0; j < 100; j++) w_matrix[i][j] = .25;
}

double v_matrix[100][4];
for (int i = 0; i < 100; i++)
{
	for (int j = 0; j<4; j++) v_matrix[i][j] = .25;
}


//Generate Inputs --> layers are bottom-up
int square9[9][9][9] ={{{1,1,1,1,1,1,1,1,1},
					   {1,1,1,1,1,1,1,1,1},
					   {1,1,1,1,1,1,1,1,1},
					   {1,1,1,1,1,1,1,1,1},
					   {1,1,1,1,1,1,1,1,1},
					   {1,1,1,1,1,1,1,1,1},
					   {1,1,1,1,1,1,1,1,1},
					   {1,1,1,1,1,1,1,1,1},
					   {1,1,1,1,1,1,1,1,1}},

					  {{1,1,1,1,1,1,1,1,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,1,1,1,1,1,1,1,1}},

					  {{1,1,1,1,1,1,1,1,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,1,1,1,1,1,1,1,1}},	

					  {{1,1,1,1,1,1,1,1,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,1,1,1,1,1,1,1,1}},	

					  {{1,1,1,1,1,1,1,1,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,1,1,1,1,1,1,1,1}},	

					  {{1,1,1,1,1,1,1,1,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,1,1,1,1,1,1,1,1}},	

					  {{1,1,1,1,1,1,1,1,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,1,1,1,1,1,1,1,1}},	

					  {{1,1,1,1,1,1,1,1,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,1,1,1,1,1,1,1,1}},	

					  {{1,1,1,1,1,1,1,1,1},
					   {1,1,1,1,1,1,1,1,1},
					   {1,1,1,1,1,1,1,1,1},
					   {1,1,1,1,1,1,1,1,1},
					   {1,1,1,1,1,1,1,1,1},
					   {1,1,1,1,1,1,1,1,1},
					   {1,1,1,1,1,1,1,1,1},
					   {1,1,1,1,1,1,1,1,1},
					   {1,1,1,1,1,1,1,1,1}}};

int triangle9[9][9][9]={{{0,0,0,0,1,0,0,0,0},
						{0,0,0,1,0,1,0,0,0},
						{0,0,1,0,0,0,1,0,0},
						{0,1,0,0,0,0,0,1,0},
						{1,0,0,0,0,0,0,0,1},
						{0,1,0,0,0,0,0,1,0},
						{0,0,1,0,0,0,1,0,0},
						{0,0,0,1,0,1,0,0,0},
						{0,0,0,0,1,0,0,0,0}},

						{{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,1,0,0,0,0},
						{0,0,0,1,0,1,0,0,0},
						{0,0,1,0,0,0,1,0,0},
						{0,1,0,0,0,0,0,1,0},
						{0,0,1,0,0,0,1,0,0},
						{0,0,0,1,0,1,0,0,0},
						{0,0,0,0,1,0,0,0,0},
						{0,0,0,0,0,0,0,0,0}},

						{{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,1,0,0,0,0},
						{0,0,0,1,0,1,0,0,0},
						{0,0,1,0,0,0,1,0,0},
						{0,0,0,1,0,1,0,0,0},
						{0,0,0,0,1,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0}},

						{{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,1,0,0,0,0},
						{0,0,0,1,0,1,0,0,0},
						{0,0,0,0,1,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0}},

						{{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,1,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0}},

						{{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0}},

						{{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0}},

						{{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0}},

						{{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0}}};

int circle9[9][9][9] =  {{{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,1,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0}},

						{{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,1,1,1,0,0,0},
						{0,0,1,1,0,1,1,0,0},
						{0,0,0,1,1,1,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0}},

						{{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,1,1,1,0,0,0},
						{0,0,1,1,0,1,1,0,0},
						{0,0,0,1,1,1,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0}},

						{{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,1,1,1,0,0,0},
						{0,0,1,1,0,1,1,0,0},
						{0,0,0,1,1,1,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0}},

						{{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,1,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0}},

						{{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0}},

						{{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0}},

						{{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0}},

						{{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0}}};

int jack9[9][9][9] =  {{{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,1,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0}},

						{{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,1,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0}},


						{{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,1,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0}},

					   {{0,0,0,0,1,0,0,0,0},
						{0,0,0,0,1,0,0,0,0},
						{0,0,0,0,1,0,0,0,0},
						{0,0,0,0,1,0,0,0,0},
						{1,1,1,1,1,1,1,1,1},
						{0,0,0,0,1,0,0,0,0},
						{0,0,0,0,1,0,0,0,0},
						{0,0,0,0,1,0,0,0,0},
						{0,0,0,0,1,0,0,0,0}},

						{{0,0,0,0,1,0,0,0,0},
						{0,0,0,0,1,0,0,0,0},
						{0,0,0,0,1,0,0,0,0},
						{0,0,0,0,1,0,0,0,0},
						{1,1,1,1,1,1,1,1,1},
						{0,0,0,0,1,0,0,0,0},
						{0,0,0,0,1,0,0,0,0},
						{0,0,0,0,1,0,0,0,0},
						{0,0,0,0,1,0,0,0,0}},

						{{0,0,0,0,1,0,0,0,0},
						{0,0,0,0,1,0,0,0,0},
						{0,0,0,0,1,0,0,0,0},
						{0,0,0,0,1,0,0,0,0},
						{1,1,1,1,1,1,1,1,1},
						{0,0,0,0,1,0,0,0,0},
						{0,0,0,0,1,0,0,0,0},
						{0,0,0,0,1,0,0,0,0},
						{0,0,0,0,1,0,0,0,0}},

						{{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,1,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0}},

						{{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,1,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0}},

						{{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,1,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0}}};

int diamond9[9][9][9]={{{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,1,0,0,0,0},
						{0,0,0,1,0,1,0,0,0},
						{0,0,1,0,0,0,1,0,0},
						{0,0,0,1,0,1,0,0,0},
						{0,0,0,0,1,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0}},

						{{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,1,0,0,0,0},
						{0,0,0,1,0,1,0,0,0},
						{0,0,1,0,0,0,1,0,0},
						{0,0,0,1,0,1,0,0,0},
						{0,0,0,0,1,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0}},

						{{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,1,0,0,0,0},
						{0,0,0,1,0,1,0,0,0},
						{0,0,1,0,0,0,1,0,0},
						{0,0,0,1,0,1,0,0,0},
						{0,0,0,0,1,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0}},

						{{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,1,0,0,0,0},
						{0,0,0,1,0,1,0,0,0},
						{0,0,1,0,0,0,1,0,0},
						{0,0,0,1,0,1,0,0,0},
						{0,0,0,0,1,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0}},

						{{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,1,0,0,0,0},
						{0,0,0,1,0,1,0,0,0},
						{0,0,1,0,0,0,1,0,0},
						{0,0,0,1,0,1,0,0,0},
						{0,0,0,0,1,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0}},

						{{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,1,0,0,0,0},
						{0,0,0,1,0,1,0,0,0},
						{0,0,1,0,0,0,1,0,0},
						{0,0,0,1,0,1,0,0,0},
						{0,0,0,0,1,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0}},

						{{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,1,0,0,0,0},
						{0,0,0,1,0,1,0,0,0},
						{0,0,1,0,0,0,1,0,0},
						{0,0,0,1,0,1,0,0,0},
						{0,0,0,0,1,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0}},

						{{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,1,0,0,0,0},
						{0,0,0,1,0,1,0,0,0},
						{0,0,1,0,0,0,1,0,0},
						{0,0,0,1,0,1,0,0,0},
						{0,0,0,0,1,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0}},

						{{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,1,0,0,0,0},
						{0,0,0,1,0,1,0,0,0},
						{0,0,1,0,0,0,1,0,0},
						{0,0,0,1,0,1,0,0,0},
						{0,0,0,0,1,0,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0}}};

					  


//Generate intensity values for each kernal
double k0tot, k1tot, k2tot, k3tot, k4tot;


//train with square, circle, triangle, jack, see where diamond gets matched to.
//pass input shape into pooling layer, receive intensity value of each kernal, pass to wta
double errortot =999;
double train;
int desired[4];
double errorcnt = 0;
double error;
//training phase
	while (errortot > 4)
	{
cout << errortot;cout <<"\n";
errorcnt = 0;
train = 1;
pooling(square9, &k0tot, &k1tot, &k2tot, &k3tot, &k4tot);
//cout << "Input Square applied to network...\n";
//	k0tot = k0tot/450; k1tot = k1tot/450; k2tot = k2tot/450; k3tot = k3tot/450; k4tot = k4tot/450;
desired[0]=1; desired[1]=0; desired[2]=0; desired[3]=0;
feed_forward_network(k0tot,k1tot,k2tot,k3tot,k4tot,train, desired,  w_matrix, v_matrix,  &error);
errorcnt = errorcnt + error;
pooling(triangle9, &k0tot, &k1tot, &k2tot, &k3tot, &k4tot);
//cout <<"Input triangle applied to network...\n";
//	k0tot = k0tot*10; k1tot = k1tot*10; k2tot = k2tot*10; k3tot = k3tot*10; k4tot = k4tot*10;
desired[0]=0;desired[1]=1;desired[2]=0;desired[3]=0; 
feed_forward_network(k0tot,k1tot,k2tot,k3tot,k4tot,train, desired,  w_matrix, v_matrix,  &error);
errorcnt = errorcnt + error;
pooling(circle9, &k0tot, &k1tot, &k2tot, &k3tot, &k4tot);
//cout <<"Input circle applied to network...\n";
//	k0tot = k0tot*10; k1tot = k1tot*10; k2tot = k2tot*10; k3tot = k3tot*10; k4tot = k4tot*10;
desired[0]=0;desired[1]=0;desired[2]=1;desired[3]=0;
feed_forward_network(k0tot,k1tot,k2tot,k3tot,k4tot,train, desired,  w_matrix, v_matrix,  &error);
errorcnt = errorcnt + error;
pooling(jack9, &k0tot, &k1tot, &k2tot, &k3tot, &k4tot);
//cout <<"Input jack applied to network...\n";
//	k0tot = k0tot*10; k1tot = k1tot*10; k2tot = k2tot*10; k3tot = k3tot*10; k4tot = k4tot*10;
desired[0]=0;desired[1]=0;desired[2]=0;desired[3]=1;
feed_forward_network(k0tot,k1tot,k2tot,k3tot,k4tot,train, desired,  w_matrix, v_matrix,  &error);
errorcnt = errorcnt + error;
errortot = errorcnt;
	}
	

	//testing phase
train = 0;
pooling(square9, &k0tot, &k1tot, &k2tot, &k3tot, &k4tot);
//	k0tot = k0tot/450; k1tot = k1tot/450; k2tot = k2tot/450; k3tot = k3tot/450; k4tot = k4tot/450;
//cout << "Input Square applied to network...\n";
desired[0]=1;desired[1]=0;desired[2]=0;desired[3]=0;
feed_forward_network(k0tot,k1tot,k2tot,k3tot,k4tot,train, desired,  w_matrix, v_matrix,  &error);

pooling(triangle9, &k0tot, &k1tot, &k2tot, &k3tot, &k4tot);
//cout <<"Input triangle applied to network...\n";
//	k0tot = k0tot*10; k1tot = k1tot*10; k2tot = k2tot*10; k3tot = k3tot*10; k4tot = k4tot*10;
desired[0]=0;desired[1]=1;desired[2]=0;desired[3]=0;
feed_forward_network(k0tot,k1tot,k2tot,k3tot,k4tot,train, desired,  w_matrix, v_matrix,  &error);

pooling(circle9, &k0tot, &k1tot, &k2tot, &k3tot, &k4tot);
//cout <<"Input circle applied to network...\n";
//	k0tot = k0tot*10; k1tot = k1tot*10; k2tot = k2tot*10; k3tot = k3tot*10; k4tot = k4tot*10;
desired[0]=0;desired[1]=0;desired[2]=1;desired[3]=0;
feed_forward_network(k0tot,k1tot,k2tot,k3tot,k4tot,train, desired,  w_matrix, v_matrix,  &error);

pooling(jack9, &k0tot, &k1tot, &k2tot, &k3tot, &k4tot);
//cout <<"Input jack applied to network...\n";
//	k0tot = k0tot*10; k1tot = k1tot*10; k2tot = k2tot*10; k3tot = k3tot*10; k4tot = k4tot*10;
desired[0]=0;desired[1]=0;desired[2]=0;desired[3]=1;
feed_forward_network(k0tot,k1tot,k2tot,k3tot,k4tot,train, desired,  w_matrix, v_matrix,  &error);

pooling(diamond9, &k0tot, &k1tot, &k2tot, &k3tot, &k4tot);
//cout <<"Input jack applied to network...\n";
//	k0tot = k0tot*10; k1tot = k1tot*10; k2tot = k2tot*10; k3tot = k3tot*10; k4tot = k4tot*10;
desired[0]=0;desired[1]=0;desired[2]=0;desired[3]=2;
feed_forward_network(k0tot,k1tot,k2tot,k3tot,k4tot,train, desired,  w_matrix, v_matrix,  &error);
	return 0;
}






void pooling(int shape[][9][9], double *k0, double *k1, double *k2, double *k3, double *k4)
{
//initialize kernels
				//Corellation: High.......................Low
int kernel0[3][3] ={{0,0,0},  //square, jack, triangle, circle
					{1,1,1},
					{0,0,0}};

int kernel1[3][3] ={{0,1,0}, //square, jack, circle, triangle
					{0,1,0},
					{0,1,0}};

int kernel2[3][3] ={{0,0,1}, //jack, triangle, circle, square
					{0,1,0},
					{1,0,0}};

int kernel3[3][3] ={{1,0,0}, //jack, triangle, circle, square
					{0,1,0},
					{0,0,1}};

int kernel4[3][3] ={{0,0,0}, //circle, jack, square, triangle
					{0,1,1},
					{0,1,0}};

//apply each kernel to input shape, send back the kernel intensities
*k0 = apply_kernel(shape, kernel0);
*k1 = apply_kernel(shape, kernel1);
*k2 = apply_kernel(shape, kernel2);
*k3 = apply_kernel(shape, kernel3);
*k4 = apply_kernel(shape, kernel4);

return;
}


int apply_kernel(int shape[][9][9], int kernel[][3])
{
	int tot = 0;
	int counter = 0;

//run over the images, perform dot products 
// If acutal masking occurs (9 dot products across 3x3 region of input shape, place total in center value, move to next pixel),
//not enough data can be extracted.  Therefore, only if all three if the bits in kernel match the area of the input image does the center pixel register.
for(int k = 0; k < 9; k++)
{
for (int i = 0; i < 9; i++)
{
	for(int j = 0; j< 9; j++)
	{ 
		tot = 0;
		tot = tot + shape[i][j][k] * kernel[1][1];
		if (i - 1 >= 0) tot = tot + shape[i-1][j][k] * kernel[0][1];
		if ((i - 1 >= 0) && (j - 1 >= 0)) tot = tot + shape[i-1][j-1][k] * kernel[0][0];
		if (j - 1 >= 0) tot = tot + shape[i][j-1][k] * kernel[1][0];
		if ((j - 1 >= 0) && (i + 1 <= 8)) tot = tot + shape[i+1][j-1][k] * kernel[2][0];
		if (i + 1 <= 8) tot = tot + shape[i+1][j][k] * kernel[2][1];
		if (j + 1 <= 8) tot = tot + shape[i][j+1][k] * kernel[1][2];
		if ((j + 1 <= 8) && (i - 1 >= 0)) tot = tot + shape[i-1][j+1][k] * kernel[0][2];
		if ((j+ 1 <= 8) && (i + 1 <= 8)) tot = tot + shape[i+1][j+1][k] * kernel[2][2];

		if (tot == 3) counter = counter + 1; //only register if all 3 parts of kernel match, instead of doing traditional spactial masking
	}
}
}
	return counter;
}

void feed_forward_network(double k0, double k1, double k2, double k3, double k4, int train, int desired[], double w_matrix[][100], double v_matrix[][4], double *error)
{

//commented code was WTA before trained network was added

/*//Kernel Intensity Order
//Square:  Order => 1 and 2 are highest, 2 and 3 are lowest
//Triangle:Order => 2 and 3 are highest, 1 and 2 are lowest
//Circle:  Order => 4 is highest, 0 is lowest
//Jack:    Order => Everything gets picked up, if min is close to highest, reg 

int tots[5] = {k0, k1, k2, k3, k4};
int max;
int min;
cout <<"Kernel Intensity Calculation..\n";
cout <<"kernel 0,1,2,3,4\n";

for (int i = 0; i < 5; i++)
{
	cout << tots[i]; cout <<" ";
}
cout <<"\n";

//based on differences in itensities of each kernel, determine detected object
if (tots[0] - tots [2] > 5) cout << "Detected Object is square.\n";
else if (tots[2] - tots[1] > 5) cout <<"Detected Object is triangle\n";
else if (tots[4] - tots[0] > 5) cout << "Detected Object is circle\n";
else cout << "Detected Object is jack\n";

cout <<"\n";
	return;
	*/

int input[5];
input[0] = k0;input[1] = k1; input[2] = k2; input[3] = k3; input[4] = k4;
int z_cells[4];
double output[4];
double ph = 0;
double bias[4];

for (int j = 0; j < 4; j++) //run input through w matrix
{
	ph = 0;
	for (int i = 0; i <5; i++)
	{
		ph = ph + input[i] * w_matrix[i][j];
	}
	z_cells[j] = ph + bias[j];
	z_cells[j] = 1 / (1 + exp(-1 * z_cells[j]));
}

for (int j = 0; j < 4; j++) //run z cells through v matrix
{
	ph = 0;
	for(int i = 0; i <4; i++)
	{
		ph = ph + z_cells[i] * v_matrix[i][j];
	}
	output[j] = ph;
	output[j] = 1 / (1 + exp(-1 * output[j]));
}

//calc error
double errortot = 0;
for (int i = 0; i < 4; i++) errortot = errortot + abs(output[i] - desired[i]) * abs(output[i] - desired[i]);
*error = errortot;

//train if in training mode
	double alpha = .1;
	if (train == 1)
	{
		cout <<"output values: \n";
		for (int i = 0; i <4; i++) {cout <<output[i]; cout<< " ";}
			cout <<"\n";
		
		cout <<"desired values: \n";
		for (int i = 0; i <4; i++){ cout <<desired[i]; cout<< " ";}
			cout <<"\n";
	
		for(int j =0; j <5; j++) //train w
		{
			for (int i = 0; i < 4; i++) w_matrix[j][i] = w_matrix[j][i] + alpha * (z_cells[i] * (1 - z_cells[i])) * (desired[i] - output[i]) * output[i] * (1 - output[i])*input[i];
		}	
			for(int j =0; j <4; j++) //train bias
		{
			 bias[j] = bias[j] + alpha * (z_cells[j] * (1 - z_cells[j])) * (desired[j] - output[j]) * output[j] * (1 - output[j])*w_matrix[4][j];
		}	
		for (int j=0; j<4; j++)//train v
		{
			for (int i = 0; i <4; i++) v_matrix[j][i] = v_matrix[j][i] + alpha * (desired[i] - output[i]) * output[i] * (1 - output[i]);
		}
	}
	//output value if not in training mode
	else{
		if(desired[0] == 1) cout << "input is square\n";
   else if(desired[1] == 1) cout << "input is triangle\n";
   else if(desired[2] == 1) cout << "input is circle\n";
   else if(desired[3] == 1) cout << "input is jack\n";
   else if(desired[3] == 2) cout << "input is diamond\n";

	//WTA stage
	const int N = sizeof(output) / sizeof(int);
	int maxx;
	maxx = distance(output, max_element(output, output + N));
 		if (maxx == 0) cout <<"The network classified the image as a square\n";
   else if (maxx == 1) cout <<"The network classified the image as a triangle\n";
   else if (maxx == 2) cout <<"The network classified the image as a circle\n";
   else cout <<"The network classified the image as a jack\n";
		}

return;
}