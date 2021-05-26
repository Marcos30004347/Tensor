#include<iostream>
#include <chrono>
#include "tensor.h"

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



int main() {
    int I[3]  = {4,3,2}; // dimensions 

    int i0[3] = {1,1,1}; // index0
    int i1[3] = {1,1,2}; // index1
    int i2[3] = {1,2,2}; // index2
    int i3[3] = {2,2,2}; // index3

    int a[3] = {1,2,1};
    int b[3] = {2,3,1};
    int c[3] = {3,1,2};

    int d[3] = {3,2,1};
    int e[3] = {1,3,2};
    int f[3] = {2,1,2};

    print_unfold(a, I, 1, 3);
    print_unfold(b, I, 1, 3);
    print_unfold(c, I, 1, 3);
    print_unfold(d, I, 1, 3);
    print_unfold(e, I, 1, 3);
    print_unfold(f, I, 1, 3);

    int R[4]  = {4,3,2,3};  

    int t[4] = {3,2,1,2};
    int g[4] = {2,2,1,3};
    int h[4] = {1,3,2,2};

    print_unfold(t, R, 1, 4);
    print_unfold(g, R, 1, 4);
    print_unfold(h, R, 1, 4);

    print_vec(a, I, 3);
    print_vec(b, I, 3);
    print_vec(c, I, 3);
    print_vec(d, I, 3);
    print_vec(e, I, 3);
    print_vec(f, I, 3);
    print_vec(t, R, 4);
    print_vec(g, R, 4);
    print_vec(h, R, 4);
    // print_vec(b, I, 3);
    // print_vec(c, I, 3);
    // std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    // print_unfold(i0, I, 2, 3);
    // std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    // std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;

    return 0;
}