/**
* @file learning_data.cpp
* @brief learning_data.hpp�����t�@�C��
*/

#include<sup/cpp/binary.hpp>
#include"learning_data.hpp"

namespace database
{
	/**
	* @brief �����f�[�^���Z�b�g
	* @param init �����f�[�^
	* @return true ���� false���s
	*/
	bool LearningDataConverter::SetInitData(const InitData& init)noexcept
	{
		try
		{
			{
				auto board_size = init.find(TEXT("Size"))->second;
				this->product.board_size.width = BoardWidthSize(board_size[0]);
				this->product.board_size.height = BoardHeightSize(board_size[1]);
			}
			{
				auto board_point = init.find(TEXT("Board"))->second;
				for (size_t i = 0; i < board_point.size() && i < kBoardMaxSize; ++i)
				{
					this->product.board_point[i] = board_point[i];
				}
			}
			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	/**
	* @brief �I���f�[�^���Z�b�g
	* @param term �I���f�[�^
	* @return true ���� false���s
	*/
	bool LearningDataConverter::SetTermData(const TermData& term)noexcept
	{
		try
		{
			auto result = term.find(TEXT("Ateam"))->second;
			this->product.result = MatchResult(result == TEXT("win"));
			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	/**
	* @brief �^�[���f�[�^���Z�b�g
	* @param turn �^�[���f�[�^
	* @return true ���� false���s
	*/
	bool LearningDataConverter::SetTurnData(const TurnData& turn)noexcept
	{
		try
		{
			{
				auto MakeAgentInfo = [&](const sup::String& key)
				{
					AgentInfo ans{};
					auto agent_info = turn.find(key)->second;
					ans.position.width = AgentWidthPosition(agent_info[0]);
					ans.position.height = AgentHeightPosition(agent_info[1]);
					ans.action = static_cast<AgentActionList>(
						agent_info[2] != 9 ? agent_info[2] : agent_info[2] + agent_info[3] - 1
						);
					return ans;
				};

				this->product.team_a_agents[0] = MakeAgentInfo(TEXT("AteamAgentA"));
				this->product.team_a_agents[1] = MakeAgentInfo(TEXT("AteamAgentB"));
				this->product.team_b_agents[0] = MakeAgentInfo(TEXT("BteamAgentA"));
				this->product.team_b_agents[1] = MakeAgentInfo(TEXT("BteamAgentB"));
			}
			{
				auto tile_state = turn.find(TEXT("Board"))->second;
				for (size_t i = 0; i < tile_state.size() && i < kBoardMaxSize; ++i)
				{
					this->product.board_state[i] = static_cast<BoardTileStateList>(tile_state[i]);
				}
			}
			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	/**
	* @brief �ϊ��f�[�^���󂯎��
	*/
	void LearningDataConverter::Convert(LearningData* product)noexcept
	{
		(*product) = this->product;
	}
}