/**
* @file binary.hpp
* @brief �o�C�i������̕⏕���`����t�@�C��
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
	* @brief �r�b�g�����擾����
	* @tparam �r�b�g�����擾����^
	* @return �r�b�g��
	*/
	template<typename T>
	constexpr size_t BitNum()noexcept
	{
		return sizeof(T) * 8U;
	}

	/**
	* @brief �r�b�g�����擾����
	* @tparam �r�b�g�����擾����^
	* @return �r�b�g��
	*/
	template<typename T>
	constexpr size_t BitNum(T)noexcept
	{
		return sizeof(T) * 8U;
	}

	/**
	* @brief �z��^�̃r�b�g�����擾����
	* @tparam �z��^�̌��̌^
	* @param �z��^�̕ϐ�
	* @return �r�b�g��
	*/
	template<typename T, size_t Size>
	constexpr size_t BitNum(T (&)[Size])noexcept
	{
		return BitNum<T>() * Size;
	}

	/**
	* @brief �r�b�g�����o�C�g���ɕϊ�����
	* @param bit_num �r�b�g��
	* @return �o�C�g��
	*/
	constexpr size_t ByteNum(size_t bit_num)noexcept
	{
		return bit_num / 8U;
	}

	/**
	* @brief �擪�r�b�g����̈ʒu���擾����
	* @tparam T �r�b�g�����̌��ƂȂ�^���
	* @return �ʒu���
	*/
	template<typename T>
	constexpr size_t BitPosFromHead(size_t pos)noexcept
	{
		return BitNum<T>() - 1 - pos;
	}

	/**
	* @brief �S�Ă�bit��on�ɂ���
	* @tparam T �I���ɂ���^
	* @return �S�Ă�bit��on�ɂȂ��Ă���l
	*/
	template<typename T>
	constexpr T BitFill()noexcept
	{
		T fill = 0;
		return ~fill;
	}

	/**
	* @brief �S�Ă�bit��on�ɂ���
	* @tparam T �I���ɂ���^
	* @return �S�Ă�bit��on�ɂȂ��Ă���l
	*/
	template<typename T>
	constexpr T BitFill(T)noexcept
	{
		T fill = 0;
		return ~fill;
	}

	/**
	* @brief �l����ʂƉ��ʂɕ�������
	* @tparam T �����O�̒l�̌^
	* @param val �����������l
	* @return ���������l first ��� second ����
	*/
	template<typename T>
	constexpr std::pair<T, T> DivValue(const T& val)noexcept
	{
		size_t arg_type_div_size = BitNum(sizeof(T)) / 2;
		T low_value = (val << arg_type_div_size); //�͂ݏo�����f�[�^���폜���邽�߂ɑ��
		return std::make_pair<T, T>(val >> arg_type_div_size, low_value >> arg_type_div_size);
	}

	/**
	* @brief 2�̒l����ʁE���ʂƂ��Ĉ�̒l�ɑ��
	* @tparam ReturnType �߂�l�Ɏg���^
	* @tparam ValueType �����̌^
	* @param height_val ��ʃr�b�g�ɓ����l
	* @param low_val ���ʃr�b�g�ɓ����l
	* @return �������
	*/
	template<typename ReturnType, typename ValueType>
	constexpr ReturnType MakeValue(ValueType high, ValueType low)noexcept
	{
		size_t return_type_div_size = BitNum(sizeof(ReturnType)) / 2;
		return static_cast<ReturnType>(high << return_type_div_size) | static_cast<ReturnType>(low);
	}

	/**
	* @brief �z�����̕ϐ��ɋl�ߍ���
	* @tparam T �l�ߍ��ݐ�̕ϐ��̌^
	* @tparam InputIterator ���͂̌^
	* @param first �J�n�ʒu
	* @param last �I���ʒu
	* @return �l�ߍ��񂾕ϐ�
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
	* @brief �z���ʂ̔z��Ƀp�b�N����
	* @tparam InputType ���͂̌^
	* @tparam OutputType �o�͂̌^
	* @tparam InputIterator ���͂̃C�e���[�^�[�^
	* @tparam OutputIterator �o�͂̃C�e���[�^�[�^
	* @param first �J�n�ʒu
	* @param last �I���ʒu
	* @param output �o�͐�
	* @attention
	*	PackArray�̕��i�ł��邽�ߒ��ڎg�p���Ȃ�
	*	�T�C�Y��InputType <= OutputType�ƂȂ��Ă���Ƃ��̂ݎg�p 
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
	* @brief �z���ʂ̔z��Ƀp�b�N����
	* @tparam InputType ���͂̌^
	* @tparam OutputType �o�͂̌^
	* @tparam InputIterator ���͂̃C�e���[�^�[�^
	* @tparam OutputIterator �o�͂̃C�e���[�^�[�^
	* @param first �J�n�ʒu
	* @param last �I���ʒu
	* @param output �o�͐�
	* @attention
	*	PackArray�̕��i�ł��邽�ߒ��ڎg�p���Ȃ�
	*	�T�C�Y��InputType > OutputType�ƂȂ��Ă���Ƃ��̂ݎg�p
	*/
	template<typename InputType, typename OutputType, typename InputIterator, typename OutputIterator, std::enable_if_t<!(sizeof(InputType) <= sizeof(OutputType)), std::nullptr_t> = nullptr>
	constexpr void PackArray(InputIterator first, InputIterator last, OutputIterator output)noexcept
	{
		OutputType array_value = 0;
		auto shift_size = BitNum<OutputType>();
		size_t shift_num = 1;
		while (first != last)
		{
			//���l�؂�̂Ă̂��߃L���X�g
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
	* @brief �z���ʂ̔z��Ƀp�b�N����
	* @tparam T �l�ߍ��ݐ�̕ϐ��̌^
	* @tparam InputIterator ���͂̌^
	* @tparam OutputIterator �o�͐�̌^
	* @param first �J�n�ʒu
	* @param last �I���ʒu
	* @param output �o�͐�
	*/
	template<typename InputIterator, typename OutputIterator>
	constexpr void PackArray(InputIterator first, InputIterator last, OutputIterator output)noexcept
	{
		using InputType = std::remove_reference_t<decltype(*first)>;
		using OutputType = std::remove_reference_t<decltype(*output)>;
		details::PackArray<InputType, OutputType>(first, last, output);
	}

	/**
	* @brief �w��r�b�g�̒l������������
	* @tparam ValueType ����������l�̌^
	* @param value �ύX�����l
	* @param pos �ύX�ʒu
	* @param on true��1 false��0 �ɂ���
	* @retrun �����������l
	*/
	template<typename ValueType>
	constexpr ValueType SetBit(ValueType value, size_t pos, bool on)noexcept
	{
		return on ? value | (static_cast<ValueType>(1) << pos) : value & (~(static_cast<ValueType>(1) << pos));
	}

	/**
	* @brief ��L��SetBit�̎w��ʒu��擪����������̂ǂ��炩�炩�w��\�ɂ�������
	* @tparam reverse true�Ő擪�ʒu����̈ʒu�w�� false�Ō���ʒu����̈ʒu�w��
	* @tparam ValueType ����������l�̌^
	* @param value �ύX�����l
	* @param pos �ύX�ʒu
	* @param on true��1 false��0 �ɂ���
	* @retrun �����������l
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
	* @brief SetBit�z��� �z�����̑傫�ȕϐ��������ĂĒl������������
	* @tparam ValueType ����������l�̌^
	* @param value �ύX�����l
	* @param array_size �z��
	* @param pos �ύX�ʒu
	* @param on true��1 false��0 �ɂ���
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
	* @brief SetBit�z��� �z�����̑傫�ȕϐ��������ĂĒl������������
	* @tparam reverse true�Ő擪�ʒu����̈ʒu�w�� false�Ō���ʒu����̈ʒu�w��
	* @tparam ValueType ����������l�̌^
	* @param value �ύX�����l
	* @param array_size �z��
	* @param pos �ύX�ʒu
	* @param on true��1 false��0 �ɂ���
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
	* @brief �ebit���ɒl���w�肵�ď���������
	* @tparam ValueType �l�̌^
	* @tpram Predicate �������̌^
	* @param value ����������l
	* @param pos ���������J�n�ʒu
	* @param pred ������
	* @return �����������l
	* @attention
	*	Predicate
	*	param size_t pos �ʒu���
	*	return true��on false��off�ɂ���
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
	* @brief �z��̊ebit���ɒl���w�肵�ď���������
	* @tparam ValueType �l�̌^
	* @tpram Predicate �������̌^
	* @param value ����������z��
	* @param array_size �z��
	* @param pos ���������J�n�ʒu
	* @param pred ������
	* @attention
	*	Predicate
	*	param size_t pos �ʒu���
	*	return true��on false��off�ɂ���
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
	* @brief �ebit���ɒl���w�肵�ď���������
	* @tparam reverse true�Ő擪�ʒu����̈ʒu�w�� false�Ō���ʒu����̈ʒu�w��
	* @tparam ValueType �l�̌^
	* @tpram Predicate �������̌^
	* @param value ����������l
	* @param pos ���������J�n�ʒu
	* @param pred ������
	* @return �����������l
	* @attention
	*	Predicate
	*	param size_t pos reverse��true�Ȃ�擪����̈ʒu��� false�Ȃ疖������̈ʒu���
	*	return true��on false��off�ɂ���
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
	* @brief �z��̊ebit���ɒl���w�肵�ď���������
	* @tparam reverse true�Ő擪�ʒu����̈ʒu�w�� false�Ō���ʒu����̈ʒu�w��
	* @tparam ValueType �l�̌^
	* @tpram Predicate �������̌^
	* @param value ����������z��
	* @param array_size �z��
	* @param pos ���������J�n�ʒu
	* @param pred ������
	* @return �����������l
	* @attention
	*	Predicate
	*	param size_t pos reverse��true�Ȃ�擪����̈ʒu��� false�Ȃ疖������̈ʒu���
	*	return true��on false��off�ɂ���
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
	* @brief �ebit���ɒl���w�肵�ď���������
	* @tparam ValueType �l�̌^
	* @tpram Predicate �������̌^
	* @param value ����������l
	* @param begin_pos ���������J�n�ʒu
	* @param end_pos ���������I���ʒu
	* @param pred ������
	* @return �����������l
	* @attention
	*	Predicate
	*	param size_t pos �ʒu���
	*	return true��on false��off�ɂ���
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
	* @brief �z��̊ebit���ɒl���w�肵�ď���������
	* @tparam ValueType �l�̌^
	* @tpram Predicate �������̌^
	* @param value ����������z��
	* @param array_size �z��
	* @param begin_pos ���������J�n�ʒu
	* @param end_pos ���������I���ʒu
	* @param pred ������
	* @attention
	*	Predicate
	*	param size_t pos �ʒu���
	*	return true��on false��off�ɂ���
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
	* @brief �ebit���ɒl���w�肵�ď���������
	* @tparam reverse true�Ő擪�ʒu����̈ʒu�w�� false�Ō���ʒu����̈ʒu�w��
	* @tparam ValueType �l�̌^
	* @tpram Predicate �������̌^
	* @param value ����������l
	* @param begin_pos ���������J�n�ʒu
	* @param end_pos ���������I���ʒu
	* @param pred ������
	* @return �����������l
	* @attention
	*	Predicate
	*	param size_t pos reverse��true�Ȃ�擪����̈ʒu��� false�Ȃ疖������̈ʒu���
	*	return true��on false��off�ɂ���
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
	* @brief �z��̊ebit���ɒl���w�肵�ď���������
	* @tparam reverse true�Ő擪�ʒu����̈ʒu�w�� false�Ō���ʒu����̈ʒu�w��
	* @tparam ValueType �l�̌^
	* @tpram Predicate �������̌^
	* @param value ����������z��
	* @param array_size �z��
	* @param begin_pos ���������J�n�ʒu
	* @param end_pos ���������I���ʒu
	* @param pred ������
	* @return �����������l
	* @attention
	*	Predicate
	*	param size_t pos reverse��true�Ȃ�擪����̈ʒu��� false�Ȃ疖������̈ʒu���
	*	return true��on false��off�ɂ���
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
	* @brief �ϐ��̎w��͈͈ȊO��bit��on�܂���off�ɂ���
	* @tparam ValueType �ύX���̌^
	* @param value �ύX��
	* @param range �͈�
	* @param pos ���ʂ���̈ʒu
	* @param flag true��on false��off
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
	* @brief �w��͈͂�bit��on�܂���off�ɂ���
	* @tparam ValueType �ύX���̌^
	* @param value �ύX��
	* @param range �͈�
	* @param pos ���ʂ���̈ʒu
	* @param flag true��on false��off
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
	* @brief �w��͈͂�bit�����o��
	* @tparam SourceType ���o�����̌^
	* @param source ���o����
	* @param range �͈�
	* @param pos ���ʂ���̈ʒu
	*/
	template<typename SourceType>
	constexpr SourceType SliceBit(SourceType source, size_t range, size_t pos)noexcept
	{
		SourceType cut_needless = SetBitOther(source, range, pos, false);
		return cut_needless >> static_cast<SourceType>(pos);
	}

	/**
	* @brief �r�b�g����Ԃ��R�s�[����
	* @tparam DestType �R�s�[��̌^
	* @tparam SourceType �R�s�[���̌^
	* @param dest �R�s�[��
	* @param source �R�s�[��
	* @param range �͈�
	* @param dest_pos �R�s�[��̓\��t���ʒu
	* @param souce_pos �R�s�[���̐؂���ʒu
	*/
	template<typename DestType, typename SourceType>
	constexpr DestType CopyBit(DestType dest, SourceType source, size_t range, size_t dest_pos, size_t source_pos)noexcept
	{
		DestType cut_need = SetBitRange(dest, range, dest_pos, false);
		DestType cut_needless = static_cast<DestType>(SliceBit(source, range, source_pos)); //���l�؂�̂Ă��N����Ȃ��悤SliceBit�̌�L���X�g
		return cut_need | (cut_needless << dest_pos);
	}

	/**
	* @brief ��ʃr�b�g�̒l������������
	* @tparam BaseType �����������̌^
	* @tparam ValueType ���������Ɏg���l
	* @param base �����������̒l
	* @param new_val ����������̒l
	* @return �����������l
	*/
	template<typename BaseType, typename ValueType>
	constexpr BaseType NewHighBit(BaseType base, ValueType new_val)noexcept
	{
		size_t base_type_div_size = BitNum(sizeof(BaseType)) / 2;
		return static_cast<BaseType>(new_val << base_type_div_size) | ((base << base_type_div_size) >> base_type_div_size);
	}

	/**
	* @brief ���ʃr�b�g�̒l������������
	* @tparam BaseType �����������̌^
	* @tparam ValueType ���������Ɏg���l
	* @param base �����������̒l
	* @param new_val ����������̒l
	* @return �����������l
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