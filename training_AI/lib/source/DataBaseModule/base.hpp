/**
* @file base.hpp
* @brief データベースで使用する共通処理宣言ファイル
*/

#pragma once
#include<map>
#include<vector>
#include<list>
#include<cstdint>
#include<sup/cpp/string.hpp>
#include<sup/cpp/literal_class.hpp>
#include<sup/cpp/enum_extend.hpp>

namespace database
{
//-----------------------------------------------------------------------------------------------------------------------------------------
//python type
	using InitData		= std::map<sup::String, std::vector<int>>;
	using TurnData		= std::map<sup::String, std::vector<int>>;
	using TermData		= std::map<sup::String, sup::String>;
	using SearchInfo	= std::map<sup::String, std::vector<int>>;
	using Recode		= std::map<sup::String, std::vector<int>>;

//-----------------------------------------------------------------------------------------------------------------------------------------
//agent type
	/**
	* @def kOneTeamAgentNum
	* @brief 1チームのエージェント数
	*/
	constexpr size_t kOneTeamAgentNum = 2;

	/**
	* @def kAgentNum
	* @breif 1ゲームのエージェント数
	*/
	constexpr size_t kAgentNum = 4;

	/**
	* @enum AgentActionList
	* @brief エージェント動作
	*/
	enum class AgentActionList : size_t
	{
		WAIT,					//待機
		MOVE_RIGHT,				//右移動
		MOVE_BOTTOM_RIGHT,		//右下移動
		MOVE_UNDER,				//下移動
		MOVE_BOTTOM_LEFT,		//左下移動
		MOVE_LEFT,				//左移動
		MOVE_UPPER_LEFT,		//左上移動	
		MOVE_UP,				//上移動
		MOVE_UPPER_RIGHT,		//右上移動
		REMOVE_RIGHT,			//右タイル除去
		REMOVE_BOTTOM_RIGHT,	//右下タイル除去
		REMOVE_UNDER,			//下タイル除去
		REMOVE_BOTTOM_LEFT,		//左下タイル除去
		REMOVE_LEFT,			//左タイル除去
		REMOVE_UPPER_LEFT,		//左上タイル除去
		REMOVE_UP,				//上タイル除去
		REMOVE_UPPER_RIGHT,		//右上タイル除去	
		ENUM_ITEM_NUM			//項目数取得用
	};

	/**
	* @class AgentWidthPosition
	* @brief エージェント横位置
	*/
	LITERAL_CLASS(AgentWidthPosition, std::uint8_t, width_position);

	/**
	* @class AgentHeightPosition
	* @brief エージェント縦位置
	*/
	LITERAL_CLASS(AgentHeightPosition, std::uint8_t, height_position);

	/**
	* @struct AgentPosition
	* @brief エージェント位置情報
	*/
	struct AgentPosition
	{
		AgentWidthPosition width;	//!< 横位置
		AgentHeightPosition height; //!< 縦位置
	};

	/**
	* @struct AgentInfo
	* @brief エージェント情報
	*/
	struct AgentInfo
	{
		AgentPosition	position; //!< 位置情報
		AgentActionList action;   //!< 動作情報
	};

//-----------------------------------------------------------------------------------------------------------------------------------------
//board type
	/**
	* @brief 盤面の最大横幅
	*/
	constexpr size_t kBoardWidthMaxSize = 12U;

	/**
	* @brief 盤面の最大縦幅
	*/
	constexpr size_t kBoardHeightMaxSize = 12U;

	/**
	* @biref 盤面最大サイズ
	*/
	constexpr size_t kBoardMaxSize = kBoardWidthMaxSize * kBoardHeightMaxSize;

	/**
	* @enum BoardTileStateList
	* @brief 盤面のタイル状態
	*/
	enum class BoardTileStateList : size_t
	{
		DEFAULT,	 //!<誰も所有しない
		TEAM_A,		 //!<A所持
		TEAM_B,		 //!<B所持
	};

	/**
	* @class BoardWidthSize
	* @brief 盤面の横サイズ
	*/
	LITERAL_CLASS(BoardWidthSize, std::uint8_t, width_size);

	/**
	* @class BoardHeightSize
	* @brief 盤面の横サイズ
	*/
	LITERAL_CLASS(BoardHeightSize, std::uint8_t, height_size);

	/**
	* @class BoardPoint
	* @brief 盤面点数情報
	*/
	LITERAL_ARRAY_CLASS(BoardPoint, int, point, kBoardMaxSize);

	/**
	* @class BoardTileState
	* @brief 盤面のタイル状態
	*/
	LITERAL_ARRAY_CLASS(BoardTileState, BoardTileStateList, tile_state, kBoardMaxSize);

	/**
	* @struct BoardSize
	* @brief 盤面サイズ
	*/
	struct BoardSize
	{
		BoardWidthSize width;	//!< 横幅
		BoardHeightSize height; //!< 縦幅
	};

//-----------------------------------------------------------------------------------------------------------------------------------------
//other type
	/**
	* @class MatchResult
	* @brief 試合結果
	*/
	LITERAL_CLASS(MatchResult, bool, win);
}