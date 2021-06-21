#include<iostream>
#include <chrono>
//#include "vec.h"
#include "tensor/tensor.h"

int main() {
    setup_core_lib();
    
    int I[3]  = { 4, 2, 2 };

    int* is = allocate_indices_array(I, 3);

    int R[3];
    get_indices(is, I, R, 3);
    int S = I[0]*I[1]*I[2];
    printf("Indices:\n");

    for(int i=0; i<I[0]*I[1]*I[2]; i++)
       printf("(%i, %i, %i)", is[0*S + i], is[1*S + i], is[2*S + i]);
    printf("\n");

    int col[16] = {0};
    int lin[16] = {0};

    unfold_mat_x_multiple(is, I, 1, 3, 16, col);
    unfold_mat_y_multiple(is, I, 1, 3, 16, lin);

    printf("\nFold:\n");

    for(int i=0; i<16; i++)
       printf("  (%i, %i) ", lin[i], col[i]);
    printf("\n");

    fold_mat_xy_multiple(is, I, 1, 3, 16, lin, col);

    printf("\nUnfold:\n");

    for(int i=0; i<I[0]*I[1]*I[2]; i++)
       printf("(%i, %i, %i)", is[0*S + i], is[1*S + i], is[2*S + i]);
    printf("\n");

    return 0;
}