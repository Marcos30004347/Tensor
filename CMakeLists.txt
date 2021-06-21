cmake_minimum_required(VERSION 3.10)

project(Tensor)

# Debug config
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")

# Release config
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

add_executable(
    Tensor
    src/main.cpp
)

target_include_directories(Tensor PRIVATE "src/")

# Optimize for current architecture
if(TENSOR_OPTIMIZE_NATIVE)
    if(
        "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang" or
        "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU"
    )
        target_compile_options(Tensor PRIVATE -march=native)
        target_compile_options(Tensor PRIVATE -march=native)
    endif()
endif()


# Tune optimizations for current architecture
if(TENSOR_TUNE_NATIVE)
    if(
        "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang" or
        "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU"
        )
        target_compile_options(Tensor PRIVATE -mtune=native)
    endif()
endif()


# Enable simd extensions for clang and gcc
if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    target_compile_options(Tensor PRIVATE -msse)
    target_compile_options(Tensor PRIVATE -msse2) 
    target_compile_options(Tensor PRIVATE -msse3)
    target_compile_options(Tensor PRIVATE -mavx)
    target_compile_options(Tensor PRIVATE -mavx2)
    target_compile_options(Tensor PRIVATE -mavx512f)
    target_compile_options(Tensor PRIVATE -msse4.1)
endif()


if("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
    target_compile_options(Tensor PRIVATE -msse)
    target_compile_options(Tensor PRIVATE -msse2)
    target_compile_options(Tensor PRIVATE -msse3)
    target_compile_options(Tensor PRIVATE -mavx)
    target_compile_options(Tensor PRIVATE -mavx2)
    target_compile_options(Tensor PRIVATE -mavx512f)
    target_compile_options(Tensor PRIVATE -msse4.1)
endif()


# Enable simd extensions for MSVC
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    target_compile_options(Tensor PRIVATE /arch:SSE)
    target_compile_options(Tensor PRIVATE /arch:SSE2)
    target_compile_options(Tensor PRIVATE /arch:AVX)
    target_compile_options(Tensor PRIVATE /arch:AVX2)
    target_compile_options(Tensor PRIVATE /arch:AVX512)
endif()

# Enable simd extensions for Emscripten
if("${CMAKE_SYSTEM_NAME}" MATCHES "Emscripten")
    target_compile_options(Tensor PRIVATE -msimd128)
endif()
