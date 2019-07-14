""" ゲームの入力に関する機能をまとめたモジュール　"""
from lib.conversion_action import conversioActionToCUIFromGUI
from lib.socket_communication import sendDataToClient
import json


class GUIInput():
    """
    GUIのエージェントの入力を行うクラス
    """

    def __init__(self, play):
        self._play = play

    def input(self) -> dict:
        """
        エージェントの動作の入力をGUIから行う
        @return agentAction エージェントA~Dのそれぞれの入力データ
        """

        actionOfEachAgentForGUI = {
            "agentA": {
                "direction": 0,
                "do": 0,
            },
            "agentB": {
                "direction": 0,
                "do": 0,
            },
            "agentC": {
                "direction": 0,
                "do": 0,
            },
            "agentD": {
                "direction": 0,
                "do": 0,
            }
        }

        # クライアントから入力データを受信
        response = sendDataToClient("")
        inputData = json.loads(response)

        # エージェント１人１人に対して入力を行う
        for agentName in actionOfEachAgentForGUI.keys():
            # クライアントから受信したデータの解析
            action = inputData[f"actionOf{agentName.replace('a', 'A')}"]
            direction = int(action[0])
            do = int(action[1])

            actionOfEachAgentForGUI[agentName]["direction"] = direction
            actionOfEachAgentForGUI[agentName]["do"] = do

        actionOfEachAgentForCUI = conversioActionToCUIFromGUI(actionOfEachAgentForGUI)

        return actionOfEachAgentForCUI
