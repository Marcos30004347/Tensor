#include <iostream>
#include <string.h>

#include "core/core.h"

int unfoldVecY(int* i, int* n, int N) {
    int col = i[0];

    int* M = new int[N]{1};

    for(int j=1; j<N; j++) 
        M[j] = M[j-1]*n[j-1];

    for(int idx=1; idx<N; idx++) 
        col+= M[idx]*(i[idx] - 1);

    delete[] M;

    return col;

}

void foldVecY(int* i, int* n, int N, int c) {
    int* M = new int[N]{1};

    for(int j=1; j<N; j++) 
        M[j] = M[j-1]*n[j-1];
  
    for(int idx=N-1; idx>=1; idx--) {
        i[idx] = 1 + c/M[idx];
        c = c % M[idx];
    }

    delete[] M;

    i[0] = c;
}


int unfoldMatX(int* i, int* I, int n, int N) {
    int col = 0;

    int* M = new int[N]{1};

    for(int m=1; m<=N; m++) {
        if(m == n) {
            M[m] = M[m-1];
        } else {
            M[m] = M[m-1] * I[m-1];
        }
    }

    for(int k=1; k<=N; k++) {
        if(k==n) continue;
        col += M[k-1]*(i[k-1] - 1);
    }

    col+=1;

    delete[] M;

    return col;
}

int unfoldMatY(int* i, int* I, int n, int N) {
    return i[n-1];
}

void foldMatXY(int *i, int *I, int n, int N, int l, int c) {
    i[n-1] = l;
    c -= 1;
    int* M = new int[N]{1};
            
    for(int m=1; m < N; m++)
        if(m == n) M[m] = M[m-1];
        else M[m] = M[m-1] * I[m-1];

    for(int k=N; k>=1; k--) {
        if(k != n) {
            i[k-1] = 1 + c/M[k-1];
            c = c % M[k-1];
        }
    }

    delete[] M;
}

void get_indices_rec(int* P, int* I, int* R, int N, int S, int* n, int j) {
    if(j == N) {
        int p = *n;
        for(int i=0; i<N; i++)
            P[(i*S)+p] = R[i];
        
        *n = p+1;
        return;
    } 

    for(int i=0; i<I[j]; i++) {
        R[j] = i;
        get_indices_rec(P, I, R, N, S, n, j+1);
    }
}

void get_indices(int* P, int* I, int* R, int N) {
    int n = 0;

    int S = I[0];
    for(int i = 1; i<N; i++)
        S*=I[i];

    get_indices_rec(P, I, R, N, S, &n, 0);
}

int* allocate_indices_array(int* I, int N) {
    int S = I[0];
    
    for(int i = 1; i<N; i++)
        S*=I[i];

    int* idx = new int[N*S];

    return idx;
}

void fold_mat_xy_multiple(int *i, int *I, int n, int N, int size, int* l, int* c) {
    int* M = new int[N]{1};
    int* T = new int[size]{0};
    int* C = new int[size];

    memcpy(&i[(n-1)*size], l, size*sizeof(i32));// add_i32array_i32(size, l, 0, &i[(n-1)*size]);
    memcpy(C, c, size*sizeof(i32));

    for(int m=1; m < N; m++)
        if(m == n) M[m] = M[m-1];
        else M[m] = M[m-1] * I[m-1];

    for(int k=N; k>=1; k--) {
        if(k != n) {
            div_i32array_i32(size, C, M[k-1], &i[(k-1)*size]);
            mul_i32array_i32(size, &i[(k-1)*size], M[k-1], T);
            sub_i32array(size, C, T, C);
        }
    }

    delete[] M;
    delete[] T;
    delete[] C;
}

void unfold_mat_x_multiple(int* i, int* I, int n, int N, int size, int* col) {
   int* M = new int[N]{1};
   int* A = new int[size];
   
   for(int m=1; m < N; m++)
       if(m == n) M[m] = M[m-1];
       else M[m] = M[m-1] * I[m-1];

   for(int k=1; k<=N; k++) {
       if(k==n) continue;
        memcpy(A, &i[(k-1)*size], size*sizeof(i32)); // sub_i32array_i32(size, &i[(k-1)*size], 0, A);
        mul_i32array_i32(size, A, M[k-1], A);
        add_i32array(size, col, A, col);
   }

   delete[] A;
   delete[] M;
}

void unfold_mat_y_multiple(int* i, int* I, int n, int N, int size, int* lins) {
   memcpy(lins, &i[(n-1)*size], size*sizeof(i32));// sub_i32array_i32(size, &i[(n-1)*size], 0, lins);
}


int isOddPermutations(int* a, int n) {
    int ans=0;
    int* tr = new int[n]{0};

    for(int i=0;i<n;i++) {
        for(int j=a[i];j;j-=j&-j)
            ans+=tr[j - 1];
        for(int j=a[i];j<n;j+=j&-j)
            tr[j - 1]++;
    }

    delete[] tr;

    return (n*(n-1)/2-ans)%2;
}

int e(int *a, int N) {
    for(int i=0; i<N; i++) {
        for(int j=i+1; j<N; j++) {
            if(a[i] == a[j])
                return 0;
        }
    }

    if(isOddPermutations(a, N))
        return -1;

    return 1;
}