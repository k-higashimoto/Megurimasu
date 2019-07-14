/**
* @file learning.hpp
* @brief �w�K���������t�@�C��
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
	* @brief �����f�[�^���Z�b�g����
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
	* @brief �����f�[�^���Z�b�g����
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
	* @brief �^�[���f�[�^��~����
	* @param turn �^�[���f�[�^
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
	* @brief �^�[���f�[�^�����o��
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
	* @brief �^�[���f�[�^��j������
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
	* @brief �w�K�f�[�^��ۑ�����
	* @return true�Ő��� false���s
	*/
	bool DataBaseLearning::Save()noexcept
	{
		try
		{
			//�w�K�f�[�^�֕ϊ�
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

			//�w�K�f�[�^���L�^
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

			//�w�K�f�[�^�폜
			Recorder::Clear();

			return true;
		}
		catch(...)
		{
			return false;
		}
	}
}