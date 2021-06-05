#ifndef SSE_H
#define SSE_H

#include "types.h"

#include <xmmintrin.h>
#include <emmintrin.h>
#include <pmmintrin.h>
#include <tmmintrin.h>
#include <smmintrin.h>

float32 reduce_f32_array(int64 size, float32* a) {
    __m128 r = _mm_loadu_ps(a);

    for(int32 i=4; i<size; i+=4) 
        r = _mm_add_ps(r, _mm_load_ps(&a[i]));

    r = _mm_hadd_ps(r, r);
    r = _mm_hadd_ps(r, r);

    float32 arr[4];
    _mm_storeu_ps(arr, r);

    return arr[0];
}


int32 reduce_i32_array(unsigned size, int32* a) {
    __m128i r = _mm_load_si128((__m128i*) &a[0]);

    for(int32 i=8; i<size; i+=8)
        r = _mm_add_epi32(r, _mm_load_si128((__m128i*) &a[i]));

    r = _mm_hadd_epi32(r, r);
    r = _mm_hadd_epi32(r, r);

    int t;
    _mm_storeu_si32(&t, r);
    return t;
}


void add_f32_array(unsigned size, float32* a, float32* b, float32* c) {
    for(int32 i=0; i<size; i+=4) {
        __m128 v0 = _mm_loadu_ps(&a[i]);
        __m128 v1 = _mm_loadu_ps(&b[i]);
        _mm_storeu_ps(&c[i], _mm_add_ps(v0, v1));
    }
}

void add_i32_array(unsigned size, int32* a, int32* b, int32* c) {
    for(int32 i=0; i<size; i+=4) {
        __m128i v0 = _mm_loadu_si128((__m128i*) &a[i]);
        __m128i v1 = _mm_loadu_si128((__m128i*) &b[i]);
        _mm_storeu_si128((__m128i*)&c[i], _mm_add_epi32(v0, v1));
    }
}


void sub_f32_array(unsigned size, float32* a, float32* b, float32* c) {
    for(int32 i=0; i<size; i+=4) {
        __m128 v0 = _mm_loadu_ps(&a[i]);
        __m128 v1 = _mm_loadu_ps(&b[i]);
        _mm_storeu_ps(&c[i], _mm_sub_ps(v0, v1));
    }
}

void sub_i32_array(unsigned size, int32* a, int32* b, int32* c) {
    for(int32 i=0; i<size; i+=4) {
        __m128i v0 = _mm_loadu_si128((__m128i*) &a[0]);
        __m128i v1 = _mm_loadu_si128((__m128i*) &b[0]);
        _mm_storeu_si128((__m128i*)&c[i], _mm_sub_epi32(v0, v1));
    }
}


void mul_f32_array(unsigned size, float32* a, float32* b, float32* c) {
    for(int32 i=0; i<size; i+=4) {
        __m128 v0 = _mm_loadu_ps(&a[i]);
        __m128 v1 = _mm_loadu_ps(&b[i]);
        _mm_storeu_ps(&c[i], _mm_mul_ps(v0, v1));
    }
}

void mul_i32_array(unsigned size, int32* a, int32* b, int32* c) {
    for(int32 i=0; i<size; i+=4) {
        __m128 v0 =  _mm_cvtepi32_ps(_mm_loadu_si128((__m128i*) &a[i]));
        __m128 v1 =  _mm_cvtepi32_ps(_mm_loadu_si128((__m128i*) &b[i]));
        _mm_storeu_si128((__m128i*)&c[i], _mm_cvttps_epi32(_mm_mul_ps(v0, v1)));
    }
}
void div_i32_array(unsigned size, int32* a, int32* b, int32* c) {
    for(int32 i=0; i<size; i+=4) {
        __m128 v0 =  _mm_cvtepi32_ps(_mm_loadu_si128((__m128i*) &a[i]));
        __m128 v1 =  _mm_cvtepi32_ps(_mm_loadu_si128((__m128i*) &b[i]));
        __m128 v2 =  _mm_floor_ps(_mm_div_ps(v0, v1));
        _mm_storeu_si128((__m128i*)&c[i], _mm_cvttps_epi32(v2));
    }
}


void div_f32_array(unsigned size, float32* a, float32* b, float32* c) {
    for(int32 i=0; i<size; i+=4) {
        __m128 v0 = _mm_loadu_ps(&a[i]);
        __m128 v1 = _mm_loadu_ps(&b[i]);
        _mm_storeu_ps(&c[i], _mm_div_ps(v0, v1));
    }
}

void mul_f32_array(unsigned size, float32* a, float32 b, float32* c) {
    __m128 v1 = _mm_set1_ps(b);
    for(int32 i=0; i<size; i+=4) {
        __m128 v0 = _mm_loadu_ps(&a[i]);
        _mm_storeu_ps(&c[i], _mm_mul_ps(v0, v1));
    }
}

void mul_i32_array(unsigned size, int32* a, int32 b, int32* c) {

    __m128 v1 =  _mm_cvtepi32_ps(_mm_set1_epi32(b));
    for(int32 i=0; i<size; i+=4) {
        __m128 v0 =  _mm_cvtepi32_ps(_mm_loadu_si128((__m128i*) &a[i]));
        _mm_storeu_si128((__m128i*)&c[i], _mm_cvttps_epi32(_mm_mul_ps(v0, v1)));
    }

}

void add_i32_array(unsigned size, int32* a, int32 b, int32* c) {
    __m128i v1 = _mm_set1_epi32(b);
    for(int32 i=0; i<size; i+=4) {
        __m128i v0 =  _mm_loadu_si128((__m128i*) &a[i]);
        _mm_storeu_si128((__m128i*)&c[i], _mm_add_epi32(v0, v1));
    }
}

void add_f32_array(unsigned size, float32* a, float32 b, float32* c) {
    __m128 v1 = _mm_set1_ps(b);
    for(int32 i=0; i<size; i+=4) {
        __m128 v0 = _mm_loadu_ps(&a[i]);
        _mm_storeu_ps(&c[i], _mm_add_ps(v0, v1));
    }
}

void sub_f32_array(unsigned size, float32* a, float32 b, float32* c) {
    __m128 v1 = _mm_set1_ps(b);
    for(int32 i=0; i<size; i+=4) {
        __m128 v0 = _mm_loadu_ps(&a[i]);
        _mm_storeu_ps(&c[i], _mm_sub_ps(v0, v1));
    }
}

void sub_i32_array(unsigned size, int32* a, int32 b, int32* c) {
    __m128i v1 = _mm_set1_epi32(b);
    for(int32 i=0; i<size; i+=4) {
        __m128i v0 =  _mm_loadu_si128((__m128i*) &a[i]);
        _mm_storeu_si128((__m128i*)&c[i], _mm_sub_epi32(v0, v1));
    }
}


float dot_f32_array(unsigned size, float32* a, float32* b) {
    float* c = new float[size];
    
    mul_f32_array(size, a, b, c);
    float d = reduce_f32_array(size, c);
    
    delete[] c;
    
    return d;
}

void sqrt_f32_array(unsigned size, float32* a, float32* c) {
    for(int32 i=0; i<size; i+=4) {
        __m128 v0 = _mm_loadu_ps(&a[i]);
        _mm_storeu_ps(&c[i], _mm_sqrt_ps(v0));
    }
}

#endif
