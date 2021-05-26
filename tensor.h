#include <iostream>

int unfoldVecY(int* i, int* n, int N) {
    int col = i[0];
    int M[N] = {1};

    for(int j=1; j<N; j++) 
        M[j] = M[j-1]*n[j-1];

    for(int idx=1; idx<N; idx++) 
        col+= M[idx]*(i[idx] - 1);

    return col;
}

void foldVecY(int* i, int* n, int N, int c) {
    int M[N] = {1};

    for(int j=1; j<N; j++) 
        M[j] = M[j-1]*n[j-1];
  
    for(int idx=N-1; idx>=1; idx--) {
        i[idx] = 1 + c/M[idx];
        c = c % M[idx];
    }

    i[0] = c;
}







int unfoldMatX(int* i, int* I, int n, int N) {
    int col = 0;

    int M[N] = {1};

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
    return col;
}

int unfoldMatY(int* i, int* I, int n, int N) {
    return i[n-1];
}

void foldMatXY(int *i, int *I, int n, int N, int l, int c) {
    i[n-1] = l;
    c -= 1;
    int M[N] = {1};
            
    for(int m=1; m < N; m++)
        if(m == n) M[m] = M[m-1];
        else M[m] = M[m-1] * I[m-1];

    for(int k=N; k>=1; k--) {
        if(k != n) {
            i[k-1] = 1 + c/M[k-1];
            c = c % M[k-1];
        }
    }
}


































int isOddPermutations(int* a, int n) {
    int ans=0;
    int tr[n] = {0};

    for(int i=0;i<n;i++) {
        for(int j=a[i];j;j-=j&-j)
            ans+=tr[j - 1];
        for(int j=a[i];j<n;j+=j&-j)
            tr[j - 1]++;
    }

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