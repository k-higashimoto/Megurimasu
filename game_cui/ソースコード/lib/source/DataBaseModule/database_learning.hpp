/**
* @file database_learning.hpp
* @brief DataBaseLearning宣言ファイル
*/

#pragma once
#include<vector>
#include<map>
#include<boost/python.hpp>
#include"base.hpp"

namespace database
{	
	/**
	* @class DataBaseLearning
	* @brief 学習用クラス
	*/
	class DataBaseLearning final
	{
	private:
		InitData init_data;					//!< 初期データ
		TermData term_data;					//!< 終了データ 
		std::vector<TurnData> turn_data;	//!< 学習データ

	public:
		/**
		* @brief 初期データをセットする
		*/
		void SetInit(const boost::python::dict& dict)noexcept;

		/**
		* @brief 初期データをセットする
		*/
		void SetTerm(const boost::python::dict& dict)noexcept;

		/**
		* @brief ターンデータを蓄える
		* @param turn ターンデータ
		*/
		void PushTurn(const boost::python::dict& dict)noexcept;

		/**
		* @brief ターンデータを取り出す
		*/
		void PopTurn()noexcept;

		/**
		* @brief ターンデータを破棄する
		*/
		void ClearTurn()noexcept;

		/**
		* @brief 学習データを保存する
		* @return trueで成功 false失敗
		*/
		bool Save()noexcept;
	};
}