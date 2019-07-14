/**
* @file boost_python.hpp
* @brief boost_pythonの拡張ファイル
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
	* @brief 辞書型の値をmapに変換する
	* @tparam T mapのキー型
	* @tparam U mapの値の型
	* @param dict pythonの値
	* @return 変換結果
	*/
	template<typename T, typename U>
	std::map<T, U> ConvertDictToMap(const ::boost::python::dict& dict)
	{
		std::map<T, U> ans{};
		int len = static_cast<int>(::boost::python::len(dict));
		auto keys = dict.keys();

		for (int i = 0; i < len; ++i)
		{
			//Tでなくautoで受け取ろうとするとTに変換されずextract<T>を受け取ろうとしてエラーが出る
			T key_val = ::boost::python::extract<T>(keys[i]);
			ans[key_val] = ::boost::python::extract<U>(dict[key_val]);
		}

		return ans;
	}

	/**
	* @brief mapを辞書型に変換する
	* @tparam T mapのキーの型
	* @tparam U mapの格納する型
	* @param map 変換したいmapの値
	* @return 変換結果
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
	* @brief リストをvectorに変換する
	* @tparam T vectorテンプレート引数に渡す型
	* @param list 変換元
	* @return 変換後のデータ
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
	* @brief vectorをリストに変換する
	* @tparam T vectorテンプレート引数に渡す型
	* @param vector 変換元
	* @return 変換結果
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
