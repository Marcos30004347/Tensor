#ifdef ANDROID

https://stackoverflow.com/questions/26701262/how-to-check-the-existence-of-neon-on-arm

#error TODO

#include <cpu-features.h>

void test()
{
    bool support_neon = (android_getCpuFamily() == ANDROID_CPU_FAMILY_ARM) && (android_getCpuFeatures() & ANDROID_CPU_ARM_FEATURE_NEON);
}

#endif