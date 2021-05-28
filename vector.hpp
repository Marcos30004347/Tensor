
// static void (*resolve_memcpy (void)) (void)
// {
//   // ifunc resolvers fire before constructors, explicitly call the init
//   // function.
//   __builtin_cpu_init ();
//   if (__builtin_cpu_supports ("ssse3"))
//     return ssse3_memcpy; // super fast memcpy with ssse3 instructions.
//   else
//     return default_memcpy;
// }

// void t() {
//     __builtin_cpu_init();

//     const bool sse    = __builtin_cpu_supports("sse");
//     const bool sse2   = __builtin_cpu_supports("sse2");
//     const bool sse3   = __builtin_cpu_supports("sse3");
//     const bool sse4_1 = __builtin_cpu_supports("sse4.1");
//     const bool sse4_2 = __builtin_cpu_supports("sse4.2");
//     const bool avx    = __builtin_cpu_supports("avx");
//     const bool avx2   = __builtin_cpu_supports("avx2");

//     printf("%i\n", sse);
//     printf("%i\n", sse2);
//     printf("%i\n", sse3);
//     printf("%i\n", sse4_1);
//     printf("%i\n", sse4_2);
//     printf("%i\n", avx);
//     printf("%i\n", avx2);
// }
