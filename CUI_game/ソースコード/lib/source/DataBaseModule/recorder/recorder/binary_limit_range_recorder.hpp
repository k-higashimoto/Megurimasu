/**
* @file binary_limit_range_recorder.hpp
* @biref BinaryLimitRangeRecorder��`�t�@�C��
*/

#pragma once

#include"../recorder.hpp"

namespace database
{
	/**
	* @def kSourceSideSize
	* @brief �f�[�^���Ƃ鐳���`�͈͂̈�ӂ̃T�C�Y
	*/
	constexpr size_t kSourceSideSize = 5;

	/**
	* @def kSourceAreaSize
	* @brief �f�[�^���Ƃ鐳���`�̖ʐσT�C�Y
	*/
	constexpr size_t kSourceAreaSize = kSourceSideSize * kSourceSideSize;

	/**
	* @def kSourceAmplitudeSize
	* @brief �G�[�W�F���g�ʒu�����_�Ƃ����Ƃ��̐U�ꕝ
	*/
	constexpr size_t kSourceAmplitudeSize = static_cast<size_t>(kSourceSideSize / 2);

	/**
	* @struct BinaryLimitLearningData
	* @brief 5X5�͈͂̃o�C�i���w�K�f�[�^
	*/
	struct BinaryLimitLearningData
	{
		bool result;					//!< ��������
		std::uint32_t invalid_area;		//!< �͈͊O���(1�ŗL�� 0�Ŗ���)
		std::uint64_t board_state;		//!< �^�C�����
		std::uint32_t board_sign;		//!< �Ֆʂ̕���
		std::uint8_t action;			//!< ��σG�[�W�F���g�̓���
		std::uint8_t my;				//!< ��σG�[�W�F���g�̈ʒu
		std::uint8_t friend_agent;		//!< �����G�[�W�F���g�̈ʒu
		std::uint8_t enemy_agent1;		//!< �G�G�[�W�F���g�̈ʒu1
		std::uint8_t enemy_agent2;		//!< �G�G�[�W�F���g�̈ʒu2
	};

	/**
	* @class BinaryLimitRangeRecorder
	* @brief �f�[�^�̈ꕔ���o�C�i�������ċL�^���郌�R�[�_�[
	*/
	class BinaryLimitRangeRecorder final :
		public Recorder
	{
	public:
		static constexpr const sup::Char* const database_name = TEXT("BinaryLimitRangeDataBase.db");

	private:
		/**
		* @brief �f�[�^�̑��݂��m�F����
		* @param stmt �g�p����X�e�[�g�����g
		* @param data �w�K�f�[�^
		* @return true���� false�Ȃ�
		*/
		bool Exists(sup::SQlite::SQliteStmt& stmt, const BinaryLimitLearningData& data);

		/**
		* @brief �f�[�^��}��
		* @param data �w�K�f�[�^
		*/
		void Insert(sup::SQlite::SQliteStmt& stmt, const BinaryLimitLearningData& data);

		/**
		* @brief �f�[�^���X�V
		* @param data �w�K�f�[�^
		*/
		void Update(sup::SQlite::SQliteStmt& stmt, const BinaryLimitLearningData& data);

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