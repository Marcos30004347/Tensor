
// #if (defined(_M_AMD64) || defined(_M_X64) || defined(__amd64)) && ! 
//     defined(__x86_64__)
// #define __x86_64__ 1
// #endif


// #ifndef SIMD_INSTR_SET
// #if defined (__AVX2__)
//     #define SIMD_INSTR_SET 8
// #elif defined ( __AVX__ )
//     #define SIMD_INSTR_SET 7
// #elif defined ( __SSE4_2__ )
//     #define SIMD_INSTR_SET 6
// #elif defined ( __SSE4_1__ )
//     #define SIMD_INSTR_SET 5
// #elif defined ( __SSSE3__ )
//     #define SIMD_INSTR_SET 4
// #elif defined ( __SSE3__ )
//     #define SIMD_INSTR_SET 3
// #elif defined ( __SSE2__ ) || defined ( __x86_64__ )
//     #define SIMD_INSTR_SET 2 //this is where the color has changed
// #elif defined ( __SSE__ )
//     #define SIMD_INSTR_SET 1
// #elif defined ( _M_IX86_FP )    
//    #define SIMD_INSTR_SET _M_IX86_FP
// #else
//    #define SIMD_INSTR_SET 0
// #endif // instruction set defines
// #endif // SIMD_INSTR_SET

// #define MMX
#define SSE
#define SSE2
#define SSE3
#define SSSE3
#define SSE4_1
#define SSE4_2
#define SSE4A

// #define AES

#define AVX

// #ifdef MMX
// #include <mmintrin.h>
// #endif

#ifdef SSE
#include <xmmintrin.h>
#endif

#ifdef SSE2
#include <emmintrin.h>
#endif

#ifdef SSE3
#include <pmmintrin.h>
#endif

#ifdef SSSE3
#include <tmmintrin.h>
#endif

#ifdef SSE4_1
#include <smmintrin.h>
#endif

#ifdef SSE4_2
#include <nmmintrin.h>
#endif

#ifdef SSE4A
#include <ammintrin.h>
#endif

// #ifdef AES
// #include <wmmintrin.h>
// #endif

#ifdef AVX
#include <immintrin.h>
#endif


