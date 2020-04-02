//Matthew Capuano
//EE 556 - Backpropogation function approximation of cosine from 0 to 180

#include <iostream>
#include <stdio.h>
#include <cmath>
#include <stdlib.h>
using namespace std;


void run_through_network(double degrees, double w_matrix[][500], double v_matrix[], double *err, double t_value, double *y_out);

int main()
{
///////////initialize inputs and weights
	double counter = 0;
	double err_tot = 0;
	double err = 0;
	double error = 99999;
	double degrees[181]; //scale from 0 to 180
	degrees[0] = 0;

	double w_matrix[2][500]; //500 cells, 2nd row is bias
	double v_matrix[501]; 
	double t_value[181];
	t_value[0] = 1;
	double y_out;

	for (int i = 0; i < 500; i++)
	{
		w_matrix[0][i] = .01; //initialize w weight to .01
		w_matrix[1][i] = .1; //initialize w bias to .1
		v_matrix[i] = .01;  //initialize v weight to .01
	}
	v_matrix[50] = .1; //initialize v bias to .1


//////////run program
	while (error > .15 && counter < 1000)
	{
		run_through_network(degrees[0], w_matrix, v_matrix, &err, t_value[0], &y_out);
		err_tot = err_tot + err;
		for (int i = 1; i < 91; i++) //181 --> 91
	{
		degrees[i] = degrees[i-1] + 1;
		t_value[i] = cos(degrees[i] * 3.1459 / 180);
		run_through_network(degrees[i], w_matrix, v_matrix, &err, t_value[i], &y_out);
		err_tot = err_tot + err;
	}

		error = err_tot;
		err_tot = 0;
		counter = counter + 1;
		cout << "\nCycle #:   "; cout << counter;
		cout << "\nError Total:   "; cout << error;
	}

////////training complete
	cout << "\nTraining Complete\n";
	cout << "Final Output Values:  \n";
	run_through_network(degrees[0], w_matrix, v_matrix, &err, t_value[0], &y_out);
	cout << "Input = "; cout << degrees[0]; cout <<"    Output = "; 
	cout << y_out;
	cout <<"\n";
		for (int i = 1; i < 91; i++) //181 -> 91
	{
		degrees[i] = degrees[i-1] + 1;
		t_value[i] = cos(degrees[i] * 3.1459 / 180);
		run_through_network(degrees[i], w_matrix, v_matrix, &err, t_value[i], &y_out);
		cout << "Input = "; cout << degrees[i]; cout <<"    Output = "; 
		cout << y_out;
		cout << "\n";
	}
return 0;
}


void run_through_network(double degrees, double w_matrix[][500], double v_matrix[], double *err, double t_value, double *y_out)
{
	double one = 1;
	double z_cells[500];
	double y_out1 = 0;

/////////run through network
	for (int i = 0; i < 500; i++)
	{
		z_cells[i] = degrees * w_matrix[0][i] + one * w_matrix[1][i]; 	
		z_cells[i] = -1 + 2 / (1 + exp(-1 * z_cells[i]));//bipolar sigmoid on hidden layer
	}
	for (int i = 0; i < 500; i++)
	{
		y_out1 = y_out1 + z_cells[i] * v_matrix[i];
	}
		y_out1 = y_out1 + v_matrix[501];
		y_out1 = -1 + 2 / (1 + exp(-1 * y_out1));//bipolar sigmoid on output layer

////////calculate error	 
	   *err = abs(y_out1 - t_value) * abs(y_out1 - t_value);
	   *y_out = y_out1;

/////////train network
	  double alpha = .01;
for (int i = 0; i < 500; i++)
	{
		w_matrix[0][i] = w_matrix[0][i] + alpha * (z_cells[i] * (1 - z_cells[i])) * (t_value - y_out1) * y_out1 * (1 - y_out1) * degrees;
		w_matrix[1][i] = w_matrix[1][i] + alpha * z_cells[i] * (1 - z_cells[i]) * (t_value - y_out1) * y_out1 * (1 - y_out1) * v_matrix[i];
		v_matrix[i] = v_matrix[i] + alpha * (t_value - y_out1) * y_out1 * (1 - y_out1) * z_cells[i];
	}
		v_matrix[501] = v_matrix[501] + alpha * (t_value - y_out1) * y_out1 * (1 - y_out1);
	return;
}
