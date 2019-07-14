/**
* @file literal_class.hpp
* @brief リテラルラップクラス実装ファイル
*/

#ifndef SUP_LIB_CPP_LITERAL_CLASS_HPP
#define SUP_LIB_CPP_LITERAL_CLASS_HPP

/**
* @brief リテラルのラップクラスを作成する
* @param CLASS_NAME クラス名
* @param TYPE_NAME ラップするリテラルの型
* @param VAR_NAME メンバ変数の名前
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
* @brief リテラルで配列型のラップクラスを作成する
* @param CLASS_NAME クラス名
* @param TYPE_NAME ラップするリテラルの型
* @param VAR_NAME メンバ変数の名前
* @param ARRAY_SIZE 配列数
* @attention 関数内で使用不可であることに注意
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