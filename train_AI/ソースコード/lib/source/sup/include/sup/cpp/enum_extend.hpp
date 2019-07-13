/**
* @file enum_size.hpp
* @brief 列挙の機能拡張用のマクロ・関数定義ファイル
*/

#ifndef SUP_LIB_CPP_ENUM_SIZE_HPP
#define SUP_LIB_CPP_ENUM_SIZE_HPP

#include<type_traits>

namespace sup
{
inline namespace cpp
{
	/**
	* @def ITEM_NUM
	* @breif 列挙サイズ取得用に列挙の最後に使用するマクロ
	* @attention
	*	・列挙の途中で値を指定していた場合、又は列挙名が重複する場合使用不可
	*	・使用例 : enum { ITEM_A, ITEM_B, ITEM_NUM }; 
	*/
	#define ENUM_ITEM_NUM ENUM_ITEM_NUM_BOOK_MARK

	/**
	* @def enum_size
	* @brief 列挙サイズを取得する
	* @attention
	*	上記で定義したENUM_ITEM_NUMを使用した列挙からサイズを取得する
	*/
	template<typename T, std::enable_if_t<std::is_enum_v<T>, std::nullptr_t> = nullptr>
	constexpr size_t enum_size = static_cast<size_t>(T::ENUM_ITEM_NUM);

	/**
	* @brief 列挙の値を基底型の値に変換する
	* @param item 変換する値
	*/
	template<typename T, std::enable_if_t<std::is_enum_v<T>, std::nullptr_t> = nullptr>
	constexpr auto ToUnderlyingValue(T item)noexcept
		->std::underlying_type_t<T>
	{
		return static_cast<std::underlying_type_t<T>>(item);
	}


}
}

#endif
