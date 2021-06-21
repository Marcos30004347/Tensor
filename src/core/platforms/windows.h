#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)


#include <windows.h>
#include <iostream>
#include <vector>
#include <bitset>
#include <array>
#include <string>
#include <intrin.h>

HMODULE getThisModuleHandle()
{
    HMODULE hModule = NULL;
    ::GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | 
        GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, 
        (LPCTSTR)getThisModuleHandle, &hModule);

    return hModule;
}

typedef int (CALLBACK* function_teste)();

extern "C"
{

__declspec(dllexport) int teste()
{
    printf("hehe\n");
    return 0;
}

};

//int t()
//{
//    HMODULE hDLL = getThisModuleHandle();
//    function_teste function_teste_ptr;
//     
//     if (hDLL != NULL)
//     {
//         function_teste_ptr = (function_teste)GetProcAddress(hDLL, "teste");
//         int k = function_teste_ptr();
//        
//     }
//
//     return 0;
//}

class InstructionSet
{
    class InstructionSet_Internal;

public:
    static std::string Vendor() { return CPU_Rep.vendor_; }
    static std::string Brand() { return CPU_Rep.brand_; }

    static bool SSE3() { return CPU_Rep.f_1_ECX_[0]; }
    static bool PCLMULQDQ() { return CPU_Rep.f_1_ECX_[1]; }
    static bool MONITOR() { return CPU_Rep.f_1_ECX_[3]; }
    static bool SSSE3() { return CPU_Rep.f_1_ECX_[9]; }
    static bool FMA() { return CPU_Rep.f_1_ECX_[12]; }
    static bool CMPXCHG16B() { return CPU_Rep.f_1_ECX_[13]; }
    static bool SSE41() { return CPU_Rep.f_1_ECX_[19]; }
    static bool SSE42() { return CPU_Rep.f_1_ECX_[20]; }
    static bool MOVBE() { return CPU_Rep.f_1_ECX_[22]; }
    static bool POPCNT() { return CPU_Rep.f_1_ECX_[23]; }
    static bool AES() { return CPU_Rep.f_1_ECX_[25]; }
    static bool XSAVE() { return CPU_Rep.f_1_ECX_[26]; }
    static bool OSXSAVE() { return CPU_Rep.f_1_ECX_[27]; }
    static bool AVX() { return CPU_Rep.f_1_ECX_[28]; }
    static bool F16C() { return CPU_Rep.f_1_ECX_[29]; }
    static bool RDRAND() { return CPU_Rep.f_1_ECX_[30]; }

    static bool MSR() { return CPU_Rep.f_1_EDX_[5]; }
    static bool CX8() { return CPU_Rep.f_1_EDX_[8]; }
    static bool SEP() { return CPU_Rep.f_1_EDX_[11]; }
    static bool CMOV() { return CPU_Rep.f_1_EDX_[15]; }
    static bool CLFSH() { return CPU_Rep.f_1_EDX_[19]; }
    static bool MMX() { return CPU_Rep.f_1_EDX_[23]; }
    static bool FXSR() { return CPU_Rep.f_1_EDX_[24]; }
    static bool SSE() { return CPU_Rep.f_1_EDX_[25]; }
    static bool SSE2() { return CPU_Rep.f_1_EDX_[26]; }

    static bool FSGSBASE() { return CPU_Rep.f_7_EBX_[0]; }
    static bool BMI1() { return CPU_Rep.f_7_EBX_[3]; }
    static bool HLE() { return CPU_Rep.isIntel_ && CPU_Rep.f_7_EBX_[4]; }
    static bool AVX2() { return CPU_Rep.f_7_EBX_[5]; }
    static bool BMI2() { return CPU_Rep.f_7_EBX_[8]; }
    static bool ERMS() { return CPU_Rep.f_7_EBX_[9]; }
    static bool INVPCID() { return CPU_Rep.f_7_EBX_[10]; }
    static bool RTM() { return CPU_Rep.isIntel_ && CPU_Rep.f_7_EBX_[11]; }
    static bool AVX512F() { return CPU_Rep.f_7_EBX_[16]; }
    static bool RDSEED() { return CPU_Rep.f_7_EBX_[18]; }
    static bool ADX() { return CPU_Rep.f_7_EBX_[19]; }
    static bool AVX512PF() { return CPU_Rep.f_7_EBX_[26]; }
    static bool AVX512ER() { return CPU_Rep.f_7_EBX_[27]; }
    static bool AVX512CD() { return CPU_Rep.f_7_EBX_[28]; }
    static bool SHA() { return CPU_Rep.f_7_EBX_[29]; }

    static bool PREFETCHWT1() { return CPU_Rep.f_7_ECX_[0]; }

    static bool LAHF() { return CPU_Rep.f_81_ECX_[0]; }
    static bool LZCNT() { return CPU_Rep.isIntel_ && CPU_Rep.f_81_ECX_[5]; }
    static bool ABM() { return CPU_Rep.isAMD_ && CPU_Rep.f_81_ECX_[5]; }
    static bool SSE4a() { return CPU_Rep.isAMD_ && CPU_Rep.f_81_ECX_[6]; }
    static bool XOP() { return CPU_Rep.isAMD_ && CPU_Rep.f_81_ECX_[11]; }
    static bool TBM() { return CPU_Rep.isAMD_ && CPU_Rep.f_81_ECX_[21]; }

    static bool SYSCALL() { return CPU_Rep.isIntel_ && CPU_Rep.f_81_EDX_[11]; }
    static bool MMXEXT() { return CPU_Rep.isAMD_ && CPU_Rep.f_81_EDX_[22]; }
    static bool RDTSCP() { return CPU_Rep.isIntel_ && CPU_Rep.f_81_EDX_[27]; }
    static bool _3DNOWEXT() { return CPU_Rep.isAMD_ && CPU_Rep.f_81_EDX_[30]; }
    static bool _3DNOW() { return CPU_Rep.isAMD_ && CPU_Rep.f_81_EDX_[31]; }

private:
    static const InstructionSet_Internal CPU_Rep;

    class InstructionSet_Internal
    {
    public:
        InstructionSet_Internal()
            : nIds_{ 0 },
            nExIds_{ 0 },
            isIntel_{ false },
            isAMD_{ false },
            f_1_ECX_{ 0 },
            f_1_EDX_{ 0 },
            f_7_EBX_{ 0 },
            f_7_ECX_{ 0 },
            f_81_ECX_{ 0 },
            f_81_EDX_{ 0 },
            data_{},
            extdata_{}
        {
            std::array<int, 4> cpui;

            __cpuid(cpui.data(), 0);
            nIds_ = cpui[0];

            for (int i = 0; i <= nIds_; ++i)
            {
                __cpuidex(cpui.data(), i, 0);
                data_.push_back(cpui);
            }

            char vendor[0x20];
            memset(vendor, 0, sizeof(vendor));
            *reinterpret_cast<int*>(vendor) = data_[0][1];
            *reinterpret_cast<int*>(vendor + 4) = data_[0][3];
            *reinterpret_cast<int*>(vendor + 8) = data_[0][2];
            vendor_ = vendor;
            if (vendor_ == "GenuineIntel")
            {
                isIntel_ = true;
            }
            else if (vendor_ == "AuthenticAMD")
            {
                isAMD_ = true;
            }

            if (nIds_ >= 1)
            {
                f_1_ECX_ = data_[1][2];
                f_1_EDX_ = data_[1][3];
            }

            if (nIds_ >= 7)
            {
                f_7_EBX_ = data_[7][1];
                f_7_ECX_ = data_[7][2];
            }

            __cpuid(cpui.data(), 0x80000000);
            nExIds_ = cpui[0];

            char brand[0x40];
            memset(brand, 0, sizeof(brand));

            for (int i = 0x80000000; i <= nExIds_; ++i)
            {
                __cpuidex(cpui.data(), i, 0);
                extdata_.push_back(cpui);
            }

            if (nExIds_ >= 0x80000001)
            {
                f_81_ECX_ = extdata_[1][2];
                f_81_EDX_ = extdata_[1][3];
            }

            if (nExIds_ >= 0x80000004)
            {
                memcpy(brand, extdata_[2].data(), sizeof(cpui));
                memcpy(brand + 16, extdata_[3].data(), sizeof(cpui));
                memcpy(brand + 32, extdata_[4].data(), sizeof(cpui));
                brand_ = brand;
            }
        };

        int nIds_;
        int nExIds_;
        std::string vendor_;
        std::string brand_;
        bool isIntel_;
        bool isAMD_;
        std::bitset<32> f_1_ECX_;
        std::bitset<32> f_1_EDX_;
        std::bitset<32> f_7_EBX_;
        std::bitset<32> f_7_ECX_;
        std::bitset<32> f_81_ECX_;
        std::bitset<32> f_81_EDX_;
        std::vector<std::array<int, 4>> data_;
        std::vector<std::array<int, 4>> extdata_;
    };
};

const InstructionSet::InstructionSet_Internal InstructionSet::CPU_Rep;

#include "types.h"

#if defined(__AVX__) && defined(__AVX2__)
#include "../handlers/avx.h"
#endif

#if defined(_M_AMD64 ) || defined(_M_X64) || defined(_M_IX86_FP)
#include "../handlers/sse.h"
#endif

#include "../handlers/naive.h"

i32	(__stdcall* reduce_i32array)(ui64, i32*);
f32	(__stdcall* reduce_f32array)(ui64, f32*);
f32	(__stdcall* dot_f32array)(ui64, f32*, f32*);

void(__stdcall* add_f32array)(ui64, f32*, f32*, f32*);
void(__stdcall* add_i32array)(ui64, i32*, i32*, i32*);
void(__stdcall* add_i32array_i32)(ui64, i32*, i32, i32*);
void(__stdcall* add_f32array_f32)(ui64, f32*, f32, f32*);

void(__stdcall* sub_f32array)(ui64, f32*, f32*, f32*);
void(__stdcall* sub_i32array)(ui64, i32*, i32*, i32*);
void(__stdcall* sub_f32array_f32)(ui64, f32*, f32, f32*);
void(__stdcall* sub_i32array_i32)(ui64, i32*, i32, i32*);

void(__stdcall* mul_f32array)(ui64, f32*, f32*, f32*);
void(__stdcall* mul_i32array)(ui64, i32*, i32*, i32*);
void(__stdcall* mul_f32array_f32)(ui64, f32*, f32, f32*);
void(__stdcall* mul_i32array_i32)(ui64, i32*, i32, i32*);

void(__stdcall* div_f32array)(ui64, f32*, f32*, f32*);
void(__stdcall* div_i32array)(ui64, i32*, i32*, i32*);
void(__stdcall* div_i32array_i32)(ui64, i32*, i32, i32*);
void(__stdcall* div_f32array_f32)(ui64, f32*, f32, f32*);

void(__stdcall* sqrt_f32array)(ui64, f32* a, f32* c);

void setup_core_lib()
{
	if (InstructionSet::AVX())
	{
		reduce_f32array = (f32(*)(ui64, f32*))GetProcAddress(getThisModuleHandle(), "reduce_f32array_avx");
		reduce_i32array = (i32(*)(ui64, i32*))GetProcAddress(getThisModuleHandle(), "reduce_i32array_avx");
		add_f32array = (void(*)(ui64, f32*, f32*, f32*))GetProcAddress(getThisModuleHandle(), "add_f32array_avx");
		add_i32array = (void(*)(ui64, i32*, i32*, i32*))GetProcAddress(getThisModuleHandle(), "add_i32array_avx");
		add_i32array_i32 = (void(*)(ui64, i32*, i32, i32*))GetProcAddress(getThisModuleHandle(), "add_i32array_i32_avx");
		add_f32array_f32 = (void(*)(ui64, f32*, f32, f32*))GetProcAddress(getThisModuleHandle(), "add_f32array_f32_avx");
		sub_f32array = (void(*)(ui64, f32*, f32*, f32*))GetProcAddress(getThisModuleHandle(), "sub_f32array_avx");
		sub_i32array = (void(*)(ui64, i32*, i32*, i32*))GetProcAddress(getThisModuleHandle(), "sub_i32array_avx");
		sub_i32array_i32 = (void(*)(ui64, i32*, i32, i32*))GetProcAddress(getThisModuleHandle(), "sub_i32array_i32_avx");
		sub_f32array_f32 = (void(*)(ui64, f32*, f32, f32*))GetProcAddress(getThisModuleHandle(), "sub_f32array_f32_avx");
		mul_f32array = (void(*)(ui64, f32*, f32*, f32*))GetProcAddress(getThisModuleHandle(), "mul_f32array_avx");
		mul_i32array = (void(*)(ui64, i32*, i32*, i32*))GetProcAddress(getThisModuleHandle(), "mul_i32array_avx");
		mul_i32array_i32 = (void(*)(ui64, i32*, i32, i32*))GetProcAddress(getThisModuleHandle(), "mul_i32array_i32_avx");
		mul_f32array_f32 = (void(*)(ui64, f32*, f32, f32*))GetProcAddress(getThisModuleHandle(), "mul_f32array_f32_avx");
		div_f32array = (void(*)(ui64, f32*, f32*, f32*))GetProcAddress(getThisModuleHandle(), "div_f32array_avx");
		div_i32array = (void(*)(ui64, i32*, i32*, i32*))GetProcAddress(getThisModuleHandle(), "div_i32array_avx");
		div_i32array_i32 = (void(*)(ui64, i32*, i32, i32*))GetProcAddress(getThisModuleHandle(), "div_i32array_i32_avx");
		div_f32array_f32 = (void(*)(ui64, f32*, f32, f32*))GetProcAddress(getThisModuleHandle(), "div_f32array_f32_avx");
	}
	else if (InstructionSet::SSE())
	{
		reduce_f32array = (f32(*)(ui64, f32*))GetProcAddress(getThisModuleHandle(), "reduce_f32array_sse");
		reduce_i32array = (i32(*)(ui64, i32*))GetProcAddress(getThisModuleHandle(), "reduce_i32array_sse");
		add_f32array = (void(*)(ui64, f32*, f32*, f32*))GetProcAddress(getThisModuleHandle(), "add_f32array_sse");
		add_i32array = (void(*)(ui64, i32*, i32*, i32*))GetProcAddress(getThisModuleHandle(), "add_i32array_sse");
		add_i32array_i32 = (void(*)(ui64, i32*, i32, i32*))GetProcAddress(getThisModuleHandle(), "add_i32array_i32_sse");
		add_f32array_f32 = (void(*)(ui64, f32*, f32, f32*))GetProcAddress(getThisModuleHandle(), "add_f32array_f32_sse");
		sub_f32array = (void(*)(ui64, f32*, f32*, f32*))GetProcAddress(getThisModuleHandle(), "sub_f32array_sse");
		sub_i32array = (void(*)(ui64, i32*, i32*, i32*))GetProcAddress(getThisModuleHandle(), "sub_i32array_sse");
		sub_i32array_i32 = (void(*)(ui64, i32*, i32, i32*))GetProcAddress(getThisModuleHandle(), "sub_i32array_i32_sse");
		sub_f32array_f32 = (void(*)(ui64, f32*, f32, f32*))GetProcAddress(getThisModuleHandle(), "sub_f32array_f32_sse");
		mul_f32array = (void(*)(ui64, f32*, f32*, f32*))GetProcAddress(getThisModuleHandle(), "mul_f32array_sse");
		mul_i32array = (void(*)(ui64, i32*, i32*, i32*))GetProcAddress(getThisModuleHandle(), "mul_i32array_sse");
		mul_i32array_i32 = (void(*)(ui64, i32*, i32, i32*))GetProcAddress(getThisModuleHandle(), "mul_i32array_i32_sse");
		mul_f32array_f32 = (void(*)(ui64, f32*, f32, f32*))GetProcAddress(getThisModuleHandle(), "mul_f32array_f32_sse");
		div_f32array = (void(*)(ui64, f32*, f32*, f32*))GetProcAddress(getThisModuleHandle(), "div_f32array_sse");
		div_i32array = (void(*)(ui64, i32*, i32*, i32*))GetProcAddress(getThisModuleHandle(), "div_i32array_sse");
		div_i32array_i32 = (void(*)(ui64, i32*, i32, i32*))GetProcAddress(getThisModuleHandle(), "div_i32array_i32_sse");
		div_f32array_f32 = (void(*)(ui64, f32*, f32, f32*))GetProcAddress(getThisModuleHandle(), "div_f32array_f32_sse");
	}
	else
	{
		reduce_f32array = (f32(*)(ui64, f32*))GetProcAddress(getThisModuleHandle(), "reduce_f32array_naive");
		reduce_i32array = (i32(*)(ui64, i32*))GetProcAddress(getThisModuleHandle(), "reduce_i32array_naive");
		add_f32array = (void(*)(ui64, f32*, f32*, f32*))GetProcAddress(getThisModuleHandle(), "add_f32array_naive");
		add_i32array = (void(*)(ui64, i32*, i32*, i32*))GetProcAddress(getThisModuleHandle(), "add_i32array_naive");
		add_i32array_i32 = (void(*)(ui64, i32*, i32, i32*))GetProcAddress(getThisModuleHandle(), "add_i32array_i32_naive");
		add_f32array_f32 = (void(*)(ui64, f32*, f32, f32*))GetProcAddress(getThisModuleHandle(), "add_f32array_f32_naive");
		sub_f32array = (void(*)(ui64, f32*, f32*, f32*))GetProcAddress(getThisModuleHandle(), "sub_f32array_naive");
		sub_i32array = (void(*)(ui64, i32*, i32*, i32*))GetProcAddress(getThisModuleHandle(), "sub_i32array_naive");
		sub_i32array_i32 = (void(*)(ui64, i32*, i32, i32*))GetProcAddress(getThisModuleHandle(), "sub_i32array_i32_naive");
		sub_f32array_f32 = (void(*)(ui64, f32*, f32, f32*))GetProcAddress(getThisModuleHandle(), "sub_f32array_f32_naive");
		mul_f32array = (void(*)(ui64, f32*, f32*, f32*))GetProcAddress(getThisModuleHandle(), "mul_f32array_naive");
		mul_i32array = (void(*)(ui64, i32*, i32*, i32*))GetProcAddress(getThisModuleHandle(), "mul_i32array_naive");
		mul_i32array_i32 = (void(*)(ui64, i32*, i32, i32*))GetProcAddress(getThisModuleHandle(), "mul_i32array_i32_naive");
		mul_f32array_f32 = (void(*)(ui64, f32*, f32, f32*))GetProcAddress(getThisModuleHandle(), "mul_f32array_f32_naive");
		div_f32array = (void(*)(ui64, f32*, f32*, f32*))GetProcAddress(getThisModuleHandle(), "div_f32array_naive");
		div_i32array = (void(*)(ui64, i32*, i32*, i32*))GetProcAddress(getThisModuleHandle(), "div_i32array_naive");
		div_i32array_i32 = (void(*)(ui64, i32*, i32, i32*))GetProcAddress(getThisModuleHandle(), "div_i32array_i32_naive");
		div_f32array_f32 = (void(*)(ui64, f32*, f32, f32*))GetProcAddress(getThisModuleHandle(), "div_f32array_f32_naive");
	}
}

#endif