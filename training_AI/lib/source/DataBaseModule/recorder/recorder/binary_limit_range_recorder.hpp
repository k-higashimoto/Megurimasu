/**
* @file binary_limit_range_recorder.hpp
* @biref BinaryLimitRangeRecorder定義ファイル
*/

#pragma once

#include"../recorder.hpp"

namespace database
{
	/**
	* @def kSourceSideSize
	* @brief データをとる正方形範囲の一辺のサイズ
	*/
	constexpr size_t kSourceSideSize = 5;

	/**
	* @def kSourceAreaSize
	* @brief データをとる正方形の面積サイズ
	*/
	constexpr size_t kSourceAreaSize = kSourceSideSize * kSourceSideSize;

	/**
	* @def kSourceAmplitudeSize
	* @brief エージェント位置を原点としたときの振れ幅
	*/
	constexpr size_t kSourceAmplitudeSize = static_cast<size_t>(kSourceSideSize / 2);

	/**
	* @struct BinaryLimitLearningData
	* @brief 5X5範囲のバイナリ学習データ
	*/
	struct BinaryLimitLearningData
	{
		bool result;					//!< 試合結果
		std::uint32_t invalid_area;		//!< 範囲外情報(1で有効 0で無効)
		std::uint64_t board_state;		//!< タイル状態
		std::uint32_t board_sign;		//!< 盤面の符号
		std::uint8_t action;			//!< 主観エージェントの動作
		std::uint8_t my;				//!< 主観エージェントの位置
		std::uint8_t friend_agent;		//!< 味方エージェントの位置
		std::uint8_t enemy_agent1;		//!< 敵エージェントの位置1
		std::uint8_t enemy_agent2;		//!< 敵エージェントの位置2
	};

	/**
	* @class BinaryLimitRangeRecorder
	* @brief データの一部をバイナリ化して記録するレコーダー
	*/
	class BinaryLimitRangeRecorder final :
		public Recorder
	{
	public:
		static constexpr const sup::Char* const database_name = TEXT("BinaryLimitRangeDataBase.db");

	private:
		/**
		* @brief データの存在を確認する
		* @param stmt 使用するステートメント
		* @param data 学習データ
		* @return true存在 falseない
		*/
		bool Exists(sup::SQlite::SQliteStmt& stmt, const BinaryLimitLearningData& data);

		/**
		* @brief データを挿入
		* @param data 学習データ
		*/
		void Insert(sup::SQlite::SQliteStmt& stmt, const BinaryLimitLearningData& data);

		/**
		* @brief データを更新
		* @param data 学習データ
		*/
		void Update(sup::SQlite::SQliteStmt& stmt, const BinaryLimitLearningData& data);

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