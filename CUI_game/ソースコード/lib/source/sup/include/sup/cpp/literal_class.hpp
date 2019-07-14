/**
* @file literal_class.hpp
* @brief ���e�������b�v�N���X�����t�@�C��
*/

#ifndef SUP_LIB_CPP_LITERAL_CLASS_HPP
#define SUP_LIB_CPP_LITERAL_CLASS_HPP

/**
* @brief ���e�����̃��b�v�N���X���쐬����
* @param CLASS_NAME �N���X��
* @param TYPE_NAME ���b�v���郊�e�����̌^
* @param VAR_NAME �����o�ϐ��̖��O
*/
#define LITERAL_CLASS(CLASS_NAME, TYPE_NAME, VAR_NAME)				\
class CLASS_NAME final												\
{																	\
public:																\
	using literal_type = TYPE_NAME;									\
																	\
public:																\
	CLASS_NAME() = default;											\
																	\
public:																\
	constexpr explicit CLASS_NAME(TYPE_NAME value)noexcept :		\
		VAR_NAME(value)												\
	{																\
	};																\
																	\
public:																\
	TYPE_NAME VAR_NAME;												\
																	\
public:																\
	TYPE_NAME& operator()()noexcept									\
	{																\
		return this->VAR_NAME;										\
	};																\
																	\
	const TYPE_NAME& operator()()const noexcept						\
	{																\
		return this->VAR_NAME;										\
	};																\
}


/**
* @brief ���e�����Ŕz��^�̃��b�v�N���X���쐬����
* @param CLASS_NAME �N���X��
* @param TYPE_NAME ���b�v���郊�e�����̌^
* @param VAR_NAME �����o�ϐ��̖��O
* @param ARRAY_SIZE �z��
* @attention �֐����Ŏg�p�s�ł��邱�Ƃɒ���
*/
#define LITERAL_ARRAY_CLASS(CLASS_NAME, TYPE_NAME, VAR_NAME, ARRAY_SIZE)		\
class CLASS_NAME final															\
{																				\
public:																			\
	using literal_type = TYPE_NAME;												\
	using literal_array_type = TYPE_NAME[ARRAY_SIZE];							\
																				\
public:																			\
	static constexpr size_t array_size = ARRAY_SIZE;							\
																				\
public:																			\
	CLASS_NAME() = default;														\
																				\
public:																			\
	constexpr explicit CLASS_NAME(TYPE_NAME value[ARRAY_SIZE])noexcept :		\
		VAR_NAME()																\
	{																			\
		for(size_t i = 0; i < ARRAY_SIZE; ++i)									\
		{																		\
			VAR_NAME[i] = value[i];												\
		}																		\
	};																			\
																				\
public:																			\
	TYPE_NAME VAR_NAME[ARRAY_SIZE];												\
																				\
public:																			\
	TYPE_NAME& operator[](size_t size)noexcept									\
	{																			\
		return this->VAR_NAME[size];											\
	};																			\
																				\
	const TYPE_NAME& operator[](size_t size)const noexcept						\
	{																			\
		return this->VAR_NAME[size];											\
	};																			\
																				\
	TYPE_NAME* begin()noexcept													\
	{																			\
		return this->VAR_NAME;													\
	};																			\
																				\
	TYPE_NAME* end()noexcept													\
	{																			\
		return &this->VAR_NAME[ARRAY_SIZE];										\
	};																			\
																				\
	const TYPE_NAME* begin()const noexcept										\
	{																			\
		return this->VAR_NAME;													\
	};																			\
																				\
	const TYPE_NAME* end()const noexcept										\
	{																			\
		return &this->VAR_NAME[ARRAY_SIZE];										\
	};																			\
}

#endif