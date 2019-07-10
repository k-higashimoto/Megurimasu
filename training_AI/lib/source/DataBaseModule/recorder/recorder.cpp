/**
* @file recorder.cpp
* @brief recorder�����t�@�C��
*/

#include"recorder.hpp"

namespace database
{
	/**
	* @brief �w�K�f�[�^��~����
	* @param data �w�K�f�[�^
	*/
	void Recorder::PushBack(const LearningData& data)
	{
		Recorder::learning_data.push_back(data);
	}

	/**
	* @brief ���̊w�K�f�[�^���폜
	*/
	void Recorder::PopBack()
	{
		Recorder::learning_data.pop_back();
	}

	/**
	* @brief �w�K�f�[�^���폜
	*/
	void Recorder::Clear()
	{
		Recorder::learning_data.clear();
	}

	/**
	* @brief �w�K�f�[�^���L�^����
	* @return true���� false���s
	*/
	bool Recorder::Record()
	{
		auto table_name = this->GetTableName();

		if (!this->CreateTable(table_name))
		{
			return false;
		}

		if (!this->Update(table_name))
		{
			return false;
		}

		return true;
	}
}