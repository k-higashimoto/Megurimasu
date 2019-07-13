/**
* @file basic_type.hpp
* @brief 基本型定義ファイル
*/

#include<cstdint>

namespace sup
{
inline namespace cpp
{
    /**
    * @typedef BOOL
    * @brief 論理型
    */
    using BOOL = bool;

    /**
    * @typedef CHAR
    * @brief 8bit以上
    */
    using CHAR = std::int8_t;

    /**
    * @typedef SHORT
    * @brief 16bit以上
    */
    using SHORT = std::int16_t;

    /**
    * @typedef INT
    * @brief 32bit以上
    */
    using INT = std::int32_t;

    /**
     * @typedef LONG
     * @brief 32bit以上
     */
    using LONG = std::int32_t;

    /**
     * @tpedef LONGLONG
     * @brief 64bit以上
     */
    using LONGLONG = std::int64_t;

    /**
    * @typedef UCHAR
    * @brief 符号なし8bit以上
    */
    using UCHAR = std::uint8_t;

    /**
    * @typedef USHORT
    * @brief 符号なし16bit以上
    */
    using USHORT = std::uint16_t;

    /**
    * @typedef UINT
    * @brief 符号なし32bit以上
    */
    using UINT = std::uint32_t;

    /**
     * @typedef ULONG
     * @brief 符号なし32bit以上
     */
    using ULONG = std::uint32_t;

    /**
     * @tpedef ULONGLONG
     * @brief 符号なし64bit以上
     */
    using ULONGLONG = std::uint64_t;
}
}