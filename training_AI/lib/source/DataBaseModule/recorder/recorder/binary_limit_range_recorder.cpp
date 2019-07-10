/**
* @file binary_limit_range_recorder.hpp
* @brief BinaryLimitRangeRecorder実装ファイル
*/

#pragma once

#include<sup/boost_extend/boost_format.hpp>
#include<sup/cpp/string.hpp>
#include<sup/cpp/binary.hpp>
#include<sup/cpp/algorithm.hpp>
#include"binary_limit_range_recorder.hpp"

namespace database
{
namespace
{
	/**
	* @brief 基本学習型をバイナリに変換
	* @param data 変換元
	* @param receive 受け取り用
	*/
	static void Convert(const LearningData& data, std::vector<BinaryLimitLearningData>* receive)
	{
		receive->clear();
		auto SetData = [&](const AgentInfo& agent, const AgentInfo& friend_agent, const AgentInfo enemy_agents[2], bool result)
		{
			BinaryLimitLearningData push_data;
			bool valid = true;
			size_t bit_pos = 0;

			//result
			push_data.result = result;

			//action
			push_data.action = static_cast<uint8_t>(agent.action);

			//agent_pos
			push_data.friend_agent = sup::MakeValue<std::uint8_t>(friend_agent.position.width(), friend_agent.position.height());
			push_data.enemy_agent1 = sup::MakeValue<std::uint8_t>(enemy_agents[0].position.width(), enemy_agents[0].position.height());
			push_data.enemy_agent2 = sup::MakeValue<std::uint8_t>(enemy_agents[1].position.width(), enemy_agents[1].position.height());
			if (push_data.enemy_agent1 < push_data.enemy_agent2)
			{
				std::swap(push_data.enemy_agent1, push_data.enemy_agent2);
			}

			for(long long i = -static_cast<long long>(kSourceAmplitudeSize); i < (kSourceAmplitudeSize + 1); ++i)
			for(long long j = -static_cast<long long>(kSourceAmplitudeSize); j < (kSourceAmplitudeSize + 1); ++j)
			{
				//valid
				int height = static_cast<int>(agent.position.height() + i);
				int width = static_cast<int>(agent.position.width() + j);
				long long pos = height * kSourceSideSize + width;
				valid = (0 <= height) && (0 <= width);

				//invalid_area
				push_data.invalid_area = sup::SetBit<true>(push_data.invalid_area, bit_pos, valid);

				if(valid)
				{
					//board_state
					switch (data.board_state[pos])
					{
					default:
					case BoardTileStateList::DEFAULT:
						push_data.board_state = sup::SetBit<true>(push_data.board_state, bit_pos * 2, false);
						push_data.board_state = sup::SetBit<true>(push_data.board_state, bit_pos * 2 + 1, false);
						break;

					case BoardTileStateList::TEAM_A:
						push_data.board_state = sup::SetBit<true>(push_data.board_state, bit_pos * 2, false);
						push_data.board_state = sup::SetBit<true>(push_data.board_state, bit_pos * 2 + 1, true);
						break;

					case BoardTileStateList::TEAM_B:
						push_data.board_state = sup::SetBit<true>(push_data.board_state, bit_pos * 2, true);
						push_data.board_state = sup::SetBit<true>(push_data.board_state, bit_pos * 2 + 1, true);
						break;
					}
					
					//board_sign
					push_data.board_sign = sup::SetBit<true>(push_data.board_sign, bit_pos, 0 <= data.board_point[pos]);
				}

				++bit_pos;
			}

			receive->push_back(push_data);
		};

		SetData(data.team_a_agents[0], data.team_a_agents[1], data.team_b_agents, data.result());
		SetData(data.team_a_agents[1], data.team_a_agents[0], data.team_b_agents, data.result());
		SetData(data.team_b_agents[0], data.team_b_agents[1], data.team_a_agents, !data.result());
		SetData(data.team_b_agents[1], data.team_b_agents[0], data.team_a_agents, !data.result());
	}
}
	/**
	* @brief データの存在を確認する
	* @param stmt 使用するステートメント
	* @param data 学習データ
	* @return true存在 falseない
	*/
	bool BinaryLimitRangeRecorder::Exists(sup::SQlite::SQliteStmt& stmt, const BinaryLimitLearningData& data)
	{
		auto ans = stmt
			<< sup::BindBlob(&data.invalid_area, sizeof data.invalid_area)
			<< sup::BindBlob(&data.my, sizeof data.my)
			<< sup::BindBlob(&data.friend_agent, sizeof data.friend_agent)
			<< sup::BindBlob(&data.enemy_agent1, sizeof data.enemy_agent1)
			<< sup::BindBlob(&data.enemy_agent2, sizeof data.enemy_agent2)
			<< sup::BindBlob(&data.board_state, sizeof data.board_state)
			<< sup::BindBlob(&data.board_sign, sizeof data.board_sign)
			<< sup::ColumnRun();
		stmt.Reset();
		return ans;
	}

	/**
	* @brief データを挿入
	* @param stmt 使用するステートメント
	* @param data 学習データ
	*/
	void BinaryLimitRangeRecorder::Insert(sup::SQlite::SQliteStmt& stmt, const BinaryLimitLearningData& data)
	{
		stmt
			<< sup::BindBlob(&data.invalid_area, sizeof data.invalid_area)
			<< sup::BindBlob(&data.my, sizeof data.my)
			<< sup::BindBlob(&data.friend_agent, sizeof data.friend_agent)
			<< sup::BindBlob(&data.enemy_agent1, sizeof data.enemy_agent1)
			<< sup::BindBlob(&data.enemy_agent2, sizeof data.enemy_agent2)
			<< sup::BindBlob(&data.board_state, sizeof data.board_state)
			<< sup::BindBlob(&data.board_sign, sizeof data.board_sign);

		for (size_t i = 0; i < sup::enum_size<AgentActionList>; ++i)
		{
			unsigned long long bind_value = (i == data.action ? 1 : 0);
			stmt << sup::BindBlob(&bind_value, sizeof bind_value);
		}

		stmt << sup::Run(true);
	}

	/**
	* @brief データを更新
	* @param stmt 使用するステートメント
	* @param data 学習データ
	*/
	void BinaryLimitRangeRecorder::Update(sup::SQlite::SQliteStmt& stmt, const BinaryLimitLearningData& data)
	{
		for (size_t i = 0; i < sup::enum_size<AgentActionList>; ++i)
		{
			unsigned long long bind_value = (i == data.action ? 1 : 0);
			stmt << sup::BindBlob(&bind_value, sizeof bind_value);
		}

		stmt
			<< sup::BindBlob(&data.invalid_area, sizeof data.invalid_area)
			<< sup::BindBlob(&data.my, sizeof data.my)
			<< sup::BindBlob(&data.friend_agent, sizeof data.friend_agent)
			<< sup::BindBlob(&data.enemy_agent1, sizeof data.enemy_agent1)
			<< sup::BindBlob(&data.enemy_agent2, sizeof data.enemy_agent2)
			<< sup::BindBlob(&data.board_state, sizeof data.board_state)
			<< sup::BindBlob(&data.board_sign, sizeof data.board_sign);

		stmt << sup::Run(true);
	}

	/**
	* @brief テーブル名作製
	* @return テーブル名
	*/
	sup::String BinaryLimitRangeRecorder::GetTableName()
	{
		return TEXT("DataTable");
	}

	/**
	* @brief テーブルがなければ作成する
	* @param table_name テーブル名
	* @return true正常に動作　false異常終了
	*/
	bool BinaryLimitRangeRecorder::CreateTable(const sup::String& table_name)
	{
		try
		{
			sup::SQlite sqlite(this->database_name);
			sup::SQlite::SQliteStmt stmt(&sqlite);

			stmt <<
				(sup::Format(
					TEXT(
						"CREATE TABLE IF NOT EXISTS %1%(\
						INVALID_AREA BLOB, MY_POSITION BLOB, FRINED_POSITION BLOB, ENEMY_A_POSITION BLOB, ENEMY_B_POSITION BLOB, TILE_STATE BLOB, MASS_SIGN BLOB, \
						WAIT BLOB, MOVE_RIGHT BLOB, MOVE_BOTTOM_RIGHT BLOB, MOVE_UNDER BLOB, MOVE_BOTTOM_LEFT BLOB, MOVE_LEFT BLOB, MOVE_UPPER_LEFT BLOB, MOVE_UP BLOB, MOVE_UPPER_RIGHT BLOB, REMOVE_RIGHT BLOB, REMOVE_BOTTOM_RIGHT BLOB, REMOVE_UNDER BLOB, REMOVE_BOTTOM_LEFT BLOB, REMOVE_LEFT BLOB, REMOVE_UPPER_LEFT BLOB, REMOVE_UP BLOB, REMOVE_UPPER_RIGHT BLOB, \
						PRIMARY KEY(MY_POSITION, FRINED_POSITION, ENEMY_A_POSITION, ENEMY_B_POSITION, TILE_STATE, MASS_SIGN))"
					)
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
	bool BinaryLimitRangeRecorder::Update(const sup::String& table_name)
	{
		try
		{
			sup::SQlite sqlite(this->database_name);
			sup::SQlite::SQliteStmt stmt(&sqlite);
			sup::SQlite::SQliteStmt exists_stmt(&sqlite);
			sup::SQlite::SQliteStmt insert_stmt(&sqlite);
			sup::SQlite::SQliteStmt update_stmt(&sqlite);

			exists_stmt << (sup::Format(TEXT(
				"SELECT * FROM %1% WHERE "
				"INVALID_AREA=? AND MY_POSITION=? AND FRINED_POSITION=? AND ENEMY_A_POSITION=? AND ENEMY_B_POSITION=? AND TILE_STATE=? AND MASS_SIGN=?"
			)) % table_name).str().c_str();

			insert_stmt << (sup::Format(TEXT(
				"INSERT INTO %1%("
					"INVALID_AREA, MY_POSITION, FRINED_POSITION, ENEMY_A_POSITION, ENEMY_B_POSITION, TILE_STATE, MASS_SIGN, "
					"WAIT, MOVE_RIGHT, MOVE_BOTTOM_RIGHT, MOVE_UNDER, MOVE_BOTTOM_LEFT, MOVE_LEFT, MOVE_UPPER_LEFT, MOVE_UP, MOVE_UPPER_RIGHT, REMOVE_RIGHT, REMOVE_BOTTOM_RIGHT, REMOVE_UNDER, REMOVE_BOTTOM_LEFT, REMOVE_LEFT, REMOVE_UPPER_LEFT, REMOVE_UP, REMOVE_UPPER_RIGHT"
				")"
				"VALUES("
					"?, ?, ?, ?, ?, ?, ?, "
					"?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?"
				")"
			)) % table_name).str().c_str();

			update_stmt << (sup::Format(TEXT(
				"UPDATE %1% SET "
				"WAIT = WAIT + ?, MOVE_RIGHT = MOVE_RIGHT + ?, MOVE_BOTTOM_RIGHT = MOVE_BOTTOM_RIGHT + ?, MOVE_UNDER = MOVE_UNDER + ?, MOVE_BOTTOM_LEFT = MOVE_BOTTOM_LEFT + ?, MOVE_LEFT = MOVE_LEFT + ?, MOVE_UPPER_LEFT = + ?, MOVE_UP = MOVE_UP + ?, MOVE_UPPER_RIGHT = MOVE_UPPER_RIGHT + ?, REMOVE_RIGHT = REMOVE_RIGHT + ?, REMOVE_BOTTOM_RIGHT = REMOVE_BOTTOM_RIGHT + ?, REMOVE_UNDER = REMOVE_UNDER + ?, REMOVE_BOTTOM_LEFT = REMOVE_BOTTOM_LEFT + ?, REMOVE_LEFT = REMOVE_LEFT + ?, REMOVE_UPPER_LEFT = REMOVE_UPPER_LEFT + ?, REMOVE_UP = REMOVE_UP + ?, REMOVE_UPPER_RIGHT = REMOVE_UPPER_RIGHT + ? "
				"WHERE "
				"INVALID_AREA = ? and MY_POSITION = ? and FRINED_POSITION = ? and ENEMY_A_POSITION = ? and ENEMY_B_POSITION = ? and TILE_STATE = ? and MASS_SIGN = ?"
			)) % table_name).str().c_str();

			stmt << TEXT("BEGIN") << sup::Run();

			for (const auto& it : this->learning_data)
			{
				std::vector<BinaryLimitLearningData> data_list;
				Convert(it, &data_list);
				for(const auto& data: data_list)
				{
					if (!this->Exists(exists_stmt, data))
					{
						this->Insert(insert_stmt, data);
					}
					else
					{
						this->Update(update_stmt, data);
					}
				}
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