#include "simd.h"
#include <cstdint>
#include <cfloat>
#include <iostream>
#include <cmath>
#include <string.h>



float32 reduce_f32array(int64 size, float32* a) {
    #if defined(AVX)
        __m256 r = _mm256_loadu_ps(a);

        for(int32 i=8; i<size; i+=8)
            r = _mm256_add_ps(r, _mm256_load_ps(&a[i]));

        r = _mm256_hadd_ps(r, r);
        r = _mm256_hadd_ps(r, r);

        float32 arr[8];
        _mm256_storeu_ps(arr, r);
        return arr[3] + arr[4];
    #elif defined(SSE)
        __m128 r = _mm_loadu_ps(a);

        for(int32 i=4; i<size; i+=4) 
            r = _mm_add_ps(r, _mm_load_ps(&a[i]));

        r = _mm_hadd_ps(r, r);
        r = _mm_hadd_ps(r, r);

        float32 arr[4];
        _mm_storeu_ps(arr, r);

        return arr[0];
    #else 
        float32 r = 0;
        for(int32 i=0; i<size; i++) 
            r += a[i];
        return r;
    #endif
}


int32 reduce_i32array(unsigned size, int32* a) {
    #if defined(AVX)
        __m256i r = _mm256_loadu_si256((__m256i*) &a[0]);

        for(int32 i=8; i<size; i+=8)
            r = _mm256_add_epi32(r, _mm256_loadu_si256((__m256i*) &a[i]));

        r = _mm256_hadd_epi32(r, r);
        r = _mm256_hadd_epi32(r, r);

        return  _mm256_extract_epi32(r, 3) + 
                _mm256_extract_epi32(r, 4);

    #elif defined(SSE)
        __m128i r = _mm_load_si128((__m128i*) &a[0]);

        for(int32 i=8; i<size; i+=8)
            r = _mm_add_epi32(r, _mm_load_si128((__m128i*) &a[i]));

        r = _mm_hadd_epi32(r, r);
        r = _mm_hadd_epi32(r, r);

        return  _mm_extract_epi32(r, 0);
    #else 
        int32 r = 0;
        for(int32 i=0; i<size; i++) 
            r += a[i];
        return r;
    #endif
}


void add_f32array(unsigned size, float32* a, float32* b, float32* c) {
    #if defined(AVX)
        for(int32 i=0; i<size; i+=8) {
            __m256 v0 = _mm256_loadu_ps(&a[i]);
            __m256 v1 = _mm256_loadu_ps(&b[i]);
            _mm256_storeu_ps(&c[i], _mm256_add_ps(v0, v1));
        }
    #elif defined(SSE)
        for(int32 i=0; i<size; i+=4) {
            __m128 v0 = _mm_loadu_ps(&a[i]);
            __m128 v1 = _mm_loadu_ps(&b[i]);
            _mm_storeu_ps(&c[i], _mm_add_ps(v0, v1));
        }
    #else
        for(int32 i=0; i<size; i++) {
            c[i] = a[i] + b[i];
        }
    #endif
}

void add_i32array(unsigned size, int32* a, int32* b, int32* c) {
    #if defined(AVX)
        for(int32 i=0; i<size; i+=8) {
            __m256i v0 = _mm256_loadu_si256((__m256i*) &a[i]);
            __m256i v1 = _mm256_loadu_si256((__m256i*) &b[i]);
            _mm256_storeu_si256((__m256i*)&c[i], _mm256_add_epi32(v0, v1));
        }
    #elif defined(SSE)
        for(int32 i=0; i<size; i+=4) {
            __m128i v0 = _mm_loadu_si128((__m128i*) &a[i]);
            __m128i v1 = _mm_loadu_si128((__m128i*) &b[i]);
            _mm_storeu_si128((__m128i*)&c[i], _mm_add_epi32(v0, v1));
        }
    #else
        for(int32 i=0; i<size; i++) {
            c[i] = a[i] + b[i];
        }
    #endif
}


void sub_f32array(unsigned size, float32* a, float32* b, float32* c) {
    #if defined(AVX)
        for(int32 i=0; i<size; i+=8) {
            __m256 v0 = _mm256_loadu_ps(&a[i]);
            __m256 v1 = _mm256_loadu_ps(&b[i]);
            _mm256_storeu_ps(&c[i], _mm256_sub_ps(v0, v1));
        }
    #elif defined(SSE)
        for(int32 i=0; i<size; i+=4) {
            __m128 v0 = _mm_loadu_ps(&a[i]);
            __m128 v1 = _mm_loadu_ps(&b[i]);
            _mm_storeu_ps(&c[i], _mm_sub_ps(v0, v1));
        }
    #else
        for(int32 i=0; i<size; i++) {
            c[i] = a[i] - b[i];
        }
    #endif
}

void sub_i32array(unsigned size, int32* a, int32* b, int32* c) {
    #if defined(AVX)
        for(int32 i=0; i<size; i+=8) {
            __m256i v0 = _mm256_loadu_si256((__m256i*) &a[0]);
            __m256i v1 = _mm256_loadu_si256((__m256i*) &b[0]);
            _mm256_store_si256((__m256i*)&c[i], _mm256_sub_epi32(v0, v1));
        }
    #elif defined(SSE)
        for(int32 i=0; i<size; i+=4) {
            __m128i v0 = _mm_loadu_si128((__m128i*) &a[0]);
            __m128i v1 = _mm_loadu_si128((__m128i*) &b[0]);
            _mm_storeu_si128((__m128i*)&c[i], _mm_sub_epi32(v0, v1));
        }
    #else
        for(int32 i=0; i<size; i++) {
            c[i] = a[i] - b[i];
        }
    #endif
}


void mul_f32array(unsigned size, float32* a, float32* b, float32* c) {
    #if defined(AVX)
        for(int32 i=0; i<size; i+=8) {
            __m256 v0 = _mm256_loadu_ps(&a[i]);
            __m256 v1 = _mm256_loadu_ps(&b[i]);
            _mm256_storeu_ps(&c[i], _mm256_mul_ps(v0, v1));
        }
    #elif defined(SSE)
        for(int32 i=0; i<size; i+=4) {
            __m128 v0 = _mm_loadu_ps(&a[i]);
            __m128 v1 = _mm_loadu_ps(&b[i]);
            _mm_storeu_ps(&c[i], _mm_mul_ps(v0, v1));
        }
    #else
        for(int32 i=0; i<size; i++) {
            c[i] = a[i] * b[i];
        }
    #endif
}

void mul_i32array(unsigned size, int32* a, int32* b, int32* c) {
    #if defined(AVX)
        for(int32 i=0; i<size; i+=8) {
            __m256i v0 = _mm256_loadu_si256((__m256i*) &a[0]);
            __m256i v1 = _mm256_loadu_si256((__m256i*) &b[0]);
            _mm256_storeu_si256((__m256i*)&c[i], _mm256_mul_epi32(v0, v1));
        }
    #elif defined(SSE)
        for(int32 i=0; i<size; i+=4) {
            __m128i v0 = _mm_loadu_si128((__m128i*) &a[0]);
            __m128i v1 = _mm_loadu_si128((__m128i*) &b[0]);
            _mm_storeu_si128((__m128i*)&c[i], _mm_mul_epi32(v0, v1));
        }
    #else
        for(int32 i=0; i<size; i++) {
            c[i] = a[i] * b[i];
        }
    #endif
}


void div_f32array(unsigned size, float32* a, float32* b, float32* c) {
    #if defined(AVX)
        for(int32 i=0; i<size; i+=8) {
            __m256 v0 = _mm256_loadu_ps(&a[i]);
            __m256 v1 = _mm256_loadu_ps(&b[i]);
            _mm256_storeu_ps(&c[i], _mm256_div_ps(v0, v1));
        }
    #elif defined(SSE)
        for(int32 i=0; i<size; i+=4) {
            __m128 v0 = _mm_loadu_ps(&a[i]);
            __m128 v1 = _mm_loadu_ps(&b[i]);
            _mm_storeu_ps(&c[i], _mm_div_ps(v0, v1));
        }
    #else
        for(int32 i=0; i<size; i++) {
            c[i] = a[i] / b[i];
        }
    #endif
}

void fma_f32array(unsigned size, float32* a, float32* b, float32* c, float32* d) {
    #if defined(FMA_AVX)
        for(int32 i=0; i<size; i+=8) {
            __m256 v0 = _mm256_loadu_ps(&a[i]);
            __m256 v1 = _mm256_loadu_ps(&b[i]);
            __m256 v2 = _mm256_loadu_ps(&c[i]);
            _mm256_storeu_ps(&d[i], _mm256_fmadd_ps(v0, v1, v2));
        }
    #elif defined(FMA_SSE)
        for(int32 i=0; i<size; i+=4) {
            __m128 v0 = _mm_loadu_ps(&a[i]);
            __m128 v1 = _mm_loadu_ps(&b[i]);
            __m128 v2 = _mm_loadu_ps(&c[i]);
            _mm_storeu_ps(&d[i], _mm_fmadd_ps(v0, v1, v2));
        }
    #else
        add_f32array(size, a, b, d);
        mul_f32array(size, d, c, d);
    #endif
}

void fma_i32array(unsigned size, int32* a, int32* b, int32* c, int32* d) {
    add_i32array(size, a, b, d);
    mul_i32array(size, d, c, d);
}

void mul_f32array(unsigned size, float32* a, float32 b, float32* c) {
    #if defined(AVX)
        __m256 v1 = _mm256_set1_ps(b);
        for(int32 i=0; i<size; i+=8) {
            __m256 v0 = _mm256_loadu_ps(&a[i]);
            _mm256_storeu_ps(&c[i], _mm256_mul_ps(v0, v1));
        }
    #elif defined(SSE)
        __m128 v1 = _mm_set1_ps(b);
        for(int32 i=0; i<size; i+=4) {
            __m128 v0 = _mm_loadu_ps(&a[i]);
            __m128 v1 = _mm_loadu_ps(&b[i]);
            _mm_storeu_ps(&c[i], _mm_mul_ps(v0, v1));
        }
    #else
        for(int32 i=0; i<size; i++) {
            c[i] = a[i] * b;
        }
    #endif
}

void mul_i32array(unsigned size, int32* a, int32 b, int32* c) {
    #if defined(AVX)
        int32 l[8] = { b,b,b,b,b,b,b };
        for(int32 i=0; i<size; i+=8) {
            __m256i first_values  = _mm256_loadu_si256((__m256i*)&a[i]);
            __m256i second_values = _mm256_loadu_si256((__m256i*)l);
            _mm256_storeu_si256((__m256i*)&c[i], _mm256_castps_si256(_mm256_mul_ps(_mm256_castsi256_ps(first_values), _mm256_castsi256_ps(second_values))));
        }
    #elif defined(SSE)
        __m128i v1 = _mm_set1_epi32(b);
        for(int32 i=0; i<size; i+=4) {
            __m128i v0 =  _mm_loadu_si128((__m128i*) &a[i]);
            _mm_storeu_si128((__m128i*)&c[i], _mm_mul_epi32(v0, v1));
        }
    #else
        for(int32 i=0; i<size; i++) {
            c[i] = a[i] * b;
        }
    #endif
}


void add_i32array(unsigned size, int32* a, int32 b, int32* c) {
    #if defined(AVX)
        __m256i v1 = _mm256_set1_epi32(b);
        for(int32 i=0; i<size; i+=8) {
            __m256i v0 = _mm256_loadu_si256((__m256i*) &a[i]);
            _mm256_storeu_si256((__m256i*)&c[i], _mm256_add_epi32(v0, v1));
        }
    #elif defined(SSE)
        __m128i v1 = _mm_set1_epi32(b);
        for(int32 i=0; i<size; i+=4) {
            __m128i v0 =  _mm_loadu_si128((__m128i*) &a[i]);
            _mm_storeu_si128((__m128i*)&c[i], _mm_add_epi32(v0, v1));
        }
    #else
        for(int32 i=0; i<size; i++) {
            c[i] = a[i] + b;
        }
    #endif
}


void add_f32array(unsigned size, float32* a, float32 b, float32* c) {
    #if defined(AVX)
        __m256 v1 = _mm256_set1_ps(b);
        for(int32 i=0; i<size; i+=8) {
            __m256 v0 = _mm256_loadu_ps(&a[i]);
            _mm256_storeu_ps(&c[i], _mm256_add_ps(v0, v1));
        }
    #elif defined(SSE)
        __m128 v1 = _mm128_set1_ps(b);
        for(int32 i=0; i<size; i+=4) {
            __m128 v0 = _mm_loadu_ps(&a[i]);
            _mm_storeu_ps(&c[i], _mm_add_ps(v0, v1));
        }
    #else
        for(int32 i=0; i<size; i++) {
            c[i] = a[i] + b;
        }
    #endif
}

void sub_f32array(unsigned size, float32* a, float32 b, float32* c) {
    #if defined(AVX)
        __m256 v1 = _mm256_set1_ps(b);
        for(int32 i=0; i<size; i+=8) {
            __m256 v0 = _mm256_loadu_ps(&a[i]);
            _mm256_storeu_ps(&c[i], _mm256_sub_ps(v0, v1));
        }
    #elif defined(SSE)
        __m128 v1 = _mm128_set1_ps(b);
        for(int32 i=0; i<size; i+=4) {
            __m128 v0 = _mm_loadu_ps(&a[i]);
            _mm_storeu_ps(&c[i], _mm_sub_ps(v0, v1));
        }
    #else
        for(int32 i=0; i<size; i++) {
            c[i] = a[i] - b;
        }
    #endif
}

void sub_i32array(unsigned size, int32* a, int32 b, int32* c) {
    #if defined(AVX)
        __m256i v1 = _mm256_set1_epi32(b);
        for(int32 i=0; i<size; i+=8) {
            __m256i v0 = _mm256_loadu_si256((__m256i*) &a[i]);
            _mm256_storeu_si256((__m256i*)&c[i], _mm256_sub_epi32(v0, v1));
        }
    #elif defined(SSE)
        __m128i v1 = _mm_set1_epi32(b);
        for(int32 i=0; i<size; i+=4) {
            __m128i v0 =  _mm_loadu_si128((__m128i*) &a[i]);
            _mm_storeu_si128((__m128i*)&c[i], _mm_sub_epi32(v0, v1));
        }
    #else
        for(int32 i=0; i<size; i++) {
            c[i] = a[i] - b;
        }
    #endif
}


float dot_f32array(unsigned size, float32* a, float32* b) {
    float* c = new float[size];
    
    mul_f32array(size, a, b, c);
    float d = reduce_f32array(size, c);
    
    delete[] c;
    
    return d;
}


void sqrt_f32array(unsigned size, float32* a, float32* c) {
    #if defined(AVX)
        for(int32 i=0; i<size; i+=8) {
            __m256 v0 = _mm256_loadu_ps(&a[i]);
            _mm256_storeu_ps(&c[i], _mm256_sqrt_ps(v0));
        }
    #elif defined(SSE)
        for(int32 i=0; i<size; i+=4) {
            __m128 v0 = _mm_loadu_ps(&a[i]);
            _mm_storeu_ps(&c[i], _mm256_sqrt_ps(v0));
        }
    #else
        for(int32 i=0; i<size; i++) {
            c[i] = sqrt(a[i]);
        }
    #endif
}

void unfold_mat_x_multiple(int* i, int* I, int n, int N, int size, int* col) {
    int* M = new int[N]{1};
    int* A = new int[size];
    
    for(int m=1; m < N; m++)
        if(m == n) M[m] = M[m-1];
        else M[m] = M[m-1] * I[m-1];

    for(int k=1; k<=N; k++) {
        if(k==n) continue;
        sub_i32array(size, &i[(k-1)*size], 1, A);
        mul_f32array(size, (float*)A, (float)M[k-1], (float*)A);
        add_i32array(size, col, A, col);
    }

    delete[] A;
    delete[] M;
}

void unfold_mat_y_multiple(int* i, int* I, int n, int N, int size, int* lins) {
    sub_i32array(size, &i[(n-1)*size], 1, lins);
}
