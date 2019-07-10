/**
* @file recorder.hpp
* @brief recorder��`�t�@�C��
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
	* @brief ���R�[�_�[�̊��N���X
	*/
	class Recorder
	{
	protected:
		static inline std::vector<LearningData> learning_data; //!< �w�K�f�[�^

	protected:
		/**
		* @brief �e�[�u�������擾����
		* @return �e�[�u����
		*/
		virtual sup::String GetTableName() = 0;

		/**
		* @brief �e�[�u�����Ȃ���΍쐬����
		* @param table_name �e�[�u����
		* @return true����ɓ���@false�ُ�I��
		*/
		virtual bool CreateTable(const sup::String& table_name) = 0;

		/**
		* @brief �f�[�^�x�[�X���X�V����
		* @param table_name �e�[�u����
		* @return true�����@false���s
		*/
		virtual bool Update(const sup::String& table_name) = 0;

	public:
		/**
		* @brief �w�K�f�[�^��~����
		* @param data �w�K�f�[�^
		*/
		static void PushBack(const LearningData& data);

		/**
		* @brief ���̊w�K�f�[�^���폜
		*/
		static void PopBack();

		/**
		* @brief �w�K�f�[�^���폜
		*/
		static void Clear();

		/**
		* @brief �w�K�f�[�^���L�^����
		* @return true���� false���s
		*/
		virtual bool Record()final;
	};
}