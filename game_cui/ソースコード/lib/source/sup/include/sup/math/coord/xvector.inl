/**
* @file xvector.inl
* @brief xvectorèàóùé¿ëïÉtÉ@ÉCÉã
*/

namespace sup
{
inline namespace math
{
namespace details
{
//----------------------------------------------------------------------------------------------------------------------------------------------------
//helper
	inline SIMD __fastcall SIMD2Dot(const SIMD& v1, const SIMD& v2)
	{
		return SIMDHAdd2(
			SIMDMul(v1, v2)
		);
	}

	inline SIMD __fastcall SIMD2Cross(const SIMD& v1, const SIMD& v2)
	{
		return SIMDHSub2(
			SIMDMul(
				v1,
				SIMDSort<SIMD_SHUFFLE(1, 0, 2, 3)>(v2)
			)
		);
	}

	inline SIMD __fastcall SIMD2SquareSize(const SIMD& v)
	{
		return SIMDHAdd2(
			SIMDMul(v, v)
		);
	}

	inline SIMD __fastcall SIMD3Dot(const SIMD& v1, const SIMD& v2)
	{
		return SIMDHAdd3(
			SIMDMul(v1, v2)
		);
	}
	
	inline SIMD __fastcall SIMD3Cross(const SIMD& v1, const SIMD& v2)
	{
		SIMD temp = SIMDMul(
			SIMDSort<SIMD_SHUFFLE(1, 2, 0, 3)>(v1),
			SIMDSort<SIMD_SHUFFLE(2, 0, 1, 3)>(v2)
		); 
		SIMD temp2 = SIMDMul(
			SIMDSort<SIMD_SHUFFLE(2, 0, 1, 3)>(v1),
			SIMDSort<SIMD_SHUFFLE(1, 2, 0, 3)>(v2)
		);
		return SIMDSub(temp, temp2);
	}

	inline SIMD __fastcall SIMD3SquareSize(const SIMD& v)
	{
		return SIMDHAdd3(
			SIMDMul(v, v)
		);
	}

	inline SIMD __fastcall SIMD4Dot(const SIMD& v1, const SIMD& v2)
	{
		return SIMDHAdd4(
			SIMDMul(v1, v2)
		);
	}

	inline SIMD __fastcall SIMD4Cross(const SIMD& v1, const SIMD& v2)
	{
		SIMD temp1 = SIMDMul(
			SIMDSort<SIMD_SHUFFLE(1, 0, 0, 3)>(v1),
			SIMDSort<SIMD_SHUFFLE(2, 2, 1, 3)>(v1)
		);
		temp1 = SIMDMul(temp1, kSIMDMinus1);

		SIMD temp2 = SIMDMul(
			SIMDSort<SIMD_SHUFFLE(2, 2, 1, 3)>(v2),
			SIMDSort<SIMD_SHUFFLE(1, 0, 0, 3)>(v2)
		);
		temp2 = SIMDMul(SIMDMul(temp2, kSIMDMinus0), kSIMDMinus2);

		SIMD ans;
		ans = SIMDAdd(temp1, temp2);
		ans = SIMDAnd(ans, kSIMDMask2);

		return ans;
	}
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
//class
	inline XVECTOR::XVECTOR()noexcept :
		si(SIMDLoadZero())
	{
	}

	inline XVECTOR XVECTOR::operator+(const XVECTOR& v)const
	{
		XVECTOR ans;
		ans.si = SIMDAdd(this->si, v.si);
		return ans;
	}

	inline XVECTOR XVECTOR::operator-(const XVECTOR& v)const
	{
		XVECTOR ans;
		ans.si = SIMDAdd(this->si, v.si);
		return ans;
	}

	inline void XVECTOR::operator+=(const XVECTOR& v)
	{
		this->si = SIMDAdd(this->si, v.si);
	}

	inline void XVECTOR::operator-=(const XVECTOR& v)
	{
		this->si = SIMDSub(this->si, v.si);
	}

	template<typename T, std::enable_if_t<std::is_integral_v<T> || std::is_floating_point_v<T>, std::nullptr_t>>
	inline XVECTOR XVECTOR::operator*(T s)const
	{
		XVECTOR ans;
		ans.si = SIMDMul(
			this->si,
			SIMDLoadFloat4(static_cast<float>(s))
		);
		return ans;
	}

	template<typename T, std::enable_if_t<std::is_integral_v<T> || std::is_floating_point_v<T>, std::nullptr_t>>
	inline XVECTOR XVECTOR::operator/(T s)const
	{
		XVECTOR ans;
		ans.si = SIMDDiv(
			this->si,
			SIMDLoadFloat4(static_cast<float>(s))
		);
		return ans;
	}

	template<typename T, std::enable_if_t<std::is_integral_v<T> || std::is_floating_point_v<T>, std::nullptr_t>>
	inline void XVECTOR::operator*=(T s)
	{
		this->si = SIMDMul(
			this->si,
			SIMDLoadFloat4(static_cast<float>(s))
		);
	}

	template<typename T, std::enable_if_t<std::is_integral_v<T> || std::is_floating_point_v<T>, std::nullptr_t>>
	inline void XVECTOR::operator/=(T s)
	{
		this->si = SIMDDiv(
			this->si,
			SIMDLoadFloat4(static_cast<float>(s))
		);
	}

//----------------------------------------------------------------------------------------------------------------------------------------------------
//xvector function
	//load
	inline XVECTOR __fastcall XVectorLoadZero()
	{
		XVECTOR ans;
		ans.si = SIMDLoadZero();
		return ans;
	}

	inline XVECTOR __fastcall XVectorLoadVector2(const VECTOR2& v)
	{
		XVECTOR ans;
		ans.si = SIMDLoadFloat2(v.v);
		return ans;
	}

	inline XVECTOR __fastcall XVectorLoadVector2A(const VECTOR2A& v)
	{
		XVECTOR ans;
		ans.si = SIMDLoadFloat2A(v.v);
		return ans;
	}

	inline XVECTOR __fastcall XVectorLoadVector3(const VECTOR3& v)
	{
		XVECTOR ans;
		ans.si = SIMDLoadFloat3(v.v);
		return ans;
	}

	inline XVECTOR __fastcall XVectorLoadVector3A(const VECTOR3A& v)
	{
		XVECTOR ans;
		ans.si = SIMDLoadFloat3A(v.v);
		return ans;
	}

	inline XVECTOR __fastcall XVectorLoadVector4(const VECTOR4& v)
	{
		XVECTOR ans;
		ans.si = SIMDLoadFloat4(v.v);
		return ans;
	}

	inline XVECTOR __fastcall XVectorLoadVector4A(const VECTOR4A& v)
	{
		XVECTOR ans;
		ans.si = SIMDLoadFloat4A(v.v);
		return ans;
	}

	//store
	inline void __fastcall XVectorStoreVector2(const XVECTOR& xv, VECTOR2* v)
	{
		SIMDStoreFloat2(v->v, xv.si);
	}

	inline void __fastcall XVectorStoreVector2A(const XVECTOR& xv, VECTOR2A* v)
	{
		SIMDStoreFloat2A(v->v, xv.si);
	}

	inline void __fastcall XVectorStoreVector3(const XVECTOR& xv, VECTOR3* v)
	{
		SIMDStoreFloat3(v->v, xv.si);
	}

	inline void __fastcall XVectorStoreVector3A(const XVECTOR& xv, VECTOR3A* v)
	{
		SIMDStoreFloat3A(v->v, xv.si);
	}

	inline void __fastcall XVectorStoreVector4(const XVECTOR& xv, VECTOR4* v)
	{
		SIMDStoreFloat4(v->v, xv.si);
	}

	inline void __fastcall XVectorStoreVector4A(const XVECTOR& xv, VECTOR4A* v)
	{
		SIMDStoreFloat4A(v->v, xv.si);
	}

	//set
	inline XVECTOR __fastcall XVectorSetX(const XVECTOR& v, float x)
	{
		XVECTOR ans;
		ans.si = SIMDSetFloatX(v.si, x);
		return ans;
	}

	inline XVECTOR __fastcall XVectorSetY(const XVECTOR& v, float y)
	{
		XVECTOR ans;
		ans.si = SIMDSetFloatY(v.si, y);
		return ans;
	}

	inline XVECTOR __fastcall XVectorSetZ(const XVECTOR& v, float z)
	{
		XVECTOR ans;
		ans.si = SIMDSetFloatZ(v.si, z);
		return ans;
	}

	inline XVECTOR __fastcall XVectorSetW(const XVECTOR& v, float w)
	{
		XVECTOR ans;
		ans.si = SIMDSetFloatW(v.si, w);
		return ans;
	}

	//get
	inline float __fastcall XVectorGetX(const XVECTOR& v)
	{
		return SIMDGetFloatX(v.si);
	}

	inline float __fastcall XVectorGetY(const XVECTOR& v)
	{
		return SIMDGetFloatY(v.si);
	}

	inline float __fastcall XVectorGetZ(const XVECTOR& v)
	{
		return SIMDGetFloatZ(v.si);
	}

	inline float __fastcall XVectorGetW(const XVECTOR& v)
	{
		return SIMDGetFloatW(v.si);
	}

	//arithmetic 
	inline XVECTOR __fastcall XVectorAdd(const XVECTOR& v1, const XVECTOR& v2)
	{
		XVECTOR ans;
		ans.si = SIMDAdd(v1.si, v2.si);
		return ans;
	}

	inline XVECTOR __fastcall XVectorSub(const XVECTOR& v1, const XVECTOR& v2)
	{
		XVECTOR ans;
		ans.si = SIMDSub(v1.si, v2.si);
		return ans;
	}

	template<typename T, std::enable_if_t<std::is_integral_v<T> || std::is_floating_point_v<T>, std::nullptr_t>>
	inline  XVECTOR __fastcall XVectorMul(const XVECTOR& v, T s)
	{
		XVECTOR ans;
		ans.si = SIMDMul(
			v.si,
			SIMDLoadFloat4(static_cast<float>(s))
		);
		return ans;
	}

	template<typename T, std::enable_if_t<std::is_integral_v<T> || std::is_floating_point_v<T>, std::nullptr_t>>
	inline XVECTOR __fastcall XVectorDiv(const XVECTOR& v, T s)
	{
		XVECTOR ans;
		ans.si = SIMDDiv(
			v.si,
			SIMDLoadFloat4(static_cast<float>(s))
		);
		return ans;
	}

	//vector2
	inline XVECTOR __fastcall XVector2Transform(const XVECTOR& v, const XMATRIX& m)
	{
		XVECTOR ans;
		SIMD mul = SIMDSetFloatZ(v.si, 1.0f);
		ans.si = SIMDPack3(
			SIMDHAdd3(
				SIMDMul(mul, m.si[0])
			), 
			SIMDHAdd3(
				SIMDMul(mul, m.si[1])
			), 
			SIMDHAdd3(
				SIMDMul(mul, m.si[2])
			)
		);
		return ans;
	}

	inline XVECTOR __fastcall XVector2Inverse(const XVECTOR& v)
	{
		XVECTOR ans;
		ans.si = SIMDMul(v.si, kSIMDMinus0);
		ans.si = SIMDMul(ans.si, kSIMDMinus1);
		return ans;
	}

	inline XVECTOR __fastcall XVector2Normalize(const XVECTOR& v)
	{
		XVECTOR ans;
		ans.si = SIMDMul(v.si, v.si);
		ans.si = SIMDHAdd2(ans.si);
		ans.si = SIMDSqrt(ans.si);
		ans.si = SIMDDiv(
			v.si, 
			SIMDFill<0>(ans.si)
		);
		return ans;
	}

	inline float __fastcall XVector2Dot(const XVECTOR& v1, const XVECTOR& v2)
	{
		return SIMDGetFloatX(
			details::SIMD2Dot(v1.si, v2.si)
		);
	}

	inline float __fastcall XVector2Cross(const XVECTOR& v1, const XVECTOR& v2)
	{
		return SIMDGetFloatX(
			details::SIMD2Cross(v1.si, v2.si)
		);
	}

	inline float __fastcall XVector2Size(const XVECTOR& v)
	{
		return SIMDGetFloatX(
			SIMDSqrt(
				details::SIMD2SquareSize(v.si)
			)
		);
	}

	inline float __fastcall XVector2SquareSize(const XVECTOR& v)
	{
		return SIMDGetFloatX(
			details::SIMD2SquareSize(v.si)
		);
	}

	inline float __fastcall XVector2BetweenSin(const XVECTOR& start, const XVECTOR& end)
	{
		SIMD v1_size = SIMDSqrt(details::SIMD2SquareSize(start.si));
		SIMD v2_size = SIMDSqrt(details::SIMD2SquareSize(end.si));
		SIMD cross = details::SIMD2Cross(start.si, end.si);
		SIMD ans = SIMDDiv(
			SIMDDiv(cross, v1_size),
			v2_size
		);
		return SIMDGetFloatX(ans);
	}

	float __fastcall XVector2BetweenCos(const XVECTOR& start, const XVECTOR& end)
	{
		SIMD v1_size = SIMDSqrt(details::SIMD2SquareSize(start.si));
		SIMD v2_size = SIMDSqrt(details::SIMD2SquareSize(end.si));
		SIMD dot = details::SIMD2Dot(start.si, end.si);
		SIMD ans = SIMDDiv(
			SIMDDiv(dot, v1_size),
			v2_size
		);
		return SIMDGetFloatX(ans);
	}

	inline float __fastcall XVector2BetweenTan(const XVECTOR& start, const XVECTOR& end)
	{
		SIMD v1_size = SIMDSqrt(details::SIMD2SquareSize(start.si));
		SIMD v2_size = SIMDSqrt(details::SIMD2SquareSize(end.si));

		SIMD cross = details::SIMD2Cross(start.si, end.si);
		SIMD sin = SIMDDiv(
			SIMDDiv(cross, v1_size),
			v2_size
		);

		SIMD dot = details::SIMD2Dot(start.si, end.si);
		SIMD cos = SIMDDiv(
			SIMDDiv(dot, v1_size),
			v2_size
		);

		SIMD ans = SIMDDiv(sin, cos);
		
		return SIMDGetFloatX(ans);
	}

	//vector3
	inline XVECTOR __fastcall XVector3Transform(const XVECTOR& v, const XMATRIX& m)
	{
		XVECTOR ans;
		SIMD mul = SIMDSetFloatW(v.si, 1.0f);
		ans.si = SIMDPack4(
			SIMDHAdd4(
				SIMDMul(mul, m.si[0])
			),
			SIMDHAdd4(
				SIMDMul(mul, m.si[1])
			),
			SIMDHAdd4(
				SIMDMul(mul, m.si[2])
			),
			SIMDHAdd4(
				SIMDMul(mul, m.si[3])
			)
		);
		return ans;
	}

	inline XVECTOR __fastcall XVector3Inverse(const XVECTOR& v)
	{
		XVECTOR ans;
		ans.si = SIMDMul(v.si, kSIMDMinus0);
		ans.si = SIMDMul(ans.si, kSIMDMinus1);
		ans.si = SIMDMul(ans.si, kSIMDMinus2);
		return ans;
	}

	inline XVECTOR __fastcall XVector3Normalize(const XVECTOR& v)
	{
		XVECTOR ans;
		ans.si = SIMDMul(v.si, v.si);
		ans.si = SIMDHAdd3(ans.si);
		ans.si = SIMDSqrt(ans.si);
		ans.si = SIMDDiv(
			v.si, 
			SIMDFill<0>(ans.si)
		);
		return ans;
	}

	inline float __fastcall XVector3Dot(const XVECTOR& v1, const XVECTOR& v2)
	{
		return SIMDGetFloatX(
			details::SIMD3Dot(v1.si, v2.si)
		);
	}

	inline XVECTOR __fastcall XVector3Cross(const XVECTOR& v1, const XVECTOR& v2)
	{
		XVECTOR ans;
		ans.si = details::SIMD3Cross(v1.si, v2.si);
		return ans;
	}
	
	inline float __fastcall XVector3Size(const XVECTOR& v)
	{
		return SIMDGetFloatX(
			SIMDSqrt(
				details::SIMD3SquareSize(v.si)
			)
		);
	}

	inline float __fastcall XVector3SquareSize(const XVECTOR& v)
	{
		return SIMDGetFloatX(
			details::SIMD3SquareSize(v.si)
		);
	}

	inline float __fastcall XVector3BetweenSin(const XVECTOR& start, const XVECTOR& end)
	{
		SIMD v1_size = SIMDSqrt(details::SIMD3SquareSize(start.si));
		SIMD v2_size = SIMDSqrt(details::SIMD3SquareSize(end.si));
		SIMD cross = SIMDSqrt(details::SIMD3SquareSize(details::SIMD3Cross(start.si, end.si)));
		SIMD ans = SIMDDiv(
			SIMDDiv(cross, v1_size),
			v2_size
		);
		return SIMDGetFloatX(ans);
	}

	inline float __fastcall XVector3BetweenCos(const XVECTOR& start, const XVECTOR& end)
	{
		SIMD v1_size = SIMDSqrt(details::SIMD3SquareSize(start.si));
		SIMD v2_size = SIMDSqrt(details::SIMD3SquareSize(end.si));
		SIMD dot = details::SIMD3Dot(start.si, end.si);
		SIMD ans = SIMDDiv(
			SIMDDiv(dot, v1_size),
			v2_size
		);
		return SIMDGetFloatX(ans);
	}

	inline float __fastcall XVector3BetweenTan(const XVECTOR& start, const XVECTOR& end)
	{
		SIMD v1_size = SIMDSqrt(details::SIMD3SquareSize(start.si));
		SIMD v2_size = SIMDSqrt(details::SIMD3SquareSize(end.si));

		SIMD cross = SIMDSqrt(details::SIMD3SquareSize(details::SIMD3Cross(start.si, end.si)));
		SIMD sin = SIMDDiv(
			SIMDDiv(cross, v1_size),
			v2_size
		);

		SIMD dot = details::SIMD3Dot(start.si, end.si);
		SIMD cos = SIMDDiv(
			SIMDDiv(dot, v1_size),
			v2_size
		);

		SIMD ans = SIMDDiv(sin, cos);

		return SIMDGetFloatX(ans);
	}

	//vector4
	inline XVECTOR __fastcall XVector4Transform(const XVECTOR& v, const XMATRIX& m)
	{
		XVECTOR ans;
		ans.si = SIMDPack4(
			SIMDHAdd4(
				SIMDMul(v.si, m.si[0])
			),
			SIMDHAdd4(
				SIMDMul(v.si, m.si[1])
			),
			SIMDHAdd4(
				SIMDMul(v.si, m.si[2])
			),
			SIMDHAdd4(
				SIMDMul(v.si, m.si[3])
			)
		);
		return ans;
	}
	
	inline XVECTOR __fastcall XVector4Inverse(const XVECTOR& v)
	{
		XVECTOR ans;
		ans.si = SIMDMul(v.si, kSIMDMinus0);
		ans.si = SIMDMul(ans.si, kSIMDMinus1);
		ans.si = SIMDMul(ans.si, kSIMDMinus2);
		ans.si = SIMDMul(ans.si, kSIMDMinus3);
		return ans;
	}

	inline float __fastcall XVector4Dot(const XVECTOR& v1, const XVECTOR& v2)
	{
		return SIMDGetFloatX(
			details::SIMD4Dot(v1.si, v2.si)
		);
	}

	inline XVECTOR __fastcall XVector4Cross(const XVECTOR& v1, const XVECTOR& v2)
	{
		XVECTOR ans;
		ans.si = details::SIMD4Cross(v1.si, v2.si);
		return ans;
	}
}
}
