/**
* @file simd.inl
* @brief simdèàóùé¿ëïÉtÉ@ÉCÉã
*/

namespace sup
{
inline namespace cpp
{
//----------------------------------------------------------------------------------------------------------------------------------------------------
	inline bool __fastcall SIMDSupport()
	{
		int cpu_info[4];
		__cpuid(cpu_info, 1);
		return cpu_info[3] & SSSE3_READY;
	}

//----------------------------------------------------------------------------------------------------------------------------------------------------
	inline sup::cpp::SIMD __fastcall SIMDLoadZero()
	{
		return _mm_setzero_ps();
	}

	inline sup::cpp::SIMD __fastcall SIMDLoadInt(int x)
	{
		return _mm_load_ss(reinterpret_cast<float*>(&x));
	}

	inline sup::cpp::SIMD __fastcall SIMDLoadUInt(std::uint32_t x)
	{
		return _mm_load_ss(reinterpret_cast<float*>(&x));
	}

	inline sup::cpp::SIMD __fastcall SIMDLoadFloat(float x)
	{
		return _mm_load_ss(&x);
	}

	inline sup::cpp::SIMD __fastcall SIMDLoadFloat(const float* p)
	{
		return _mm_load_ss(p);
	}

	inline sup::cpp::SIMD __fastcall SIMDLoadInt2(const INT2& p)
	{
		return _mm_unpacklo_ps(
			_mm_load_ss(reinterpret_cast<const float*>(&p.x)),
			_mm_load_ss(reinterpret_cast<const float*>(&p.y))
		);
	}

	inline sup::cpp::SIMD __fastcall SIMDLoadInt2A(const INT2A& p)
	{
		return _mm_castsi128_ps(
			_mm_loadl_epi64(reinterpret_cast<const __m128i*>(p.i))
		);
	}

	inline sup::cpp::SIMD __fastcall SIMDLoadUInt2(const UINT2& p)
	{
		return _mm_unpacklo_ps(
			_mm_load_ss(reinterpret_cast<const float*>(&p.x)),
			_mm_load_ss(reinterpret_cast<const float*>(&p.y))
		);
	}

	inline sup::cpp::SIMD __fastcall SIMDLoadUInt2A(const UINT2A& p)
	{
		return _mm_castsi128_ps(
			_mm_loadl_epi64(reinterpret_cast<const __m128i*>(p.ui))
		);
	}

	inline sup::cpp::SIMD __fastcall SIMDLoadFloat2(float x, float y)
	{
		return _mm_unpacklo_ps(
			_mm_load_ss(&x),
			_mm_load_ss(&y)
		);
	}

	inline sup::cpp::SIMD __fastcall SIMDLoadFloat2(const float* p)
	{
		return _mm_unpacklo_ps(
			_mm_load_ss(&p[0]),
			_mm_load_ss(&p[1])
		);
	}

	inline sup::cpp::SIMD __fastcall SIMDLoadFloat2(const FLOAT2& p)
	{
		return _mm_unpacklo_ps(
			_mm_load_ss(&p.x),
			_mm_load_ss(&p.y)
		);
	}

	inline sup::cpp::SIMD __fastcall SIMDLoadFloat2A(const float* p)
	{
		return _mm_castsi128_ps(
			_mm_loadl_epi64(reinterpret_cast<const __m128i*>(p))
		);
	}

	inline sup::cpp::SIMD __fastcall SIMDLoadFloat2A(const FLOAT2A& p)
	{
		return _mm_castsi128_ps(
			_mm_loadl_epi64(reinterpret_cast<const __m128i*>(p.f))
		);
	}

	inline sup::cpp::SIMD __fastcall SIMDLoadInt3(const INT3& p)
	{
		return _mm_movelh_ps(
			_mm_unpacklo_ps(
				_mm_load_ss(reinterpret_cast<const float*>(&p.x)),
				_mm_load_ss(reinterpret_cast<const float*>(&p.y))
			),
			_mm_load_ss(reinterpret_cast<const float*>(&p.z))
		);
	}

	inline sup::cpp::SIMD __fastcall SIMDLoadInt3A(const INT3A& p)
	{
		return _mm_and_ps(
			_mm_load_ps(reinterpret_cast<const float*>(p.i)),
			kSIMDMask2
		);
	}

	inline sup::cpp::SIMD __fastcall SIMDLoadUInt3(const UINT3& p)
	{
		return _mm_movelh_ps(
			_mm_unpacklo_ps(
				_mm_load_ss(reinterpret_cast<const float*>(&p.x)),
				_mm_load_ss(reinterpret_cast<const float*>(&p.y))
			),
			_mm_load_ss(reinterpret_cast<const float*>(&p.z))
		);
	}

	inline sup::cpp::SIMD __fastcall SIMDLoadUInt3A(const UINT3A& p)
	{
		return _mm_and_ps(
			_mm_load_ps(reinterpret_cast<const float*>(p.ui)),
			kSIMDMask2
		);
	}

	inline sup::cpp::SIMD __fastcall SIMDLoadFloat3(float x, float y, float z)
	{
		return _mm_movelh_ps(
			_mm_unpacklo_ps(
				_mm_load_ss(&x),
				_mm_load_ss(&y)
			),
			_mm_load_ss(&z)
		);
	}

	inline sup::cpp::SIMD __fastcall SIMDLoadFloat3(const float* p)
	{
		return _mm_movelh_ps(
			_mm_unpacklo_ps(
				_mm_load_ss(&p[0]),
				_mm_load_ss(&p[1])
			),
			_mm_load_ss(&p[2])
		);
	}

	inline sup::cpp::SIMD __fastcall SIMDLoadFloat3(const FLOAT3& p)
	{
		return _mm_movelh_ps(
			_mm_unpacklo_ps(
				_mm_load_ss(&p.x),
				_mm_load_ss(&p.y)
			),
			_mm_load_ss(&p.z)
		);
	}

	inline sup::cpp::SIMD __fastcall SIMDLoadFloat3A(const float* p)
	{
		return _mm_and_ps(
			_mm_load_ps(p),
			kSIMDMask2
		);
	}

	inline sup::cpp::SIMD __fastcall SIMDLoadFloat3A(const FLOAT3& p)
	{
		return _mm_and_ps(
			_mm_load_ps(p.f),
			kSIMDMask2
		);
	}

	inline sup::cpp::SIMD __fastcall SIMDLoadInt4(const INT4& p)
	{
		return _mm_loadu_ps(reinterpret_cast<const float*>(p.i));
	}

	inline sup::cpp::SIMD __fastcall SIMDLoadInt4A(const INT4A& p)
	{
		return _mm_load_ps(reinterpret_cast<const float*>(p.i));
	}

	inline sup::cpp::SIMD __fastcall SIMDLoadUInt4(const UINT4& p)
	{
		return _mm_loadu_ps(reinterpret_cast<const float*>(p.ui));
	}

	inline sup::cpp::SIMD __fastcall SIMDLoadUInt4A(const UINT4A& p)
	{
		return _mm_load_ps(reinterpret_cast<const float*>(p.ui));
	}

	inline sup::cpp::SIMD __fastcall SIMDLoadFloat4(float x)
	{
		return _mm_load1_ps(&x);
	}

	inline sup::cpp::SIMD __fastcall SIMDLoadFloat4(float x, float y, float z, float w)
	{
		return _mm_setr_ps(x, y, z, w);
	}

	inline sup::cpp::SIMD __fastcall SIMDLoadFloat4(const float* p)
	{
		return _mm_loadu_ps(p);
	}

	inline sup::cpp::SIMD __fastcall SIMDLoadFloat4(const FLOAT4& p)
	{
		return _mm_loadu_ps(p.f);
	}

	inline sup::cpp::SIMD __fastcall SIMDLoadFloat4A(const float* p)
	{
		return _mm_load_ps(p);
	}

	inline sup::cpp::SIMD __fastcall SIMDLoadFloat4A(const FLOAT4& p)
	{
		return _mm_load_ps(p.f);
	}

//----------------------------------------------------------------------------------------------------------------------------------------------------
	void __fastcall SIMDStoreInt(int* dest, const sup::cpp::SIMD& si)
	{
		_mm_store_ss(reinterpret_cast<float*>(dest), si);
	}

	void __fastcall SIMDStoreUInt(std::uint32_t* dest, const sup::cpp::SIMD& si)
	{
		_mm_store_ss(reinterpret_cast<float*>(dest), si);
	}

	inline void __fastcall SIMDStoreFloat(float* dest, const sup::cpp::SIMD& si)
	{
		_mm_store_ss(dest, si);
	}

	inline void __fastcall SIMDStoreInt2(INT2* dest, const sup::cpp::SIMD& si)
	{
		_mm_store_ss(reinterpret_cast<float*>(&dest[0]), si);
		_mm_store_ss(
			reinterpret_cast<float*>(&dest[1]),
			_mm_shuffle_ps(si, si, _MM_SHUFFLE(1, 1, 1, 1))
		);
	}

	inline void __fastcall SIMDStoreInt2A(INT2A* dest, const sup::cpp::SIMD& si)
	{
		_mm_storel_epi64(
			reinterpret_cast<__m128i*>(dest),
			_mm_castps_si128(si)
		);
	}

	inline void __fastcall SIMDStoreUInt2(UINT2* dest, const sup::cpp::SIMD& si)
	{
		_mm_store_ss(reinterpret_cast<float*>(&dest[0]), si);
		_mm_store_ss(
			reinterpret_cast<float*>(&dest[1]),
			_mm_shuffle_ps(si, si, _MM_SHUFFLE(1, 1, 1, 1))
		);
	}

	inline void __fastcall SIMDStoreUInt2A(UINT2A* dest, const sup::cpp::SIMD& si)
	{
		_mm_storel_epi64(
			reinterpret_cast<__m128i*>(dest),
			_mm_castps_si128(si)
		);
	}

	inline void __fastcall SIMDStoreFloat2(float* dest, const sup::cpp::SIMD& si)
	{
		_mm_store_ss(&dest[0], si);
		_mm_store_ss(
			&dest[1],
			_mm_shuffle_ps(si, si, _MM_SHUFFLE(1, 1, 1, 1))
		);
	}

	inline void __fastcall SIMDStoreFloat2(FLOAT2* dest, const sup::cpp::SIMD& si)
	{
		_mm_store_ss(&dest->x, si);
		_mm_store_ss(
			&dest->y,
			_mm_shuffle_ps(si, si, _MM_SHUFFLE(1, 1, 1, 1))
		);
	}

	inline void __fastcall SIMDStoreFloat2A(float* dest, const sup::cpp::SIMD& si)
	{
		_mm_storel_epi64(
			reinterpret_cast<__m128i*>(dest),
			_mm_castps_si128(si)
		);
	}

	inline void __fastcall SIMDStoreFloat2A(FLOAT2A* dest, const sup::cpp::SIMD& si)
	{
		_mm_storel_epi64(
			reinterpret_cast<__m128i*>(dest),
			_mm_castps_si128(si)
		);
	}

	inline void __fastcall SIMDStoreInt3(INT3* dest, const sup::cpp::SIMD& si)
	{
		_mm_store_ss(reinterpret_cast<float*>(&dest[0]), si);
		_mm_store_ss(
			reinterpret_cast<float*>(&dest[1]),
			_mm_shuffle_ps(si, si, _MM_SHUFFLE(1, 1, 1, 1))
		);
		_mm_store_ss(
			reinterpret_cast<float*>(&dest[2]),
			_mm_shuffle_ps(si, si, _MM_SHUFFLE(1, 1, 1, 1))
		);
	}

	inline void __fastcall SIMDStoreInt3A(INT3A* dest, const sup::cpp::SIMD& si)
	{
		_mm_storel_epi64(
			reinterpret_cast<__m128i*>(dest),
			_mm_castps_si128(si)
		);
		_mm_store_ss(
			reinterpret_cast<float*>(&dest->i[2]),
			_mm_shuffle_ps(si, si, _MM_SHUFFLE(2, 2, 2, 2))
		);
	}

	inline void __fastcall SIMDStoreUInt3(UINT3* dest, const sup::cpp::SIMD& si)
	{
		_mm_store_ss(reinterpret_cast<float*>(&dest[0]), si);
		_mm_store_ss(
			reinterpret_cast<float*>(&dest[1]),
			_mm_shuffle_ps(si, si, _MM_SHUFFLE(1, 1, 1, 1))
		);
		_mm_store_ss(
			reinterpret_cast<float*>(&dest[2]),
			_mm_shuffle_ps(si, si, _MM_SHUFFLE(1, 1, 1, 1))
		);
	}

	inline void __fastcall SIMDStoreUInt3A(UINT3A* dest, const sup::cpp::SIMD& si)
	{
		_mm_storel_epi64(
			reinterpret_cast<__m128i*>(dest),
			_mm_castps_si128(si)
		);
		_mm_store_ss(
			reinterpret_cast<float*>(&dest->ui[2]),
			_mm_shuffle_ps(si, si, _MM_SHUFFLE(2, 2, 2, 2))
		);
	}

	inline void __fastcall SIMDStoreFloat3(float* dest, const sup::cpp::SIMD& si) 
	{
		_mm_store_ss(&dest[0], si);
		_mm_store_ss(
			&dest[1],
			_mm_shuffle_ps(si, si, _MM_SHUFFLE(1, 1, 1, 1))
		);
		_mm_store_ss(
			&dest[2],
			_mm_shuffle_ps(si, si, _MM_SHUFFLE(2, 2, 2, 2))
		);
	}

	inline void __fastcall SIMDStoreFloat3(FLOAT3* dest, const sup::cpp::SIMD& si)
	{
		_mm_store_ss(&dest->x, si);
		_mm_store_ss(
			&dest->y,
			_mm_shuffle_ps(si, si, _MM_SHUFFLE(1, 1, 1, 1))
		);
		_mm_store_ss(
			&dest->z,
			_mm_shuffle_ps(si, si, _MM_SHUFFLE(2, 2, 2, 2))
		);
	}

	inline void __fastcall SIMDStoreFloat3A(float* dest, const sup::cpp::SIMD& si)
	{
		_mm_storel_epi64(
			reinterpret_cast<__m128i*>(dest),
			_mm_castps_si128(si)
		);
		_mm_store_ss(
			reinterpret_cast<float*>(&dest[2]),
			_mm_shuffle_ps(si, si, _MM_SHUFFLE(2, 2, 2, 2))
		);
	}

	inline void __fastcall SIMDStoreFloat3A(FLOAT3A* dest, const sup::cpp::SIMD& si)
	{
		_mm_storel_epi64(
			reinterpret_cast<__m128i*>(dest),
			_mm_castps_si128(si)
		);
		_mm_store_ss(
			reinterpret_cast<float*>(&dest->z),
			_mm_shuffle_ps(si, si, _MM_SHUFFLE(2, 2, 2, 2))
		);
	}

	inline void __fastcall SIMDStoreInt4(INT4* dest, const sup::cpp::SIMD& si)
	{
		_mm_storeu_si128(reinterpret_cast<__m128i*>(dest), _mm_castps_si128(si));
	}

	inline void __fastcall SIMDStoreInt4A(INT4A* dest, const sup::cpp::SIMD& si)
	{
		_mm_store_si128(reinterpret_cast<__m128i*>(dest), _mm_castps_si128(si));
	}

	inline void __fastcall SIMDStoreUInt4(UINT4* dest, const sup::cpp::SIMD& si)
	{
		_mm_storeu_si128(reinterpret_cast<__m128i*>(dest), _mm_castps_si128(si));
	}

	inline void __fastcall SIMDStoreUInt4A(UINT4A* dest, const sup::cpp::SIMD& si)
	{
		_mm_store_si128(reinterpret_cast<__m128i*>(dest), _mm_castps_si128(si));
	}

	inline void __fastcall SIMDStoreFloat4(float* dest, const sup::cpp::SIMD& si)
	{ 
		_mm_storeu_ps(dest, si);
	}

	inline void __fastcall SIMDStoreFloat4(FLOAT4* dest, const sup::cpp::SIMD& si)
	{
		_mm_storeu_ps(reinterpret_cast<float*>(dest), si);
	}

	inline void __fastcall SIMDStoreFloat4A(float* dest, const sup::cpp::SIMD& si)
	{
		_mm_store_ps(dest, si);
	}

	inline void __fastcall SIMDStoreFloat4A(FLOAT4* dest, const sup::cpp::SIMD& si)
	{
		_mm_storeu_ps(reinterpret_cast<float*>(dest), si);
	}

//----------------------------------------------------------------------------------------------------------------------------------------------------
	inline sup::cpp::SIMD __fastcall SIMDSetIntX(const sup::cpp::SIMD& si, std::int32_t i)
	{
		return _mm_move_ss(
			si,
			_mm_load_ss(reinterpret_cast<float*>(&i))
		);
	}

	inline sup::cpp::SIMD __fastcall SIMDSetIntY(const sup::cpp::SIMD& si, std::int32_t i)
	{
		SIMD temp = _mm_move_ss(
			_mm_shuffle_ps(si, si, _MM_SHUFFLE(3, 2, 0, 1)),
			_mm_load_ss(reinterpret_cast<float*>(&i))
		);
		return _mm_shuffle_ps(temp, temp, _MM_SHUFFLE(3, 2, 0, 1));
	}

	inline sup::cpp::SIMD __fastcall SIMDSetIntZ(const sup::cpp::SIMD& si, std::int32_t i)
	{
		SIMD temp = _mm_move_ss(
			_mm_shuffle_ps(si, si, _MM_SHUFFLE(3, 0, 1, 2)),
			_mm_load_ss(reinterpret_cast<float*>(&i))
		);
		return _mm_shuffle_ps(temp, temp, _MM_SHUFFLE(3, 0, 1, 2));
	}

	inline sup::cpp::SIMD __fastcall SIMDSetIntW(const sup::cpp::SIMD& si, std::int32_t i)
	{
		SIMD temp = _mm_move_ss(
			_mm_shuffle_ps(si, si, _MM_SHUFFLE(0, 2, 1, 3)),
			_mm_load_ss(reinterpret_cast<float*>(&i))
		);
		return _mm_shuffle_ps(temp, temp, _MM_SHUFFLE(0, 2, 1, 3));
	}

	inline sup::cpp::SIMD __fastcall SIMDSetUIntX(const sup::cpp::SIMD& si, std::uint32_t ui)
	{
		return _mm_move_ss(
			si,
			_mm_load_ss(reinterpret_cast<float*>(&ui))
		);
	}

	inline sup::cpp::SIMD __fastcall SIMDSetUIntY(const sup::cpp::SIMD& si, std::uint32_t ui)
	{
		SIMD temp = _mm_move_ss(
			_mm_shuffle_ps(si, si, _MM_SHUFFLE(3, 2, 0, 1)),
			_mm_load_ss(reinterpret_cast<float*>(&ui))
		);
		return _mm_shuffle_ps(temp, temp, _MM_SHUFFLE(3, 2, 0, 1));
	}

	inline sup::cpp::SIMD __fastcall SIMDSetUIntZ(const sup::cpp::SIMD& si, std::uint32_t ui)
	{
		SIMD temp = _mm_move_ss(
			_mm_shuffle_ps(si, si, _MM_SHUFFLE(3, 0, 1, 2)),
			_mm_load_ss(reinterpret_cast<float*>(&ui))
		);
		return _mm_shuffle_ps(temp, temp, _MM_SHUFFLE(3, 0, 1, 2));
	}

	inline sup::cpp::SIMD __fastcall SIMDSetUIntW(const sup::cpp::SIMD& si, std::uint32_t ui)
	{
		SIMD temp = _mm_move_ss(
			_mm_shuffle_ps(si, si, _MM_SHUFFLE(0, 2, 1, 3)),
			_mm_load_ss(reinterpret_cast<float*>(&ui))
		);
		return _mm_shuffle_ps(temp, temp, _MM_SHUFFLE(0, 2, 1, 3));
	}

	inline sup::cpp::SIMD __fastcall SIMDSetFloatX(const sup::cpp::SIMD& si, float f)
	{
		return _mm_move_ss(
			si,
			_mm_load_ss(&f)
		);
	}

	inline sup::cpp::SIMD __fastcall SIMDSetFloatY(const sup::cpp::SIMD& si, float f)
	{
		SIMD temp = _mm_move_ss(
			_mm_shuffle_ps(si, si, _MM_SHUFFLE(3, 2, 0, 1)),
			_mm_load_ss(&f)
		);
		return _mm_shuffle_ps(temp, temp, _MM_SHUFFLE(3, 2, 0, 1));
	}

	inline sup::cpp::SIMD __fastcall SIMDSetFloatZ(const sup::cpp::SIMD& si, float f)
	{
		SIMD temp = _mm_move_ss(
			_mm_shuffle_ps(si, si, _MM_SHUFFLE(3, 0, 1, 2)),
			_mm_load_ss(&f)
		);
		return _mm_shuffle_ps(temp, temp, _MM_SHUFFLE(3, 0, 1, 2));
	}

	inline sup::cpp::SIMD __fastcall SIMDSetFloatW(const sup::cpp::SIMD& si, float f)
	{
		SIMD temp = _mm_move_ss(
			_mm_shuffle_ps(si, si, _MM_SHUFFLE(0, 2, 1, 3)),
			_mm_load_ss(&f)
		);
		return _mm_shuffle_ps(temp, temp, _MM_SHUFFLE(0, 2, 1, 3));
	}

//----------------------------------------------------------------------------------------------------------------------------------------------------
	inline std::int32_t __fastcall SIMDGetIntX(const sup::cpp::SIMD& si)
	{
		return _mm_cvtsi128_si32(
			_mm_castps_si128(si)
		);
	}

	inline std::int32_t __fastcall SIMDGetIntY(const sup::cpp::SIMD& si)
	{
		return _mm_cvtsi128_si32(
			_mm_castps_si128(
				_mm_shuffle_ps(si, si, _MM_SHUFFLE(1, 1, 1, 1))
			)
		);
	}

	inline std::int32_t __fastcall SIMDGetIntZ(const sup::cpp::SIMD& si)
	{
		return _mm_cvtsi128_si32(
			_mm_castps_si128(
				_mm_shuffle_ps(si, si, _MM_SHUFFLE(2, 2, 2, 2))
			)
		);
	}

	inline std::int32_t __fastcall SIMDGetIntW(const sup::cpp::SIMD& si)
	{
		return _mm_cvtsi128_si32(
			_mm_castps_si128(
				_mm_shuffle_ps(si, si, _MM_SHUFFLE(3, 3, 3, 3))
			)
		);
	}

	inline std::uint32_t __fastcall SIMDGetUIntX(const sup::cpp::SIMD& si)
	{
		return static_cast<std::uint32_t>(
			_mm_cvtsi128_si32(
				_mm_castps_si128(si)
			)
		);
	}

	std::uint32_t __fastcall SIMDGetUIntY(const sup::cpp::SIMD& si)
	{
		return static_cast<std::uint32_t>(
			_mm_cvtsi128_si32(
				_mm_castps_si128(
					_mm_shuffle_ps(si, si, _MM_SHUFFLE(1, 1, 1, 1))
				)
			)
		);
	}

	inline std::uint32_t __fastcall SIMDGetUIntZ(const sup::cpp::SIMD& si)
	{
		return static_cast<std::uint32_t>(
			_mm_cvtsi128_si32(
				_mm_castps_si128(
					_mm_shuffle_ps(si, si, _MM_SHUFFLE(2, 2, 2, 2))
				)
			)
		);
	}

	inline std::uint32_t __fastcall SIMDGetUIntW(const sup::cpp::SIMD& si)
	{
		return static_cast<std::uint32_t>(
			_mm_cvtsi128_si32(
				_mm_castps_si128(
					_mm_shuffle_ps(si, si, _MM_SHUFFLE(3, 3, 3, 3))
				)
			)
		);
	}

	inline float __fastcall SIMDGetFloatX(const sup::cpp::SIMD& si)
	{ 
		return _mm_cvtss_f32(si);
	}

	inline float __fastcall SIMDGetFloatY(const sup::cpp::SIMD& si)
	{ 
		return _mm_cvtss_f32(
			_mm_shuffle_ps(si, si, _MM_SHUFFLE(1, 1, 1, 1))
		);
	}

	inline float __fastcall SIMDGetFloatZ(const sup::cpp::SIMD& si)
	{ 
		return _mm_cvtss_f32(
			_mm_shuffle_ps(si, si, _MM_SHUFFLE(2, 2, 2, 2))
		); 
	}

	inline float __fastcall SIMDGetFloatW(const sup::cpp::SIMD& si)
	{ 
		return _mm_cvtss_f32(
			_mm_shuffle_ps(si, si, _MM_SHUFFLE(3, 3, 3, 3))
		);
	}

//----------------------------------------------------------------------------------------------------------------------------------------------------
	inline sup::cpp::SIMD __fastcall SIMDMove(const sup::cpp::SIMD& si1, const sup::SIMD& si2)
	{
		return _mm_move_ss(si1, si2);
	}

	inline sup::cpp::SIMD __fastcall SIMDMoveLow(const sup::cpp::SIMD& si1, const sup::SIMD& si2)
	{
		return _mm_movelh_ps(si1, si2);
	}

	inline sup::cpp::SIMD __fastcall SIMDMoveHigh(const sup::cpp::SIMD& si1, const sup::SIMD& si2)
	{
		return _mm_movelh_ps(si1, si2);
	}

	inline sup::cpp::SIMD __fastcall SIMDPackLow(const sup::cpp::SIMD& si1, const sup::SIMD& si2)
	{
		return _mm_unpacklo_ps(si1, si2);
	}

	inline sup::cpp::SIMD __fastcall SIMDPackHigh(const sup::cpp::SIMD& si1, const sup::SIMD& si2)
	{
		return _mm_unpackhi_ps(si1, si2);
	}

	inline sup::cpp::SIMD __fastcall SIMDPack3(const sup::cpp::SIMD& si1, const sup::cpp::SIMD& si2, const sup::cpp::SIMD& si3)
	{
		return _mm_movelh_ps(
			_mm_unpacklo_ps(si1, si2),
			si3
		);
	}

	inline sup::cpp::SIMD __fastcall SIMDPack4(const sup::cpp::SIMD& si1, const sup::cpp::SIMD& si2, const sup::cpp::SIMD& si3, const sup::cpp::SIMD& si4)
	{
		SIMD temp = _mm_unpacklo_ps(_mm_unpacklo_ps(si1, si2), _mm_unpacklo_ps(si3, si4));
		return _mm_shuffle_ps(temp, temp, _MM_SHUFFLE(3, 1, 2, 0));
	}

	template<unsigned int imm8>
	inline sup::cpp::SIMD __fastcall SIMDSort(const sup::cpp::SIMD& si)
	{
		return _mm_shuffle_ps(si, si, imm8);
	}

	template<unsigned int pos>
	inline sup::cpp::SIMD __fastcall SIMDFill(const sup::cpp::SIMD& si)
	{
		return SIMDSort<_MM_SHUFFLE(pos, pos, pos, pos)>(si);
	}

//----------------------------------------------------------------------------------------------------------------------------------------------------
	inline sup::cpp::SIMD __fastcall SIMDAdd(const sup::SIMD& f1, const sup::SIMD& f2) 
	{ 
		return _mm_add_ps(f1, f2); 
	}

	inline sup::cpp::SIMD __fastcall SIMDSub(const sup::SIMD& f1, const sup::SIMD& f2) 
	{ 
		return _mm_sub_ps(f1, f2);
	}

	inline sup::cpp::SIMD __fastcall SIMDMul(const sup::SIMD& f1, const sup::SIMD& f2) 
	{ 
		return _mm_mul_ps(f1, f2); 
	}

	inline sup::cpp::SIMD __fastcall SIMDDiv(const sup::SIMD& f1, const sup::SIMD& f2) 
	{ 
		return _mm_div_ps(f1, f2); 
	}

	inline sup::cpp::SIMD __fastcall SIMDHAdd2(const sup::SIMD& si) 
	{ 
		return _mm_hadd_ps(si, si); 
	}

	inline sup::cpp::SIMD __fastcall SIMDHAdd3(const sup::SIMD& si) 
	{ 
		return _mm_add_ss(
			_mm_hadd_ps(si, si), 
			_mm_shuffle_ps(si, si, _MM_SHUFFLE(2, 2, 2, 2))
		); 
	}

	inline sup::cpp::SIMD __fastcall SIMDHAdd4(const sup::SIMD& si) 
	{ 
		SIMD temp = _mm_hadd_ps(si, si);
		return _mm_hadd_ps(temp, temp);
	}

	inline sup::cpp::SIMD __fastcall SIMDHSub2(const sup::SIMD& si) 
	{ 
		return _mm_hsub_ps(si, si); 
	}

	inline sup::cpp::SIMD __fastcall SIMDHSub3(const sup::SIMD& si) 
	{ 
		return _mm_sub_ss(
			_mm_hsub_ps(si, si), 
			_mm_shuffle_ps(si, si, _MM_SHUFFLE(2, 2, 2, 2))
		); 
	}

	inline sup::cpp::SIMD __fastcall SIMDHSub4(const sup::SIMD& si) 
	{
		return _mm_hsub_ps(
			_mm_move_ss(
				_mm_hadd_ps(si, si),
				_mm_hsub_ps(si, si)
			),
			_mm_setzero_ps()
		);
	}

	inline sup::cpp::SIMD __fastcall SIMDSqrt(const sup::SIMD& si) 
	{ 
		return _mm_sqrt_ss(si); 
	}

	inline sup::cpp::SIMD __fastcall SIMDSqrt4(const sup::SIMD& si) 
	{ 
		return _mm_sqrt_ps(si); 
	}

	inline sup::cpp::SIMD __fastcall SIMDMin(const sup::SIMD& si1, const sup::SIMD& si2)
	{
		return _mm_min_ss(si1, si2);
	}

	inline sup::cpp::SIMD __fastcall SIMDMin4(const sup::SIMD& si1, const sup::SIMD& si2)
	{
		return _mm_min_ps(si1, si2);
	}

	inline sup::cpp::SIMD __fastcall SIMDMax(const sup::SIMD& si1, const sup::SIMD& si2)
	{
		return _mm_max_ss(si1, si2);
	}

	inline sup::cpp::SIMD __fastcall SIMDMax4(const sup::SIMD& si1, const sup::SIMD& si2)
	{
		return _mm_max_ps(si1, si2);
	}

//----------------------------------------------------------------------------------------------------------------------------------------------------
	inline sup::cpp::SIMD __fastcall SIMDAnd(const sup::SIMD& si1, const sup::SIMD& si2)
	{
		return _mm_and_ps(si1, si2);
	}

	inline sup::cpp::SIMD __fastcall SIMDAndNot(const sup::SIMD& si1, const sup::SIMD& si2)
	{
		return _mm_andnot_ps(si1, si2);
	}

	inline sup::cpp::SIMD __fastcall SIMDOr(const sup::SIMD& si1, const sup::SIMD& si2)
	{
		return _mm_or_ps(si1, si2);
	}

	inline sup::cpp::SIMD __fastcall SIMDXor(const sup::SIMD& si1, const sup::SIMD& si2)
	{
		return _mm_xor_ps(si1, si2);
	}

//----------------------------------------------------------------------------------------------------------------------------------------------------
	inline sup::cpp::SIMD __fastcall SIMDCompEqual4(const sup::SIMD& si1, const sup::SIMD& si2)
	{
		return _mm_cmpeq_ps(si1, si2);
	}

	inline sup::cpp::SIMD __fastcall SIMDCompNotEqual4(const sup::SIMD& si1, const sup::SIMD& si2)
	{
		return _mm_cmpneq_ps(si1, si2);
	}

	inline sup::cpp::SIMD __fastcall SIMDCompLess4(const sup::SIMD si1, const sup::SIMD& si2)
	{
		return _mm_cmplt_ps(si1, si2);
	}

	inline sup::cpp::SIMD __fastcall SIMDCompNotLess4(const sup::SIMD si1, const sup::SIMD& si2)
	{
		return _mm_cmpnlt_ps(si1, si2);
	}

	inline sup::cpp::SIMD __fastcall SIMDCompLessEqual4(const sup::SIMD si1, const sup::SIMD& si2)
	{
		return _mm_cmple_ps(si1, si2);
	}

	inline sup::cpp::SIMD __fastcall SIMDCompNotLessEqual4(const sup::SIMD si1, const sup::SIMD& si2)
	{
		return _mm_cmpnle_ps(si1, si2);
	}

	inline sup::cpp::SIMD __fastcall SIMDCompGreater4(const sup::SIMD si1, const sup::SIMD& si2)
	{
		return _mm_cmpgt_ps(si1, si2);
	}

	inline sup::cpp::SIMD __fastcall SIMDCompNotGreater4(const sup::SIMD si1, const sup::SIMD& si2)
	{
		return _mm_cmpngt_ps(si1, si2);
	}

	inline sup::cpp::SIMD __fastcall SIMDCompGreaterEqual4(const sup::SIMD si1, const sup::SIMD& si2)
	{
		return _mm_cmpge_ps(si1, si2);
	}

	inline sup::cpp::SIMD __fastcall SIMDCompNotGreaterEqual4(const sup::SIMD si1, const sup::SIMD& si2)
	{
		return _mm_cmpnge_ps(si1, si2);
	}
}
}