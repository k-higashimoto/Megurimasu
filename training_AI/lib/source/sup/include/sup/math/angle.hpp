/**
* @file angle.hpp
* @brief 角度処理定義ファイル
*/

#include<type_traits>
#include<sup/math/constant.hpp>

namespace sup
{
inline namespace math
{
//----------------------------------------------------------------------------------------------------------------------------------------------------
//convert function
	template<typename T, std::enable_if_t<std::is_integral_v<T> || std::is_floating_point_v<T>, std::nullptr_t> = nullptr>
	constexpr double __fastcall ToRadian(T degree)noexcept 
	{ 
		return static_cast<double>((kPI / 180.0) * degree); 
	}

	template<typename T, std::enable_if_t<std::is_integral_v<T> || std::is_floating_point_v<T>, std::nullptr_t> = nullptr>
	constexpr double __fastcall ToDegree(T radian)noexcept 
	{ 
		return static_cast<double>((180.0 / kPI) * radian); 
	}
}
}