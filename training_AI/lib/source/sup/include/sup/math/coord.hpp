/**
* @file coord.hpp
* @brief 座標計算宣言ファイル
*/
#ifndef SUP_LIB_MATH_CALCULATION_HPP
#define SUP_LIB_MATH_CALCULATION_HPP

#include<cmath>
#include<cstdint>
#include<type_traits>
#include<sup/cpp/simd.hpp>

namespace sup
{
inline namespace math
{
//----------------------------------------------------------------------------------------------------------------------------------------------------
//main struct declaration
	struct VECTOR2;
	struct VECTOR3;
	struct VECTOR4;
	struct MATRIX2X2;
	struct MATRIX3X3;
	struct MATRIX4X4;
	struct VECTOR2A;
	struct VECTOR3A;
	struct VECTOR4A;
	struct MATRIX2X2A;
	struct MATRIX3X3A;
	struct MATRIX4X4A;

//main class declaration
	class XVECTOR;
	class XMATRIX;

//----------------------------------------------------------------------------------------------------------------------------------------------------
//main struct
	struct VECTOR2
	{
		union
		{
			struct
			{
				float x;
				float y;
			};
			float v[2];
		};

		VECTOR2()noexcept = default;
		VECTOR2(float x, float y)noexcept : x(x), y(y) {}
		VECTOR2(const float* p)noexcept : x(p[0]), y(p[1]) {}
	};

	struct alignas(16) VECTOR2A : VECTOR2
	{
		VECTOR2A()noexcept = default;
		VECTOR2A(float x, float y)noexcept : VECTOR2(x, y) {}
		VECTOR2A(const float* p)noexcept : VECTOR2(p) {}
	};

	struct VECTOR3
	{
		union
		{
			struct
			{
				float x;
				float y;
				float z;
			};
			float v[3];
		};

		VECTOR3()noexcept = default;
		VECTOR3(float x, float y, float z)noexcept : x(x), y(y), z(z) {}
		VECTOR3(const float* p)noexcept : x(p[0]), y(p[1]), z(p[2]) {}
	};

	struct alignas(16) VECTOR3A : VECTOR3
	{
		VECTOR3A()noexcept = default;
		VECTOR3A(float x, float y, float z)noexcept : VECTOR3(x, y, z) {}
		VECTOR3A(const float* p)noexcept : VECTOR3(p) {}
	};

	struct VECTOR4
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
			float v[4];
		};

		VECTOR4()noexcept = default;
		VECTOR4(float x, float y, float z, float w)noexcept : x(x), y(y), z(z), w(w) {}
		VECTOR4(const float* p)noexcept : x(p[0]), y(p[1]), z(p[2]), w(p[3]) {}
	};

	struct alignas(16) VECTOR4A : public VECTOR4
	{
		VECTOR4A()noexcept = default;
		VECTOR4A(float x, float y, float z, float w)noexcept : VECTOR4(x, y, z, w) {}
		VECTOR4A(const float* p)noexcept : VECTOR4(p) {}
	};

	struct MATRIX2X2
	{
		union
		{
			struct
			{
				float
				m00, m01,
				m10, m11;
			};
			float m[2][2];
		};

		MATRIX2X2()noexcept = default;
		MATRIX2X2(
			float m00, float m01,
			float m10, float m11
		)noexcept :
			m00(m00), m01(m01),
			m10(m10), m11(m11)
		{}
		MATRIX2X2(const float* p)noexcept
		{
			for(int i = 0; i < 2; ++i)
			for(int j = 0; j < 2; ++j)
				m[i][j] = p[i*j];
		}
		float operator()(size_t row, size_t col) { return m[row][col]; };
	};

	struct alignas(16) MATRIX2X2A : public MATRIX2X2
	{
		MATRIX2X2A()noexcept = default;
		MATRIX2X2A(
			float m00, float m01,
			float m10, float m11
		)noexcept :
			MATRIX2X2(
				m00, m01,
				m10, m11
			)
		{}
		MATRIX2X2A(const float* p)noexcept : MATRIX2X2(p) {}
	};

	struct MATRIX3X3
	{
		union
		{
			struct
			{
				float
				m00, m01, m02,
				m10, m11, m12,
				m20, m21, m22;
			};
			float m[3][3];
		};

		MATRIX3X3()noexcept = default;
		MATRIX3X3(
			float m00, float m01, float m02,
			float m10, float m11, float m12,
			float m20, float m21, float m22
		)noexcept :
			m00(m00), m01(m01), m02(m02),
			m10(m10), m11(m11), m12(m12),
			m20(m20), m21(m21), m22(m22)
		{}
		MATRIX3X3(const float* p)noexcept
		{
			for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
					m[i][j] = p[i*j];
		}
		float operator()(size_t row, size_t col) { return m[row][col]; };
	};

	struct alignas(16) MATRIX3X3A : public MATRIX3X3
	{
		MATRIX3X3A()noexcept = default;
		MATRIX3X3A(
			float m00, float m01, float m02,
			float m10, float m11, float m12,
			float m20, float m21, float m22
		)noexcept :
			MATRIX3X3(
				m00, m01, m02,
				m10, m11, m12,
				m20, m21, m22
			)
		{}
		MATRIX3X3A(const float* p)noexcept : MATRIX3X3(p){}
	};

	struct MATRIX4X4
	{
		union
		{
			struct
			{
				float
				m00, m01, m02, m03,
				m10, m11, m12, m13,
				m20, m21, m22, m23,
				m30, m31, m32, m33;
			};
			float m[4][4];
		};

		MATRIX4X4()noexcept = default;
		MATRIX4X4(
			float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33
		)noexcept :
			m00(m00), m01(m01), m02(m02), m03(m03),
			m10(m10), m11(m11), m12(m12), m13(m13),
			m20(m20), m21(m21), m22(m22), m23(m23),
			m30(m30), m31(m31), m32(m32), m33(m33)
		{}
		MATRIX4X4(const float* p)noexcept
		{
			for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				m[i][j] = p[i*j];
		}
		float operator()(size_t row, size_t col) { return m[row][col]; };
	};

	struct alignas(16) MATRIX4X4A : public MATRIX4X4
	{
		MATRIX4X4A()noexcept = default;
		MATRIX4X4A(
			float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33
		)noexcept :
			MATRIX4X4(
				m00, m01, m02, m03,
				m10, m11, m12, m13,
				m20, m21, m22, m23,
				m30, m31, m32, m33
			)
		{}
		MATRIX4X4A(const float* p)noexcept : MATRIX4X4(p){}
	};

//----------------------------------------------------------------------------------------------------------------------------------------------------
//main class	
	class alignas(16) XVECTOR
	{
	public:
		sup::cpp::SIMD si;

	public:
		XVECTOR(const XVECTOR&)noexcept = default;
		XVECTOR(XVECTOR&&)noexcept = default;
		~XVECTOR()noexcept = default;
		XVECTOR& operator=(const XVECTOR&)noexcept = default;
		XVECTOR& operator=(XVECTOR&&)noexcept = default;

	public:
		XVECTOR()noexcept;

	public:
		XVECTOR operator+(const XVECTOR& v)const;
		XVECTOR operator-(const XVECTOR& v)const;
		void operator+=(const XVECTOR& v);
		void operator-=(const XVECTOR& v);
		template<typename T, std::enable_if_t<std::is_integral_v<T> || std::is_floating_point_v<T>, std::nullptr_t> = nullptr> 
		XVECTOR operator*(T s)const;
		template<typename T, std::enable_if_t<std::is_integral_v<T> || std::is_floating_point_v<T>, std::nullptr_t> = nullptr>
		XVECTOR operator/(T s)const;
		template<typename T, std::enable_if_t<std::is_integral_v<T> || std::is_floating_point_v<T>, std::nullptr_t> = nullptr>
		void operator*=(T s);
		template<typename T, std::enable_if_t<std::is_integral_v<T> || std::is_floating_point_v<T>, std::nullptr_t> = nullptr>
		void operator/=(T s);
	};
	
	class alignas(16) XMATRIX
	{
	public:
		SIMD si[4];

	public:
		XMATRIX()noexcept = default;
		XMATRIX(const XMATRIX&)noexcept = default;
		XMATRIX(XMATRIX&&)noexcept = default;
		~XMATRIX()noexcept = default;
		XMATRIX& operator=(const XMATRIX&)noexcept = default;
		XMATRIX& operator=(XMATRIX&&)noexcept = default;

	public:
		XMATRIX operator+(const XMATRIX& m)const;
		XMATRIX operator-(const XMATRIX& m)const;
		XMATRIX operator*(const XMATRIX& m)const;
		void operator+=(const XMATRIX& m);
		void operator-=(const XMATRIX& m);
		void operator*=(const XMATRIX& m);
		template<typename T, std::enable_if_t<std::is_integral_v<T> || std::is_floating_point_v<T>, std::nullptr_t> = nullptr>
		XMATRIX operator*(T s)const;
		template<typename T, std::enable_if_t<std::is_integral_v<T> || std::is_floating_point_v<T>, std::nullptr_t> = nullptr>
		XMATRIX operator/(T s)const;
		template<typename T, std::enable_if_t<std::is_integral_v<T> || std::is_floating_point_v<T>, std::nullptr_t> = nullptr>
		void operator*=(T s);
		template<typename T, std::enable_if_t<std::is_integral_v<T> || std::is_floating_point_v<T>, std::nullptr_t> = nullptr>
		void operator/=(T s);
	};

//----------------------------------------------------------------------------------------------------------------------------------------------------
//XVECTOR function
	//load
	XVECTOR __fastcall XVectorLoadZero();
	XVECTOR __fastcall XVectorLoadVector2(const VECTOR2& v);
	XVECTOR __fastcall XVectorLoadVector2A(const VECTOR2A& v);
	XVECTOR __fastcall XVectorLoadVector3(const VECTOR3& v);
	XVECTOR __fastcall XVectorLoadVector3A(const VECTOR3A& v);
	XVECTOR __fastcall XVectorLoadVector4(const VECTOR4& v);
	XVECTOR __fastcall XVectorLoadVector4A(const VECTOR4A& v);

	//store
	void __fastcall XVectorStoreVector2(const XVECTOR& xv, VECTOR2* v);
	void __fastcall XVectorStoreVector2A(const XVECTOR& xv, VECTOR2A* v);
	void __fastcall XVectorStoreVector3(const XVECTOR& xv, VECTOR3* v);
	void __fastcall XVectorStoreVector3A(const XVECTOR& xv, VECTOR3A* v);
	void __fastcall XVectorStoreVector4(const XVECTOR& xv, VECTOR4* v);
	void __fastcall XVectorStoreVector4A(const XVECTOR& xv, VECTOR4A* v);

	//set
	XVECTOR __fastcall XVectorSetX(const XVECTOR& v, float x);
	XVECTOR __fastcall XVectorSetY(const XVECTOR& v, float y);
	XVECTOR __fastcall XVectorSetZ(const XVECTOR& v, float z);
	XVECTOR __fastcall XVectorSetW(const XVECTOR& v, float w);

	//get
	float __fastcall XVectorGetX(const XVECTOR& v);
	float __fastcall XVectorGetY(const XVECTOR& v);
	float __fastcall XVectorGetZ(const XVECTOR& v);
	float __fastcall XVectorGetW(const XVECTOR& v);

	//arithmetic 
	XVECTOR __fastcall XVectorAdd(const XVECTOR& v1, const XVECTOR& v2);
	XVECTOR __fastcall XVectorSub(const XVECTOR& v1, const XVECTOR& v2);
	template<typename T, std::enable_if_t<std::is_integral_v<T> || std::is_floating_point_v<T>, std::nullptr_t> = nullptr>
	XVECTOR __fastcall XVectorMul(const XVECTOR& v, T s);
	template<typename T, std::enable_if_t<std::is_integral_v<T> || std::is_floating_point_v<T>, std::nullptr_t> = nullptr>
	XVECTOR __fastcall XVectorDiv(const XVECTOR& v, T s);

	//vector2
	XVECTOR __fastcall XVector2Transform(const XVECTOR& v, const XMATRIX& m);
	XVECTOR __fastcall XVector2Inverse(const XVECTOR& v);
	XVECTOR __fastcall XVector2Normalize(const XVECTOR& v);
	float   __fastcall XVector2Dot(const XVECTOR& v1, const XVECTOR& v2);
	float   __fastcall XVector2Cross(const XVECTOR& v1, const XVECTOR& v2);
	float   __fastcall XVector2Size(const XVECTOR& v);
	float	__fastcall XVector2SquareSize(const XVECTOR& v);
	float	__fastcall XVector2BetweenSin(const XVECTOR& start, const XVECTOR& end);
	float	__fastcall XVector2BetweenCos(const XVECTOR& start, const XVECTOR& end);
	float	__fastcall XVector2BetweenTan(const XVECTOR& start, const XVECTOR& end);

	//vector3
	XVECTOR __fastcall XVector3Transform(const XVECTOR& v, const XMATRIX& m);
	XVECTOR __fastcall XVector3Inverse(const XVECTOR& v);
	XVECTOR __fastcall XVector3Normalize(const XVECTOR& v);
	float   __fastcall XVector3Dot(const XVECTOR& v1, const XVECTOR& v2);
	XVECTOR __fastcall XVector3Cross(const XVECTOR& v1, const XVECTOR& v2);
	float   __fastcall XVector3Size(const XVECTOR& v);
	float	__fastcall XVector3SquareSize(const XVECTOR& v);
	float	__fastcall XVector3BetweenSin(const XVECTOR& start, const XVECTOR& end);
	float	__fastcall XVector3BetweenCos(const XVECTOR& start, const XVECTOR& end);
	float	__fastcall XVector3BetweenTan(const XVECTOR& start, const XVECTOR& end);

	//vector4
	XVECTOR __fastcall XVector4Transform(const XVECTOR& v, const XMATRIX& m);
	XVECTOR __fastcall XVector4Inverse(const XVECTOR& v);
	float   __fastcall XVector4Dot(const XVECTOR& v1, const XVECTOR& v2);
	XVECTOR __fastcall XVector4Cross(const XVECTOR& v1, const XVECTOR& v2);
	
//XMATRIX function
	//load
	XMATRIX __fastcall XMatrixLoadZero();
	XMATRIX __fastcall XMatrixLoadIdentity();
	XMATRIX __fastcall XMatrixLoadMatrix2X2(const MATRIX2X2& m);
	XMATRIX __fastcall XMatrixLoadMatrix2X2A(const MATRIX2X2A& m);
	XMATRIX __fastcall XMatrixLoadMatrix3X3(const MATRIX3X3& m);
	XMATRIX __fastcall XMatrixLoadMatrix3X3A(const MATRIX3X3A& m);
	XMATRIX __fastcall XMatrixLoadMatrix4X4(const MATRIX4X4& m);
	XMATRIX __fastcall XMatrixLoadMatrix4X4A(const MATRIX4X4A& m);

	//store
	void __fastcall XMatrixStoreMatrix2X2(const XMATRIX& xm, MATRIX2X2* m);
	void __fastcall XMatrixStoreMatrix2X2A(const XMATRIX& xm, MATRIX2X2A* m);
	void __fastcall XMatrixStoreMatrix3X3(const XMATRIX& xm, MATRIX3X3* m);
	void __fastcall XMatrixStoreMatrix3X3A(const XMATRIX& xm, MATRIX3X3A* m);
	void __fastcall XMatrixStoreMatrix4X4(const XMATRIX& xm, MATRIX4X4* m);
	void __fastcall XMatrixStoreMatrix4X4A(const XMATRIX& xm, MATRIX4X4A* m);

	//arithmetic
	XMATRIX __fastcall XMatrixTranspose(const XMATRIX& m);
	XMATRIX __fastcall XMatrixAdd(const XMATRIX& m1, const XMATRIX& m2);
	XMATRIX __fastcall XMatrixSub(const XMATRIX& m1, const XMATRIX& m2);
	XMATRIX __fastcall XMatrixMul(const XMATRIX& m1, const XMATRIX& m2);
	template<typename T, std::enable_if_t<std::is_integral_v<T> || std::is_floating_point_v<T>, std::nullptr_t> = nullptr>
	XMATRIX __fastcall XMatrixMul(const XMATRIX& m, T s);
	template<typename T, std::enable_if_t<std::is_integral_v<T> || std::is_floating_point_v<T>, std::nullptr_t> = nullptr>
	XMATRIX __fastcall XMatrixDiv(const XMATRIX& m, T s);
	
	//2D
	XMATRIX __fastcall XMatrixScaling2D(const XVECTOR& v);
	XMATRIX __fastcall XMatrixRotation2D(float radian);
	XMATRIX __fastcall XMatrixTranslation2D(const XVECTOR& v);

	//3D
	XMATRIX __fastcall XMatrixScaling3D(const XVECTOR& v);
	XMATRIX __fastcall XMatrixRotationX(float radian);
	XMATRIX __fastcall XMatrixRotationY(float radian);
	XMATRIX __fastcall XMatrixRotationZ(float radian);
	XMATRIX __fastcall XMatrixTranslation3D(const XVECTOR& v);
}
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
//include imple file
#include<sup/math/coord/xvector.inl>
#include<sup/math/coord/xmatrix.inl>

#endif