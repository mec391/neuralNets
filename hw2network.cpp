//Matthew Capuano
//EE 556 -- Simple Error Based Network for Grade Prediction

//Input Features:  (Each value normalized)  [homework total, exams total, # of missing assignments(remove .1 from 1 for each missing assignment)]

//1 Weight Matrix w/ 5 Cells (Initialized to 0, No bias, Unipolar Step Activation FN with threshold at .8 isntead of 0) routing to a WTA output of ABCDF Grade

//

//Error Type Used: Misclassification error = (#pts where desired != output) / sample size
//Delta Value (Error Value Needed to Stop Training) = .250 >>> 5% Error total

//traing formula Used:  WijNEW = WijOLD + STUDENTi*(desired - output)
//Where training constant alpha  = .01

//Program Sequence:  1 Training Phase(Random sample of 10 students, at least 1 of each grade), No Validation Phase, 1 Testing Phase(All 30 students)


//Notes: for this Application, error based training does not work, threshold at 0 causes oscillations due to having to train around the value 0, which means that negative weights must be used.. this causes problems
//because inputs lose their significance when applied to negative weights ... Example: input of .8 ( strong positive correlation) multipled by weight of -1 now pulls the output further down instead of further up.. this
//is fixed by increasing the threshold from 0 to .8, so that weights get trained more positively and don't dip into negative values as much

#include <iostream>
#include <stdio.h>
#include <cmath>
#include <stdlib.h>



using namespace std;

const int inputs = 3;
const int cells =  5;
const int N = 30;

void train(double win[][5], double student[], double desired[], double *error);
void test(double win[][5], double student[]);



int main()
{   
    double students[N][inputs] = 
    {
    {1.0100,    0.9250,    1.0000},//A1
    {0.9775,   1.0275,    1.0000},   //A2
    {0.9375,    0.4475,    1.0000}, //D3
    {   0.01,    0.1250,         0.01},//F4
    {1.0300,    0.7300,    1.0000}, //B5
    {0.9800,    1.1225,    1.0000},//A6
    {1.0225,    0.8475,    1.0000}, //A7
    {0.9575,    1.1150,    0.9000},//A8
    {0.7700,    0.9850,    0.6000},//B9
    {1.0425,    1.1475,    1.0000},//A10
    {0.0375,    0.1900,         0.01},//F11
    {1.1425,    1.1550,    1.0000},//A12
    {0.6575,    0.8200,    0.5000},//C13
    {0.5950,    0.8900,    0.5000},//C14
    {0.3650,    0.7650,         0.01},//F15
    {0.9625,    0.8975,    1.0000},//A16
    {0.4675,    0.7075,    0.1000},//F17
    {0.7875,    0.7325,    0.6000},//C18
    {1.0200,   1.0125,    1.0000},//A19
    {0.3275,    0.8250,         0.01},//F20
    {0.8725,    0.9525,    0.7000},//A21
    {0.5850,    0.7450,    0.4000},//D22
    {0.9575,   1.0225,   1.0000},//A23
    {1.0175,    0.8050,    1.0000},//A24
    {0.4075,    0.8925,         0.01},//D25
    {0.6725,    0.9600,    0.3000},//B26
    {0.1800,    0.1625,         0.01},//F27
    {1.0550,    1.1625,    1.0000},//A28
    {1.0450,    1.1775,    1.0000},//A29
    {1.0050,    1.1375,    1.0000}  //A30
    };    
    //Random students for training:1,3, 11, 5, 13, 15, 30, 26, 14, 22
    
    char grades[31] = {"AADFBAAABAFACCFAFCAFADAADBFAAA"};
       
    double weights [inputs][cells];
    for (int i = 0; i < cells; i++)
        {
         for (int j =0 ; j < inputs; j++)
            weights[j][i] = 0.30;
        }
    
    
    
    
    //execute training sequence
int iteration_counter = 0;
double error_total = 50;    
double error_tracker[200];
 while (error_total > 2 && iteration_counter < 200)
 {                      
    double error_sum = 0;
    double error = 0;
    
    double student_train0[3] = {1.0100, .9259, 1.0000}; //A1
    double desired0[5] = {1, 1, 1, 1, 1};
    train(weights, student_train0, desired0, &error);
    error_sum = error_sum + error;
    error = 0;
    
    double student_train1[3] = {0.9375,    0.4475,    1.0000}; //D3
    double desired1[5] = {0, 0, 0, 1, 1};
    train(weights, student_train1, desired1, &error);
    error_sum = error_sum + error;
    error = 0;
    
    double student_train2[3] = {0.0375,    0.1900,         0}; //F11
    double desired2[5] = {0, 0, 0, 0, 1};
    train(weights, student_train2, desired2, &error);
    error_sum = error_sum + error;
    error = 0;
    
    double student_train3[3] = {1.0300,    0.7300,    1.0000}; //B5
    double desired3[5] = {0, 1, 1, 1, 1};
    train(weights, student_train3, desired3, &error);
    error_sum = error_sum + error;
    error = 0;
    
    double student_train4[3] = {0.6575,    0.8200,    0.5000}; //C13
    double desired4[5] = {0, 0, 1, 1, 1};
    train(weights, student_train4, desired4, &error);
    error_sum = error_sum + error;
    error = 0;
    
    double student_train5[3] = {0.3650,    0.7650,         0}; //F15
    double desired5[5] = {0, 0, 0, 0, 1};
    train(weights, student_train5, desired5, &error);
    error_sum = error_sum + error;
    error = 0;
    
    double student_train6[3] = {1.0050,    1.1375,    1.0000}; //A30
    double desired6[5] = {1,1, 1, 1, 1};
    train(weights, student_train6, desired6, &error);
    error_sum = error_sum + error;
    error = 0;
    
    double student_train7[3] = {0.6725,    0.9600,    0.3000}; //B26
    double desired7[5] = {0, 1, 1, 1, 1};
    train(weights, student_train7, desired7, &error);
    error_sum = error_sum + error;
    error = 0;
    
    double student_train8[3] = {0.5950,    0.8900,    0.5000}; //C14
    double desired8[5] = {0, 0, 1, 1, 1};
    train(weights, student_train8, desired8, &error);
    error_sum = error_sum + error;
    error = 0;
    
    double student_train9[3] = {0.5850,    0.7450,    0.4000}; //D22
    double desired9[5] = {0, 0,0, 1, 1};
    train(weights, student_train9, desired9, &error);
    error_sum = error_sum + error;
    error = 0;
    
    error_total = error_sum;//error_total = error_sum / 10;
    cout << "Error_Total: ";
    cout << error_total;
    cout <<"\n";
    error_tracker[iteration_counter] = error_total;
    iteration_counter = iteration_counter + 1;
    
    
}
    
    cout << "Training Is Complete.  Number of iterations through training set: ";
    cout << iteration_counter;
    cout << "\n";
    
    
    //execute testing sequence
    double student_train[3];
    for(int i = 0; i < 30; i++)
    {
        cout << "Student ";
        cout << i;
        cout << ": ";
        cout << "Actual Grade = ";
        cout << grades[i];
        cout << ".   ";
        for (int j = 0; j < 3; j++)
        {
        student_train[j] = students[i][j];
        }
        test(weights, student_train);        
    }


    for (int i = 0; i <200; i++)
    {
     cout << error_tracker[i];
     cout << "\n";
    }
    
   
 return 0;   
}











//training fn
void train(double win[][cells], double student[], double desired[], double *error)
{
    
    //calculate output vector
    double output[5];
    for (int i = 0; i < 5; i++)
    {
        double sum = 0;
        for (int j = 0; j < 3; j++)
        {
            sum = sum + student[j]*win[j][i];    
        }
        //adding a bias
        //sum = sum + .5;
        if(sum > .8) //CHANGING THRESHOLD TO .5 INSTEAD OF 0, TRYING TO KEEP EVERYTHING POSITIVE
        {
         output[i] = 1;
         }   
        else
        {
         output[i] = 0;
         }
    }
    
    //calculate error
    for (int i = 0; i < 5; i++)
        {
            *error = *error + abs(desired[i] - output[i]);
        }
    
    //reassign weights
    double alpha = .01;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            //2/17 update
            /*
            if(desired[i] - output[i] == 0)
                {
                    if (output[i] == 1)
                        {
                            win[j][i] = win[j][i] + .01;
                        }
                    else
                        {
                            win[j][i] = win[j][i] -.01;
                        }
                }
                //end 2/17 update
              
                
                else{
                  */
                  //changed to hebian
            win[j][i] = win[j][i] +  student[j] * (desired[i] - output[i]);  
            
        }
    } 
    
    
      for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            std::cout << win[i][j] << ' ';
        }
        std::cout << std::endl;
        
    }
    cout <<"----------\n";
    
    
 return;   
}






//testing fn
void test(double win[][cells], double student[])
{
    //calculate output vector
    double output[5];
    for (int i = 0; i < 5; i++)
    {
        double sum = 0;
        for (int j = 0; j < 3; j++)
        {
            sum = sum + student[j]*win[j][i];    
        }
        //adding a bias
       //sum = sum + .5;
        if(sum > .8)
        {
         output[i] = 1;
         }   
        else
        {
         output[i] = 0;
         }
    }
    
    cout << "NN Grade = ";
    
    //calculate WTA
    if(output[0] == 1)
    {
        cout << "A\n";
    }
    else if(output[1] == 1)
    {
        cout <<"B\n";
    }
    else if(output[2] == 1)
    {
        cout <<"C\n";   
    }
    else if(output[3] == 1)
    {
        cout <<"D\n";   
    }
    else
    {
        cout <<"F\n";
    }
    
    
 return;   
}

