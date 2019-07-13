/**
* @file container_algorithm.hpp
* @brief �R���e�i���g�p�����A���S���Y���̒�`�t�@�C��
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
	* @brief �w����e���R���e�i����폜����
	* @tparam T �R���e�i�̌^
	* @tparam U �폜�v�f�̌^
	* @param container �R���e�i
	* @param value �폜����l
	*/
	template<typename T, typename U>
	void Remove(T* container, const U& value)
	{
		container->erase(std::remove(container->begin(), container->end(), value), container->end());
	}

	/**
	* @brief �����𖞂��������e���R���e�i����폜����
	* @tparam T �R���e�i�̌^
	* @param container �R���e�i
	* @param value �폜����l
	* @attention
	*	Predicate 
	*	�߂�l : bool true�ō폜 false�Ŏc��
	*	���� �C�e���[�^i��*i
	*/
	template<typename T, typename Predicate>
	void RemoveIf(T* container, Predicate pred)
	{
		container->erase(std::remove_if(container->begin(), container->end(), pred), container->end());
	}

	/**
	* @brief �R���e�i���̃f�[�^���V�t�g������
	* @tparam right �V�t�g����
	* @tparam T �R���e�i�̌^
	* @param container �V�t�g������R���e�i
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
	* @brief �w�萔�R���e�i���̃f�[�^���V�t�g������
	* @tparam right �V�t�g����
	* @tparam T �R���e�i�̌^
	* @param container �V�t�g������R���e�i
	* @param count �V�t�g��
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
* @brief for���[�v�̊ȗ��\�L�p
* @attention ���[�v�ɂ�int�ϐ�i���g�p����
*/
#undef FOR
#define FOR(num) for(int i = 0; i < num; ++i)

/**
* @def FOR2
* @brief 2�d��for���[�v�̊ȗ��\�L�p
* @attention ���[�v�ɂ�int�ϐ�i,j���g�p����
*/
#undef FOR2
#define FOR2(num1, num2) for(int i = 0; i < num1; ++i) for(int j = 0; j < num2; ++j)

/**
* @def FOR3
* @brief 3�d��for���[�v�̊ȗ��\�L�p
* @attention ���[�v�ɂ�int�ϐ�i,j,k���g�p����
*/
#undef FOR3
#define FOR3(num1, num2, num3) for(int i = 0; i < num1; ++i) for(int j = 0; j < num2; ++j) for(int k = 0; k < num3; ++k)
}
}

#endif