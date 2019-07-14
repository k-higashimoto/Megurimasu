/**
* @file xmatrix.inl
* @brief xmatrixèàóùé¿ëïÉtÉ@ÉCÉã
*/

#include<iterator>

namespace sup
{
inline namespace math
{
//----------------------------------------------------------------------------------------------------------------------------------------------------
//class
	inline XMATRIX XMATRIX::operator+(const XMATRIX& m)const
	{
		XMATRIX ans;
		for(size_t i = 0; i < std::size(this->si); ++i)
		{
			ans.si[i] = SIMDAdd(this->si[i], m.si[i]);
		}
		return ans;
	}

	inline XMATRIX XMATRIX::operator-(const XMATRIX& m)const
	{
		XMATRIX ans;
		for (size_t i = 0; i < std::size(this->si); ++i)
		{
			ans.si[i] = SIMDSub(this->si[i], m.si[i]);
		}
		return ans;
	}

	inline XMATRIX XMATRIX::operator*(const XMATRIX& m)const
	{
		XMATRIX ans;
		XMATRIX temp = m;
		SIMD_TRANSPOSE(temp.si[0], temp.si[1], temp.si[2], temp.si[3]);

		for(size_t i = 0; i < std::size(this->si); ++i)
		{
			ans.si[i] = SIMDPack4(
				SIMDHAdd4(SIMDMul(this->si[i], temp.si[0])),
				SIMDHAdd4(SIMDMul(this->si[i], temp.si[1])),
				SIMDHAdd4(SIMDMul(this->si[i], temp.si[2])),
				SIMDHAdd4(SIMDMul(this->si[i], temp.si[3]))
			);
		}

		return ans;
	}

	inline void XMATRIX::operator+=(const XMATRIX& m)
	{
		for (size_t i = 0; i < std::size(this->si); ++i)
		{
			this->si[i] = SIMDAdd(this->si[i], m.si[i]);
		}
	}

	inline void XMATRIX::operator-=(const XMATRIX& m)
	{
		for (size_t i = 0; i < std::size(this->si); ++i)
		{
			this->si[i] = SIMDSub(this->si[i], m.si[i]);
		}
	}

	inline void XMATRIX::operator*=(const XMATRIX& m)
	{
		XMATRIX ans;
		XMATRIX temp = m;
		SIMD_TRANSPOSE(temp.si[0], temp.si[1], temp.si[2], temp.si[3]);

		for (size_t i = 0; i < std::size(this->si); ++i)
		{
			ans.si[i] = SIMDPack4(
				SIMDHAdd4(SIMDMul(this->si[i], temp.si[0])),
				SIMDHAdd4(SIMDMul(this->si[i], temp.si[1])),
				SIMDHAdd4(SIMDMul(this->si[i], temp.si[2])),
				SIMDHAdd4(SIMDMul(this->si[i], temp.si[3]))
			);
		}

		(*this) = ans;
	}

	template<typename T, std::enable_if_t<std::is_integral_v<T> || std::is_floating_point_v<T>, std::nullptr_t>>
	inline XMATRIX XMATRIX::operator*(T s)const
	{
		XMATRIX ans;
		SIMD temp = SIMDLoadFloat4(static_cast<float>(s));
		for (size_t i = 0; i < std::size(this->si); ++i)
		{
			ans.si[i] = SIMDMul(this->si[i], temp);
		}
		return ans;
	}

	template<typename T, std::enable_if_t<std::is_integral_v<T> || std::is_floating_point_v<T>, std::nullptr_t>>
	inline XMATRIX XMATRIX::operator/(T s)const
	{
		XMATRIX ans;
		SIMD temp = SIMDLoadFloat4(static_cast<float>(s));
		for (size_t i = 0; i < std::size(this->si); ++i)
		{
			ans.si[i] = SIMDDiv(this->si[i], temp);
		}
		return ans;
	}

	template<typename T, std::enable_if_t<std::is_integral_v<T> || std::is_floating_point_v<T>, std::nullptr_t>>
	inline void XMATRIX::operator*=(T s)
	{
		SIMD temp = SIMDLoadFloat4(static_cast<float>(s));
		for (size_t i = 0; i < std::size(this->si); ++i)
		{
			this->si[i] = SIMDMul(this->si[i], temp);
		}
	}

	template<typename T, std::enable_if_t<std::is_integral_v<T> || std::is_floating_point_v<T>, std::nullptr_t>>
	inline void XMATRIX::operator/=(T s)
	{
		SIMD temp = SIMDLoadFloat4(static_cast<float>(s));
		for (size_t i = 0; i < std::size(this->si); ++i)
		{
			this->si[i] = SIMDDiv(this->si[i], temp);
		}
	}

//----------------------------------------------------------------------------------------------------------------------------------------------------
//xmatrix function
//load
	inline XMATRIX __fastcall XMatrixLoadZero()
	{
		XMATRIX ans;
		ans.si[0] = SIMDLoadZero();
		ans.si[1] = SIMDLoadZero();
		ans.si[2] = SIMDLoadZero();
		ans.si[3] = SIMDLoadZero();
		return ans;
	}

	inline XMATRIX __fastcall XMatrixLoadIdentity()
	{
		XMATRIX ans;
		ans.si[0] = kSIMDIdentity0;
		ans.si[1] = kSIMDIdentity1;
		ans.si[2] = kSIMDIdentity2;
		ans.si[3] = kSIMDIdentity3;
		return ans;
	}

	inline XMATRIX __fastcall XMatrixLoadMatrix2X2(const MATRIX2X2& m)
	{
		XMATRIX ans;
		ans.si[0] = SIMDLoadFloat2(m.m[0]);
		ans.si[1] = SIMDLoadFloat2(m.m[1]);
		return ans;
	}

	inline XMATRIX __fastcall XMatrixLoadMatrix2X2A(const MATRIX2X2A& m)
	{
		XMATRIX ans;
		ans.si[0] = SIMDLoadFloat2A(m.m[0]);
		ans.si[1] = SIMDLoadFloat2A(m.m[1]);
		return ans;
	}

	inline XMATRIX __fastcall XMatrixLoadMatrix3X3(const MATRIX3X3& m)
	{
		XMATRIX ans;
		ans.si[0] = SIMDLoadFloat3(m.m[0]);
		ans.si[1] = SIMDLoadFloat3(m.m[1]);
		ans.si[2] = SIMDLoadFloat3(m.m[2]);
		return ans;
	}

	inline XMATRIX __fastcall XMatrixLoadMatrix3X3A(const MATRIX3X3A& m)
	{
		XMATRIX ans;
		ans.si[0] = SIMDLoadFloat3A(m.m[0]);
		ans.si[1] = SIMDLoadFloat3A(m.m[1]);
		ans.si[2] = SIMDLoadFloat3A(m.m[2]);
		return ans;
	}

	inline XMATRIX __fastcall XMatrixLoadMatrix4X4(const MATRIX4X4& m)
	{
		XMATRIX ans;
		ans.si[0] = SIMDLoadFloat4(m.m[0]);
		ans.si[1] = SIMDLoadFloat4(m.m[1]);
		ans.si[2] = SIMDLoadFloat4(m.m[2]);
		ans.si[3] = SIMDLoadFloat4(m.m[3]);
		return ans;
	}

	inline XMATRIX __fastcall XMatrixLoadMatrix4X4A(const MATRIX4X4A& m)
	{
		XMATRIX ans;
		ans.si[0] = SIMDLoadFloat4A(m.m[0]);
		ans.si[1] = SIMDLoadFloat4A(m.m[1]);
		ans.si[2] = SIMDLoadFloat4A(m.m[2]);
		ans.si[3] = SIMDLoadFloat4A(m.m[3]);
		return ans;
	}

	//store
	inline void __fastcall XMatrixStoreMatrix2X2(const XMATRIX& xm, MATRIX2X2* m)
	{
		for(int i = 0; i < 2; ++i)
		{
			SIMDStoreFloat2(m->m[i], xm.si[i]);
		}
	}

	inline void __fastcall XMatrixStoreMatrix2X2A(const XMATRIX& xm, MATRIX2X2A* m)
	{
		for (int i = 0; i < 2; ++i)
		{
			SIMDStoreFloat2A(m->m[i], xm.si[i]);
		}
	}
	
	inline void __fastcall XMatrixStoreMatrix3X3(const XMATRIX& xm, MATRIX3X3* m)
	{
		for (int i = 0; i < 3; ++i)
		{
			SIMDStoreFloat3(m->m[i], xm.si[i]);
		}
	}

	inline void __fastcall XMatrixStoreMatrix3X3A(const XMATRIX& xm, MATRIX3X3A* m)
	{
		for (int i = 0; i < 3; ++i)
		{
			SIMDStoreFloat3A(m->m[i], xm.si[i]);
		}
	}

	inline void __fastcall XMatrixStoreMatrix4X4(const XMATRIX& xm, MATRIX4X4* m)
	{
		for (int i = 0; i < 4; ++i)
		{
			SIMDStoreFloat4(m->m[i], xm.si[i]);
		}
	}

	inline void __fastcall XMatrixStoreMatrix4X4A(const XMATRIX& xm, MATRIX4X4A* m)
	{
		for (int i = 0; i < 4; ++i)
		{
			SIMDStoreFloat4A(m->m[i], xm.si[i]);
		}
	}

	//arithmetic
	inline XMATRIX __fastcall XMatrixTranspose(const XMATRIX& m)
	{
		XMATRIX ans = m;
		SIMD_TRANSPOSE(ans.si[0], ans.si[1], ans.si[2], ans.si[3]);
		return ans;
	}

	inline XMATRIX __fastcall XMatrixAdd(const XMATRIX& m1, const XMATRIX& m2)
	{
		XMATRIX ans;
		for (size_t i = 0; i < 4; ++i)
		{
			ans.si[i] = SIMDAdd(m1.si[i], m2.si[i]);
		}
		return ans;
	}

	inline XMATRIX __fastcall XMatrixSub(const XMATRIX& m1, const XMATRIX& m2)
	{
		XMATRIX ans;
		for (size_t i = 0; i < 4; ++i)
		{
			ans.si[i] = SIMDSub(m1.si[i], m2.si[i]);
		}
		return ans;
	}

	inline XMATRIX __fastcall XMatrixMul(const XMATRIX& m1, const XMATRIX& m2)
	{
		XMATRIX ans;
		XMATRIX temp = m2;
		SIMD_TRANSPOSE(temp.si[0], temp.si[1], temp.si[2], temp.si[3]);

		for (size_t i = 0; i < 4; ++i)
		{
			ans.si[i] = SIMDPack4(
				SIMDHAdd4(SIMDMul(m1.si[i], temp.si[0])),
				SIMDHAdd4(SIMDMul(m1.si[i], temp.si[1])),
				SIMDHAdd4(SIMDMul(m1.si[i], temp.si[2])),
				SIMDHAdd4(SIMDMul(m1.si[i], temp.si[3]))
			);
		}

		return ans;
	}

	template<typename T, std::enable_if_t<std::is_integral_v<T> || std::is_floating_point_v<T>, std::nullptr_t>>
	inline XMATRIX __fastcall XMatrixMul(const XMATRIX& m, T s)
	{
		XMATRIX ans;
		SIMD temp = SIMDLoadFloat4(static_cast<float>(s));
		for (size_t i = 0; i < 4; ++i)
		{
			ans.si[i] = SIMDMul(m.si[i], temp);
		}
		return ans;
	}

	template<typename T, std::enable_if_t<std::is_integral_v<T> || std::is_floating_point_v<T>, std::nullptr_t>>
	inline XMATRIX __fastcall XMatrixDiv(const XMATRIX& m, T s)
	{
		XMATRIX ans;
		SIMD temp = SIMDLoadFloat4(static_cast<float>(s));
		for (size_t i = 0; i < 4; ++i)
		{
			ans.si[i] = SIMDDiv(m.si[i], temp);
		}
		return ans;
	}

	//2D
	inline XMATRIX __fastcall XMatrixScaling2D(const XVECTOR& v)
	{
		XMATRIX ans;
		ans.si[0] = SIMDMul(v.si, kSIMDIdentity0);
		ans.si[1] = SIMDMul(v.si, kSIMDIdentity1);
		ans.si[2] = kSIMDIdentity2;
		ans.si[3] = kSIMDIdentity3;
		return ans;
	}

	inline XMATRIX __fastcall XMatrixRotation2D(float radian)
	{
		XMATRIX ans;
		ans.si[0] = SIMDLoadFloat2(std::cos(radian),  -std::sin(radian));
		ans.si[1] = SIMDLoadFloat2(std::sin(radian),   std::cos(radian));
		ans.si[2] = kSIMDIdentity2;
		ans.si[3] = kSIMDIdentity3;
		return ans;
	}

	inline XMATRIX __fastcall XMatrixTranslation2D(const XVECTOR& v)
	{
		XMATRIX ans;
		ans.si[0] = SIMDAdd(
			SIMDSort<SIMD_SHUFFLE(1, 1, 0, 1)>(
				SIMDMul(v.si, kSIMDIdentity0)
			),
			kSIMDIdentity0
		);
		ans.si[1] = SIMDAdd(
			SIMDSort<SIMD_SHUFFLE(0, 0, 1, 0)>(
				SIMDMul(v.si, kSIMDIdentity1)
			),
			kSIMDIdentity1
		);
		ans.si[2] = kSIMDIdentity2;
		ans.si[3] = kSIMDIdentity3;
		return ans;
	}

	//3D
	inline XMATRIX __fastcall XMatrixScaling3D(const XVECTOR& v)
	{
		XMATRIX ans;
		ans.si[0] = SIMDMul(v.si, kSIMDIdentity0);
		ans.si[1] = SIMDMul(v.si, kSIMDIdentity1);
		ans.si[2] = SIMDMul(v.si, kSIMDIdentity2);
		ans.si[3] = kSIMDIdentity3;
		return ans;
	}

	inline XMATRIX __fastcall XMatrixRotationX(float radian)
	{
		XMATRIX ans;
		ans.si[0] = kSIMDIdentity0;
		ans.si[1] = SIMDLoadFloat2(std::cos(radian), -std::sin(radian));
		ans.si[2] = SIMDLoadFloat2(std::sin(radian), std::cos(radian));
		ans.si[3] = kSIMDIdentity3;
		return ans;
	}

	inline XMATRIX __fastcall XMatrixRotationY(float radian)
	{
		XMATRIX ans;
		ans.si[0] = SIMDLoadFloat3(std::cos(radian), 0.f, std::sin(radian));
		ans.si[1] = kSIMDIdentity1;
		ans.si[2] = SIMDLoadFloat3(-std::sin(radian), 0.f, std::cos(radian));
		ans.si[3] = kSIMDIdentity3;
		return ans;
	}

	inline XMATRIX __fastcall XMatrixRotationZ(float radian)
	{
		XMATRIX ans; 
		ans.si[0] = SIMDLoadFloat2(std::cos(radian), -std::sin(radian));
		ans.si[1] = SIMDLoadFloat2(std::sin(radian), std::cos(radian));
		ans.si[2] = kSIMDIdentity2;
		ans.si[3] = kSIMDIdentity3;
		return ans;
	}

	inline XMATRIX __fastcall XMatrixTranslation3D(const XVECTOR& v)
	{
		XMATRIX ans;
		ans.si[0] = SIMDAdd(
			SIMDSort<SIMD_SHUFFLE(1, 1, 1, 0)>(
				SIMDMul(v.si, kSIMDIdentity0)
			),
			kSIMDIdentity0
		);
		ans.si[1] = SIMDAdd(
			SIMDSort<SIMD_SHUFFLE(0, 0, 0, 1)>(
				SIMDMul(v.si, kSIMDIdentity1)
			),
			kSIMDIdentity1
		);
		ans.si[2] = SIMDAdd(
			SIMDSort<SIMD_SHUFFLE(0, 0, 0, 2)>(
				SIMDMul(v.si, kSIMDIdentity2)
			),
			kSIMDIdentity2
		);
		ans.si[3] = kSIMDIdentity3;
		return ans;
	}
}
}