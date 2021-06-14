cmake_minimum_required(VERSION 3.10)

project(Tensor)

add_executable(Tensor main.cpp "core/windows.h" "core/macros.h")

if(MSVC)
    target_compile_options(Tensor PRIVATE  /arch:AVX)
    target_compile_options(Tensor PRIVATE  /arch:AVX2)
else()
    target_compile_options(Tensor PRIVATE  -msse4.1)
endif()
