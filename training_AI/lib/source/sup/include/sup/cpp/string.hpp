/**
* @file string.hpp
* @brief 文字列処理定義ファイル
*/

#ifndef SUP_LIB_CPP_STRING_HPP
#define SUP_LIB_CPP_STRING_HPP

#include<string>
#include<string_view>

namespace sup
{
inline namespace cpp
{
//undef
#undef TEXT

#ifdef _UNICODE

//type
	using Char = wchar_t;
	using String = std::wstring;
	using StringView = std::wstring_view;

//macro
#define TEXT(str) L##str

#else

//type
	using Char = char;
	using String = std::string;
	using StringView = std::string_view;

//macro
#define TEXT(str) str

#endif
}
}

#endif