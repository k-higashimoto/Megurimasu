/**
* @file recorder.cpp
* @brief recorder実装ファイル
*/

#include"recorder.hpp"

namespace database
{
	/**
	* @brief 学習データを蓄える
	* @param data 学習データ
	*/
	void Recorder::PushBack(const LearningData& data)
	{
		Recorder::learning_data.push_back(data);
	}

	/**
	* @brief 後ろの学習データを削除
	*/
	void Recorder::PopBack()
	{
		Recorder::learning_data.pop_back();
	}

	/**
	* @brief 学習データを削除
	*/
	void Recorder::Clear()
	{
		Recorder::learning_data.clear();
	}

	/**
	* @brief 学習データを記録する
	* @return true成功 false失敗
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