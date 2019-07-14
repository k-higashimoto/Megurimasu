/**
* @file enum_size.hpp
* @brief �񋓂̋@�\�g���p�̃}�N���E�֐���`�t�@�C��
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
	* @breif �񋓃T�C�Y�擾�p�ɗ񋓂̍Ō�Ɏg�p����}�N��
	* @attention
	*	�E�񋓂̓r���Œl���w�肵�Ă����ꍇ�A���͗񋓖����d������ꍇ�g�p�s��
	*	�E�g�p�� : enum { ITEM_A, ITEM_B, ITEM_NUM }; 
	*/
	#define ENUM_ITEM_NUM ENUM_ITEM_NUM_BOOK_MARK

	/**
	* @def enum_size
	* @brief �񋓃T�C�Y���擾����
	* @attention
	*	��L�Œ�`����ENUM_ITEM_NUM���g�p�����񋓂���T�C�Y���擾����
	*/
	template<typename T, std::enable_if_t<std::is_enum_v<T>, std::nullptr_t> = nullptr>
	constexpr size_t enum_size = static_cast<size_t>(T::ENUM_ITEM_NUM);

	/**
	* @brief �񋓂̒l�����^�̒l�ɕϊ�����
	* @param item �ϊ�����l
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
