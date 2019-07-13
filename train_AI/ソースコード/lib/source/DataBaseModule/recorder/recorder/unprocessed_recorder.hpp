/**
* @file unprocessed_recorder.hpp
* @biref UnprocessedRecorder��`�t�@�C��
*/

#pragma once

#include<sup/cpp/string.hpp>
#include"../recorder.hpp"

namespace database
{
	/**
	* @class UnprocessedRecorder
	* @brief �f�[�^�����̂܂܋L�^���郌�R�[�_�[
	*/
	class UnprocessedRecorder final :
		public Recorder
	{
	public:
		static constexpr const sup::Char* const database_name = TEXT("UnprocessDataBase.db");

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