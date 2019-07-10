/**
* @file unprocessed_recorder.hpp
* @biref UnprocessedRecorder定義ファイル
*/

#pragma once

#include<sup/cpp/string.hpp>
#include"../recorder.hpp"

namespace database
{
	/**
	* @class UnprocessedRecorder
	* @brief データをそのまま記録するレコーダー
	*/
	class UnprocessedRecorder final :
		public Recorder
	{
	public:
		static constexpr const sup::Char* const database_name = TEXT("UnprocessDataBase.db");

	protected:
		/**
		* @brief テーブル名作製
		* @return テーブル名
		*/
		virtual sup::String GetTableName()override;

		/**
		* @brief テーブルがなければ作成する
		* @param table_name テーブル名
		* @return true正常に動作　false異常終了
		*/
		virtual bool CreateTable(const sup::String& table_name)override;

		/**
		* @brief データベースを更新する
		* @param table_name テーブル名
		* @return true成功　false失敗
		*/
		virtual bool Update(const sup::String& table_name)override;
	};
}