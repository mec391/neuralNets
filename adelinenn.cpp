//Adeline Mk1 Neural Net (broken)
#include <iostream>
#include <stdio.h>
using namespace std;


void assignweights(float *wa, float *wb, float *xa, float *yinput, float *za, float  *zb, float *zina, float *zinb);
void trainweights(float *wa, float aa, float zina,float zinb, float da, float *x); 
void trainweights2(float *wa, float aa, float zina,float zinb, float da, float *x); 


int main() {

    //input xbars
    float x1 [2] = {-1, -1};
    float x2 [2] = {-1, 1};
    float x3 [2] = {1, -1};
    float x4 [2] = {1, 1};

    //desired output
    float d1 = -1;
    float d2 = 1;
    float d3 = 1;
    float d4 = -1;

    //init weights
    float w1 [3] = {.05, .2, .3};
    float w2 [3] = {.1, .2, .15};

    //alpha and output
    float a = .5;
    float yin = 0;
    
    //z values
    float z1 = 0;
    float z2 = 0;
    float zin1 = 0;
    float zin2 = 0;
    

    int state = 0;
    int counter = 4;

//initial weights
cout <<"Initial Weights: " <<endl;
cout << "weight1 = "<<endl <<w1[0] <<endl <<w1[1] <<endl <<w1[2] <<endl;
cout << "weight2 = "<<endl <<w2[0] <<endl <<w2[1] <<endl <<w2[2]  <<endl;
cout << "..........." <<endl;


//cycling
while (counter != 0)
{

//check x1   
if (state == 0)
{
assignweights(w1, w2, x1, &yin, &z1, &z2, &zin1, &zin2);
cout <<"Checking X1...." <<endl;
cout <<"zin1 = " <<zin1 <<endl;
cout <<"zin2 = " <<zin2 <<endl;
cout <<"z1 = " <<z1 <<endl;
cout <<"z2 = " <<z2 <<endl;
cout <<"y = "  <<yin <<endl;
if(yin != d1)
{

    if (z1 != d1)
    {
        trainweights(w1, a, zin1, zin2, d1, x1 );
    }
    if (z2 != d1)
    {
        trainweights2(w2, a, zin1, zin2, d1, x1);
    }
    cout <<"New weights: " <<endl;
    cout << "weight1 = "<<endl <<w1[0] <<endl <<w1[1] <<endl <<w1[2] <<endl;
    cout << "weight2 = "<<endl <<w2[0] <<endl <<w2[1] <<endl <<w2[2]  <<endl;
    cout << "..........." <<endl; 
    state = 1;
    counter = 4;
}
else
{
state = 1;
counter = counter - 1;
}
}

//check x2
if(state == 1)
{
    assignweights(w1, w2, x2, &yin, &z1, &z2, &zin1, &zin2);
cout <<"Checking X2...." <<endl;
cout <<"zin1 = " <<zin1 <<endl;
cout <<"zin2 = " <<zin2 <<endl;
cout <<"z1 = " <<z1 <<endl;
cout <<"z2 = " <<z2 <<endl;
cout <<"y = "  <<yin <<endl;

    if(yin != d2)
    {

    if (z1 != d2)
    {
        trainweights(w1, a, zin1, zin2, d2, x2 );
    }
    if (z2 != d2)
    {
        trainweights2(w2, a, zin1, zin2, d2, x2);
    }
    cout <<"New weights: " <<endl;
    cout << "weight1 = "<<endl <<w1[0] <<endl <<w1[1] <<endl <<w1[2] <<endl;
    cout << "weight2 = "<<endl <<w2[0] <<endl <<w2[1] <<endl <<w2[2]  <<endl;
    cout << "..........." <<endl; 
    state = 2;
    counter = 4;
               
            }
    else
    {
        state = 2;
        counter = counter - 1;
    }
}

//check x3
if(state == 2)
{
        assignweights(w1, w2, x3, &yin, &z1, &z2, &zin1, &zin2);
cout <<"Checking X3...." <<endl;
cout <<"zin1 = " <<zin1 <<endl;
cout <<"zin2 = " <<zin2 <<endl;
cout <<"z1 = " <<z1 <<endl;
cout <<"z2 = " <<z2 <<endl;
cout <<"y = "  <<yin <<endl;
    
    if(yin != d3)
    {
    if (z1 != d3)
    {
        trainweights(w1, a, zin1, zin2, d3, x3 );
    }
    if (z2 != d3)
    {
        trainweights2(w2, a, zin1, zin2, d3, x3);
    }
    cout <<"New weights: " <<endl;
    cout << "weight1 = "<<endl <<w1[0] <<endl <<w1[1] <<endl <<w1[2] <<endl;
    cout << "weight2 = "<<endl <<w2[0] <<endl <<w2[1] <<endl <<w2[2]  <<endl;
    cout << "..........." <<endl; 
    state = 3;
    counter = 4;
               
            }
    else
    {
        state = 3;
        counter = counter - 1;
    }
}

//check x4
if (state == 3)
{
           assignweights(w1, w2, x4, &yin, &z1, &z2, &zin1, &zin2);
cout <<"Checking X4...." <<endl;
cout <<"zin1 = " <<zin1 <<endl;
cout <<"zin2 = " <<zin2 <<endl;
cout <<"z1 = " <<z1 <<endl;
cout <<"z2 = " <<z2 <<endl;
cout <<"y = "  <<yin <<endl;
    
    if(yin != d4)
    {

    if (z1 != d4)
    {
        trainweights(w1, a, zin1, zin2, d4, x4 );
    }
    if (z2 != d4)
    {
        trainweights2(w2, a, zin1, zin2, d4, x4);
    }
    cout <<"New weights: " <<endl;
    cout << "weight1 = "<<endl <<w1[0] <<endl <<w1[1] <<endl <<w1[2] <<endl;
    cout << "weight2 = "<<endl <<w2[0] <<endl <<w2[1] <<endl <<w2[2]  <<endl;
    cout << "..........." <<endl; 
    state = 0;
    counter = 4;
    
               
            }
    else
    {
        state = 0;
        counter = counter - 1;
    } 
}
}

//cycling done
    cout << "Training done.." <<endl;
    cout << "weight 1 final: " <<endl << w1[0] <<endl <<w1[1] <<endl <<w1[2]  <<endl;
    cout << "weight 2 final: " <<endl << w2[0] <<endl <<w2[1] <<endl <<w2[2]  <<endl;


    
    return 0;
}






void assignweights(float *wa, float *wb, float *xa, float *yinput, float *za, float  *zb, float *zina, float *zinb)
{
    float va[3] = {0.5, 0.5, 0.5};
    
    *zina = wa[0] * xa[0] + wa[1] * xa[1] + wa[2];
    *zinb = wb[0] * xa[0] + wb[1] * xa[1] + wb[2];
    
    if (*zina > 0)
    {
        *za = 1;
    }
    else 
    {
        *za = -1;
    }
    if (*zinb > 0)
    {
        *zb = 1;
    }
    else
    {
        *zb = -1;
    }
    *yinput = va[0] * *za + va[1] * *zb + va[2];
    if(*yinput > 0 )
    {
        *yinput = 1;
    }
    else{
        *yinput = -1;
    }
    return;
}


void trainweights(float *wa, float aa, float zina,float zinb, float da, float *x)
{
    wa[0] = wa[0] + aa * (da- zina) * x[0];
    wa[1] = wa[1] + aa * (da- zinb) * x[1];
    wa[2] = wa[2] + aa * (da - zina);
    return;
}

void trainweights2(float *wa, float aa, float zina,float zinb, float da, float *x)
{
    wa[0] = wa[0] + aa * (da- zina) * x[0];
    wa[1] = wa[1] + aa * (da- zinb) * x[1];
    wa[2] = wa[2] + aa * (da - zinb);
    return;
}