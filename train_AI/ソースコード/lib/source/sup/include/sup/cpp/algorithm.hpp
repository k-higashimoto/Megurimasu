/**
* @file container_algorithm.hpp
* @brief コンテナを使用したアルゴリズムの定義ファイル
*/

#ifndef SUP_LIB_CPP_ALGORITHM_HPP
#define SUP_LIB_CPP_ALGORITHM_HPP

#include<algorithm>

namespace sup
{
inline namespace cpp
{
//----------------------------------------------------------------------------------------------------------------------------------------------------
	/**
	* @brief 指定内容をコンテナから削除する
	* @tparam T コンテナの型
	* @tparam U 削除要素の型
	* @param container コンテナ
	* @param value 削除する値
	*/
	template<typename T, typename U>
	void Remove(T* container, const U& value)
	{
		container->erase(std::remove(container->begin(), container->end(), value), container->end());
	}

	/**
	* @brief 女件を満たした内容をコンテナから削除する
	* @tparam T コンテナの型
	* @param container コンテナ
	* @param value 削除する値
	* @attention
	*	Predicate 
	*	戻り値 : bool trueで削除 falseで残す
	*	引数 イテレータiの*i
	*/
	template<typename T, typename Predicate>
	void RemoveIf(T* container, Predicate pred)
	{
		container->erase(std::remove_if(container->begin(), container->end(), pred), container->end());
	}

	/**
	* @brief コンテナ内のデータをシフトさせる
	* @tparam right シフト方向
	* @tparam T コンテナの型
	* @param container シフトさせるコンテナ
	*/
	template<bool right, typename T>
	void Sift(T* container)
	{
		if constexpr(right)
		{
			container->insert(container->begin(), container->back());
			container->pop_back();
		}
		else
		{
			container->push_back(container->front());
			container->erase(container->begin());
		}
	}

	/**
	* @brief 指定数コンテナ内のデータをシフトさせる
	* @tparam right シフト方向
	* @tparam T コンテナの型
	* @param container シフトさせるコンテナ
	* @param count シフト数
	*/
	template<bool right, typename T>
	void Sift(T* container, size_t count)
	{
		for(size_t i = 0; i < count; ++i)
		{
			Sift<right>(container);
		}
	}


//----------------------------------------------------------------------------------------------------------------------------------------------------
/**
* @def FOR
* @brief forループの簡略表記用
* @attention ループにはint変数iを使用する
*/
#undef FOR
#define FOR(num) for(int i = 0; i < num; ++i)

/**
* @def FOR2
* @brief 2重のforループの簡略表記用
* @attention ループにはint変数i,jを使用する
*/
#undef FOR2
#define FOR2(num1, num2) for(int i = 0; i < num1; ++i) for(int j = 0; j < num2; ++j)

/**
* @def FOR3
* @brief 3重のforループの簡略表記用
* @attention ループにはint変数i,j,kを使用する
*/
#undef FOR3
#define FOR3(num1, num2, num3) for(int i = 0; i < num1; ++i) for(int j = 0; j < num2; ++j) for(int k = 0; k < num3; ++k)
}
}

#endif