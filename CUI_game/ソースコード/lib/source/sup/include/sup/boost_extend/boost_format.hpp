/**
* @file boost_format.hpp
* @brief boost formatŠg’£ƒtƒ@ƒCƒ‹
*/

#ifndef SUP_LIB_BOOST_EXTEND_BOOST_FORMAT_HPP
#define SUP_LIB_BOOST_EXTEND_BOOST_FORMAT_HPP

#include<boost/format.hpp>
#include<sup/cpp/string.hpp>

namespace sup
{
inline namespace boost_extend
{
//-------------------------------------------------------------------------------------------------------------------
//basic type
#undef Format
#ifdef _UNICODE
	using Format = boost::wformat;
#else
	using Format = boost::format;
#endif

//-------------------------------------------------------------------------------------------------------------------
}
}

#endif