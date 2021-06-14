#ifndef AVX_H
#define AVX_H

#include "macros.h"
#include "types.h"

#include <cmath>

#include <iostream>
#ifdef WIN32
#include <intrin.h>
#else
#include <immintrin.h>
#endif

TENSOR_EXPORT float32 reduce_f32array_avx(uint64 size, float32* a) {
    __m256 r = _mm256_loadu_ps(a);
    uint64 k = (size - size % 8);
    for(int32 i=8; i<k; i+=8)
        r = _mm256_add_ps(r, _mm256_load_ps(&a[i]));

    r = _mm256_hadd_ps(r, r);
    r = _mm256_hadd_ps(r, r);

    float32 arr[8];
    _mm256_storeu_ps(arr, r);

    float32 x = arr[3] + arr[4];

    int32 t = size%8;

    for (int32 i = 1; i <= t; i++)
        x += a[size-i];

    return x;
}

TENSOR_EXPORT int32 reduce_i32array_avx(uint64 size, int32* a) {
    __m256i r = _mm256_loadu_si256((__m256i*) &a[0]);
    uint64 k = (size - size % 8);
    for(int32 i=8; i<k; i+=8)
        r = _mm256_add_epi32(r, _mm256_loadu_si256((__m256i*) &a[i]));

    r = _mm256_hadd_epi32(r, r);
    r = _mm256_hadd_epi32(r, r);

    int32 x = _mm256_extract_epi32(r, 3) + 
              _mm256_extract_epi32(r, 4);

    int32 t = size%8;

    for(int i=1; i<=t; i++)
        x += a[size-i];

    return x;
}

TENSOR_EXPORT void add_f32array_avx(uint64 size, float32* a, float32* b, float32* c) {
    uint64 k = (size - size % 8);

    for (int32 i = 0; i < k; i += 8) {
        __m256 v0 = _mm256_loadu_ps(&a[i]);
        __m256 v1 = _mm256_loadu_ps(&b[i]);
        _mm256_storeu_ps(&c[i], _mm256_add_ps(v0, v1));
    }

    int32 t = size % 8;
    for (int i = 1; i <= t; i++)
        c[size - i] = a[size - i] + b[size - i];
}

TENSOR_EXPORT void add_f32array_f32_avx(uint64 size, float32* a, float32 b, float32* c) {
    __m256 v1 = _mm256_set1_ps(b);
    uint64 k = (size - size % 8);

    for (int32 i = 0; i < k; i += 8) {
        __m256 v0 = _mm256_loadu_ps(&a[i]);
        _mm256_storeu_ps(&c[i], _mm256_add_ps(v0, v1));
    }

    int32 t = size % 8;
    for (int i = 1; i <= t; i++)
        c[size - i] = a[size - i] + b;
}

TENSOR_EXPORT void add_i32array_avx(uint64 size, int32* a, int32* b, int32* c) {
    uint64 k = (size - size % 8);

    for (int32 i = 0; i < k; i += 8) {
        __m256i v0 = _mm256_loadu_si256((__m256i*) & a[i]);
        __m256i v1 = _mm256_loadu_si256((__m256i*) & b[i]);
        _mm256_storeu_si256((__m256i*) & c[i], _mm256_add_epi32(v0, v1));
    }

    int32 t = size % 8;
    for (int i = 1; i <= t; i++)
        c[size - i] = a[size - i] + b[size - i];
}

TENSOR_EXPORT void add_i32array_i32_avx(uint64 size, int32* a, int32 b, int32* c) {
    __m256i v1 = _mm256_set1_epi32(b);
    uint64 k = (size - size % 8);

    for (int32 i = 0; i < k; i += 8) {
        __m256i v0 = _mm256_loadu_si256((__m256i*) & a[i]);
        _mm256_storeu_si256((__m256i*) & c[i], _mm256_add_epi32(v0, v1));
    }

    int32 t = size % 8;
    for (int i = 1; i <= t; i++)
        c[size - i] = a[size - i] + b;
}

TENSOR_EXPORT void sub_f32array_avx(uint64 size, float32* a, float32* b, float32* c) {
    uint64 k = (size - size % 8);

    for (int32 i = 0; i < k; i += 8) {
        __m256 v0 = _mm256_loadu_ps(&a[i]);
        __m256 v1 = _mm256_loadu_ps(&b[i]);
        _mm256_storeu_ps(&c[i], _mm256_sub_ps(v0, v1));
    }

    int32 t = size % 8;
    for (int i = 1; i <= t; i++)
        c[size - i] = a[size - i] - b[size - 1];
}

TENSOR_EXPORT void sub_f32array_f32_avx(uint64 size, float32* a, float32 b, float32* c) {
    uint64 k = (size - size % 8);

    __m256 v1 = _mm256_set1_ps(b);
    for (int32 i = 0; i < k; i += 8) {
        __m256 v0 = _mm256_loadu_ps(&a[i]);
        _mm256_storeu_ps(&c[i], _mm256_sub_ps(v0, v1));
    }

    int32 t = size % 8;
    for (int i = 1; i <= t; i++)
        c[size - i] = a[size - i] - b;
}

TENSOR_EXPORT void sub_i32array_avx(uint64 size, int32* a, int32* b, int32* c) {
    uint64 k = (size - size % 8);

    for (int32 i = 0; i < k; i += 8) {
        __m256i v0 = _mm256_loadu_si256((__m256i*) & a[0]);
        __m256i v1 = _mm256_loadu_si256((__m256i*) & b[0]);
        _mm256_store_si256((__m256i*) & c[i], _mm256_sub_epi32(v0, v1));
    }

    int32 t = size % 8;
    for (int i = 1; i <= t; i++)
        c[size - i] = a[size - i] - b[size - 1];
}

TENSOR_EXPORT void sub_i32array_i32_avx(uint64 size, int32* a, int32 b, int32* c) {
    uint64 k = (size - size % 8);

    __m256i v1 = _mm256_set1_epi32(b);
    for (int32 i = 0; i < k; i += 8) {
        __m256i v0 = _mm256_loadu_si256((__m256i*) & a[i]);
        _mm256_storeu_si256((__m256i*) & c[i], _mm256_sub_epi32(v0, v1));
    }

    int32 t = size % 8;
    for (int i = 1; i <= t; i++)
        c[size - i] = a[size - i] - b;
}

TENSOR_EXPORT void mul_i32array_avx(uint64 size, int32* a, int32* b, int32* c) {
    uint64 k = (size - size % 8);

    for (int32 i = 0; i < k; i += 8) {
        __m256i v0 = _mm256_loadu_si256((__m256i*) & a[0]);
        __m256i v1 = _mm256_loadu_si256((__m256i*) & b[0]);
        _mm256_storeu_si256((__m256i*) & c[i], _mm256_mul_epi32(v0, v1));
    }

    int32 t = size % 8;
    for (int i = 1; i <= t; i++)
        c[size - i] = a[size - i] * b[size - 1];
}

TENSOR_EXPORT void mul_i32array_i32_avx(uint64 size, int32* a, int32 b, int32* c) {
    uint64 k = (size - size % 8);
    __m256i second_values = _mm256_set1_epi32(b);

    for (int32 i = 0; i < k; i += 8) {
        __m256i first_values = _mm256_loadu_si256((__m256i*) & a[i]);
        _mm256_storeu_si256((__m256i*) & c[i], _mm256_castps_si256(_mm256_mul_ps(_mm256_castsi256_ps(first_values), _mm256_castsi256_ps(second_values))));
    }

    int32 t = size % 8;
    for (int i = 1; i <= t; i++)
        c[size - i] = a[size - i] * b;
}

TENSOR_EXPORT void mul_f32array_avx(uint64 size, float32* a, float32* b, float32* c) {
    uint64 k = (size - size % 8);

    for (int32 i = 0; i < k; i += 8) {
        __m256 v0 = _mm256_loadu_ps(&a[i]);
        __m256 v1 = _mm256_loadu_ps(&b[i]);
        _mm256_storeu_ps(&c[i], _mm256_mul_ps(v0, v1));
    }

    int32 t = size % 8;
    for (int i = 1; i <= t; i++)
        c[size - i] = a[size - i] * b[size - 1];
}

TENSOR_EXPORT void mul_f32array_f32_avx(uint64 size, float32* a, float32 b, float32* c) {
    uint64 k = (size - size % 8);

    __m256 v1 = _mm256_set1_ps(b);
    for (int32 i = 0; i < k; i += 8) {
        __m256 v0 = _mm256_loadu_ps(&a[i]);
        _mm256_storeu_ps(&c[i], _mm256_mul_ps(v0, v1));
    }

    int32 t = size % 8;
    for (int i = 1; i <= t; i++)
        c[size - i] = a[size - i] * b;
}

TENSOR_EXPORT void div_i32array_avx(uint64 size, int32* a, int32* b, int32* c) {
    uint64 k = (size - size % 8);

    for (int32 i = 0; i < k; i += 8) {
        __m256 v0 = _mm256_cvtepi32_ps(_mm256_loadu_epi32(&a[i]));
        __m256 v1 = _mm256_cvtepi32_ps(_mm256_loadu_epi32(&b[i]));
        __m256 v2 = _mm256_floor_ps(_mm256_div_ps(v0, v1));
        _mm256_storeu_si256((__m256i*) & c[i], _mm256_cvtps_epi32(v2));
    }

    int32 t = size % 8;
    for (int i = 1; i <= t; i++)
        c[size - i] = static_cast<int32>(floor(static_cast<float32>(a[size - i]) / static_cast<float32>(b[size - i])));
}

TENSOR_EXPORT void div_i32array_i32_avx(uint64 size, int32* a, int32 b, int32* c) {
    uint64 k = (size - size % 8);

    __m256 v1 = _mm256_cvtepi32_ps(_mm256_set1_epi32(b));
    for (int32 i = 0; i < k; i += 8) {
        __m256 v0 = _mm256_cvtepi32_ps(_mm256_loadu_epi32(&a[i]));
        __m256 v2 = _mm256_floor_ps(_mm256_div_ps(v0, v1));
        _mm256_storeu_si256((__m256i*) & c[i], _mm256_cvtps_epi32(v2));
    }

    int32 t = size % 8;
    for (int i = 1; i <= t; i++)
        c[size - i] = static_cast<int32>(floor(static_cast<float32>(a[size - i]) / static_cast<float32>(b)));
}

TENSOR_EXPORT void div_f32array_avx(uint64 size, float32* a, float32* b, float32* c) {
    uint64 k = (size - size % 8);

    for (int32 i = 0; i < k; i += 8) {
        __m256 v0 = _mm256_loadu_ps(&a[i]);
        __m256 v1 = _mm256_loadu_ps(&b[i]);
        _mm256_storeu_ps(&c[i], _mm256_div_ps(v0, v1));
    }

    int32 t = size % 8;
    for (int i = 1; i <= t; i++)
        c[size - i] = a[size - i] / b[size - 1];
}

TENSOR_EXPORT void div_f32array_f32_avx(uint64 size, float32* a, float32 b, float32* c) {
    uint64 k = (size - size % 8);

    __m256 v1 = _mm256_set1_ps(b);
    for (int32 i = 0; i < k; i += 8) {
        __m256 v0 = _mm256_loadu_ps(&a[i]);
        _mm256_storeu_ps(&c[i], _mm256_div_ps(v0, v1));
    }

    int32 t = size % 8;
    for (int i = 1; i <= t; i++)
        c[size - i] = a[size - i] / b;
}

TENSOR_EXPORT float32 dot_f32array_avx(uint64 size, float32* a, float32* b) {
    float* c = new float[size];

    mul_f32array_avx(size, a, b, c);
    float d = reduce_f32array_avx(size, c);

    delete[] c;
    
    return d;
}

TENSOR_EXPORT void sqrt_f32array_avx(uint64 size, float32* a, float32* c) {
    uint64 k = (size - size % 8);

    for(int32 i=0; i<k; i+=8) {
        __m256 v0 = _mm256_loadu_ps(&a[i]);
        _mm256_storeu_ps(&c[i], _mm256_sqrt_ps(v0));
    }

    int32 t = size%8;
    for(int i=1; i<=t; i++)
        c[size-i] = sqrt(a[size-i]);
}

#endif