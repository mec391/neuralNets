/*
Matthew Capuano EE 556 -- TSP

	0 philedephia
	1 pittsburgh
	2 allentown
	3 erie
	4 reading
	5 upper darby
	6 scranton
	7 bethlehem
	8 lancaster
	9 lower marion

Max cost = max possible distance between 2 farthest cities ~ 480km
Cost:
 A: sum any row = 0 	COST
 B: sum any column = 0	COST
 C: sum any row >= 2	COST
 D: sum any col >= 2	COST
 E: distance traveled	max around 480
*/

//problem -- Either modify code to remove a city or modify code to end in a different city

#include <iostream>
#include <stdio.h>
#include <cmath>
#include <stdlib.h>
#include <time.h>
using namespace std;

void initialize_matrix(double matrix[][10]);
void print_matrix(double matrix[][10]);
void calc_penalty(double matrix[][10], double *error_total); 
void flip_calc_decide(double matrix[][10], double error_total, double *reject_counter);

int main()
{
srand (time(NULL));
double matrix[10][10];
double error_total = 0;
double reject_counter = 0;

initialize_matrix(matrix);
while (reject_counter < 25) //21
{
error_total = 0;
calc_penalty(matrix, &error_total); 
flip_calc_decide(matrix, error_total, &reject_counter);
print_matrix(matrix);
cout <<"\nConsecutive Rejects: "; cout <<reject_counter;
}
cout << "\nOptimization Complete, Final Path:";
print_matrix(matrix);

	return 0;
}

void initialize_matrix(double matrix[][10])
{
	matrix[0][0] = 1; //start and end in phil.
	matrix[0][9] = 1;

for (int i = 1; i < 10; i++)
{
	matrix[i][0] = 0;
	matrix[i][9] = 0;
}
for (int i = 1; i <9; i++)
{
	matrix[0][i] = 0;
}  

for (int i = 1; i < 10; i++)
{
	for (int j = 1; j <9; j++)
	{
		matrix[i][j] = rand() % 2 + 0;
	}
}
	return;
}


void print_matrix(double matrix[][10])
{
	cout << "\n0 philedephia "; for (int i = 0; i<10; i++){cout << matrix[0][i]; cout << " ";}
	cout << "\n1 pittsburgh  "; for (int i = 0; i<10; i++){cout << matrix[1][i]; cout <<" ";}
	cout << "\n2 allentown   "; for (int i = 0; i<10; i++){cout << matrix[2][i]; cout <<" ";}
	cout << "\n3 erie        "; for (int i = 0; i<10; i++){cout <<matrix[3][i]; cout <<" ";}
	cout << "\n4 reading     "; for (int i = 0; i<10; i++){cout << matrix[4][i]; cout <<" ";}
	cout << "\n5 upper darby "; for (int i = 0; i<10; i++){cout <<matrix[5][i]; cout <<" ";}
	cout << "\n6 scranton    "; for (int i = 0; i<10; i++){cout <<matrix[6][i]; cout <<" ";}
	cout << "\n7 bethlehem   "; for (int i = 0; i<10; i++){cout <<matrix[7][i]; cout <<" ";}
	cout << "\n8 lancaster   "; for (int  i= 0; i<10; i++){cout <<matrix[8][i]; cout <<" ";}
	cout << "\n9 lower marion"; for (int i = 0; i<10; i++){cout <<matrix[9][i]; cout <<" ";}
	cout <<" \n              "; for (int i = 0; i<10; i++){cout<<i; cout <<" ";}
	return;
}

void calc_penalty(double matrix[][10], double *error_total)
{
double distances[10][10] =
{
	{0.00,	414.28,	76.86,	478.78,	77.58,	8.87,	167.47,	76.95,	87.03,	12.87},
	{414.28,	0.00,	383.25,	188.12,	345.17,	406.99,	380.05,	391.83,	327.30,	403.14},
	{76.86,	383.25,	0.00,	421.19,	48.68,	78.24,	91.22,	8.92,	86.17,	66.23},
	{478.78,	188.12,	421.19,	0.00,	401.24,	474.06,	375.80,	427.82,	401.40,	466.00},
	{77.58,	345.17,	48.68,	401.24,	0.00,	73.40,	121.55,	57.13,	38.62,	64.77},
	{8.87,	406.99,	78.24,	474.06,	73.40,	0.00,	169.39,	79.32,	79.70,	12.04},
	{167.47,	380.05,	91.22,	375.80,	121.55,	169.39,	0.00,	90.56,	157.77,	157.36},
	{76.95,	391.83,	8.92,	427.82,	57.13,	79.32,	90.56,	0.00,	94.11,	67.30},
	{87.03,	327.30,	86.17,	401.40,	38.62,	79.70,	157.77,	94.11,	0.00,	76.36},
	{12.87,	403.14,	66.23,	466.00,	64.77,	12.04,	157.36,	67.30,	76.36,	0.00}
};
double A = 0;
double B = 0;
double C = 0;
double D = 0;
double E = 0;
double COST = 400;
//calc penalty A and C
double A_tot = 0;
for (int i = 1; i < 10; i++)
{
	for (int j = 0; j < 10; j++)
	{
		A_tot = A_tot + matrix[i][j];
	}
	if (A_tot == 0){
		A = A + COST;
	}
	else if(A_tot >= 2){
		C = C + COST * A_tot; //4/20update
	}
	A_tot = 0;
}

//calc penalty B and D
double B_tot = 0;
for(int i = 0; i < 10; i++)
{
	for (int j = 0; j < 10; j++)
	{
		B_tot = B_tot + matrix[j][i];
	}
	if(B_tot == 0){
		B = B + COST;
	}
	else if(B_tot >= 2){
		D = D + COST * B_tot; //4/20update
	}
	B_tot = 0;
}

//calc penalty E
int cntr = 0; 
//find # of 1s, create array, input the locations into that array
for (int i = 0; i < 10; i++)
{
	for(int j = 0; j < 10; j++)
	{
		if(matrix[j][i] == 1){
			cntr = cntr + 1;
		}
	}
}
int locations[150];
int cntr1 = 0;
for (int i = 0; i < 10; i++)
{
	for (int j = 0; j < 10; j++)
	{
		if(matrix[j][i] == 1){
			locations[cntr1] = j;
			cntr1 = cntr1 + 1;
		}
	}
}

//now have an array with city locations that is properly sequential
//group and find distances

E = distances[locations[0]][locations[1]];
for (int i =2; i <cntr; i++)
{
	E = E + distances[locations[i-1]][locations[i]];
}


//calc error
*error_total = A + B + C + D + E;

cout <<"\n \n "; cout << "Error total: "; cout << *error_total; cout <<"\n";
cout <<"Skip City = "; cout << A; cout<< " Skip Day = "; cout << B; cout <<" Repeat City = "; cout << C;cout <<" Mult City in 1 Day = "; cout <<D; cout <<" Total Distance = "; cout <<E;
	return;
}

void flip_calc_decide(double matrix[][10], double error_total, double *reject_counter)
{
int row = 0;
int col = 0;

//perform random flip
row = rand() % 9 + 1;
col = rand() % 8 + 1;


if (matrix[row][col] == 1)
{
	matrix[row][col] = 0;
}
else
{
	matrix[row][col] = 1;
}

//recalc error
double new_error = 0;
calc_penalty(matrix, &new_error);

//decide whether to keep flip
double A = 0;
double temp = 1;
A = 1 / (1 + exp(-1 * (error_total - new_error)/temp));
temp = temp * 1.1;//temp = exp(temp);

double random_decimal[10] = {0, .1, .2, .3, .4, .5, .6, .7, .8, .9};
int rand_pick = rand() % 10 + 0;
if (random_decimal[rand_pick] > A) //reject flip
{
	*reject_counter = *reject_counter + 1;
	if(matrix[row][col] == 1)
	{
		matrix[row][col] = 0;
	}
	else
	{
		matrix[row][col] = 1;
	}
}
else
{
	*reject_counter = 0;
}

return;
}