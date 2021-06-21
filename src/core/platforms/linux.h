#if defined(__unix__) || defined(__linux__) || defined(_POSIX_VERSION) || (defined(__APPLE__) && defined(TARGET_OS_MAC))

#include "../types.h"

#include "../handlers/avx.h"
#include "../handlers/sse.h"
#include "../handlers/naive.h"

#if defined(__x86_64__) || defined(__i386__)

extern "C" {

static i32 (*resolve_reduce_i32array (void)) (ui64, i32*) {
    __builtin_cpu_init ();

    if (
        __builtin_cpu_supports ("avx") &&
        __builtin_cpu_supports ("avx2")
    ) return reduce_i32array_avx; 
    else if (
        __builtin_cpu_supports ("sse") &&
        __builtin_cpu_supports ("sse2") &&
        __builtin_cpu_supports ("sse3") &&
        __builtin_cpu_supports ("ssse3") &&
        __builtin_cpu_supports ("sse4.1") &&
        __builtin_cpu_supports ("sse4.2")
    ) return reduce_i32array_sse; 

    return reduce_i32array_naive; 
}

static f32 (*resolve_reduce_f32array (void)) (ui64, f32*) {
    __builtin_cpu_init ();

    if (
        __builtin_cpu_supports ("avx") &&
        __builtin_cpu_supports ("avx2")
    ) return reduce_f32array_avx; 
    else if (
        __builtin_cpu_supports ("sse") &&
        __builtin_cpu_supports ("sse2") &&
        __builtin_cpu_supports ("sse3") &&
        __builtin_cpu_supports ("ssse3") &&
        __builtin_cpu_supports ("sse4.1") &&
        __builtin_cpu_supports ("sse4.2")
    ) return reduce_f32array_sse; 

    return reduce_f32array_naive; 
}

static f32 (*resolve_dot_f32array (void)) (ui64, f32*, f32*) {
    __builtin_cpu_init ();

    if (
        __builtin_cpu_supports ("avx") &&
        __builtin_cpu_supports ("avx2")
    ) return dot_f32array_avx; 
    else if (
        __builtin_cpu_supports ("sse") &&
        __builtin_cpu_supports ("sse2") &&
        __builtin_cpu_supports ("sse3") &&
        __builtin_cpu_supports ("ssse3") &&
        __builtin_cpu_supports ("sse4.1") &&
        __builtin_cpu_supports ("sse4.2")
    ) return dot_f32array_sse; 

    return dot_f32array_naive; 
}

static void (*resolve_add_f32array (void)) (ui64, f32*, f32*, f32*) {
    __builtin_cpu_init ();

    if (
        __builtin_cpu_supports ("avx") &&
        __builtin_cpu_supports ("avx2")
    ) return add_f32array_avx; 
    else if (
        __builtin_cpu_supports ("sse") &&
        __builtin_cpu_supports ("sse2") &&
        __builtin_cpu_supports ("sse3") &&
        __builtin_cpu_supports ("ssse3") &&
        __builtin_cpu_supports ("sse4.1") &&
        __builtin_cpu_supports ("sse4.2")
    ) return add_f32array_sse; 

    return add_f32array_naive; 
}

static void (*resolve_add_i32array (void)) (ui64, i32*, i32*, i32*) {
    __builtin_cpu_init ();

    if (
        __builtin_cpu_supports ("avx") &&
        __builtin_cpu_supports ("avx2")
    ) return add_i32array_avx; 
    else if (
        __builtin_cpu_supports ("sse") &&
        __builtin_cpu_supports ("sse2") &&
        __builtin_cpu_supports ("sse3") &&
        __builtin_cpu_supports ("ssse3") &&
        __builtin_cpu_supports ("sse4.1") &&
        __builtin_cpu_supports ("sse4.2")
    ) return add_i32array_sse; 

    return add_i32array_naive; 
}

static void (*resolve_add_i32array_i32 (void)) (ui64, i32*, i32, i32*) {
    __builtin_cpu_init ();

    if (
        __builtin_cpu_supports ("avx") &&
        __builtin_cpu_supports ("avx2")
    ) return add_i32array_i32_avx; 
    else if (
        __builtin_cpu_supports ("sse") &&
        __builtin_cpu_supports ("sse2") &&
        __builtin_cpu_supports ("sse3") &&
        __builtin_cpu_supports ("ssse3") &&
        __builtin_cpu_supports ("sse4.1") &&
        __builtin_cpu_supports ("sse4.2")
    ) return add_i32array_i32_sse; 

    return add_i32array_i32_naive; 
}

static void (*resolve_add_f32array_f32 (void)) (ui64, f32*, f32, f32*) {
    __builtin_cpu_init ();

    if (
        __builtin_cpu_supports ("avx") &&
        __builtin_cpu_supports ("avx2")
    ) return add_f32array_f32_avx; 
    else if (
        __builtin_cpu_supports ("sse") &&
        __builtin_cpu_supports ("sse2") &&
        __builtin_cpu_supports ("sse3") &&
        __builtin_cpu_supports ("ssse3") &&
        __builtin_cpu_supports ("sse4.1") &&
        __builtin_cpu_supports ("sse4.2")
    ) return add_f32array_f32_sse; 

    return add_f32array_f32_naive; 
}

static void (*resolve_sub_f32array (void)) (ui64, f32*, f32*, f32*) {
    __builtin_cpu_init ();

    if (
        __builtin_cpu_supports ("avx") &&
        __builtin_cpu_supports ("avx2")
    ) return sub_f32array_avx; 
    else if (
        __builtin_cpu_supports ("sse") &&
        __builtin_cpu_supports ("sse2") &&
        __builtin_cpu_supports ("sse3") &&
        __builtin_cpu_supports ("ssse3") &&
        __builtin_cpu_supports ("sse4.1") &&
        __builtin_cpu_supports ("sse4.2")
    ) return sub_f32array_sse; 

    return sub_f32array_naive; 
}

static void (*resolve_sub_i32array (void)) (ui64, i32*, i32*, i32*) {
    __builtin_cpu_init ();

    if (
        __builtin_cpu_supports ("avx") &&
        __builtin_cpu_supports ("avx2")
    ) return sub_i32array_avx; 
    else if (
        __builtin_cpu_supports ("sse") &&
        __builtin_cpu_supports ("sse2") &&
        __builtin_cpu_supports ("sse3") &&
        __builtin_cpu_supports ("ssse3") &&
        __builtin_cpu_supports ("sse4.1") &&
        __builtin_cpu_supports ("sse4.2")
    ) return sub_i32array_sse; 

    return sub_i32array_naive; 
}

static void (*resolve_sub_i32array_i32 (void)) (ui64, i32*, i32, i32*) {
    __builtin_cpu_init ();

    if (
        __builtin_cpu_supports ("avx") &&
        __builtin_cpu_supports ("avx2")
    ) return sub_i32array_i32_avx; 
    else if (
        __builtin_cpu_supports ("sse") &&
        __builtin_cpu_supports ("sse2") &&
        __builtin_cpu_supports ("sse3") &&
        __builtin_cpu_supports ("ssse3") &&
        __builtin_cpu_supports ("sse4.1") &&
        __builtin_cpu_supports ("sse4.2")
    ) return sub_i32array_i32_sse; 

    return sub_i32array_i32_naive; 
}

static void (*resolve_sub_f32array_f32 (void)) (ui64, f32*, f32, f32*) {
    __builtin_cpu_init ();

    if (
        __builtin_cpu_supports ("avx") &&
        __builtin_cpu_supports ("avx2")
    ) return sub_f32array_f32_avx; 
    else if (
        __builtin_cpu_supports ("sse") &&
        __builtin_cpu_supports ("sse2") &&
        __builtin_cpu_supports ("sse3") &&
        __builtin_cpu_supports ("ssse3") &&
        __builtin_cpu_supports ("sse4.1") &&
        __builtin_cpu_supports ("sse4.2")
    ) return sub_f32array_f32_sse; 

    return sub_f32array_f32_naive; 
}

static void (*resolve_mul_f32array (void)) (ui64, f32*, f32*, f32*) {
    __builtin_cpu_init ();

    if (
        __builtin_cpu_supports ("avx") &&
        __builtin_cpu_supports ("avx2")
    ) return mul_f32array_avx; 
    else if (
        __builtin_cpu_supports ("sse") &&
        __builtin_cpu_supports ("sse2") &&
        __builtin_cpu_supports ("sse3") &&
        __builtin_cpu_supports ("ssse3") &&
        __builtin_cpu_supports ("sse4.1") &&
        __builtin_cpu_supports ("sse4.2")
    ) return mul_f32array_sse; 

    return mul_f32array_naive; 
}

static void (*resolve_mul_i32array (void)) (ui64, i32*, i32*, i32*) {
    __builtin_cpu_init ();

    if (
        __builtin_cpu_supports ("avx") &&
        __builtin_cpu_supports ("avx2")
    ) return mul_i32array_avx; 
    else if (
        __builtin_cpu_supports ("sse") &&
        __builtin_cpu_supports ("sse2") &&
        __builtin_cpu_supports ("sse3") &&
        __builtin_cpu_supports ("ssse3") &&
        __builtin_cpu_supports ("sse4.1") &&
        __builtin_cpu_supports ("sse4.2")
    ) return mul_i32array_sse; 

    return mul_i32array_naive; 
}

static void (*resolve_mul_i32array_i32 (void)) (ui64, i32*, i32, i32*) {
    __builtin_cpu_init ();

    if (
        __builtin_cpu_supports ("avx") &&
        __builtin_cpu_supports ("avx2")
    ) return mul_i32array_i32_avx; 
    else if (
        __builtin_cpu_supports ("sse") &&
        __builtin_cpu_supports ("sse2") &&
        __builtin_cpu_supports ("sse3") &&
        __builtin_cpu_supports ("ssse3") &&
        __builtin_cpu_supports ("sse4.1") &&
        __builtin_cpu_supports ("sse4.2")
    ) return mul_i32array_i32_sse; 

    return mul_i32array_i32_naive; 
}

static void (*resolve_mul_f32array_f32 (void)) (ui64, f32*, f32, f32*) {
    __builtin_cpu_init ();

    if (
        __builtin_cpu_supports ("avx") &&
        __builtin_cpu_supports ("avx2")
    ) return mul_f32array_f32_avx; 
    else if (
        __builtin_cpu_supports ("sse") &&
        __builtin_cpu_supports ("sse2") &&
        __builtin_cpu_supports ("sse3") &&
        __builtin_cpu_supports ("ssse3") &&
        __builtin_cpu_supports ("sse4.1") &&
        __builtin_cpu_supports ("sse4.2")
    ) return mul_f32array_f32_sse; 

    return mul_f32array_f32_naive; 
}

static void (*resolve_div_f32array (void)) (ui64, f32*, f32*, f32*) {
    __builtin_cpu_init ();

    if (
        __builtin_cpu_supports ("avx") &&
        __builtin_cpu_supports ("avx2")
    ) return div_f32array_avx; 
    else if (
        __builtin_cpu_supports ("sse") &&
        __builtin_cpu_supports ("sse2") &&
        __builtin_cpu_supports ("sse3") &&
        __builtin_cpu_supports ("ssse3") &&
        __builtin_cpu_supports ("sse4.1") &&
        __builtin_cpu_supports ("sse4.2")
    ) return div_f32array_sse; 

    return div_f32array_naive; 
}

static void (*resolve_div_i32array (void)) (ui64, i32*, i32*, i32*) {
    __builtin_cpu_init ();

    if (
        __builtin_cpu_supports ("avx") &&
        __builtin_cpu_supports ("avx2")
    ) return div_i32array_avx; 
    else if (
        __builtin_cpu_supports ("sse") &&
        __builtin_cpu_supports ("sse2") &&
        __builtin_cpu_supports ("sse3") &&
        __builtin_cpu_supports ("ssse3") &&
        __builtin_cpu_supports ("sse4.1") &&
        __builtin_cpu_supports ("sse4.2")
    ) return div_i32array_sse; 

    return div_i32array_naive; 
}

static void (*resolve_div_i32array_i32 (void)) (ui64, i32*, i32, i32*) {
    __builtin_cpu_init ();

    if (
        __builtin_cpu_supports ("avx") &&
        __builtin_cpu_supports ("avx2")
    ) return div_i32array_i32_avx; 
    else if (
        __builtin_cpu_supports ("sse") &&
        __builtin_cpu_supports ("sse2") &&
        __builtin_cpu_supports ("sse3") &&
        __builtin_cpu_supports ("ssse3") &&
        __builtin_cpu_supports ("sse4.1") &&
        __builtin_cpu_supports ("sse4.2")
    ) return div_i32array_i32_sse; 

    return div_i32array_i32_naive; 
}

static void (*resolve_div_f32array_f32 (void)) (ui64, f32*, f32, f32*) {
    __builtin_cpu_init ();

    if (
        __builtin_cpu_supports ("avx") &&
        __builtin_cpu_supports ("avx2")
    ) return div_f32array_f32_avx; 
    else if (
        __builtin_cpu_supports ("sse") &&
        __builtin_cpu_supports ("sse2") &&
        __builtin_cpu_supports ("sse3") &&
        __builtin_cpu_supports ("ssse3") &&
        __builtin_cpu_supports ("sse4.1") &&
        __builtin_cpu_supports ("sse4.2")
    ) return div_f32array_f32_sse; 

    return div_f32array_f32_naive; 
}

static void (*resolve_sqrt_f32array (void)) (ui64, f32*, f32*) {
    __builtin_cpu_init ();

    if (
        __builtin_cpu_supports ("avx") &&
        __builtin_cpu_supports ("avx2")
    ) return sqrt_f32array_avx; 
    else if (
        __builtin_cpu_supports ("sse") &&
        __builtin_cpu_supports ("sse2") &&
        __builtin_cpu_supports ("sse3") &&
        __builtin_cpu_supports ("ssse3") &&
        __builtin_cpu_supports ("sse4.1") &&
        __builtin_cpu_supports ("sse4.2")
    ) return sqrt_f32array_sse; 

    return sqrt_f32array_naive; 
}

}

void sqrt_f32array(ui64, f32*, f32*)
    __attribute__ ((ifunc ("resolve_sqrt_f32array")));
void div_f32array_f32(ui64, f32*, f32, f32*)
    __attribute__ ((ifunc ("resolve_div_f32array_f32")));
void div_i32array_i32(ui64, i32*, i32, i32*) 
    __attribute__ ((ifunc ("resolve_div_i32array_i32")));
void div_i32array(ui64, i32*, i32*, i32*) 
    __attribute__ ((ifunc ("resolve_div_i32array")));
void div_f32array(ui64, f32*, f32*, f32*) 
    __attribute__ ((ifunc ("resolve_div_f32array")));
void mul_f32array_f32(ui64, f32*, f32, f32*) 
    __attribute__ ((ifunc ("resolve_mul_f32array_f32")));
void mul_i32array_i32(ui64, i32*, i32, i32*) 
    __attribute__ ((ifunc ("resolve_mul_i32array_i32")));
void mul_i32array(ui64, i32*, i32*, i32*) 
    __attribute__ ((ifunc ("resolve_mul_i32array")));
void mul_f32array(ui64, f32*, f32*, f32*) 
    __attribute__ ((ifunc ("resolve_mul_f32array")));
void sub_f32array_f32(ui64, f32*, f32, f32*) 
    __attribute__ ((ifunc ("resolve_sub_f32array_f32")));
void sub_i32array_i32(ui64, i32*, i32, i32*) 
    __attribute__ ((ifunc ("resolve_sub_i32array_i32")));
void sub_i32array(ui64, i32*, i32*, i32*) 
    __attribute__ ((ifunc ("resolve_sub_i32array")));
void sub_f32array(ui64, f32*, f32*, f32*) 
    __attribute__ ((ifunc ("resolve_sub_f32array")));
void add_f32array_f32(ui64, f32*, f32, f32*) 
    __attribute__ ((ifunc ("resolve_add_f32array_f32")));
void add_i32array_i32(ui64, i32*, i32, i32*) 
    __attribute__ ((ifunc ("resolve_add_i32array_i32")));
void add_i32array(ui64, i32*, i32*, i32*) 
    __attribute__ ((ifunc ("resolve_add_i32array")));
void add_f32array(ui64, f32*, f32*, f32*) 
    __attribute__ ((ifunc ("resolve_add_f32array")));
f32 dot_f32array(ui64, f32*, f32*) 
    __attribute__ ((ifunc ("resolve_dot_f32array")));
f32 reduce_f32array(ui64, f32*) 
    __attribute__ ((ifunc ("resolve_reduce_f32array")));
i32 reduce_i32array(ui64, i32*) 
    __attribute__ ((ifunc ("resolve_reduce_i32array")));

void setup_core_lib(){}


#endif

#if defined(__arm__) || defined(_ARM) || defined(_M_ARM)

#error TODO

// https://community.arm.com/developer/tools-software/oss-platforms/b/android-blog/posts/runtime-detection-of-cpu-features-on-an-armv8-a-cpu
// https://stackoverflow.com/questions/26701262/how-to-check-the-existence-of-neon-on-arm

#include <dlfcn.h>
#include <sys/auxv.h>
#include <asm/hwcap.h>


void setup_core_lib(){
    bool t = getauxval(AT_HWCAP) & HWCAP_NEON;

    void* handle = reinterpret_cast<void(*)()> dlopen(NULL, RTLD_NOW);
}

#endif



#endif