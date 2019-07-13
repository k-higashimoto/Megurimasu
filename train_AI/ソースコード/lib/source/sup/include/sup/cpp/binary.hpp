/**
* @file binary.hpp
* @brief バイナリ操作の補助を定義するファイル
*/

#ifndef SUP_LIB_CPP_BINARY_HPP
#define SUP_LIB_CPP_BINARY_HPP

#include<utility>
#include<iterator>
#include<type_traits>
#include<bitset>

namespace sup
{
inline namespace cpp
{
	/**
	* @brief ビット数を取得する
	* @tparam ビット数を取得する型
	* @return ビット数
	*/
	template<typename T>
	constexpr size_t BitNum()noexcept
	{
		return sizeof(T) * 8U;
	}

	/**
	* @brief ビット数を取得する
	* @tparam ビット数を取得する型
	* @return ビット数
	*/
	template<typename T>
	constexpr size_t BitNum(T)noexcept
	{
		return sizeof(T) * 8U;
	}

	/**
	* @brief 配列型のビット数を取得する
	* @tparam 配列型の元の型
	* @param 配列型の変数
	* @return ビット数
	*/
	template<typename T, size_t Size>
	constexpr size_t BitNum(T (&)[Size])noexcept
	{
		return BitNum<T>() * Size;
	}

	/**
	* @brief ビット数をバイト数に変換する
	* @param bit_num ビット数
	* @return バイト数
	*/
	constexpr size_t ByteNum(size_t bit_num)noexcept
	{
		return bit_num / 8U;
	}

	/**
	* @brief 先頭ビットからの位置を取得する
	* @tparam T ビット数情報の元となる型情報
	* @return 位置情報
	*/
	template<typename T>
	constexpr size_t BitPosFromHead(size_t pos)noexcept
	{
		return BitNum<T>() - 1 - pos;
	}

	/**
	* @brief 全てのbitをonにする
	* @tparam T オンにする型
	* @return 全てのbitがonになっている値
	*/
	template<typename T>
	constexpr T BitFill()noexcept
	{
		T fill = 0;
		return ~fill;
	}

	/**
	* @brief 全てのbitをonにする
	* @tparam T オンにする型
	* @return 全てのbitがonになっている値
	*/
	template<typename T>
	constexpr T BitFill(T)noexcept
	{
		T fill = 0;
		return ~fill;
	}

	/**
	* @brief 値を上位と下位に分解する
	* @tparam T 分割前の値の型
	* @param val 分割したい値
	* @return 分割した値 first 上位 second 下位
	*/
	template<typename T>
	constexpr std::pair<T, T> DivValue(const T& val)noexcept
	{
		size_t arg_type_div_size = BitNum(sizeof(T)) / 2;
		T low_value = (val << arg_type_div_size); //はみ出したデータを削除するために代入
		return std::make_pair<T, T>(val >> arg_type_div_size, low_value >> arg_type_div_size);
	}

	/**
	* @brief 2つの値を上位・下位として一つの値に代入
	* @tparam ReturnType 戻り値に使う型
	* @tparam ValueType 引数の型
	* @param height_val 上位ビットに入れる値
	* @param low_val 下位ビットに入れる値
	* @return 代入結果
	*/
	template<typename ReturnType, typename ValueType>
	constexpr ReturnType MakeValue(ValueType high, ValueType low)noexcept
	{
		size_t return_type_div_size = BitNum(sizeof(ReturnType)) / 2;
		return static_cast<ReturnType>(high << return_type_div_size) | static_cast<ReturnType>(low);
	}

	/**
	* @brief 配列を一つの変数に詰め込む
	* @tparam T 詰め込み先の変数の型
	* @tparam InputIterator 入力の型
	* @param first 開始位置
	* @param last 終了位置
	* @return 詰め込んだ変数
	*/
	template<typename T, typename InputIterator>
	constexpr T PackArray(InputIterator first, InputIterator last)noexcept
	{
		T ans = 0;
		auto shift_size = BitNum<std::remove_reference_t<decltype(*first)>>();
		size_t shift_num = 1;
		while(first != last)
		{
			_ASSERT(shift_size * shift_num <= BitNum<T>());
			ans |= (*first++) << (BitNum<T>() - shift_size * shift_num++);
		}
		return ans;
	} 

namespace details
{
	/**
	* @brief 配列を別の配列にパックする
	* @tparam InputType 入力の型
	* @tparam OutputType 出力の型
	* @tparam InputIterator 入力のイテレーター型
	* @tparam OutputIterator 出力のイテレーター型
	* @param first 開始位置
	* @param last 終了位置
	* @param output 出力先
	* @attention
	*	PackArrayの部品であるため直接使用しない
	*	サイズがInputType <= OutputTypeとなっているときのみ使用 
	*/
	template<typename InputType, typename OutputType, typename InputIterator, typename OutputIterator, std::enable_if_t<sizeof(InputType) <= sizeof(OutputType), std::nullptr_t> = nullptr>
	constexpr void PackArray(InputIterator first, InputIterator last, OutputIterator output)noexcept
	{
		OutputType array_value = 0;
		auto shift_size = BitNum<InputType>();
		size_t shift_num = 1;
		while (first != last)
		{
			array_value |= (*first++) << (BitNum<OutputType>() - shift_size * shift_num++);
			if (BitNum<OutputType>() < shift_size * shift_num)
			{
				(*output++) = array_value;
				array_value = 0;
				shift_num = 1;
			}
		}
	}

	/**
	* @brief 配列を別の配列にパックする
	* @tparam InputType 入力の型
	* @tparam OutputType 出力の型
	* @tparam InputIterator 入力のイテレーター型
	* @tparam OutputIterator 出力のイテレーター型
	* @param first 開始位置
	* @param last 終了位置
	* @param output 出力先
	* @attention
	*	PackArrayの部品であるため直接使用しない
	*	サイズがInputType > OutputTypeとなっているときのみ使用
	*/
	template<typename InputType, typename OutputType, typename InputIterator, typename OutputIterator, std::enable_if_t<!(sizeof(InputType) <= sizeof(OutputType)), std::nullptr_t> = nullptr>
	constexpr void PackArray(InputIterator first, InputIterator last, OutputIterator output)noexcept
	{
		OutputType array_value = 0;
		auto shift_size = BitNum<OutputType>();
		size_t shift_num = 1;
		while (first != last)
		{
			//数値切り捨てのためキャスト
			(*output++) = static_cast<OutputType>((*first) >> (BitNum<InputType>() - shift_size * shift_num++));
			if(BitNum<InputType>() < shift_size * shift_num)
			{
				++first;
				array_value = 0;
				shift_num = 1;
			}
		}
	}
}

	/**
	* @brief 配列を別の配列にパックする
	* @tparam T 詰め込み先の変数の型
	* @tparam InputIterator 入力の型
	* @tparam OutputIterator 出力先の型
	* @param first 開始位置
	* @param last 終了位置
	* @param output 出力先
	*/
	template<typename InputIterator, typename OutputIterator>
	constexpr void PackArray(InputIterator first, InputIterator last, OutputIterator output)noexcept
	{
		using InputType = std::remove_reference_t<decltype(*first)>;
		using OutputType = std::remove_reference_t<decltype(*output)>;
		details::PackArray<InputType, OutputType>(first, last, output);
	}

	/**
	* @brief 指定ビットの値を書き換える
	* @tparam ValueType 書き換える値の型
	* @param value 変更される値
	* @param pos 変更位置
	* @param on trueで1 falseで0 にする
	* @retrun 書き換えた値
	*/
	template<typename ValueType>
	constexpr ValueType SetBit(ValueType value, size_t pos, bool on)noexcept
	{
		return on ? value | (static_cast<ValueType>(1) << pos) : value & (~(static_cast<ValueType>(1) << pos));
	}

	/**
	* @brief 上記のSetBitの指定位置を先頭か末尾からのどちらからか指定可能にしたもの
	* @tparam reverse trueで先頭位置からの位置指定 falseで後方位置からの位置指定
	* @tparam ValueType 書き換える値の型
	* @param value 変更される値
	* @param pos 変更位置
	* @param on trueで1 falseで0 にする
	* @retrun 書き換えた値
	*/
	template<bool reverse, typename ValueType>
	constexpr ValueType SetBit(ValueType value, size_t pos, bool on)noexcept
	{
		if constexpr(!reverse)
		{
			return on ? value | (static_cast<ValueType>(1) << pos) : value & (~(static_cast<ValueType>(1) << pos));
		}
		else
		{
			size_t bit_pos = BitPosFromHead<ValueType>(pos);
			return on ? value | (static_cast<ValueType>(1) << bit_pos) : value & (~(static_cast<ValueType>(1) << bit_pos));
		}
	}

	/**
	* @brief SetBit配列版 配列を一つの大きな変数を見立てて値を書き換える
	* @tparam ValueType 書き換える値の型
	* @param value 変更される値
	* @param array_size 配列数
	* @param pos 変更位置
	* @param on trueで1 falseで0 にする
	*/
	template<typename ValueType>
	constexpr void SetBit(ValueType* value, size_t array_size, size_t pos, bool on)noexcept
	{
		_ASSERT(pos < BitNum<ValueType>() * array_size);
		size_t bit_size = BitNum<ValueType>();
		size_t bit_pos = pos % bit_size;
		size_t array_tail_pos = array_size - 1;
		size_t array_pos_offset = (pos - bit_pos) / bit_size;
		size_t array_pos = array_tail_pos - array_pos_offset;
		value[array_pos] = on ? value[array_pos] | (static_cast<ValueType>(1) << bit_pos) : value[array_pos] & (~(static_cast<ValueType>(1) << bit_pos));
	}

	/**
	* @brief SetBit配列版 配列を一つの大きな変数を見立てて値を書き換える
	* @tparam reverse trueで先頭位置からの位置指定 falseで後方位置からの位置指定
	* @tparam ValueType 書き換える値の型
	* @param value 変更される値
	* @param array_size 配列数
	* @param pos 変更位置
	* @param on trueで1 falseで0 にする
	*/
	template<bool reverse, typename ValueType>
	constexpr void SetBit(ValueType* value, size_t array_size, size_t pos, bool on)noexcept
	{
		_ASSERT(pos < BitNum<ValueType>() * array_size);
		if constexpr(!reverse)
		{
			size_t bit_size = BitNum<ValueType>();
			size_t bit_pos = pos % bit_size;
			size_t array_tail_pos = array_size - 1;
			size_t array_pos_offset = (pos - bit_pos) / bit_size;
			size_t array_pos = array_tail_pos - array_pos_offset;
			value[array_pos] = on ? value[array_pos] | (static_cast<ValueType>(1) << bit_pos) : value[array_pos] & (~(static_cast<ValueType>(1) << bit_pos));
		}
		else
		{
			size_t bit_size = BitNum<ValueType>();
			size_t bit_max_pos = bit_size - 1;
			size_t bit_pos_offset = (pos % bit_size);
			size_t bit_pos = bit_max_pos - bit_pos_offset;
			size_t array_pos = (pos - bit_pos_offset) / bit_size;
			value[array_pos] = on ? value[array_pos] | (static_cast<ValueType>(1) << bit_pos) : value[array_pos] & (~(static_cast<ValueType>(1) << bit_pos));
		}
	}

	/**
	* @brief 各bit毎に値を指定して書き換える
	* @tparam ValueType 値の型
	* @tpram Predicate 条件式の型
	* @param value 書き換える値
	* @param pos 書き換え開始位置
	* @param pred 条件式
	* @return 書き換えた値
	* @attention
	*	Predicate
	*	param size_t pos 位置情報
	*	return trueでon falseでoffにする
	*/
	template<typename ValueType, typename Predicate>
	constexpr ValueType SetBitIf(ValueType value, size_t pos, Predicate pred)noexcept
	{
		for(size_t i = pos; i < BitNum(sizeof(ValueType)); ++i)
		{
			value = SetBit(value, i, pred(i));
		}
		return value;
	}

	/**
	* @brief 配列の各bit毎に値を指定して書き換える
	* @tparam ValueType 値の型
	* @tpram Predicate 条件式の型
	* @param value 書き換える配列
	* @param array_size 配列数
	* @param pos 書き換え開始位置
	* @param pred 条件式
	* @attention
	*	Predicate
	*	param size_t pos 位置情報
	*	return trueでon falseでoffにする
	*/
	template<typename ValueType, typename Predicate>
	constexpr void SetBitIf(ValueType* value, size_t array_size, size_t pos, Predicate pred)noexcept
	{
		for (size_t i = pos, bit_num = BitNum<ValueType>() * array_size; i < bit_num; ++i)
		{
			SetBit(value, array_size, i, pred(i));
		}
	}

	/**
	* @brief 各bit毎に値を指定して書き換える
	* @tparam reverse trueで先頭位置からの位置指定 falseで後方位置からの位置指定
	* @tparam ValueType 値の型
	* @tpram Predicate 条件式の型
	* @param value 書き換える値
	* @param pos 書き換え開始位置
	* @param pred 条件式
	* @return 書き換えた値
	* @attention
	*	Predicate
	*	param size_t pos reverseがtrueなら先頭からの位置情報 falseなら末尾からの位置情報
	*	return trueでon falseでoffにする
	*/
	template<bool reverse, typename ValueType, typename Predicate>
	constexpr ValueType SetBitIf(ValueType value, size_t pos, Predicate pred)noexcept
	{
		for (size_t i = pos; i < BitNum(sizeof(ValueType)); ++i)
		{
			value = SetBit<reverse>(value, i, pred(i));
		}
		return value;
	}

	/**
	* @brief 配列の各bit毎に値を指定して書き換える
	* @tparam reverse trueで先頭位置からの位置指定 falseで後方位置からの位置指定
	* @tparam ValueType 値の型
	* @tpram Predicate 条件式の型
	* @param value 書き換える配列
	* @param array_size 配列数
	* @param pos 書き換え開始位置
	* @param pred 条件式
	* @return 書き換えた値
	* @attention
	*	Predicate
	*	param size_t pos reverseがtrueなら先頭からの位置情報 falseなら末尾からの位置情報
	*	return trueでon falseでoffにする
	*/
	template<bool reverse, typename ValueType, typename Predicate>
	constexpr void SetBitIf(ValueType* value, size_t array_size, size_t pos, Predicate pred)noexcept
	{
		for (size_t i = pos, bit_num = BitNum<ValueType>() * array_size; i < bit_num; ++i)
		{
			SetBit<reverse>(value, array_size, i, pred(i));
		}
	}

	/**
	* @brief 各bit毎に値を指定して書き換える
	* @tparam ValueType 値の型
	* @tpram Predicate 条件式の型
	* @param value 書き換える値
	* @param begin_pos 書き換え開始位置
	* @param end_pos 書き換え終了位置
	* @param pred 条件式
	* @return 書き換えた値
	* @attention
	*	Predicate
	*	param size_t pos 位置情報
	*	return trueでon falseでoffにする
	*/
	template<typename ValueType, typename Predicate>
	constexpr ValueType SetBitIf(ValueType value, size_t begin_pos, size_t end_pos, Predicate pred)noexcept
	{
		_ASSERT(begin_pos < end_pos);
		for (size_t i = begin_pos; i < BitNum(sizeof(ValueType)) && i < end_pos; ++i)
		{
			value = SetBit(value, i, pred(i));
		}
		return value;
	}

	/**
	* @brief 配列の各bit毎に値を指定して書き換える
	* @tparam ValueType 値の型
	* @tpram Predicate 条件式の型
	* @param value 書き換える配列
	* @param array_size 配列数
	* @param begin_pos 書き換え開始位置
	* @param end_pos 書き換え終了位置
	* @param pred 条件式
	* @attention
	*	Predicate
	*	param size_t pos 位置情報
	*	return trueでon falseでoffにする
	*/
	template<typename ValueType, typename Predicate>
	constexpr void SetBitIf(ValueType* value, size_t array_size, size_t begin_pos, size_t end_pos, Predicate pred)noexcept
	{
		_ASSERT(begin_pos < end_pos);
		for (size_t i = begin_pos, bit_num = BitNum<ValueType>() * array_size; i < bit_num && i < end_pos; ++i)
		{
			SetBit(value, array_size, i, pred(i));
		}
	}

	/**
	* @brief 各bit毎に値を指定して書き換える
	* @tparam reverse trueで先頭位置からの位置指定 falseで後方位置からの位置指定
	* @tparam ValueType 値の型
	* @tpram Predicate 条件式の型
	* @param value 書き換える値
	* @param begin_pos 書き換え開始位置
	* @param end_pos 書き換え終了位置
	* @param pred 条件式
	* @return 書き換えた値
	* @attention
	*	Predicate
	*	param size_t pos reverseがtrueなら先頭からの位置情報 falseなら末尾からの位置情報
	*	return trueでon falseでoffにする
	*/
	template<bool reverse, typename ValueType, typename Predicate>
	constexpr ValueType SetBitIf(ValueType value, size_t begin_pos, size_t end_pos, Predicate pred)noexcept
	{
		_ASSERT(begin_pos < end_pos);
		for (size_t i = begin_pos; i < BitNum(sizeof(ValueType)) && i < end_pos; ++i)
		{
			value = SetBit<reverse>(value, i, pred(i));
		}
		return value;
	}

	/**
	* @brief 配列の各bit毎に値を指定して書き換える
	* @tparam reverse trueで先頭位置からの位置指定 falseで後方位置からの位置指定
	* @tparam ValueType 値の型
	* @tpram Predicate 条件式の型
	* @param value 書き換える配列
	* @param array_size 配列数
	* @param begin_pos 書き換え開始位置
	* @param end_pos 書き換え終了位置
	* @param pred 条件式
	* @return 書き換えた値
	* @attention
	*	Predicate
	*	param size_t pos reverseがtrueなら先頭からの位置情報 falseなら末尾からの位置情報
	*	return trueでon falseでoffにする
	*/
	template<bool reverse, typename ValueType, typename Predicate>
	constexpr void SetBitIf(ValueType* value, size_t array_size, size_t begin_pos, size_t end_pos, Predicate pred)noexcept
	{
		_ASSERT(begin_pos < end_pos);
		for (size_t i = begin_pos, bit_num = BitNum<ValueType>() * array_size; i < bit_num && i < end_pos; ++i)
		{
			SetBit<reverse>(value, array_size, i, pred(i));
		}
	}

	/**
	* @brief 変数の指定範囲以外のbitをonまたはoffにする
	* @tparam ValueType 変更元の型
	* @param value 変更元
	* @param range 範囲
	* @param pos 下位からの位置
	* @param flag trueでon falseでoff
	*/
	template<typename ValueType>
	constexpr ValueType SetBitOther(ValueType value, size_t range, size_t pos, bool flag)noexcept
	{
		if(BitNum(value) - range < range)
		{
			for(size_t i = 0; i < pos; ++i)
			{
				value = SetBit(value, i, flag);
			}
			for(size_t i = pos + range; i < BitNum(value); ++i)
			{
				value = SetBit(value, i, flag);
			}
		}
		else
		{
			ValueType mask = flag ? 0 : BitFill<ValueType>();
			for(size_t i = pos; i < pos + range; ++i)
			{
				mask = SetBit(mask, i, flag);
			}
			value = flag ? value | (~mask) : value & (~mask);
		}
		return value;
	}

	/**
	* @brief 指定範囲のbitをonまたはoffにする
	* @tparam ValueType 変更元の型
	* @param value 変更元
	* @param range 範囲
	* @param pos 下位からの位置
	* @param flag trueでon falseでoff
	*/
	template<typename ValueType>
	constexpr ValueType SetBitRange(ValueType value, size_t range, size_t pos, bool flag)noexcept
	{
		if(BitNum<ValueType>() - range < range)
		{
			ValueType mask = flag ? BitFill<ValueType>() : 0;
			for(size_t i = 0; i < pos; ++i)
			{
				mask = SetBit(mask, i, !flag);
			}
			for(size_t i = pos + range; i < BitNum<ValueType>(); ++i)
			{
				mask = SetBit(mask, i, !flag);
			}
			value = flag ? value | mask : value & mask;
		}
		else
		{
			for (size_t i = pos; i < pos + range; ++i)
			{
				value = SetBit(value, i, flag);
			}
		}
		return value;
	}

	/**
	* @brief 指定範囲のbitを取り出す
	* @tparam SourceType 取り出し元の型
	* @param source 取り出し元
	* @param range 範囲
	* @param pos 下位からの位置
	*/
	template<typename SourceType>
	constexpr SourceType SliceBit(SourceType source, size_t range, size_t pos)noexcept
	{
		SourceType cut_needless = SetBitOther(source, range, pos, false);
		return cut_needless >> static_cast<SourceType>(pos);
	}

	/**
	* @brief ビットを状態をコピーする
	* @tparam DestType コピー先の型
	* @tparam SourceType コピー元の型
	* @param dest コピー先
	* @param source コピー元
	* @param range 範囲
	* @param dest_pos コピー先の貼り付け位置
	* @param souce_pos コピー元の切り取り位置
	*/
	template<typename DestType, typename SourceType>
	constexpr DestType CopyBit(DestType dest, SourceType source, size_t range, size_t dest_pos, size_t source_pos)noexcept
	{
		DestType cut_need = SetBitRange(dest, range, dest_pos, false);
		DestType cut_needless = static_cast<DestType>(SliceBit(source, range, source_pos)); //数値切り捨てが起こらないようSliceBitの後キャスト
		return cut_need | (cut_needless << dest_pos);
	}

	/**
	* @brief 上位ビットの値を書き換える
	* @tparam BaseType 書き換え元の型
	* @tparam ValueType 書き換えに使う値
	* @param base 書き換え元の値
	* @param new_val 書き換え先の値
	* @return 書き換えた値
	*/
	template<typename BaseType, typename ValueType>
	constexpr BaseType NewHighBit(BaseType base, ValueType new_val)noexcept
	{
		size_t base_type_div_size = BitNum(sizeof(BaseType)) / 2;
		return static_cast<BaseType>(new_val << base_type_div_size) | ((base << base_type_div_size) >> base_type_div_size);
	}

	/**
	* @brief 下位ビットの値を書き換える
	* @tparam BaseType 書き換え元の型
	* @tparam ValueType 書き換えに使う値
	* @param base 書き換え元の値
	* @param new_val 書き換え先の値
	* @return 書き換えた値
	*/
	template<typename BaseType, typename ValueType>
	constexpr BaseType NewLowBit(BaseType base, ValueType new_val)noexcept
	{
		size_t base_type_div_size = BitNum(sizeof(BaseType)) / 2;
		return static_cast<BaseType>(((new_val << base_type_div_size) >> base_type_div_size) | ((base >> base_type_div_size) << base_type_div_size));
	}
}
}

#endif