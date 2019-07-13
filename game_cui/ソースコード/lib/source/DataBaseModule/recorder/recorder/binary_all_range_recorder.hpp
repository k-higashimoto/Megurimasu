/**
* @file binary_all_range_recorder.hpp
* @brief BinaryAllRangeRecorder定義ファイル
*/

#pragma once

#include"../recorder.hpp"

namespace database
{
	/**
	* @struct BinaryLearningData
	* @brief 学習データ
	*/
	struct BinaryLearningData
	{
		bool result;					//!< 試合結果
		std::uint64_t board_state[5];	//!< タイル状態
		std::uint64_t board_sign[3];	//!< 盤面の符号
		std::uint8_t action;			//!< 主観エージェントの動作
		std::uint8_t my;				//!< 主観エージェントの位置
		std::uint8_t friend_agent;		//!< 味方エージェントの位置
		std::uint8_t enemy_agent1;		//!< 敵エージェントの位置1
		std::uint8_t enemy_agent2;		//!< 敵エージェントの位置2
	};

	/**
	* @class BinaryAllRangeRecorder
	* @brief データにバイナリ変換を適用するレコーダー
	*/
	class BinaryAllRangeRecorder final :
		public Recorder
	{
	public:
		static constexpr const sup::Char* const database_name = TEXT("BinaryAllRangeDataBase.db");

	private:
		/**
		* @brief データの存在を確認する
		* @param stmt 使用するステートメント
		* @param data 学習データ
		* @return true存在 falseない
		*/
		bool Exists(sup::SQlite::SQliteStmt& stmt, const BinaryLearningData& data);

		/**
		* @brief データを挿入
		* @param data 学習データ
		*/
		void Insert(sup::SQlite::SQliteStmt& stmt, const BinaryLearningData& data);

		/**
		* @brief データを更新
		* @param data 学習データ
		*/
		void Update(sup::SQlite::SQliteStmt& stmt, const BinaryLearningData& data);

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