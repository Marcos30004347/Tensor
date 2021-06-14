#include "platforms/windows.h"

#include "types.h"

#if defined(__AVX__) && defined(__AVX2__)
#include "avx.h"
#endif

#if defined(_M_AMD64 ) || defined(_M_X64) || defined(_M_IX86_FP)
#include "sse.h"
#endif

#include "naive.h"

int32	(__stdcall* reduce_i32array)(uint64, int32*);
float32	(__stdcall* reduce_f32array)(uint64, float32*);
float32	(__stdcall* dot_f32array)(uint64, float32*, float32*);

void(__stdcall* add_f32array)(uint64, float32*, float32*, float32*);
void(__stdcall* add_i32array)(uint64, int32*, int32*, int32*);
void(__stdcall* add_i32array_i32)(uint64, int32*, int32, int32*);
void(__stdcall* add_f32array_f32)(uint64, float32*, float32, float32*);

void(__stdcall* sub_f32array)(uint64, float32*, float32*, float32*);
void(__stdcall* sub_i32array)(uint64, int32*, int32*, int32*);
void(__stdcall* sub_f32array_f32)(uint64, float32*, float32, float32*);
void(__stdcall* sub_i32array_i32)(uint64, int32*, int32, int32*);

void(__stdcall* mul_f32array)(uint64, float32*, float32*, float32*);
void(__stdcall* mul_i32array)(uint64, int32*, int32*, int32*);
void(__stdcall* mul_f32array_f32)(uint64, float32*, float32, float32*);
void(__stdcall* mul_i32array_i32)(uint64, int32*, int32, int32*);

void(__stdcall* div_f32array)(uint64, float32*, float32*, float32*);
void(__stdcall* div_i32array)(uint64, int32*, int32*, int32*);
void(__stdcall* div_i32array_i32)(uint64, int32*, int32, int32*);
void(__stdcall* div_f32array_f32)(uint64, float32*, float32, float32*);

void(__stdcall* sqrt_f32array)(uint64, float32* a, float32* c);

void setup_core_lib()
{
	if (InstructionSet::AVX())
	{
		reduce_f32array = (float32(*)(uint64, float32*))GetProcAddress(getThisModuleHandle(), "reduce_f32array_avx");
		reduce_i32array = (int32(*)(uint64, int32*))GetProcAddress(getThisModuleHandle(), "reduce_i32array_avx");
		add_f32array = (void(*)(uint64, float32*, float32*, float32*))GetProcAddress(getThisModuleHandle(), "add_f32array_avx");
		add_i32array = (void(*)(uint64, int32*, int32*, int32*))GetProcAddress(getThisModuleHandle(), "add_i32array_avx");
		add_i32array_i32 = (void(*)(uint64, int32*, int32, int32*))GetProcAddress(getThisModuleHandle(), "add_i32array_i32_avx");
		add_f32array_f32 = (void(*)(uint64, float32*, float32, float32*))GetProcAddress(getThisModuleHandle(), "add_f32array_f32_avx");
		sub_f32array = (void(*)(uint64, float32*, float32*, float32*))GetProcAddress(getThisModuleHandle(), "sub_f32array_avx");
		sub_i32array = (void(*)(uint64, int32*, int32*, int32*))GetProcAddress(getThisModuleHandle(), "sub_i32array_avx");
		sub_i32array_i32 = (void(*)(uint64, int32*, int32, int32*))GetProcAddress(getThisModuleHandle(), "sub_i32array_i32_avx");
		sub_f32array_f32 = (void(*)(uint64, float32*, float32, float32*))GetProcAddress(getThisModuleHandle(), "sub_f32array_f32_avx");
		mul_f32array = (void(*)(uint64, float32*, float32*, float32*))GetProcAddress(getThisModuleHandle(), "mul_f32array_avx");
		mul_i32array = (void(*)(uint64, int32*, int32*, int32*))GetProcAddress(getThisModuleHandle(), "mul_i32array_avx");
		mul_i32array_i32 = (void(*)(uint64, int32*, int32, int32*))GetProcAddress(getThisModuleHandle(), "mul_i32array_i32_avx");
		mul_f32array_f32 = (void(*)(uint64, float32*, float32, float32*))GetProcAddress(getThisModuleHandle(), "mul_f32array_f32_avx");
		div_f32array = (void(*)(uint64, float32*, float32*, float32*))GetProcAddress(getThisModuleHandle(), "div_f32array_avx");
		div_i32array = (void(*)(uint64, int32*, int32*, int32*))GetProcAddress(getThisModuleHandle(), "div_i32array_avx");
		div_i32array_i32 = (void(*)(uint64, int32*, int32, int32*))GetProcAddress(getThisModuleHandle(), "div_i32array_i32_avx");
		div_f32array_f32 = (void(*)(uint64, float32*, float32, float32*))GetProcAddress(getThisModuleHandle(), "div_f32array_f32_avx");
	}
	else if (InstructionSet::SSE())
	{
		reduce_f32array = (float32(*)(uint64, float32*))GetProcAddress(getThisModuleHandle(), "reduce_f32array_sse");
		reduce_i32array = (int32(*)(uint64, int32*))GetProcAddress(getThisModuleHandle(), "reduce_i32array_sse");
		add_f32array = (void(*)(uint64, float32*, float32*, float32*))GetProcAddress(getThisModuleHandle(), "add_f32array_sse");
		add_i32array = (void(*)(uint64, int32*, int32*, int32*))GetProcAddress(getThisModuleHandle(), "add_i32array_sse");
		add_i32array_i32 = (void(*)(uint64, int32*, int32, int32*))GetProcAddress(getThisModuleHandle(), "add_i32array_i32_sse");
		add_f32array_f32 = (void(*)(uint64, float32*, float32, float32*))GetProcAddress(getThisModuleHandle(), "add_f32array_f32_sse");
		sub_f32array = (void(*)(uint64, float32*, float32*, float32*))GetProcAddress(getThisModuleHandle(), "sub_f32array_sse");
		sub_i32array = (void(*)(uint64, int32*, int32*, int32*))GetProcAddress(getThisModuleHandle(), "sub_i32array_sse");
		sub_i32array_i32 = (void(*)(uint64, int32*, int32, int32*))GetProcAddress(getThisModuleHandle(), "sub_i32array_i32_sse");
		sub_f32array_f32 = (void(*)(uint64, float32*, float32, float32*))GetProcAddress(getThisModuleHandle(), "sub_f32array_f32_sse");
		mul_f32array = (void(*)(uint64, float32*, float32*, float32*))GetProcAddress(getThisModuleHandle(), "mul_f32array_sse");
		mul_i32array = (void(*)(uint64, int32*, int32*, int32*))GetProcAddress(getThisModuleHandle(), "mul_i32array_sse");
		mul_i32array_i32 = (void(*)(uint64, int32*, int32, int32*))GetProcAddress(getThisModuleHandle(), "mul_i32array_i32_sse");
		mul_f32array_f32 = (void(*)(uint64, float32*, float32, float32*))GetProcAddress(getThisModuleHandle(), "mul_f32array_f32_sse");
		div_f32array = (void(*)(uint64, float32*, float32*, float32*))GetProcAddress(getThisModuleHandle(), "div_f32array_sse");
		div_i32array = (void(*)(uint64, int32*, int32*, int32*))GetProcAddress(getThisModuleHandle(), "div_i32array_sse");
		div_i32array_i32 = (void(*)(uint64, int32*, int32, int32*))GetProcAddress(getThisModuleHandle(), "div_i32array_i32_sse");
		div_f32array_f32 = (void(*)(uint64, float32*, float32, float32*))GetProcAddress(getThisModuleHandle(), "div_f32array_f32_sse");
	}
	else
	{
		reduce_f32array = (float32(*)(uint64, float32*))GetProcAddress(getThisModuleHandle(), "reduce_f32array_naive");
		reduce_i32array = (int32(*)(uint64, int32*))GetProcAddress(getThisModuleHandle(), "reduce_i32array_naive");
		add_f32array = (void(*)(uint64, float32*, float32*, float32*))GetProcAddress(getThisModuleHandle(), "add_f32array_naive");
		add_i32array = (void(*)(uint64, int32*, int32*, int32*))GetProcAddress(getThisModuleHandle(), "add_i32array_naive");
		add_i32array_i32 = (void(*)(uint64, int32*, int32, int32*))GetProcAddress(getThisModuleHandle(), "add_i32array_i32_naive");
		add_f32array_f32 = (void(*)(uint64, float32*, float32, float32*))GetProcAddress(getThisModuleHandle(), "add_f32array_f32_naive");
		sub_f32array = (void(*)(uint64, float32*, float32*, float32*))GetProcAddress(getThisModuleHandle(), "sub_f32array_naive");
		sub_i32array = (void(*)(uint64, int32*, int32*, int32*))GetProcAddress(getThisModuleHandle(), "sub_i32array_naive");
		sub_i32array_i32 = (void(*)(uint64, int32*, int32, int32*))GetProcAddress(getThisModuleHandle(), "sub_i32array_i32_naive");
		sub_f32array_f32 = (void(*)(uint64, float32*, float32, float32*))GetProcAddress(getThisModuleHandle(), "sub_f32array_f32_naive");
		mul_f32array = (void(*)(uint64, float32*, float32*, float32*))GetProcAddress(getThisModuleHandle(), "mul_f32array_naive");
		mul_i32array = (void(*)(uint64, int32*, int32*, int32*))GetProcAddress(getThisModuleHandle(), "mul_i32array_naive");
		mul_i32array_i32 = (void(*)(uint64, int32*, int32, int32*))GetProcAddress(getThisModuleHandle(), "mul_i32array_i32_naive");
		mul_f32array_f32 = (void(*)(uint64, float32*, float32, float32*))GetProcAddress(getThisModuleHandle(), "mul_f32array_f32_naive");
		div_f32array = (void(*)(uint64, float32*, float32*, float32*))GetProcAddress(getThisModuleHandle(), "div_f32array_naive");
		div_i32array = (void(*)(uint64, int32*, int32*, int32*))GetProcAddress(getThisModuleHandle(), "div_i32array_naive");
		div_i32array_i32 = (void(*)(uint64, int32*, int32, int32*))GetProcAddress(getThisModuleHandle(), "div_i32array_i32_naive");
		div_f32array_f32 = (void(*)(uint64, float32*, float32, float32*))GetProcAddress(getThisModuleHandle(), "div_f32array_f32_naive");
	}
}