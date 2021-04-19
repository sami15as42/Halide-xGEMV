//Halide header file
#include "Halide.h"

//For printf function
#include <stdio.h>

//For the use of a results backup file
#include <iostream>
#include <fstream>

//To avoid writing each time the namespace
using namespace std;
using namespace Halide;

int main(int argc, char **argv)
{

    //This Halide program is an implementation of level 2 BLAS functionality, which is xGEMV (generalized matrix-vector multiplication).
    //So, we will compute: alpha * A * B + beta * C, such as alpha and beta are two real numbers, A is a matrix and B and C are two vectors.
    //The constraints on dimensions are: A(n,m) B(m,1) C(n,1).
    
    //First of all we initialize A, B and C. 
    int a[6][4] = {
        {0, 1, 2, 3},
        {4, 5, 6, 7},
        {8, 9, 10, 11},
        {12, 13, 14, 15},
        {16, 17, 18, 19},
        {20, 21, 22, 23}
    };

    int b[4][1] = {
        {2},
        {4},
        {8},
        {16}
    };

    int c[6][1] = {
        {10},
        {20},
        {30},
        {40},
        {50},
        {60}
    };

    //Then, we initialize alpha and beta (two real numbers).
    int alpha = 5, beta = 7;

    //Declaring a Halide function
    //It's a pure function that defines what value each element of a matrix or a vector should have.
    Func gemv;

    //Declaring two Var objects to use as variables in the definition of our Func gemv
    Var x,y;

    // Declaring 3 buffers to store the three matrices
    Buffer<int> A(a);
    Buffer<int> B(b);
    Buffer<int> C(c);

    //Checking dimensions coherence
    if (!((B.width() == 1) && (A.width() == B.height()) && (A.height() == C.height()) && (B.width() == C.width()))){
        printf("Matrices dimensions must be: A(n,m) B(m,1) C(n,1)\n");
        exit(1);
    }

    //Declaring a reduction domain
    RDom j(0, A.width());

    //Now we'll add a definition for our Func object. Each element (x,y) of our vector result receives the value: alpha * sum(A(j, y) * B(x,j)) + beta * C(x,y).  
    gemv(x,y) = alpha * sum(A(j, y) * B(x,j)) + beta * C(x,y);

    //Realizing the function
    Buffer<int> res_vector = gemv.realize(B.width(),A.height());
    printf("Vector calculation with Halid program completed successfully !\n");

    //Saving the rasult vector into a file so the C program will be able to check it
    printf("Saving our result vector to ./result/result.txt...\n");
    ofstream output_file("./result/result.txt");
    output_file << res_vector.height() << "\n";
    for (int k = 0; k < res_vector.height(); k++)
    {
    	output_file << res_vector(k) << "\n";
    }
    output_file.close();
    printf("Saving process completed successfully !\n");

    return 0;
}
