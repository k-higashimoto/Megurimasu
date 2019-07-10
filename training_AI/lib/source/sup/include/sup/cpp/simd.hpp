/**
* @file simd.hpp
* @brief simd処理定義ファイル
*/

#ifndef SUP_LIB_CPP_SIMD_HPP
#define SUP_LIB_CPP_SIMD_HPP

#include<cstdint>

#ifdef _MSC_VER
#include<intrin.h>
#else
#include<x86intrin.h>
#include<cpuid.h>
#endif

namespace sup
{
inline namespace cpp
{
//----------------------------------------------------------------------------------------------------------------------------------------------------
//basic type
	using SIMD = __m128;

//----------------------------------------------------------------------------------------------------------------------------------------------------
//SIMD converter
	class CSIMD final
	{
	public:
		SIMD si;

		inline operator __m128() const noexcept { return si; };
		inline operator __m128i() const noexcept { return _mm_castps_si128(si); };
		inline operator __m128d() const noexcept { return _mm_castps_pd(si); }
	};

	class alignas(16) CINT32 final
	{
	public:
		union
		{
			int32_t i[4];
			SIMD si;
		};

		inline operator SIMD() const noexcept { return si; };
		inline operator int32_t*() noexcept { return i; };
	};

	class alignas(16) CUINT8 final
	{
	public:
		union
		{
			uint8_t ui[16];
			SIMD si;
		};

		inline operator SIMD() const noexcept { return si; };
		inline operator uint8_t*() noexcept { return ui; };
	};

	class alignas(16) CUINT32 final
	{
	public:
		union
		{
			uint32_t ui[4];
			SIMD si;
		};

		inline operator SIMD() const noexcept { return si; };
		inline operator uint32_t*() noexcept { return ui; };
	};

	class alignas(16) CFLOAT32 final
	{
	public:
		union
		{
			float f[4];
			SIMD si;
		};

		inline operator SIMD() const noexcept { return si; };
		inline operator float*() noexcept { return f; };
	};

//----------------------------------------------------------------------------------------------------------------------------------------------------
//int*2 storage
	struct INT2
	{
		union
		{
			struct
			{
				std::int32_t x;
				std::int32_t y;
			};
			std::int32_t i[2];
		};

		INT2() = default;
		INT2(const INT2&) = default;
		INT2& operator=(const INT2&) = default;
		inline INT2(std::int32_t x, std::int32_t y)noexcept : x(x), y(y) {};
		inline explicit INT2(const std::int32_t* p)noexcept : x(p[0]), y(p[1]) {};
	};

	struct alignas(16) INT2A : public INT2
	{
		INT2A() = default;
		INT2A(const INT2A&) = default;
		INT2A& operator=(const INT2A&) = default;
		inline INT2A(std::int32_t x, std::int32_t y)noexcept : INT2(x, y) {};
		inline explicit INT2A(const std::int32_t* p)noexcept : INT2(p) {};
	};

//----------------------------------------------------------------------------------------------------------------------------------------------------
//uint*2 storage
	struct UINT2
	{
		union
		{
			struct
			{
				std::uint32_t x;
				std::uint32_t y;
			};
			std::uint32_t ui[2];
		};

		UINT2() = default;
		UINT2(const UINT2&) = default;
		UINT2& operator=(const UINT2&) = default;
		inline UINT2(std::uint32_t x, std::uint32_t y)noexcept : x(x), y(y) {};
		inline explicit UINT2(const std::uint32_t* p)noexcept : x(p[0]), y(p[1]) {};
	};

	struct alignas(16) UINT2A : public UINT2
	{
		UINT2A() = default;
		UINT2A(const UINT2A&) = default;
		UINT2A& operator=(const UINT2A&) = default;
		inline UINT2A(std::uint32_t x, std::uint32_t y)noexcept : UINT2(x, y) {};
		inline explicit UINT2A(const std::uint32_t* p)noexcept : UINT2(p) {};
	};

//----------------------------------------------------------------------------------------------------------------------------------------------------
//float*2 storage
	struct FLOAT2 
	{
		union
		{
			struct
			{
				float x;
				float y;
			};
			float f[2];
		};

		FLOAT2() = default;
		FLOAT2(const FLOAT2&) = default;
		FLOAT2& operator=(const FLOAT2&) = default;
		inline FLOAT2(float x, float y)noexcept : x(x), y(y) {};
		inline explicit FLOAT2(const float* p)noexcept : x(p[0]), y(p[1]) {};
	};

	struct alignas(16) FLOAT2A : public FLOAT2
	{
		FLOAT2A() = default;
		FLOAT2A(const FLOAT2A&) = default;
		FLOAT2A& operator=(const FLOAT2A&) = default;
		inline FLOAT2A(float x, float y)noexcept : FLOAT2(x, y) {};
		inline explicit FLOAT2A(const float* p)noexcept : FLOAT2(p) {};
	};

//----------------------------------------------------------------------------------------------------------------------------------------------------
//int*3 storage
	struct INT3
	{
		union
		{
			struct
			{
				std::int32_t x;
				std::int32_t y;
				std::int32_t z;
			};
			std::int32_t i[3];
		};

		INT3() = default;
		INT3(const INT3&) = default;
		INT3& operator=(const INT3&) = default;
		inline INT3(std::int32_t x, std::int32_t y, std::int32_t z)noexcept : x(x), y(y), z(z) {};
		inline explicit INT3(const std::int32_t* p)noexcept : x(p[0]), y(p[1]), z(p[2]) {};
	};

	struct alignas(16) INT3A : public INT3
	{
		INT3A() = default;
		INT3A(const INT3A&) = default;
		INT3A& operator=(const INT3A&) = default;
		inline INT3A(std::int32_t x, std::int32_t y, std::int32_t z)noexcept : INT3(x, y, z) {};
		inline explicit INT3A(const std::int32_t* p)noexcept : INT3(p) {};
	};

//----------------------------------------------------------------------------------------------------------------------------------------------------
//uint*3 storage
	struct UINT3
	{
		union
		{
			struct
			{
				std::uint32_t x;
				std::uint32_t y;
				std::uint32_t z;
			};
			std::uint32_t ui[3];
		};

		UINT3() = default;
		UINT3(const UINT3&) = default;
		UINT3& operator=(const UINT3&) = default;
		inline UINT3(std::uint32_t x, std::uint32_t y, std::uint32_t z)noexcept : x(x), y(y), z(z) {};
		inline explicit UINT3(const std::uint32_t* p)noexcept : x(p[0]), y(p[1]), z(p[2]) {};
	};

	struct alignas(16) UINT3A : public UINT3
	{
		UINT3A() = default;
		UINT3A(const UINT3A&) = default;
		UINT3A& operator=(const UINT3A&) = default;
		inline UINT3A(std::uint32_t x, std::uint32_t y, std::uint32_t z)noexcept : UINT3(x, y, z) {};
		inline explicit UINT3A(const std::uint32_t* p)noexcept : UINT3(p) {};
	};

//----------------------------------------------------------------------------------------------------------------------------------------------------
//float*3 storage
	struct FLOAT3
	{
		union
		{
			struct
			{
				float x;
				float y;
				float z;
			};
			float f[3];
		};

		FLOAT3() = default;
		FLOAT3(const FLOAT3&) = default;
		FLOAT3& operator=(const FLOAT3&) = default;
		inline FLOAT3(float x, float y, float z)noexcept : x(x), y(y), z(z) {};
		inline explicit FLOAT3(const float* p)noexcept : x(p[0]), y(p[1]), z(p[2]) {};
	};

	struct alignas(16) FLOAT3A : public FLOAT3
	{
		FLOAT3A() = default;
		FLOAT3A(const FLOAT3A&) = default;
		FLOAT3A& operator=(const FLOAT3A&) = default;
		inline FLOAT3A(float x, float y, float z)noexcept : FLOAT3(x, y, z) {};
		inline explicit FLOAT3A(const float* p)noexcept : FLOAT3(p) {};
	};

//----------------------------------------------------------------------------------------------------------------------------------------------------
//int*4 storage
	struct INT4
	{
		union
		{
			struct
			{
				std::int32_t x;
				std::int32_t y;
				std::int32_t z;
				std::int32_t w;
			};
			std::int32_t i[4];
		};

		INT4() = default;
		INT4(const INT4&) = default;
		INT4& operator=(const INT4&) = default;
		inline INT4(std::int32_t x, std::int32_t y, std::int32_t z, std::int32_t w)noexcept : x(x), y(y), z(z), w(w) {};
		inline explicit INT4(const std::int32_t* p)noexcept : x(p[0]), y(p[1]), z(p[2]), w(p[3]) {};
	};

	struct alignas(16) INT4A : public INT4
	{
		INT4A() = default;
		INT4A(const INT4A&) = default;
		INT4A& operator=(const INT4A&) = default;
		inline INT4A(std::int32_t x, std::int32_t y, std::int32_t z, std::int32_t w)noexcept : INT4(x, y, z, w) {};
		inline explicit INT4A(const std::int32_t* p)noexcept : INT4(p) {};
	};

//----------------------------------------------------------------------------------------------------------------------------------------------------
//uint*4 storage
	struct UINT4
	{
		union
		{
			struct
			{
				std::uint32_t x;
				std::uint32_t y;
				std::uint32_t z;
				std::uint32_t w;
			};
			std::uint32_t ui[4];
		};

		UINT4() = default;
		UINT4(const UINT4&) = default;
		UINT4& operator=(const UINT4&) = default;
		inline UINT4(std::uint32_t x, std::uint32_t y, std::uint32_t z, std::uint32_t w)noexcept : x(x), y(y), z(z), w(w) {};
		inline explicit UINT4(const std::uint32_t* p)noexcept : x(p[0]), y(p[1]), z(p[2]), w(p[3]) {};
	};

	struct alignas(16) UINT4A : public UINT4
	{
		UINT4A() = default;
		UINT4A(const UINT4A&) = default;
		UINT4A& operator=(const UINT4A&) = default;
		inline UINT4A(std::uint32_t x, std::uint32_t y, std::uint32_t z, std::uint32_t w)noexcept : UINT4(x, y, z, w) {};
		inline explicit UINT4A(const std::uint32_t* p)noexcept : UINT4(p) {};
	};

//----------------------------------------------------------------------------------------------------------------------------------------------------
//float*4 storage
	struct FLOAT4
	{
		union
		{
			struct
			{
				float x;
				float y;
				float z;
				float w;
			};
			float f[4];
		};

		FLOAT4() = default;
		FLOAT4(const FLOAT4&) = default;
		FLOAT4& operator=(const FLOAT4&) = default;
		inline FLOAT4(float x, float y, float z, float w)noexcept : x(x), y(y), z(z), w(w) {};
		inline explicit FLOAT4(const float* p)noexcept : x(p[0]), y(p[1]), z(p[2]), w(p[3]) {};
	};

	struct alignas(16) FLOAT4A : public FLOAT4
	{
		FLOAT4A() = default;
		FLOAT4A(const FLOAT4A&) = default;
		FLOAT4A& operator=(const FLOAT4A&) = default;
		inline FLOAT4A(float x, float y, float z, float w)noexcept : FLOAT4(x, y, z, w) {};
		inline explicit FLOAT4A(const float* p)noexcept : FLOAT4(p) {};
	};

//----------------------------------------------------------------------------------------------------------------------------------------------------
//CPUID constant
	constexpr size_t MMX_READY		= 1 << 23;
	constexpr size_t SSE_READY		= 1 << 25;
	constexpr size_t SSE2_READY		= 1 << 26;
	constexpr size_t SSE3_READY		= 1;
	constexpr size_t SSSE3_READY	= 1 << 9;
	constexpr size_t AVX_READY		= 1 << 28;

//----------------------------------------------------------------------------------------------------------------------------------------------------
//SIMD constant
	extern inline const CUINT32 kSIMDMask0 = { 0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000 };
	extern inline const CUINT32 kSIMDMask1 = { 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000000 };
	extern inline const CUINT32 kSIMDMask2 = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000 };
	extern inline const CUINT32 kSIMDMask3 = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
	extern inline const CFLOAT32 kSIMDMinus0 = { -1.0f,  1.0f,  1.0f,  1.0f };
	extern inline const CFLOAT32 kSIMDMinus1 = {  1.0f, -1.0f,  1.0f,  1.0f };
	extern inline const CFLOAT32 kSIMDMinus2 = {  1.0f,  1.0f, -1.0f,  1.0f };
	extern inline const CFLOAT32 kSIMDMinus3 = {  1.0f,  1.0f,  1.0f, -1.0f };
	extern inline const CFLOAT32 kSIMDIdentity0 = { 1.0f, 0.0f, 0.0f, 0.0f };
	extern inline const CFLOAT32 kSIMDIdentity1 = { 0.0f, 1.0f, 0.0f, 0.0f };
	extern inline const CFLOAT32 kSIMDIdentity2 = { 0.0f, 0.0f, 1.0f, 0.0f };
	extern inline const CFLOAT32 kSIMDIdentity3 = { 0.0f, 0.0f, 0.0f, 1.0f };

//----------------------------------------------------------------------------------------------------------------------------------------------------
//SIMD macro
#define SIMD_SHUFFLE(x, y, z, w)		_MM_SHUFFLE(w, z, y, x)
#define SIMD_SHUFFLE_R(w, z, y, x)		_MM_SHUFFLE(w, z, y, x)
#define SIMD_TRANSPOSE(v1, v2, v3, v4)	_MM_TRANSPOSE4_PS(v1, v2, v3, v4)

//----------------------------------------------------------------------------------------------------------------------------------------------------
//check function
	bool __fastcall SIMDSupport();

//load function
	sup::cpp::SIMD __fastcall SIMDLoadZero();

	sup::cpp::SIMD __fastcall SIMDLoadInt(int x);
	sup::cpp::SIMD __fastcall SIMDLoadUInt(std::uint32_t x);
	sup::cpp::SIMD __fastcall SIMDLoadFloat(float x);
	sup::cpp::SIMD __fastcall SIMDLoadFloat(const float* p);

	sup::cpp::SIMD __fastcall SIMDLoadInt2(const INT2& p);
	sup::cpp::SIMD __fastcall SIMDLoadInt2A(const INT2A& p);
	sup::cpp::SIMD __fastcall SIMDLoadUInt2(const UINT2& p);
	sup::cpp::SIMD __fastcall SIMDLoadUInt2A(const UINT2A& p);
	sup::cpp::SIMD __fastcall SIMDLoadFloat2(float x, float y);
	sup::cpp::SIMD __fastcall SIMDLoadFloat2(const float* p);
	sup::cpp::SIMD __fastcall SIMDLoadFloat2(const FLOAT2& p);
	sup::cpp::SIMD __fastcall SIMDLoadFloat2A(const float* p);
	sup::cpp::SIMD __fastcall SIMDLoadFloat2A(const FLOAT2A& p);

	sup::cpp::SIMD __fastcall SIMDLoadInt3(const INT3& p);
	sup::cpp::SIMD __fastcall SIMDLoadInt3A(const INT3A& p);
	sup::cpp::SIMD __fastcall SIMDLoadUInt3(const UINT3& p);
	sup::cpp::SIMD __fastcall SIMDLoadUInt3A(const UINT3A& p);
	sup::cpp::SIMD __fastcall SIMDLoadFloat3(float x, float y, float z);
	sup::cpp::SIMD __fastcall SIMDLoadFloat3(const float* p);
	sup::cpp::SIMD __fastcall SIMDLoadFloat3(const FLOAT3& p);
	sup::cpp::SIMD __fastcall SIMDLoadFloat3A(const float* p);
	sup::cpp::SIMD __fastcall SIMDLoadFloat3A(const FLOAT3& p);

	sup::cpp::SIMD __fastcall SIMDLoadInt4(const INT4& p);
	sup::cpp::SIMD __fastcall SIMDLoadInt4A(const INT4A& p);
	sup::cpp::SIMD __fastcall SIMDLoadUInt4(const UINT4& p);
	sup::cpp::SIMD __fastcall SIMDLoadUInt4A(const UINT4A& p);
	sup::cpp::SIMD __fastcall SIMDLoadFloat4(float si);
	sup::cpp::SIMD __fastcall SIMDLoadFloat4(float x, float y, float z, float w);
	sup::cpp::SIMD __fastcall SIMDLoadFloat4(const float* p);
	sup::cpp::SIMD __fastcall SIMDLoadFloat4(const FLOAT4& p);
	sup::cpp::SIMD __fastcall SIMDLoadFloat4A(const float* p);
	sup::cpp::SIMD __fastcall SIMDLoadFloat4A(const FLOAT4& p);

//store function
	void __fastcall SIMDStoreInt(int* dest, const sup::cpp::SIMD& si);
	void __fastcall SIMDStoreUInt(std::uint32_t* dest, const sup::cpp::SIMD& si);
	void __fastcall SIMDStoreFloat(float* dest, const sup::cpp::SIMD& si);

	void __fastcall SIMDStoreInt2(INT2* dest, const sup::cpp::SIMD& si);
	void __fastcall SIMDStoreInt2A(INT2A* dest, const sup::cpp::SIMD& si);
	void __fastcall SIMDStoreUInt2(UINT2* dest, const sup::cpp::SIMD& si);
	void __fastcall SIMDStoreUInt2A(UINT2A* dest, const sup::cpp::SIMD& si);
	void __fastcall SIMDStoreFloat2(float* dest, const sup::cpp::SIMD& si);
	void __fastcall SIMDStoreFloat2(FLOAT2* dest, const sup::cpp::SIMD& si);
	void __fastcall SIMDStoreFloat2A(float* dest, const sup::cpp::SIMD& si);
	void __fastcall SIMDStoreFloat2A(FLOAT2A* dest, const sup::cpp::SIMD& si);

	void __fastcall SIMDStoreInt3(INT3* dest, const sup::cpp::SIMD& si);
	void __fastcall SIMDStoreInt3A(INT3A* dest, const sup::cpp::SIMD& si);
	void __fastcall SIMDStoreUInt3(UINT3* dest, const sup::cpp::SIMD& si);
	void __fastcall SIMDStoreUInt3A(UINT3A* dest, const sup::cpp::SIMD& si);
	void __fastcall SIMDStoreFloat3(float* dest, const sup::cpp::SIMD& si);
	void __fastcall SIMDStoreFloat3(FLOAT3* dest, const sup::cpp::SIMD& si);
	void __fastcall SIMDStoreFloat3A(float* dest, const sup::cpp::SIMD& si);
	void __fastcall SIMDStoreFloat3A(FLOAT3A* dest, const sup::cpp::SIMD& si);

	void __fastcall SIMDStoreInt4(INT4* dest, const sup::cpp::SIMD& si);
	void __fastcall SIMDStoreInt4A(INT4A* dest, const sup::cpp::SIMD& si);
	void __fastcall SIMDStoreUInt4(UINT4* dest, const sup::cpp::SIMD& si);
	void __fastcall SIMDStoreUInt4A(UINT4A* dest, const sup::cpp::SIMD& si);
	void __fastcall SIMDStoreFloat4(float* dest, const sup::cpp::SIMD& si);
	void __fastcall SIMDStoreFloat4(FLOAT4* dest, const sup::cpp::SIMD& si);
	void __fastcall SIMDStoreFloat4A(float* dest, const sup::cpp::SIMD& si);
	void __fastcall SIMDStoreFloat4A(FLOAT4* dest, const sup::cpp::SIMD& si);

//set function
	sup::cpp::SIMD __fastcall SIMDSetIntX(const sup::cpp::SIMD& si, std::int32_t i);
	sup::cpp::SIMD __fastcall SIMDSetIntY(const sup::cpp::SIMD& si, std::int32_t i);
	sup::cpp::SIMD __fastcall SIMDSetIntZ(const sup::cpp::SIMD& si, std::int32_t i);
	sup::cpp::SIMD __fastcall SIMDSetIntW(const sup::cpp::SIMD& si, std::int32_t i);
	sup::cpp::SIMD __fastcall SIMDSetUIntX(const sup::cpp::SIMD& si, std::uint32_t ui);
	sup::cpp::SIMD __fastcall SIMDSetUIntY(const sup::cpp::SIMD& si, std::uint32_t ui);
	sup::cpp::SIMD __fastcall SIMDSetUIntZ(const sup::cpp::SIMD& si, std::uint32_t ui);
	sup::cpp::SIMD __fastcall SIMDSetUIntW(const sup::cpp::SIMD& si, std::uint32_t ui);
	sup::cpp::SIMD __fastcall SIMDSetFloatX(const sup::cpp::SIMD& si, float f);
	sup::cpp::SIMD __fastcall SIMDSetFloatY(const sup::cpp::SIMD& si, float f);
	sup::cpp::SIMD __fastcall SIMDSetFloatZ(const sup::cpp::SIMD& si, float f);
	sup::cpp::SIMD __fastcall SIMDSetFloatW(const sup::cpp::SIMD& si, float f);

//get function
	std::int32_t __fastcall SIMDGetIntX(const sup::cpp::SIMD& si);
	std::int32_t __fastcall SIMDGetIntY(const sup::cpp::SIMD& si);
	std::int32_t __fastcall SIMDGetIntZ(const sup::cpp::SIMD& si);
	std::int32_t __fastcall SIMDGetIntW(const sup::cpp::SIMD& si);
	std::uint32_t __fastcall SIMDGetUIntX(const sup::cpp::SIMD& si);
	std::uint32_t __fastcall SIMDGetUIntY(const sup::cpp::SIMD& si);
	std::uint32_t __fastcall SIMDGetUIntZ(const sup::cpp::SIMD& si);
	std::uint32_t __fastcall SIMDGetUIntW(const sup::cpp::SIMD& si);
	float __fastcall SIMDGetFloatX(const sup::cpp::SIMD& si);
	float __fastcall SIMDGetFloatY(const sup::cpp::SIMD& si);
	float __fastcall SIMDGetFloatZ(const sup::cpp::SIMD& si);
	float __fastcall SIMDGetFloatW(const sup::cpp::SIMD& si);

//move function
	sup::cpp::SIMD __fastcall SIMDMove(const sup::cpp::SIMD& si1, const sup::SIMD& si2);
	sup::cpp::SIMD __fastcall SIMDMoveLow(const sup::cpp::SIMD& si1, const sup::SIMD& si2);
	sup::cpp::SIMD __fastcall SIMDMoveHigh(const sup::cpp::SIMD& si1, const sup::SIMD& si2);
	sup::cpp::SIMD __fastcall SIMDPackLow(const sup::cpp::SIMD& si1, const sup::SIMD& si2);
	sup::cpp::SIMD __fastcall SIMDPackHigh(const sup::cpp::SIMD& si1, const sup::SIMD& si2);
	sup::cpp::SIMD __fastcall SIMDPack3(const sup::cpp::SIMD& si1, const sup::cpp::SIMD& si2, const sup::cpp::SIMD& si3);
	sup::cpp::SIMD __fastcall SIMDPack4(const sup::cpp::SIMD& si1, const sup::cpp::SIMD& si2, const sup::cpp::SIMD& si3, const sup::cpp::SIMD& si4);
	template<unsigned int imm8> sup::cpp::SIMD __fastcall SIMDSort(const sup::cpp::SIMD& si);
	template<unsigned int pos> sup::cpp::SIMD __fastcall SIMDFill(const sup::cpp::SIMD& si);

//arithmetic function
	sup::cpp::SIMD __fastcall SIMDAdd(const sup::SIMD& f1, const sup::SIMD& f2);
	sup::cpp::SIMD __fastcall SIMDSub(const sup::SIMD& f1, const sup::SIMD& f2);
	sup::cpp::SIMD __fastcall SIMDMul(const sup::SIMD& f1, const sup::SIMD& f2);
	sup::cpp::SIMD __fastcall SIMDDiv(const sup::SIMD& f1, const sup::SIMD& f2);
	sup::cpp::SIMD __fastcall SIMDHAdd2(const sup::SIMD& si);
	sup::cpp::SIMD __fastcall SIMDHAdd3(const sup::SIMD& si);
	sup::cpp::SIMD __fastcall SIMDHAdd4(const sup::SIMD& si);
	sup::cpp::SIMD __fastcall SIMDHSub2(const sup::SIMD& si);
	sup::cpp::SIMD __fastcall SIMDHSub3(const sup::SIMD& si);
	sup::cpp::SIMD __fastcall SIMDHSub4(const sup::SIMD& si);
	sup::cpp::SIMD __fastcall SIMDSqrt(const sup::SIMD& si);
	sup::cpp::SIMD __fastcall SIMDSqrt4(const sup::SIMD& si);
	sup::cpp::SIMD __fastcall SIMDMin(const sup::SIMD& si1, const sup::SIMD& si2);
	sup::cpp::SIMD __fastcall SIMDMin4(const sup::SIMD& si1, const sup::SIMD& si2);
	sup::cpp::SIMD __fastcall SIMDMax(const sup::SIMD& si1, const sup::SIMD& si2);
	sup::cpp::SIMD __fastcall SIMDMax4(const sup::SIMD& si1, const sup::SIMD& si2);
	
//logical function
	sup::cpp::SIMD __fastcall SIMDAnd(const sup::SIMD& si1, const sup::SIMD& si2);
	sup::cpp::SIMD __fastcall SIMDAndNot(const sup::SIMD& si1, const sup::SIMD& si2);
	sup::cpp::SIMD __fastcall SIMDOr(const sup::SIMD& si1, const sup::SIMD& si2);
	sup::cpp::SIMD __fastcall SIMDXor(const sup::SIMD& si1, const sup::SIMD& si2);

//compare function
	sup::cpp::SIMD __fastcall SIMDCompEqual4(const sup::SIMD& si1, const sup::SIMD& si2);
	sup::cpp::SIMD __fastcall SIMDCompNotEqual4(const sup::SIMD& si1, const sup::SIMD& si2);
	sup::cpp::SIMD __fastcall SIMDCompLess4(const sup::SIMD si1, const sup::SIMD& si2);
	sup::cpp::SIMD __fastcall SIMDCompNotLess4(const sup::SIMD si1, const sup::SIMD& si2);
	sup::cpp::SIMD __fastcall SIMDCompLessEqual4(const sup::SIMD si1, const sup::SIMD& si2);
	sup::cpp::SIMD __fastcall SIMDCompNotLessEqual4(const sup::SIMD si1, const sup::SIMD& si2);
	sup::cpp::SIMD __fastcall SIMDCompGreater4(const sup::SIMD si1, const sup::SIMD& si2);
	sup::cpp::SIMD __fastcall SIMDCompNotGreater4(const sup::SIMD si1, const sup::SIMD& si2);
	sup::cpp::SIMD __fastcall SIMDCompGreaterEqual4(const sup::SIMD si1, const sup::SIMD& si2);
	sup::cpp::SIMD __fastcall SIMDCompNotGreaterEqual4(const sup::SIMD si1, const sup::SIMD& si2);
}
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
//include imple file
#include<sup/cpp/simd/simd.inl>

#endif