#include<iostream>
#include <chrono>
#include "tensor.h"
#include "vec.h"
// int vectorCol(int* i, int* n, int N) {
//     int col = i[0];
    
//     for(int idx=1; idx<N; idx++) {
//         int t = 1;
//         for(int j=0; j<=idx-1; j++) {
//             t*=n[j];
//         }

//         // printf("i[%i] = %i\n", idx, i[idx]);
//         // printf("c = %i\n", col);
//         // printf("t = %i\n", t);


//         t *= i[idx] - 1;
//         col+=t;
//     }

//     return col;
// }

// void vectorColToIdx(int* i, int* n, int N, int c) {
//     for(int idx=N-1; idx>=1; idx--) {

//         int t = 1;

//         for(int j=idx-1; j>=0; j--) {
//             t*=n[j];
//         }

//         // printf("t = %i\n", t);
//         // printf("c = %i\n", c%t);
//         // printf("i[%i] = %i\n", idx, 1 + c/t);
        
//         i[idx] = 1 + c/t;
//         c = c % t;
//     }
//     i[0] = c;

// }

void print_vec(int* i, int* n, int N) {
    int c = unfoldVecY(i, n, N);
    printf("A[%i] = a", c);
    for(int j=0; j<N; j++)
        printf("%i", i[j]);
    printf("\n");

    printf("a");
    int idx[N];
    foldVecY(idx, n, N, c);
    for(int j=0; j<N; j++)
        printf("%i", idx[j]);
    printf(" = A[%i]\n", c);
}

int matrixCol(int* i, int* I, int n, int N) {
    int col = 0;

    for(int k=1; k<=N; k++) {
        if(k==n) continue;
        
        int t = 1;
        for(int m=1; m<=k-1; m++) {
            if(m == n) continue;
            t*=I[m-1];
        }

        // printf("t = %i\n", t);
        t *= i[k-1] - 1;
        // printf("t *= %i\n", i[k-1] - 1);
        col += t;
        // printf("col = %i\n", col);
    }

    col+=1;
    return col;
}

int matrixLine(int* i, int* I, int n, int N) {
    return i[n-1];
}


void fold(int *i, int *I, int n, int N, int l, int c) {
    i[n-1] = l;
    c -= 1;
    
    for(int k=N; k>=1; k--) {
        if(k == n) continue;

        int t = 1;
        
        for(int m=k-1; m>=1; m--) {
            if(m == n) continue;
            t*=I[m-1];
        }
    
        i[k-1] = 1 + c/t;
        c = c % t;

    }
}

void print_unfold(int* i, int* I, int n, int N) {
    // unfold
    int l =  unfoldMatY(i, I, n, N);
    int c =  unfoldMatX(i, I, n, N);
    printf("A[%i,%i] = a", l, c);
    for(int idx=0; idx<N; idx++)
        printf("%i", i[idx]);
    printf("\n");

    // fold
    int a[N];
    foldMatXY(a, I, n, N, l, c);
    printf("a");
    for(int idx=0; idx<N; idx++)
        printf("%i", a[idx]);
    printf(" = A[%i,%i]\n", l, c);
}


#define SIZE 16000



// void t(int** P, int* I, int* R, int N, int n = 0, int j = 0) {
//     if(j == N - 1) {
//         for(int i=0; i<N; i++)
//             P[i][n] = R[i];
//         return;
//     } 

//     for(int i=0; i<I[n]; i++) {
//         R[0] = i+1;
    
//         for(int i=0; i<I[n]; i++) {
//             R[1] = i+1;
//             for(int i=0; i<I[n]; i++) {
//                 R[2] = i+1;
//                 t(P, I, R, N, n, j+1);
//                 n++;
//             }
//             n++;
//         }

//         n++;
//     }

// }

int main() {

    int I[3]  = {4,2,2}; 
    // int is[3][16] = {
    //     {1,1,2,3,2,1,3,2,1,1,2,3,2,1,3,2},
    //     {1,1,2,3,2,1,3,2,1,1,2,3,2,1,3,2},
    //     {1,1,2,3,2,1,3,2,1,1,2,3,2,1,3,2},
    // };

    int* is = allocate_indices_array(I, 3);

    int R[3];
    get_indices(is, I, R, 3);
    int S = I[0]*I[1]*I[2];
    for(int i=0; i<I[0]*I[1]*I[2]; i++)
        printf("(%i, %i, %i)", is[0*S + i], is[1*S + i], is[2*S + i]);
    printf("\n");

    int col[I[0]*I[1]*I[2]] = {0};
    int lin[I[0]*I[1]*I[2]] = {0};

    unfold_mat_x_multiple(is, I, 1, 3, I[0]*I[1]*I[2], col);
    unfold_mat_y_multiple(is, I, 1, 3, I[0]*I[1]*I[2], lin);

    for(int i=0; i<16; i++)
        printf("  (%i, %i) ", lin[i], col[i]);
    printf("\n");

    float* a = new float[SIZE]();
    float* b = new float[SIZE]();
    float* c = new float[SIZE]();
    float* d = new float[SIZE]();

    for(int i=1; i<=(SIZE); i++) a[i-1] = (float)i;
    for(int i=1; i<=(SIZE); i++) b[i-1] = (float)i;
    for(int i=1; i<=(SIZE); i++) c[i-1] = (float)i;
    for(int i=1; i<=(SIZE); i++) d[i-1] = (float)i;

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    float dot = dot_f32_array(SIZE, a, b);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    // for(int i=0; i<SIZE; i++)
    //     printf("%f\n", c[i]);

    printf("%f\n", dot);
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << "[ms]" << std::endl;
    // printf("%f\n", k0);

    // int I[3]  = {4,3,2}; // dimensions 

    // int i0[3] = {1,1,1}; // index0
    // int i1[3] = {1,1,2}; // index1
    // int i2[3] = {1,2,2}; // index2
    // int i3[3] = {2,2,2}; // index3

    // int a[3] = {1,2,1};
    // int b[3] = {2,3,1};
    // int c[3] = {3,1,2};

    // int d[3] = {3,2,1};
    // int e[3] = {1,3,2};
    // int f[3] = {2,1,2};

    // print_unfold(a, I, 1, 3);
    // print_unfold(b, I, 1, 3);
    // print_unfold(c, I, 1, 3);
    // print_unfold(d, I, 1, 3);
    // print_unfold(e, I, 1, 3);
    // print_unfold(f, I, 1, 3);

    // int R[4]  = {4,3,2,3};  

    // int t[4] = {3,2,1,2};
    // int g[4] = {2,2,1,3};
    // int h[4] = {1,3,2,2};

    // print_unfold(t, R, 1, 4);
    // print_unfold(g, R, 1, 4);
    // print_unfold(h, R, 1, 4);

    // print_vec(a, I, 3);
    // print_vec(b, I, 3);
    // print_vec(c, I, 3);
    // print_vec(d, I, 3);
    // print_vec(e, I, 3);
    // print_vec(f, I, 3);
    // print_vec(t, R, 4);
    // print_vec(g, R, 4);
    // print_vec(h, R, 4);
    // print_vec(b, I, 3);
    // print_vec(c, I, 3);
    // print_unfold(i0, I, 2, 3);

    return 0;
}