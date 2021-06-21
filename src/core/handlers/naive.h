#ifndef NAIVE_H
#define NAIVE_H

#include <cmath>
#include "macros.h"
#include "core/types.h"

TENSOR_EXPORT f32 reduce_f32array_naive(ui64 size, f32* a) {
    f32 r = 0;
    for(i32 i=0; i<size; i++) 
        r += a[i];
    return r;
}

TENSOR_EXPORT i32 reduce_i32array_naive(ui64 size, i32* a) {
    i32 r = 0;
    for(i32 i=0; i<size; i++) 
        r += a[i];
    return r;
}

TENSOR_EXPORT void add_f32array_naive(ui64 size, f32* a, f32* b, f32* c) {
    for (i32 i = 0; i < size; i++) {
        c[i] = a[i] + b[i];
    }
}

TENSOR_EXPORT void add_i32array_naive(ui64 size, i32* a, i32* b, i32* c) {
    for (i32 i = 0; i < size; i++) {
        c[i] = a[i] + b[i];
    }
}

TENSOR_EXPORT void sub_f32array_naive(ui64 size, f32* a, f32* b, f32* c) {
    for (i32 i = 0; i < size; i++) {
        c[i] = a[i] - b[i];
    }
}

TENSOR_EXPORT void sub_i32array_naive(ui64 size, i32* a, i32* b, i32* c) {
    for (i32 i = 0; i < size; i++) {
        c[i] = a[i] - b[i];
    }
}

TENSOR_EXPORT void mul_f32array_naive(ui64 size, f32* a, f32* b, f32* c) {
    for (i32 i = 0; i < size; i++) {
        c[i] = a[i] * b[i];
    }
}

TENSOR_EXPORT void mul_i32array_naive(ui64 size, i32* a, i32* b, i32* c) {
    for (i32 i = 0; i < size; i++) {
        c[i] = a[i] * b[i];
    }
}


TENSOR_EXPORT void div_f32array_naive(ui64 size, f32* a, f32* b, f32* c) {
    for (i32 i = 0; i < size; i++) {
        c[i] = a[i] / b[i];
    }
}

TENSOR_EXPORT void div_f32array_f32_naive(ui64 size, f32* a, f32 b, f32* c) {
    for (i32 i = 0; i < size; i++) {
        c[i] = a[i] / b;
    }
}

TENSOR_EXPORT void div_i32array_naive(ui64 size, i32* a, i32* b, i32* c) {
    for (i32 i = 0; i < size; i++) {
        c[i] = static_cast<i32>(floor(static_cast<f32>(a[i]) / static_cast<f32>(b[i])));
    }
}

TENSOR_EXPORT void div_i32array_i32_naive(ui64 size, i32* a, i32 b, i32* c) {
    for (i32 i = 0; i < size; i++) {
        c[i] = static_cast<i32>(floor((static_cast<f32>(a[i]) / static_cast<f32>(b))));
    }
}

TENSOR_EXPORT void mul_f32array_f32_naive(ui64 size, f32* a, f32 b, f32* c) {
    for (i32 i = 0; i < size; i++) {
        c[i] = a[i] * b;
    }
}

TENSOR_EXPORT void mul_i32array_i32_naive(ui64 size, i32* a, i32 b, i32* c) {
    for (i32 i = 0; i < size; i++) {
        c[i] = a[i] * b;
    }
}

TENSOR_EXPORT void add_i32array_i32_naive(ui64 size, i32* a, i32 b, i32* c) {
    for (i32 i = 0; i < size; i++) {
        c[i] = a[i] + b;
    }
}

TENSOR_EXPORT void add_f32array_f32_naive(ui64 size, f32* a, f32 b, f32* c) {
    for (i32 i = 0; i < size; i++) {
        c[i] = a[i] + b;
    }
}

TENSOR_EXPORT void sub_f32array_f32_naive(ui64 size, f32* a, f32 b, f32* c) {
    for (i32 i = 0; i < size; i++) {
        c[i] = a[i] - b;
    }
}

TENSOR_EXPORT void sub_i32array_i32_naive(ui64 size, i32* a, i32 b, i32* c) {
    for (i32 i = 0; i < size; i++) {
        c[i] = a[i] - b;
    }
}

TENSOR_EXPORT f32 dot_f32array_naive(ui64 size, f32* a, f32* b) {
    float* c = new float[size];
    mul_f32array_naive(size, a, b, c);
    float d = reduce_f32array_naive(size, c);
    delete[] c;
    return d;
}

TENSOR_EXPORT void sqrt_f32array_naive(ui64 size, f32* a, f32* c) {
    for(i32 i=0; i<size; i++) {
        c[i] = sqrt(a[i]);
    }
}


#endif