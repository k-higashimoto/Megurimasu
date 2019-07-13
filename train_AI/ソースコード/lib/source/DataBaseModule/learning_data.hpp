/**
* @file learning_data.hpp
* @brief ��{�w�K�f�[�^�^������`�t�@�C��
*/

#pragma once

#include"base.hpp"

namespace database
{
//-----------------------------------------------------------------------------------------------------------------------------------------
	/**
	* @struct LearningData
	* @brief ��{�w�K�f�[�^�^
	*/
	struct LearningData
	{
		MatchResult result;				 //!< �`�[��A��������
		BoardSize board_size;			 //!< �ՖʃT�C�Y
		BoardTileState board_state;		 //!< �^�C�����
		BoardPoint board_point;			 //!< �Ֆʂ̓_��
		AgentInfo team_a_agents[2];		 //!< �`�[��A�G�[�W�F���g
		AgentInfo team_b_agents[2];		 //!< �`�[��B�G�[�W�F���g
	};

//-----------------------------------------------------------------------------------------------------------------------------------------
	/**
	* @class LearningDataConverter
	* @brief LearningData�𐶐�����
	*/
	class LearningDataConverter final
	{
	private:
		LearningData product; //!< �ϊ���f�[�^

	public:
		/**
		* @brief �����f�[�^���Z�b�g
		* @param init �����f�[�^
		* @return true ���� false���s
		*/
		bool SetInitData(const InitData& init)noexcept;

		/**
		* @brief �I���f�[�^���Z�b�g
		* @param term �I���f�[�^
		* @return true ���� false���s
		*/
		bool SetTermData(const TermData& term)noexcept;

		/**
		* @brief �^�[���f�[�^���Z�b�g
		* @param turn �^�[���f�[�^
		* @return true ���� false���s
		*/
		bool SetTurnData(const TurnData& turn)noexcept;

		/**
		* @brief �ϊ��f�[�^���󂯎��
		*/
		void Convert(LearningData* product)noexcept;
	};
}