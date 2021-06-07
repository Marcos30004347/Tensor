#ifndef NAIVE_H
#define NAIVE_H

#include <cmath>
#include "types.h"

float32 reduce_f32array(int64 size, float32* a) {
    float32 r = 0;
    for(int32 i=0; i<size; i++) 
        r += a[i];
    return r;
}

int32 reduce_i32array(unsigned size, int32* a) {
    int32 r = 0;
    for(int32 i=0; i<size; i++) 
        r += a[i];
    return r;
}

void add_f32array(unsigned size, float32* a, float32* b, float32* c) {
    for(int32 i=0; i<size; i++) {
        c[i] = a[i] + b[i];
    }
}

void add_i32array(unsigned size, int32* a, int32* b, int32* c) {
    for(int32 i=0; i<size; i++) {
        c[i] = a[i] + b[i];
    }
}


void sub_f32array(unsigned size, float32* a, float32* b, float32* c) {
    for(int32 i=0; i<size; i++) {
        c[i] = a[i] - b[i];
    }
}

void sub_i32array(unsigned size, int32* a, int32* b, int32* c) {
    for(int32 i=0; i<size; i++) {
        c[i] = a[i] - b[i];
    }
}


void mul_f32array(unsigned size, float32* a, float32* b, float32* c) {
    for(int32 i=0; i<size; i++) {
        c[i] = a[i] * b[i];
    }
}

void mul_i32array(unsigned size, int32* a, int32* b, int32* c) {
    for(int32 i=0; i<size; i++) {
        c[i] = a[i] * b[i];
    }
}


void div_f32array(unsigned size, float32* a, float32* b, float32* c) {
    for(int32 i=0; i<size; i++) {
        c[i] = a[i] / b[i];
    }
}

void div_f32array(unsigned size, float32* a, float32 b, float32* c) {
    for(int32 i=0; i<size; i++) {
        c[i] = a[i] / b;
    }
}

void div_i32array(unsigned size, int32* a, int32* b, int32* c) {
    for(int32 i=0; i<size; i++) {
        c[i] = floor(a[i] / (float32)b[i]);
    }
}

void div_i32array_i32(unsigned size, int32* a, int32 b, int32* c) {
    for(int32 i=0; i<size; i++) {
        c[i] = floor(a[i] / (float32)b);
    }
}

void mul_f32array_f32(unsigned size, float32* a, float32 b, float32* c) {
    for(int32 i=0; i<size; i++) {
        c[i] = a[i] * b;
    }
}

void mul_i32array_i32(unsigned size, int32* a, int32 b, int32* c) {
    for(int32 i=0; i<size; i++) {
        c[i] = a[i] * b;
    }
}

void add_i32array_i32(unsigned size, int32* a, int32 b, int32* c) {
    for(int32 i=0; i<size; i++) {
        c[i] = a[i] + b;
    }
}

void add_f32array_f32(unsigned size, float32* a, float32 b, float32* c) {
    for(int32 i=0; i<size; i++) {
        c[i] = a[i] + b;
    }
}

void sub_f32array_f32(unsigned size, float32* a, float32 b, float32* c) {
    for(int32 i=0; i<size; i++) {
        c[i] = a[i] - b;
    }
}

void sub_i32array_i32(unsigned size, int32* a, int32 b, int32* c) {
    for(int32 i=0; i<size; i++) {
        c[i] = a[i] - b;
    }
}

float dot_f32array(unsigned size, float32* a, float32* b) {
    float* c = new float[size];
    mul_f32array(size, a, b, c);
    float d = reduce_f32array(size, c);
    delete[] c;
    return d;
}

void sqrt_f32array(unsigned size, float32* a, float32* c) {
    for(int32 i=0; i<size; i++) {
        c[i] = sqrt(a[i]);
    }
}


#endif