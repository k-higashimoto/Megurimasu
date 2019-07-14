/**
* @file boost_python.hpp
* @brief boost_python�̊g���t�@�C��
*/

#ifndef SUP_LIB_BOOST_EXTEND_BOOST_PYTHON_HPP
#define SUP_LIB_BOOST_EXTEND_BOOST_PYTHON_HPP

#include<map>
#include<vector>
#include<boost/python/dict.hpp>
#include<boost/python/list.hpp>

namespace sup
{
inline namespace boost_extend
{
	/**
	* @brief �����^�̒l��map�ɕϊ�����
	* @tparam T map�̃L�[�^
	* @tparam U map�̒l�̌^
	* @param dict python�̒l
	* @return �ϊ�����
	*/
	template<typename T, typename U>
	std::map<T, U> ConvertDictToMap(const ::boost::python::dict& dict)
	{
		std::map<T, U> ans{};
		int len = static_cast<int>(::boost::python::len(dict));
		auto keys = dict.keys();

		for (int i = 0; i < len; ++i)
		{
			//T�łȂ�auto�Ŏ󂯎�낤�Ƃ����T�ɕϊ����ꂸextract<T>���󂯎�낤�Ƃ��ăG���[���o��
			T key_val = ::boost::python::extract<T>(keys[i]);
			ans[key_val] = ::boost::python::extract<U>(dict[key_val]);
		}

		return ans;
	}

	/**
	* @brief map�������^�ɕϊ�����
	* @tparam T map�̃L�[�̌^
	* @tparam U map�̊i�[����^
	* @param map �ϊ�������map�̒l
	* @return �ϊ�����
	*/
	template<typename T, typename U>
	::boost::python::dict ConvertMapToDict(const std::map<T, U>& map)
	{
		::boost::python::dict ans{};
		for (const auto& it : map)
		{
			ans[it.first] = it.second;
		}
		return ans;
	}

	/**
	* @brief ���X�g��vector�ɕϊ�����
	* @tparam T vector�e���v���[�g�����ɓn���^
	* @param list �ϊ���
	* @return �ϊ���̃f�[�^
	*/
	template<typename T>
	std::vector<T> ConvertListToVector(const ::boost::python::list& list)
	{
		std::vector<T> ans{};
		int len = static_cast<int>(::boost::python::len(list));
		
		for(int i = 0; i < len; ++i)
		{
			ans.push_back(::boost::python::extract<T>(list[i]));
		}

		return ans;
	}

	/**
	* @brief vector�����X�g�ɕϊ�����
	* @tparam T vector�e���v���[�g�����ɓn���^
	* @param vector �ϊ���
	* @return �ϊ�����
	*/
	template<typename T>
	::boost::python::list ConvertVectorToList(const std::vector<T>& vector)
	{
		::boost::python::list ans{};
		for (const auto& it : vector)
		{
			ans.append(it);
		}
		return ans;
	}
}
}

#endif
