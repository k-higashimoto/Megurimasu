/**
* @file binary_all_range_recorder.hpp
* @brief BinaryAllRangeRecorder��`�t�@�C��
*/

#pragma once

#include"../recorder.hpp"

namespace database
{
	/**
	* @struct BinaryLearningData
	* @brief �w�K�f�[�^
	*/
	struct BinaryLearningData
	{
		bool result;					//!< ��������
		std::uint64_t board_state[5];	//!< �^�C�����
		std::uint64_t board_sign[3];	//!< �Ֆʂ̕���
		std::uint8_t action;			//!< ��σG�[�W�F���g�̓���
		std::uint8_t my;				//!< ��σG�[�W�F���g�̈ʒu
		std::uint8_t friend_agent;		//!< �����G�[�W�F���g�̈ʒu
		std::uint8_t enemy_agent1;		//!< �G�G�[�W�F���g�̈ʒu1
		std::uint8_t enemy_agent2;		//!< �G�G�[�W�F���g�̈ʒu2
	};

	/**
	* @class BinaryAllRangeRecorder
	* @brief �f�[�^�Ƀo�C�i���ϊ���K�p���郌�R�[�_�[
	*/
	class BinaryAllRangeRecorder final :
		public Recorder
	{
	public:
		static constexpr const sup::Char* const database_name = TEXT("BinaryAllRangeDataBase.db");

	private:
		/**
		* @brief �f�[�^�̑��݂��m�F����
		* @param stmt �g�p����X�e�[�g�����g
		* @param data �w�K�f�[�^
		* @return true���� false�Ȃ�
		*/
		bool Exists(sup::SQlite::SQliteStmt& stmt, const BinaryLearningData& data);

		/**
		* @brief �f�[�^��}��
		* @param data �w�K�f�[�^
		*/
		void Insert(sup::SQlite::SQliteStmt& stmt, const BinaryLearningData& data);

		/**
		* @brief �f�[�^���X�V
		* @param data �w�K�f�[�^
		*/
		void Update(sup::SQlite::SQliteStmt& stmt, const BinaryLearningData& data);

	protected:
		/**
		* @brief �e�[�u�����쐻
		* @return �e�[�u����
		*/
		virtual sup::String GetTableName()override;

		/**
		* @brief �e�[�u�����Ȃ���΍쐬����
		* @param table_name �e�[�u����
		* @return true����ɓ���@false�ُ�I��
		*/
		virtual bool CreateTable(const sup::String& table_name)override;

		/**
		* @brief �f�[�^�x�[�X���X�V����
		* @param table_name �e�[�u����
		* @return true�����@false���s
		*/
		virtual bool Update(const sup::String& table_name)override;
	};
}