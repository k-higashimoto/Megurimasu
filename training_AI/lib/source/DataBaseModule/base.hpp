/**
* @file base.hpp
* @brief �f�[�^�x�[�X�Ŏg�p���鋤�ʏ����錾�t�@�C��
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
	* @brief 1�`�[���̃G�[�W�F���g��
	*/
	constexpr size_t kOneTeamAgentNum = 2;

	/**
	* @def kAgentNum
	* @breif 1�Q�[���̃G�[�W�F���g��
	*/
	constexpr size_t kAgentNum = 4;

	/**
	* @enum AgentActionList
	* @brief �G�[�W�F���g����
	*/
	enum class AgentActionList : size_t
	{
		WAIT,					//�ҋ@
		MOVE_RIGHT,				//�E�ړ�
		MOVE_BOTTOM_RIGHT,		//�E���ړ�
		MOVE_UNDER,				//���ړ�
		MOVE_BOTTOM_LEFT,		//�����ړ�
		MOVE_LEFT,				//���ړ�
		MOVE_UPPER_LEFT,		//����ړ�	
		MOVE_UP,				//��ړ�
		MOVE_UPPER_RIGHT,		//�E��ړ�
		REMOVE_RIGHT,			//�E�^�C������
		REMOVE_BOTTOM_RIGHT,	//�E���^�C������
		REMOVE_UNDER,			//���^�C������
		REMOVE_BOTTOM_LEFT,		//�����^�C������
		REMOVE_LEFT,			//���^�C������
		REMOVE_UPPER_LEFT,		//����^�C������
		REMOVE_UP,				//��^�C������
		REMOVE_UPPER_RIGHT,		//�E��^�C������	
		ENUM_ITEM_NUM			//���ڐ��擾�p
	};

	/**
	* @class AgentWidthPosition
	* @brief �G�[�W�F���g���ʒu
	*/
	LITERAL_CLASS(AgentWidthPosition, std::uint8_t, width_position);

	/**
	* @class AgentHeightPosition
	* @brief �G�[�W�F���g�c�ʒu
	*/
	LITERAL_CLASS(AgentHeightPosition, std::uint8_t, height_position);

	/**
	* @struct AgentPosition
	* @brief �G�[�W�F���g�ʒu���
	*/
	struct AgentPosition
	{
		AgentWidthPosition width;	//!< ���ʒu
		AgentHeightPosition height; //!< �c�ʒu
	};

	/**
	* @struct AgentInfo
	* @brief �G�[�W�F���g���
	*/
	struct AgentInfo
	{
		AgentPosition	position; //!< �ʒu���
		AgentActionList action;   //!< ������
	};

//-----------------------------------------------------------------------------------------------------------------------------------------
//board type
	/**
	* @brief �Ֆʂ̍ő剡��
	*/
	constexpr size_t kBoardWidthMaxSize = 12U;

	/**
	* @brief �Ֆʂ̍ő�c��
	*/
	constexpr size_t kBoardHeightMaxSize = 12U;

	/**
	* @biref �Ֆʍő�T�C�Y
	*/
	constexpr size_t kBoardMaxSize = kBoardWidthMaxSize * kBoardHeightMaxSize;

	/**
	* @enum BoardTileStateList
	* @brief �Ֆʂ̃^�C�����
	*/
	enum class BoardTileStateList : size_t
	{
		DEFAULT,	 //!<�N�����L���Ȃ�
		TEAM_A,		 //!<A����
		TEAM_B,		 //!<B����
	};

	/**
	* @class BoardWidthSize
	* @brief �Ֆʂ̉��T�C�Y
	*/
	LITERAL_CLASS(BoardWidthSize, std::uint8_t, width_size);

	/**
	* @class BoardHeightSize
	* @brief �Ֆʂ̉��T�C�Y
	*/
	LITERAL_CLASS(BoardHeightSize, std::uint8_t, height_size);

	/**
	* @class BoardPoint
	* @brief �Ֆʓ_�����
	*/
	LITERAL_ARRAY_CLASS(BoardPoint, int, point, kBoardMaxSize);

	/**
	* @class BoardTileState
	* @brief �Ֆʂ̃^�C�����
	*/
	LITERAL_ARRAY_CLASS(BoardTileState, BoardTileStateList, tile_state, kBoardMaxSize);

	/**
	* @struct BoardSize
	* @brief �ՖʃT�C�Y
	*/
	struct BoardSize
	{
		BoardWidthSize width;	//!< ����
		BoardHeightSize height; //!< �c��
	};

//-----------------------------------------------------------------------------------------------------------------------------------------
//other type
	/**
	* @class MatchResult
	* @brief ��������
	*/
	LITERAL_CLASS(MatchResult, bool, win);
}