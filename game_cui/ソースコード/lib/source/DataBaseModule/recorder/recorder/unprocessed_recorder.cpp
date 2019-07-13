/**
* @file unprocessed_recorder.cpp
* @biref UnprocessedRecorder実装ファイル
*/

#include<sup/boost_extend/boost_format.hpp>
#include"unprocessed_recorder.hpp"

namespace database
{
	/**
	* @brief テーブル名作製
	* @return テーブル名
	*/
	sup::String UnprocessedRecorder::GetTableName()
	{
		std::time_t long_time = std::time(nullptr);
		std::tm now;
		localtime_s(&now, &long_time);
		auto ans = sup::Format(TEXT("T%04d%02d%02d%02d%02d%02d"))
			% (now.tm_year + 1900)
			% (now.tm_mon + 1)
			% now.tm_mday
			% now.tm_hour
			% now.tm_min
			% now.tm_sec;

		return ans.str();
	}

	/**
	* @brief テーブルがなければ作成する
	* @param table_name テーブル名
	* @return true正常に動作　false異常終了
	*/
	bool UnprocessedRecorder::CreateTable(const sup::String& table_name)
	{
		try
		{
			sup::SQlite sqlite(this->database_name);
			sup::SQlite::SQliteStmt stmt(&sqlite);

			stmt <<
				(sup::Format(
					TEXT("CREATE TABLE IF NOT EXISTS %1%(UnprocessedData BLOB)")
				) % table_name).str().c_str()
			<< sup::Run();

			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	/**
	* @brief データベースを更新する
	* @param table_name テーブル名
	* @return true成功　false失敗
	*/
	bool UnprocessedRecorder::Update(const sup::String& table_name)
	{
		try
		{
			sup::SQlite sqlite(this->database_name);
			sup::SQlite::SQliteStmt stmt(&sqlite);

			stmt << TEXT("BEGIN") << sup::Run();

			stmt << (sup::Format(TEXT("INSERT INTO %1%(UnprocessedData) VALUES(?)")) % table_name).str().c_str();
			for (const auto& it : this->learning_data)
			{
				stmt
				<< sup::BindBlob(&it, sizeof(typename decltype(this->learning_data)::value_type))
				<< sup::Run(true);
			}

			stmt << TEXT("COMMIT") << sup::Run();

			return true;
		}
		catch (...)
		{
			return false;
		}
	}
}