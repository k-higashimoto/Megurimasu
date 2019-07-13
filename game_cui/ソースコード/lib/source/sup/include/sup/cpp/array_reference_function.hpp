/**
* @file array_reference_function.hpp
* @brief クラスに持たせた配列の参照用の機能を簡単に追加するためのマクロを定義するファイル
*/

#ifndef SUP_LIB_CPP_ARRAY_REFERENCE_FUNCTION_HPP
#define SUP_LIB_CPP_ARRAY_REFERENCE_FUNCTION_HPP

#include<iterator>

/**
* @brief 添字演算子のオーバーロードを追加する
* @param TYPE_NAME 配列の型
* @param VAR_NAME 変数名
*/
#define ADD_ARRAY_SUFFIX_OVERLOAD(VAR_NAME)						\
decltype(auto) operator[](size_t size)noexcept					\
{																\
	return this->VAR_NAME[size];								\
};																\
																\
decltype(auto) operator[](size_t size)const noexcept			\
{																\
	return this->VAR_NAME[size];								\
};

/**
* @brief begin endを追加する
* @param VAR_NAME 変数名
*/
#define ADD_ARRAY_BEGIN_END_FUNCTION(VAR_NAME)						\
decltype(auto) begin()noexcept										\
{																	\
	return &this->VAR_NAME[0];										\
};																	\
																	\
decltype(auto) begin()const noexcept								\
{																	\
	return &this->VAR_NAME[0];										\
};																	\
																	\
decltype(auto) end()noexcept										\
{																	\
	return &this->VAR_NAME[std::size(VAR_NAME)];					\
};																	\
																	\
decltype(auto) end()const noexcept									\
{																	\
	return &this->VAR_NAME[std::size(VAR_NAME)];					\
};

/**
* @breif ARRAY_SUFFIX_OVERLOADとARRAY_BEGIN_END_FUNCTIONの両方を追加する
* @param VAR_NAME 変数名
*/
#define ADD_ARRAY_REFERENCE_FUNCTION(VAR_NAME)	\
ADD_ARRAY_SUFFIX_OVERLOAD(VAR_NAME)				\
ADD_ARRAY_BEGIN_END_FUNCTION(VAR_NAME)			

#endif