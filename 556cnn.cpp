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


void pooling(int shape[][9], int *k0, int *k1, int *k2, int *k3, int *k4); 
int apply_kernel(int shape[][9], int kernel[][3]);
void wta(int k0, int k1, int k2, int k3, int k4);


int main()
{

//Generate Inputs
int square9[9][9] =   {{1,1,1,1,1,1,1,1,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,0,0,0,0,0,0,0,1},
					   {1,1,1,1,1,1,1,1,1}};

int triangle9[9][9]=   {{0,0,0,0,1,0,0,0,0},
						{0,0,0,1,0,1,0,0,0},
						{0,0,1,0,0,0,1,0,0},
						{0,1,0,0,0,0,0,1,0},
						{1,0,0,0,0,0,0,0,1},
						{0,1,0,0,0,0,0,1,0},
						{0,0,1,0,0,0,1,0,0},
						{0,0,0,1,0,1,0,0,0},
						{0,0,0,0,1,0,0,0,0}};

int circle9[9][9] =     {{0,0,0,1,1,1,0,0,0},
						 {0,0,1,1,0,1,1,0,0},
						 {0,1,1,0,0,0,1,1,0},
						 {1,1,0,0,0,0,0,1,1},
						 {1,1,0,0,0,0,0,1,1},
						 {1,1,0,0,0,0,0,1,1},
						 {0,1,1,0,0,0,1,1,0},
						 {0,0,1,1,0,1,1,0,0},
						 {0,0,0,1,1,1,0,0,0}};

int jack9[9][9] =	    {{1,0,0,0,1,0,0,0,1},
						 {0,1,0,0,1,0,0,1,0},
						 {0,0,1,0,1,0,1,0,0},
						 {0,0,0,1,1,1,0,0,0},
						 {1,1,1,1,1,1,1,1,1},
						 {0,0,0,1,1,1,0,0,0},
						 {0,0,1,0,1,0,1,0,0},
						 {0,1,0,0,1,0,0,1,0},
						 {1,0,0,0,1,0,0,0,1}};

//Generate intensity values for each kernal
int k0tot, k1tot, k2tot, k3tot, k4tot;

//pass input shape into pooling layer, receive intensity value of each kernal, pass to wta
pooling(square9, &k0tot, &k1tot, &k2tot, &k3tot, &k4tot);
cout << "Input Square applied to network...\n";
wta(k0tot, k1tot, k2tot, k3tot, k4tot);

pooling(triangle9, &k0tot, &k1tot, &k2tot, &k3tot, &k4tot);
cout <<"Input triangle applied to network...\n";
wta(k0tot, k1tot, k2tot, k3tot, k4tot);

pooling(circle9, &k0tot, &k1tot, &k2tot, &k3tot, &k4tot);
cout <<"Input circle applied to network...\n";
wta(k0tot, k1tot, k2tot, k3tot, k4tot);

pooling(jack9, &k0tot, &k1tot, &k2tot, &k3tot, &k4tot);
cout <<"Input jack applied to network...\n";
wta(k0tot, k1tot, k2tot, k3tot, k4tot);

	return 0;
}





void pooling(int shape[][9], int *k0, int *k1, int *k2, int *k3, int *k4) 
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


int apply_kernel(int shape[][9], int kernel[][3])
{
	int tot = 0;
	int counter = 0;

//run over the images, perform dot products 
// If acutal masking occurs (9 dot products across 3x3 region of input shape, place total in center value, move to next pixel),
//not enough data can be extracted.  Therefore, only if all three if the bits in kernel match the area of the input image does the center pixel register.
for (int i = 0; i < 9; i++)
{
	for(int j = 0; j< 9; j++)
	{ 
		tot = 0;
		tot = tot + shape[i][j] * kernel[1][1];
		if (i - 1 >= 0) tot = tot + shape[i-1][j] * kernel[0][1];
		if ((i - 1 >= 0) && (j - 1 >= 0)) tot = tot + shape[i-1][j-1] * kernel[0][0];
		if (j - 1 >= 0) tot = tot + shape[i][j-1] * kernel[1][0];
		if ((j - 1 >= 0) && (i + 1 <= 8)) tot = tot + shape[i+1][j-1] * kernel[2][0];
		if (i + 1 <= 8) tot = tot + shape[i+1][j] * kernel[2][1];
		if (j + 1 <= 8) tot = tot + shape[i][j+1] * kernel[1][2];
		if ((j + 1 <= 8) && (i - 1 >= 0)) tot = tot + shape[i-1][j+1] * kernel[0][2];
		if ((j+ 1 <= 8) && (i + 1 <= 8)) tot = tot + shape[i+1][j+1] * kernel[2][2];

		if (tot == 3) counter = counter + 1; //only register if all 3 parts of kernel match, instead of doing traditional spactial masking
	}
}

	return counter;
}

void wta(int k0, int k1,int k2, int k3,int k4)
{
//Kernel Intensity Order
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
}