/**
* @file binary_all_range_recorder.hpp
* @brief BinaryAllRangeRecorder実装ファイル
*/

#include<sup/cpp/binary.hpp>
#include<sup/boost_extend/boost_format.hpp>
#include"binary_all_range_recorder.hpp"

namespace database
{
namespace
{
	/**
	* @brief 基本学習型をバイナリに変換
	* @param data 変換元
	* @param receive 受け取り用
	*/
	static void Convert(const LearningData& data, std::vector<BinaryLearningData>* receive)
	{
		receive->clear();
		BinaryLearningData ans;

		//board_sign
		for (size_t i = 0; i < data.board_point.array_size; ++i)
		{
			sup::SetBit<true>(ans.board_sign, i, std::size(ans.board_sign), 0 <= data.board_point[i]);
		}

		//agentA-A
		ans.result = data.result();
		ans.action = static_cast<uint8_t>(data.team_a_agents[0].action);
		ans.my = sup::MakeValue<std::uint8_t>(data.team_a_agents[0].position.width(), data.team_a_agents[0].position.height());
		ans.friend_agent = sup::MakeValue<std::uint8_t>(data.team_a_agents[1].position.width(), data.team_a_agents[1].position.height());
		ans.enemy_agent1 = sup::MakeValue<std::uint8_t>(data.team_b_agents[0].position.width(), data.team_b_agents[0].position.height());
		ans.enemy_agent2 = sup::MakeValue<std::uint8_t>(data.team_b_agents[1].position.width(), data.team_b_agents[1].position.height());
		if (ans.enemy_agent2 < ans.enemy_agent1)
		{
			std::swap(ans.enemy_agent1, ans.enemy_agent2);
		}
		for (size_t i = 0; i < data.board_state.array_size * 2;)
		{
			switch (data.board_state[i / 2])
			{
			default:
			case BoardTileStateList::DEFAULT:
				sup::SetBit<true>(ans.board_state, std::size(ans.board_state), i++, false);
				sup::SetBit<true>(ans.board_state, std::size(ans.board_state), i++, false);
				break;

			case BoardTileStateList::TEAM_A:
				sup::SetBit<true>(ans.board_state, std::size(ans.board_state), i++, false);
				sup::SetBit<true>(ans.board_state, std::size(ans.board_state), i++, true);
				break;

			case BoardTileStateList::TEAM_B:
				sup::SetBit<true>(ans.board_state, std::size(ans.board_state), i++, true);
				sup::SetBit<true>(ans.board_state, std::size(ans.board_state), i++, true);
				break;
			}
		}
		receive->push_back(ans);

		//agentA-B
		ans.action = static_cast<uint8_t>(data.team_a_agents[1].action);
		std::swap(ans.my, ans.friend_agent);
		receive->push_back(ans);

		//agentB-A
		ans.result = (!data.result());
		ans.action = static_cast<uint8_t>(data.team_b_agents[0].action);
		ans.my = sup::MakeValue<std::uint8_t>(data.team_b_agents[0].position.width(), data.team_b_agents[0].position.height());
		ans.friend_agent = sup::MakeValue<std::uint8_t>(data.team_b_agents[1].position.width(), data.team_b_agents[1].position.height());
		ans.enemy_agent1 = sup::MakeValue<std::uint8_t>(data.team_a_agents[0].position.width(), data.team_a_agents[0].position.height());
		ans.enemy_agent2 = sup::MakeValue<std::uint8_t>(data.team_a_agents[1].position.width(), data.team_a_agents[1].position.height());
		if (ans.enemy_agent2 < ans.enemy_agent1)
		{
			std::swap(ans.enemy_agent1, ans.enemy_agent2);
		}
		for (size_t i = 0; i < data.board_state.array_size * 2;)
		{
			switch (data.board_state[i / 2])
			{
			default:
			case BoardTileStateList::DEFAULT:
				sup::SetBit<true>(ans.board_state, std::size(ans.board_state), i++, false);
				sup::SetBit<true>(ans.board_state, std::size(ans.board_state), i++, false);
				break;

			case BoardTileStateList::TEAM_A:
				sup::SetBit<true>(ans.board_state, std::size(ans.board_state), i++, true);
				sup::SetBit<true>(ans.board_state, std::size(ans.board_state), i++, true);
				break;

			case BoardTileStateList::TEAM_B:
				sup::SetBit<true>(ans.board_state, std::size(ans.board_state), i++, false);
				sup::SetBit<true>(ans.board_state, std::size(ans.board_state), i++, true);
				break;
			}
		}
		receive->push_back(ans);

		//agentB-B
		ans.action = static_cast<uint8_t>(data.team_b_agents[1].action);
		std::swap(ans.my, ans.friend_agent);
		receive->push_back(ans);
	}
}

	/**
	* @brief データの存在を確認する
	* @param stmt 使用するステートメント
	* @param data 学習データ
	* @return true存在 falseない
	*/
	bool BinaryAllRangeRecorder::Exists(sup::SQlite::SQliteStmt& stmt, const BinaryLearningData& data)
	{
		auto ans = stmt
			<< sup::BindBlob(&data.my, sizeof data.my)
			<< sup::BindBlob(&data.friend_agent, sizeof data.friend_agent)
			<< sup::BindBlob(&data.enemy_agent1, sizeof data.enemy_agent1)
			<< sup::BindBlob(&data.enemy_agent2, sizeof data.enemy_agent2)
			<< sup::BindBlob(data.board_state, sizeof data.board_state)
			<< sup::BindBlob(data.board_sign, sizeof data.board_sign)
			<< sup::ColumnRun();
		stmt.Reset();
		return ans;
	}

	/**
	* @brief データを挿入
	* @param stmt 使用するステートメント
	* @param data 学習データ
	*/
	void BinaryAllRangeRecorder::Insert(sup::SQlite::SQliteStmt& stmt, const BinaryLearningData& data)
	{
		stmt
			<< sup::BindBlob(&data.my, sizeof data.my)
			<< sup::BindBlob(&data.friend_agent, sizeof data.friend_agent)
			<< sup::BindBlob(&data.enemy_agent1, sizeof data.enemy_agent1)
			<< sup::BindBlob(&data.enemy_agent2, sizeof data.enemy_agent2)
			<< sup::BindBlob(data.board_state, sizeof data.board_state)
			<< sup::BindBlob(data.board_sign, sizeof data.board_sign);

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
	void BinaryAllRangeRecorder::Update(sup::SQlite::SQliteStmt& stmt, const BinaryLearningData& data)
	{
		for (size_t i = 0; i < sup::enum_size<AgentActionList>; ++i)
		{
			unsigned long long bind_value = (i == data.action ? 1 : 0);
			stmt << sup::BindBlob(&bind_value, sizeof bind_value);
		}

		stmt
			<< sup::BindBlob(&data.my, sizeof data.my)
			<< sup::BindBlob(&data.friend_agent, sizeof data.friend_agent)
			<< sup::BindBlob(&data.enemy_agent1, sizeof data.enemy_agent1)
			<< sup::BindBlob(&data.enemy_agent2, sizeof data.enemy_agent2)
			<< sup::BindBlob(data.board_state, sizeof data.board_state)
			<< sup::BindBlob(data.board_sign, sizeof data.board_sign);

		stmt << sup::Run(true);
	}

	/**
	* @brief テーブル名作製
	* @return テーブル名
	*/
	sup::String BinaryAllRangeRecorder::GetTableName()
	{
		auto ans = sup::Format(TEXT("T%1%%2%"))
			% this->learning_data[0].board_size.width()
			% this->learning_data[0].board_size.height();

		return ans.str();
	}

	/**
	* @brief テーブルがなければ作成する
	* @param table_name テーブル名
	* @return true正常に動作　false異常終了
	*/
	bool BinaryAllRangeRecorder::CreateTable(const sup::String& table_name)
	{
		try
		{
			sup::SQlite sqlite(this->database_name);
			sup::SQlite::SQliteStmt stmt(&sqlite);

			stmt <<
				(sup::Format(
					TEXT(
						"CREATE TABLE IF NOT EXISTS %1%(\
						MY_POSITION BLOB, FRINED_POSITION BLOB, ENEMY_A_POSITION BLOB, ENEMY_B_POSITION BLOB, TILE_STATE BLOB, MASS_SIGN BLOB, \
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
	bool BinaryAllRangeRecorder::Update(const sup::String& table_name)
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
				"MY_POSITION=? AND FRINED_POSITION=? AND ENEMY_A_POSITION=? AND ENEMY_B_POSITION=? AND TILE_STATE=? AND MASS_SIGN=?"
			)) % table_name).str().c_str();

			insert_stmt << (sup::Format(TEXT(
				"INSERT INTO %1%("
				"MY_POSITION, FRINED_POSITION, ENEMY_A_POSITION, ENEMY_B_POSITION, TILE_STATE, MASS_SIGN, "
				"WAIT, MOVE_RIGHT, MOVE_BOTTOM_RIGHT, MOVE_UNDER, MOVE_BOTTOM_LEFT, MOVE_LEFT, MOVE_UPPER_LEFT, MOVE_UP, MOVE_UPPER_RIGHT, REMOVE_RIGHT, REMOVE_BOTTOM_RIGHT, REMOVE_UNDER, REMOVE_BOTTOM_LEFT, REMOVE_LEFT, REMOVE_UPPER_LEFT, REMOVE_UP, REMOVE_UPPER_RIGHT"
				")"
				"VALUES("
				"?, ?, ?, ?, ?, ?, "
				"?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?"
				")"
			)) % table_name).str().c_str();

			update_stmt << (sup::Format(TEXT(
				"UPDATE %1% SET "
				"WAIT = WAIT + ?, MOVE_RIGHT = MOVE_RIGHT + ?, MOVE_BOTTOM_RIGHT = MOVE_BOTTOM_RIGHT + ?, MOVE_UNDER = MOVE_UNDER + ?, MOVE_BOTTOM_LEFT = MOVE_BOTTOM_LEFT + ?, MOVE_LEFT = MOVE_LEFT + ?, MOVE_UPPER_LEFT = + ?, MOVE_UP = MOVE_UP + ?, MOVE_UPPER_RIGHT = MOVE_UPPER_RIGHT + ?, REMOVE_RIGHT = REMOVE_RIGHT + ?, REMOVE_BOTTOM_RIGHT = REMOVE_BOTTOM_RIGHT + ?, REMOVE_UNDER = REMOVE_UNDER + ?, REMOVE_BOTTOM_LEFT = REMOVE_BOTTOM_LEFT + ?, REMOVE_LEFT = REMOVE_LEFT + ?, REMOVE_UPPER_LEFT = REMOVE_UPPER_LEFT + ?, REMOVE_UP = REMOVE_UP + ?, REMOVE_UPPER_RIGHT = REMOVE_UPPER_RIGHT + ? "
				"WHERE "
				"MY_POSITION = ? and FRINED_POSITION = ? and ENEMY_A_POSITION = ? and ENEMY_B_POSITION = ? and TILE_STATE = ? and MASS_SIGN = ?"
			)) % table_name).str().c_str();

			stmt << TEXT("BEGIN") << sup::Run();

			for (const auto& it : this->learning_data)
			{
				std::vector<BinaryLearningData> data_list;
				Convert(it, &data_list);
				for (const auto& data : data_list)
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