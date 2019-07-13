/**
* @file learning.hpp
* @brief 学習処理実装ファイル
*/

#include<sup/boost_extend/boost_python.hpp>
#include"database_learning.hpp"
#include"learning_data.hpp"
#include"recorder/recorder/unprocessed_recorder.hpp"
#include"recorder/recorder/binary_all_range_recorder.hpp"
#include"recorder/recorder/binary_limit_range_recorder.hpp"

namespace database
{
	/**
	* @brief 初期データをセットする
	*/
	void DataBaseLearning::SetInit(const boost::python::dict& dict)noexcept
	{
		try
		{
			this->init_data.clear();
			auto temp = sup::ConvertDictToMap<sup::String, boost::python::list>(dict);
			for(const auto &it : temp)
			{
				this->init_data[it.first] = sup::ConvertListToVector<int>(it.second);
			}
		}
		catch(...)
		{
		}
	}

	/**
	* @brief 初期データをセットする
	*/
	void DataBaseLearning::SetTerm(const boost::python::dict& dict)noexcept
	{
		try
		{
			this->term_data = sup::ConvertDictToMap<TermData::key_type, TermData::value_type::second_type>(dict);
		}
		catch (...)
		{
		}
	}

	/**
	* @brief ターンデータを蓄える
	* @param turn ターンデータ
	*/
	void DataBaseLearning::PushTurn(const boost::python::dict& dict)noexcept
	{
		try
		{
			TurnData ans;
			auto temp = sup::ConvertDictToMap<sup::String, boost::python::list>(dict);
			for(const auto& it : temp)
			{
				ans[it.first] = sup::ConvertListToVector<int>(it.second);
			}

			this->turn_data.push_back(ans);
		}
		catch (...)
		{
		}
	}

	/**
	* @brief ターンデータを取り出す
	*/
	void DataBaseLearning::PopTurn()noexcept
	{
		try
		{
			this->turn_data.pop_back();
		}
		catch(...)
		{
		}
	}

	/**
	* @brief ターンデータを破棄する
	*/
	void DataBaseLearning::ClearTurn()noexcept
	{
		try
		{
			this->turn_data.clear();
		}
		catch(...)
		{
		}
	}

	/**
	* @brief 学習データを保存する
	* @return trueで成功 false失敗
	*/
	bool DataBaseLearning::Save()noexcept
	{
		try
		{
			//学習データへ変換
			{
				LearningDataConverter converter;
				converter.SetInitData(this->init_data);
				converter.SetTermData(this->term_data);
				for(const auto& it : this->turn_data)
				{
					LearningData data;
					converter.SetTurnData(it);
					converter.Convert(&data);
					Recorder::PushBack(data);
				}
			}

			//学習データを記録
			{
				auto record = [](auto p)
				{
					std::unique_ptr<Recorder> recorder(p);
					if(recorder)
					{
						recorder->Record();
					}
				};

				record(new UnprocessedRecorder);
				record(new BinaryAllRangeRecorder);
				record(new BinaryLimitRangeRecorder);
			}

			//学習データ削除
			Recorder::Clear();

			return true;
		}
		catch(...)
		{
			return false;
		}
	}
}