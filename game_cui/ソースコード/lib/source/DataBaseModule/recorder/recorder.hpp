/**
* @file recorder.hpp
* @brief recorder定義ファイル
*/

#pragma once

#include<vector>
#include<sup/cpp/string.hpp>
#include<sup/sqlite_extend/sqlite_extend.hpp>
#include"../base.hpp"
#include"../learning_data.hpp"

namespace database
{
	/**
	* @class Recorder
	* @brief レコーダーの基底クラス
	*/
	class Recorder
	{
	protected:
		static inline std::vector<LearningData> learning_data; //!< 学習データ

	protected:
		/**
		* @brief テーブル名を取得する
		* @return テーブル名
		*/
		virtual sup::String GetTableName() = 0;

		/**
		* @brief テーブルがなければ作成する
		* @param table_name テーブル名
		* @return true正常に動作　false異常終了
		*/
		virtual bool CreateTable(const sup::String& table_name) = 0;

		/**
		* @brief データベースを更新する
		* @param table_name テーブル名
		* @return true成功　false失敗
		*/
		virtual bool Update(const sup::String& table_name) = 0;

	public:
		/**
		* @brief 学習データを蓄える
		* @param data 学習データ
		*/
		static void PushBack(const LearningData& data);

		/**
		* @brief 後ろの学習データを削除
		*/
		static void PopBack();

		/**
		* @brief 学習データを削除
		*/
		static void Clear();

		/**
		* @brief 学習データを記録する
		* @return true成功 false失敗
		*/
		virtual bool Record()final;
	};
}