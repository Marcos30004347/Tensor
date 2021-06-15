#ifndef NAIVE_H
#define NAIVE_H

#include <cmath>
#include "macros.h"
#include "types.h"

TENSOR_EXPORT float32 reduce_f32array_naive(uint64 size, float32* a) {
    float32 r = 0;
    for(int32 i=0; i<size; i++) 
        r += a[i];
    return r;
}

TENSOR_EXPORT int32 reduce_i32array_naive(uint64 size, int32* a) {
    int32 r = 0;
    for(int32 i=0; i<size; i++) 
        r += a[i];
    return r;
}

TENSOR_EXPORT void add_f32array_naive(uint64 size, float32* a, float32* b, float32* c) {
    for (int32 i = 0; i < size; i++) {
        c[i] = a[i] + b[i];
    }
}

TENSOR_EXPORT void add_i32array_naive(uint64 size, int32* a, int32* b, int32* c) {
    for (int32 i = 0; i < size; i++) {
        c[i] = a[i] + b[i];
    }
}


TENSOR_EXPORT void sub_f32array_naive(uint64 size, float32* a, float32* b, float32* c) {
    for (int32 i = 0; i < size; i++) {
        c[i] = a[i] - b[i];
    }
}

TENSOR_EXPORT void sub_i32array_naive(uint64 size, int32* a, int32* b, int32* c) {
    for (int32 i = 0; i < size; i++) {
        c[i] = a[i] - b[i];
    }
}


TENSOR_EXPORT void mul_f32array_naive(uint64 size, float32* a, float32* b, float32* c) {
    for (int32 i = 0; i < size; i++) {
        c[i] = a[i] * b[i];
    }
}

TENSOR_EXPORT void mul_i32array_naive(uint64 size, int32* a, int32* b, int32* c) {
    for (int32 i = 0; i < size; i++) {
        c[i] = a[i] * b[i];
    }
}


TENSOR_EXPORT void div_f32array_naive(uint64 size, float32* a, float32* b, float32* c) {
    for (int32 i = 0; i < size; i++) {
        c[i] = a[i] / b[i];
    }
}

TENSOR_EXPORT void div_f32array_f32_naive(uint64 size, float32* a, float32 b, float32* c) {
    for (int32 i = 0; i < size; i++) {
        c[i] = a[i] / b;
    }
}

TENSOR_EXPORT void div_i32array_naive(uint64 size, int32* a, int32* b, int32* c) {
    for (int32 i = 0; i < size; i++) {
        c[i] = static_cast<int32>(floor(static_cast<float32>(a[i]) / static_cast<float32>(b[i])));
    }
}

TENSOR_EXPORT void div_i32array_i32_naive(uint64 size, int32* a, int32 b, int32* c) {
    for (int32 i = 0; i < size; i++) {
        c[i] = static_cast<int32>(floor((static_cast<float32>(a[i]) / static_cast<float32>(b))));
    }
}

TENSOR_EXPORT void mul_f32array_f32_naive(uint64 size, float32* a, float32 b, float32* c) {
    for (int32 i = 0; i < size; i++) {
        c[i] = a[i] * b;
    }
}

TENSOR_EXPORT void mul_i32array_i32_naive(uint64 size, int32* a, int32 b, int32* c) {
    for (int32 i = 0; i < size; i++) {
        c[i] = a[i] * b;
    }
}

TENSOR_EXPORT void add_i32array_i32_naive(uint64 size, int32* a, int32 b, int32* c) {
    for (int32 i = 0; i < size; i++) {
        c[i] = a[i] + b;
    }
}

TENSOR_EXPORT void add_f32array_f32_naive(uint64 size, float32* a, float32 b, float32* c) {
    for (int32 i = 0; i < size; i++) {
        c[i] = a[i] + b;
    }
}

TENSOR_EXPORT void sub_f32array_f32_naive(uint64 size, float32* a, float32 b, float32* c) {
    for (int32 i = 0; i < size; i++) {
        c[i] = a[i] - b;
    }
}

TENSOR_EXPORT void sub_i32array_i32_naive(uint64 size, int32* a, int32 b, int32* c) {
    for (int32 i = 0; i < size; i++) {
        c[i] = a[i] - b;
    }
}

TENSOR_EXPORT float32 dot_f32array_naive(uint64 size, float32* a, float32* b) {
    float* c = new float[size];
    mul_f32array_naive(size, a, b, c);
    float d = reduce_f32array_naive(size, c);
    delete[] c;
    return d;
}

TENSOR_EXPORT void sqrt_f32array_naive(uint64 size, float32* a, float32* c) {
    for(int32 i=0; i<size; i++) {
        c[i] = sqrt(a[i]);
    }
}


#endif