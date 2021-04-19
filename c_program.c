#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    
    //This C program is an implementation of level 2 BLAS functionality, which is xGEMV (generalized matrix-vector multiplication).
    //So, we will compute: alpha * A * B + beta * C, such as alpha and beta are two real numbers, A is a matrix and B and C are two vectors.
    //The constraints on dimensions are: A(n,m) B(m,1) C(n,1).
    //PS: A, B and C must be the same as the ones in the Halide program.
    
    //First of all we initialize A, B and C. 
    int A[6][4] = {
        {0, 1, 2, 3},
        {4, 5, 6, 7},
        {8, 9, 10, 11},
        {12, 13, 14, 15},
        {16, 17, 18, 19},
        {20, 21, 22, 23}
    };

    int B[4][1] = {
        {2},
        {4},
        {8},
        {16}
    };

    int C[6][1] = {
        {10},
        {20},
        {30},
        {40},
        {50},
        {60}
    };
    
    //Then, we initialize alpha and beta (two real numbers).
    int alpha = 5, beta = 7;

    //Openning the Halid result file
    FILE *f;
    if ((f = fopen("./result/result.txt", "r")) == NULL)
    {
        printf("Error when trying to open the Halid result file !\n");
        exit(1);
    }

    //Calucating dimensions
    int height_A = sizeof(A) / sizeof(A[0]);
    int width_A = sizeof(A[0]) / sizeof(int);
    int height_B = sizeof(B) / sizeof(B[0]);
    int width_B = sizeof(B[0]) / sizeof(int);
    int height_C = sizeof(C) / sizeof(C[0]);
    int width_C = sizeof(C[0]) / sizeof(int);
    
    //Checking dimensions coherence
    if (!((width_B == 1) && (width_A == height_B) && (height_A == height_C) && (width_B == width_C))) {
        printf("Matrices dimensions must be: A(n,m) B(m,1) C(n,1)\n");
        exit(1);
    } 
     
    //Declaration of some variables to be used 
    char halid_result_string[255];
    int c_result, halid_result;
    int correct = 1;

    //check the dimension of the vector contained in the file "result.txt" 
    if (!(height_A == atoi(fgets(halid_result_string, 255, f)))) {
        printf("Incorrect vector dimension in the file './result/result.txt'\n");
        exit(1);
    }

    //Calculation of the generalized matrix-vector multiplication and checking the results with those of Halid program
    printf("Start of the checking process...\n");
    for (int i = 0; i < height_A; i++)
    {
        c_result = 0;
        for (int j = 0; j < width_A; j++) c_result += A[i][j] * B[j][0];
        c_result = alpha * c_result + beta * C[i][0];
        fgets(halid_result_string, 255, f); //Read a result from the Halid result file, in the string "halid_result_string"
        halid_result = atoi(halid_result_string); //Convert the string "halid_result_string" to int in the variable "halid_result" 
        if (c_result != halid_result) //Checking the equality of the two results "c_result" and "halid_result"
        {
                printf("The line %d of the result vector should be %d not %d\n", i+1, c_result, halid_result);
                correct = 0;
        }
    }
    
    //Print the result of the checking process
    if (correct) printf("xGEVM function implemented in Halid works correctly.\n");
    else printf("There are some problems in the Halid program or the test matrices are not the same in the two programs !\n");
    fclose(f);
    return 0;
}
