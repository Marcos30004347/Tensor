#ifndef CORE_H
#define CORE_H

#include "types.h"

// void    (*add_f32array_ptr)(uint64, float32*, float32*, float32*)       = nullptr;
// void    (*add_f32array_f32_ptr)(uint64, float32*, float32, float32*)    = nullptr;
// void    (*add_i32array_ptr)(uint64, int32*, int32*, int32*)             = nullptr;
// void    (*add_i32array_i32_ptr)(uint64, int32*, int32, int32*)          = nullptr;
// void    (*sub_f32array_ptr)(uint64, float32*, float32*, float32*)       = nullptr;
// void    (*sub_f32array_f32_ptr)(uint64, float32*, float32, float32*)    = nullptr;
// void    (*sub_i32array_ptr)(uint64, int32*, int32*, int32*)             = nullptr;
// void    (*sub_i32array_i32_ptr)(uint64, int32*, int32, int32*)          = nullptr;
// void    (*mul_i32array_ptr)(uint64, int32*, int32*, int32*)             = nullptr;
// void    (*mul_i32array_i32_ptr)(uint64, int32*, int32, int32*)          = nullptr;
// void    (*mul_f32array_ptr)(uint64, float32*, float32*, float32*)       = nullptr;
// void    (*mul_f32array_f32_ptr)(uint64, float32*, float32, float32*)    = nullptr;
// void    (*div_i32array_ptr)(uint64, int32*, int32*, int32*)             = nullptr;
// void    (*div_i32array_i32_ptr)(uint64, int32*, int32, int32*)          = nullptr;
// void    (*div_f32array_ptr)(uint64, float32*, float32*, float32*)       = nullptr;
// void    (*div_f32array_f32_ptr)(uint64, float32*, float32, float32*)    = nullptr;
// void    (*sqrt_f32array_ptr)(uint64, float32*, float32*)                = nullptr;
// int32   (*reduce_i32array_ptr)(uint64, int32*)                          = nullptr;
// float32 (*reduce_f32array_ptr)(int64, float32*)                         = nullptr;
// float32 (*dot_f32array_ptr)(uint64, float32*, float32*)                 = nullptr;

static void (*resolve_memcpy (void)) (void)
{
  __builtin_cpu_init ();
  if (__builtin_cpu_supports ("ssse3"))
    return ssse3_memcpy; // super fast memcpy with ssse3 instructions.
  else
    return default_memcpy;
}

[[gnu::ifunc("resolve_memcpy")]]
void *memcpy (void *, const void *, unsigned long) __attribute__ ((ifunc ("resolve_memcpy")));

inline float32 reduce_f32array(int64 size, float32* a) {
    return reduce_f32array_ptr(size, a);
}

inline int32 reduce_i32array(uint64 size, int32* a) {
    return reduce_i32array_ptr(size, a);
}

inline void add_f32array(uint64 size, float32* a, float32* b, float32* c) {
    return add_f32array_ptr(size, a, b, c);
}

inline void add_f32array_f32(uint64 size, float32* a, float32 b, float32* c) {
    return add_f32array_f32_ptr(size, a, b, c);
}

inline void add_i32array(uint64 size, int32* a, int32* b, int32* c) {
    return add_i32array_ptr(size, a, b, c);
}

inline void add_i32array_i32(uint64 size, int32* a, int32 b, int32* c) {
    return add_i32array_i32_ptr(size, a, b, c);
}

inline void sub_f32array(uint64 size, float32* a, float32* b, float32* c) {
    return sub_f32array_ptr(size, a, b, c);
}

inline void sub_f32array_f32(uint64 size, float32* a, float32 b, float32* c) {
    return sub_f32array_f32_ptr(size, a, b, c);
}

inline void sub_i32array(uint64 size, int32* a, int32* b, int32* c) {
    return sub_i32array_ptr(size, a, b, c);
}

inline void sub_i32array_i32(uint64 size, int32* a, int32 b, int32* c) {
    return sub_i32array_i32_ptr(size, a, b, c);
}

inline void mul_i32array(uint64 size, int32* a, int32* b, int32* c) {
    return mul_i32array_ptr(size, a, b, c);
}

inline void mul_i32array_i32(uint64 size, int32* a, int32 b, int32* c) {
    return mul_i32array_i32_ptr(size, a, b, c);
}

inline void mul_f32array(uint64 size, float32* a, float32* b, float32* c) {
    return mul_f32array_ptr(size, a, b, c);
}

inline void mul_f32array_f32(uint64 size, float32* a, float32 b, float32* c) {
    return mul_f32array_f32_ptr(size, a, b, c);
}

inline void div_i32array(uint64 size, int32* a, int32* b, int32* c) {
    return div_i32array_ptr(size, a, b, c);
}

inline void div_i32array_i32(uint64 size, int32* a, int32 b, int32* c) {
    return div_i32array_i32_ptr(size, a, b, c);
}

inline void div_f32array(uint64 size, float32* a, float32* b, float32* c) {
    return div_f32array_ptr(size, a, b, c);
}

inline void div_f32array_f32(uint64 size, float32* a, float32 b, float32* c) {
    return div_f32array_f32_ptr(size, a, b, c);
}

inline float32 dot_f32array(uint64 size, float32* a, float32* b) {
    return dot_f32array_ptr(size, a, b);
}

inline void sqrt_f32array(uint64 size, float32* a, float32* c) {
    return sqrt_f32array_ptr(size, a, c);
}

void init_core_lib()
{
    #if defined(__x86_64__) || defined(__i386__) 
    __builtin_cpu_init();
    #endif
}

#endif