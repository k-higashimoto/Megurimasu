/**
* @file array_reference_function.hpp
* @brief �N���X�Ɏ��������z��̎Q�Ɨp�̋@�\���ȒP�ɒǉ����邽�߂̃}�N�����`����t�@�C��
*/

#ifndef SUP_LIB_CPP_ARRAY_REFERENCE_FUNCTION_HPP
#define SUP_LIB_CPP_ARRAY_REFERENCE_FUNCTION_HPP

#include<iterator>

/**
* @brief �Y�����Z�q�̃I�[�o�[���[�h��ǉ�����
* @param TYPE_NAME �z��̌^
* @param VAR_NAME �ϐ���
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
* @brief begin end��ǉ�����
* @param VAR_NAME �ϐ���
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
* @breif ARRAY_SUFFIX_OVERLOAD��ARRAY_BEGIN_END_FUNCTION�̗�����ǉ�����
* @param VAR_NAME �ϐ���
*/
#define ADD_ARRAY_REFERENCE_FUNCTION(VAR_NAME)	\
ADD_ARRAY_SUFFIX_OVERLOAD(VAR_NAME)				\
ADD_ARRAY_BEGIN_END_FUNCTION(VAR_NAME)			

#endif