#ifndef SSE_H
#define SSE_H

#include "types.h"
#include "macros.h"

#include <cmath>

#ifdef WIN32
#include <intrin.h>
#else
#include <xmmintrin.h>
#include <emmintrin.h>
#include <pmmintrin.h>
#include <tmmintrin.h>
#include <smmintrin.h>
#endif

TENSOR_EXPORT float32 reduce_f32array_sse(uint64 size, float32* a) {
    uint64 k = (size - size % 4);

    __m128 r = _mm_loadu_ps(a);
    
    for(int32 i=4; i<k; i+=4) 
        r = _mm_add_ps(r, _mm_load_ps(&a[i]));

    r = _mm_hadd_ps(r, r);
    r = _mm_hadd_ps(r, r);

    float32 arr[4];

    _mm_storeu_ps(arr, r);
    
    int32 t = size%4;
    
    for(int i=1; i<=t; i++)
        arr[0] += a[size-i];
    
    return arr[0];
}

TENSOR_EXPORT int32 reduce_i32array_sse(uint64 size, int32* a) {
    uint64 k = (size - size % 4);

    __m128i r = _mm_load_si128((__m128i*) &a[0]);

    for(int32 i=8; i<k; i+=4)
        r = _mm_add_epi32(r, _mm_load_si128((__m128i*) &a[i]));

    r = _mm_hadd_epi32(r, r);
    r = _mm_hadd_epi32(r, r);

    int32 t;
    _mm_storeu_si32(&t, r);

    int32 s = size%4;
    for(int i=1; i<=s; i++)
        t += a[size-i];
    
    return t;

}

TENSOR_EXPORT void add_f32array_sse(uint64 size, float32* a, float32* b, float32* c) {
    uint64 k = (size - size % 4);

    for(int32 i=0; i<k; i+=4) {
        __m128 v0 = _mm_loadu_ps(&a[i]);
        __m128 v1 = _mm_loadu_ps(&b[i]);
        _mm_storeu_ps(&c[i], _mm_add_ps(v0, v1));
    }

    int32 t = size%4;
    for(int i=1; i<=t; i++)
        c[size-i] = a[size-i] + b[size-i];
}

TENSOR_EXPORT void add_f32array_f32_sse(uint64 size, float32* a, float32 b, float32* c) {
    uint64 k = (size - size % 4);

    __m128 v1 = _mm_set1_ps(b);
    for(int32 i=0; i<k; i+=4) {
        __m128 v0 = _mm_loadu_ps(&a[i]);
        _mm_storeu_ps(&c[i], _mm_add_ps(v0, v1));
    }

    int32 t = size%4;
    for(int i=1; i<=t; i++)
        c[size-i] = a[size-i] + b;
}

TENSOR_EXPORT void add_i32array_sse(uint64 size, int32* a, int32* b, int32* c) {
    uint64 k = (size - size % 4);

    for(int32 i=0; i<k; i+=4) {
        __m128i v0 = _mm_loadu_si128((__m128i*) &a[i]);
        __m128i v1 = _mm_loadu_si128((__m128i*) &b[i]);
        _mm_storeu_si128((__m128i*)&c[i], _mm_add_epi32(v0, v1));
    }

    int32 t = size%4;
    for(int i=1; i<=t; i++)
        c[size-i] = a[size-i] + b[size-i];
}

TENSOR_EXPORT void add_i32array_i32_sse(uint64 size, int32* a, int32 b, int32* c) {
    uint64 k = (size - size % 4);

    __m128i v1 = _mm_set1_epi32(b);
    for(int32 i=0; i<k; i+=4) {
        __m128i v0 =  _mm_loadu_si128((__m128i*) &a[i]);
        _mm_storeu_si128((__m128i*)&c[i], _mm_add_epi32(v0, v1));
    }

    int32 t = size%4;
    for(int i=1; i<=t; i++)
        c[size-i] = a[size-i] + b;
}

TENSOR_EXPORT void sub_f32array_sse(uint64 size, float32* a, float32* b, float32* c) {
    uint64 k = (size - size % 4);

    for(int32 i=0; i<k; i+=4) {
        __m128 v0 = _mm_loadu_ps(&a[i]);
        __m128 v1 = _mm_loadu_ps(&b[i]);
        _mm_storeu_ps(&c[i], _mm_sub_ps(v0, v1));
    }

    int32 t = size%4;
    for(int i=1; i<=t; i++)
        c[size-i] = a[size-i] - b[size-i];
}

TENSOR_EXPORT void sub_f32array_f32_sse(uint64 size, float32* a, float32 b, float32* c) {
    uint64 k = (size - size % 4);

    __m128 v1 = _mm_set1_ps(b);
    for(int32 i=0; i<k; i+=4) {
        __m128 v0 = _mm_loadu_ps(&a[i]);
        _mm_storeu_ps(&c[i], _mm_sub_ps(v0, v1));
    }

    int32 t = size%4;
    for(int i=1; i<=t; i++)
        c[size-i] = a[size-i] - b;
}

TENSOR_EXPORT void sub_i32array_sse(uint64 size, int32* a, int32* b, int32* c) {
    uint64 k = (size - size % 4);

    for(int32 i=0; i<k; i+=4) {
        __m128i v0 = _mm_loadu_si128((__m128i*) &a[0]);
        __m128i v1 = _mm_loadu_si128((__m128i*) &b[0]);
        _mm_storeu_si128((__m128i*)&c[i], _mm_sub_epi32(v0, v1));
    }

    int32 t = size%4;
    for(int i=1; i<=t; i++)
        c[size-i] = a[size-i] - b[size-i];
}

TENSOR_EXPORT void sub_i32array_i32_sse(uint64 size, int32* a, int32 b, int32* c) {
    uint64 k = (size - size % 4);

    __m128i v1 = _mm_set1_epi32(b);
    for(int32 i=0; i<k; i+=4) {
        __m128i v0 =  _mm_loadu_si128((__m128i*) &a[i]);
        _mm_storeu_si128((__m128i*)&c[i], _mm_sub_epi32(v0, v1));
    }

    int32 t = size%4;
    for(int i=1; i<=t; i++)
        c[size-i] = a[size-i] - b;
}

TENSOR_EXPORT void mul_f32array_sse(uint64 size, float32* a, float32* b, float32* c) {
    uint64 k = (size - size % 4);

    for(int32 i=0; i<k; i+=4) {
        __m128 v0 = _mm_loadu_ps(&a[i]);
        __m128 v1 = _mm_loadu_ps(&b[i]);
        _mm_storeu_ps(&c[i], _mm_mul_ps(v0, v1));
    }

    int32 t = size%4;
    for(int i=1; i<=t; i++)
        c[size-i] = a[size-i] * b[size-i];
}

TENSOR_EXPORT void mul_i32array_sse(uint64 size, int32* a, int32* b, int32* c) {
    uint64 k = (size - size % 4);

    for(int32 i=0; i<k; i+=4) {
        __m128 v0 =  _mm_cvtepi32_ps(_mm_loadu_si128((__m128i*) &a[i]));
        __m128 v1 =  _mm_cvtepi32_ps(_mm_loadu_si128((__m128i*) &b[i]));
        _mm_storeu_si128((__m128i*)&c[i], _mm_cvttps_epi32(_mm_mul_ps(v0, v1)));
    }

    int32 t = size%4;
    for(int i=1; i<=t; i++)
        c[size-i] = a[size-i] * b[size-i];
}

TENSOR_EXPORT void mul_f32array_f32_sse(uint64 size, float32* a, float32 b, float32* c) {
    uint64 k = (size - size % 4);

    __m128 v1 = _mm_set1_ps(b);
    for(int32 i=0; i<k; i+=4) {
        __m128 v0 = _mm_loadu_ps(&a[i]);
        _mm_storeu_ps(&c[i], _mm_mul_ps(v0, v1));
    }

    int32 t = size%4;
    for(int i=1; i<=t; i++)
        c[size-i] = a[size-i] * b;
}

TENSOR_EXPORT void mul_i32array_i32_sse(uint64 size, int32* a, int32 b, int32* c) {
    uint64 k = (size - size % 4);

    __m128 v1 =  _mm_cvtepi32_ps(_mm_set1_epi32(b));
    for(int32 i=0; i<k; i+=4) {
        __m128 v0 =  _mm_cvtepi32_ps(_mm_loadu_si128((__m128i*) &a[i]));
        _mm_storeu_si128((__m128i*)&c[i], _mm_cvttps_epi32(_mm_mul_ps(v0, v1)));
    }

    int32 t = size%4;
    for(int i=1; i<=t; i++)
        c[size-i] = a[size-i] * b;
}

TENSOR_EXPORT void div_i32array_sse(uint64 size, int32* a, int32* b, int32* c) {
    uint64 k = (size - size % 4);

    for(int32 i=0; i<k; i+=4) {
        __m128 v0 =  _mm_cvtepi32_ps(_mm_loadu_si128((__m128i*) &a[i]));
        __m128 v1 =  _mm_cvtepi32_ps(_mm_loadu_si128((__m128i*) &b[i]));
        __m128 v2 =  _mm_floor_ps(_mm_div_ps(v0, v1));
        _mm_storeu_si128((__m128i*)&c[i], _mm_cvttps_epi32(v2));
    }

    int32 t = size%4;
    for(int i=1; i<=t; i++)
        c[size-i] = static_cast<int32>(floor(static_cast<float32>(a[size-i]) / static_cast<float32>(b[size-i])));
}

TENSOR_EXPORT void div_i32array_i32_sse(uint64 size, int32* a, int32 b, int32* c) {
    uint64 k = (size - size % 4);

    __m128 v1 =  _mm_cvtepi32_ps(_mm_set1_epi32(b));
    for(int32 i=0; i<k; i+=4) {
        __m128 v0 =  _mm_cvtepi32_ps(_mm_loadu_si128((__m128i*) &a[i]));
        __m128 v2 =  _mm_floor_ps(_mm_div_ps(v0, v1));
        _mm_storeu_si128((__m128i*)&c[i], _mm_cvttps_epi32(v2));
    }

    int32 t = size%4;
    for(int i=1; i<=t; i++)
        c[size-i] = static_cast<int32>(floor(static_cast<float32>(a[size-i]) / static_cast<float32>(b)));
}

TENSOR_EXPORT void div_f32array_sse(uint64 size, float32* a, float32* b, float32* c) {
    uint64 k = (size - size % 4);

    for(int32 i=0; i<k; i+=4) {
        __m128 v0 = _mm_loadu_ps(&a[i]);
        __m128 v1 = _mm_loadu_ps(&b[i]);
        _mm_storeu_ps(&c[i], _mm_div_ps(v0, v1));
    }
    int32 t = size%4;
    for(int i=1; i<=t; i++)
        c[size-i] = a[size-i] / b[size-i];
}

TENSOR_EXPORT void div_f32array_f32_sse(uint64 size, float32* a, float32 b, float32* c) {
    uint64 k = (size - size % 4);

    __m128 v1 = _mm_set1_ps(b);
    for(int32 i=0; i<k; i+=4) {
        __m128 v0 = _mm_loadu_ps(&a[i]);
        _mm_storeu_ps(&c[i], _mm_div_ps(v0, v1));
    }
    int32 t = size%4;
    for(int i=1; i<=t; i++)
        c[size-i] = a[size-i] / b;
}

TENSOR_EXPORT float32 dot_f32array_sse(uint64 size, float32* a, float32* b) {
    float* c = new float[size];
    
    mul_f32array_sse(size, a, b, c);
    float d = reduce_f32array_sse(size, c);
    
    delete[] c;
    
    return d;
}

TENSOR_EXPORT void sqrt_f32array_sse(uint64 size, float32* a, float32* c) {
    uint64 k = (size - size % 4);

    for(int32 i=0; i<k; i+=4) {
        __m128 v0 = _mm_loadu_ps(&a[i]);
        _mm_storeu_ps(&c[i], _mm_sqrt_ps(v0));
    }

    int32 t = size%4;
    for(int i=1; i<=t; i++)
        c[size-i] = sqrt(a[size-i]);
}

#endif
