#ifndef MACROS_H
#define MACROS_H

#if defined(_WIN32) || defined(__WIN32__)
#    define  TENSOR_EXPORT extern "C" __declspec(dllexport)
#    define  TENSOR_IMPORT extern "C" __declspec(dllimport)
#elif defined(linux) || defined(__linux)
# define TENSOR_EXPORT
#endif

#endif