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

#if defined(WIN32) || defined(__MINGW32__)
	#include <intrin.h>
#elif

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

	 #ifdef AES
		 #include <wmmintrin.h>
	 #endif

	#ifdef AVX
		#include <immintrin.h>
	#endif

#endif

