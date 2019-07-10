/**
* @file learning_data.hpp
* @brief 基本学習データ型処理定義ファイル
*/

#pragma once

#include"base.hpp"

namespace database
{
//-----------------------------------------------------------------------------------------------------------------------------------------
	/**
	* @struct LearningData
	* @brief 基本学習データ型
	*/
	struct LearningData
	{
		MatchResult result;				 //!< チームA試合結果
		BoardSize board_size;			 //!< 盤面サイズ
		BoardTileState board_state;		 //!< タイル状態
		BoardPoint board_point;			 //!< 盤面の点数
		AgentInfo team_a_agents[2];		 //!< チームAエージェント
		AgentInfo team_b_agents[2];		 //!< チームBエージェント
	};

//-----------------------------------------------------------------------------------------------------------------------------------------
	/**
	* @class LearningDataConverter
	* @brief LearningDataを生成する
	*/
	class LearningDataConverter final
	{
	private:
		LearningData product; //!< 変換後データ

	public:
		/**
		* @brief 初期データをセット
		* @param init 初期データ
		* @return true 成功 false失敗
		*/
		bool SetInitData(const InitData& init)noexcept;

		/**
		* @brief 終了データをセット
		* @param term 終了データ
		* @return true 成功 false失敗
		*/
		bool SetTermData(const TermData& term)noexcept;

		/**
		* @brief ターンデータをセット
		* @param turn ターンデータ
		* @return true 成功 false失敗
		*/
		bool SetTurnData(const TurnData& turn)noexcept;

		/**
		* @brief 変換データを受け取る
		*/
		void Convert(LearningData* product)noexcept;
	};
}