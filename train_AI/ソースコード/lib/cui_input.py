""" ゲームの入力に関する機能をまとめたモジュール　"""
from lib.game_cpu import searchBestActionOfEachAgent, createSearchInfoForSearch, createSearch
from lib.game_parts import Agent, ActType, Playing
from lib.action_type import ActType
import random
import re
import json


class CUIInput():
    """
    ゲームのエージェントの入力を司るクラス
    """

    def __init__(self,
                 play,
                 inputTypeOfAgentA="random",
                 inputTypeOfAgentB="random",
                 inputTypeOfAgentC="random",
                 inputTypeOfAgentD="random"):

        self._play = play
        self._inputTypeOfAgentA = inputTypeOfAgentA
        self._inputTypeOfAgentB = inputTypeOfAgentB
        self._inputTypeOfAgentC = inputTypeOfAgentC
        self._inputTypeOfAgentD = inputTypeOfAgentD
        self._search = self._setSearch()

    def _setSearch(self):
        """
        エージェントの入力形式から、データベース(search)を読み込むかどうか判定する
        @return search or None
        """

        if self._inputTypeOfAgentA == "cpu":
            return createSearch(self._play)
        elif self._inputTypeOfAgentB == "cpu":
            return createSearch(self._play)
        elif self._inputTypeOfAgentC == "cpu":
            return createSearch(self._play)
        elif self._inputTypeOfAgentD == "cpu":
            return createSearch(self._play)
        else:
            return None

    def input(self) -> dict:
        """
        エージェントの動作の入力を行う
        @return agentAction エージェントA~Dのそれぞれの入力データ
        """

        agentAction = {
            "agentA": {
                "act": ActType.WAIT,
                "rmAct": ActType.WAIT,
            },
            "agentB": {
                "act": ActType.WAIT,
                "rmAct": ActType.WAIT,
            },
            "agentC": {
                "act": ActType.WAIT,
                "rmAct": ActType.WAIT,
            },
            "agentD": {
                "act": ActType.WAIT,
                "rmAct": ActType.WAIT,
            }
        }

        # エージェントAの入力を行う
        if self._inputTypeOfAgentA == "cpu":
            agentAction["agentA"]["act"], agentAction["agentA"]["rmAct"] = self._CPU(
                "agentA")

        elif self._inputTypeOfAgentA == "manual":
            agentAction["agentA"]["act"], agentAction["agentA"]["rmAct"] = self._manual(
                "agentA")

        elif self._inputTypeOfAgentA == "random":
            agentAction["agentA"]["act"], agentAction["agentA"]["rmAct"] = self._random(
                "agentA")

        # エージェントBの入力を行う
        if self._inputTypeOfAgentB == "cpu":
            agentAction["agentB"]["act"], agentAction["agentB"]["rmAct"] = self._CPU(
                "agentB")

        elif self._inputTypeOfAgentB == "manual":
            agentAction["agentB"]["act"], agentAction["agentB"]["rmAct"] = self._manual(
                "agentB")

        elif self._inputTypeOfAgentB == "random":
            agentAction["agentB"]["act"], agentAction["agentB"]["rmAct"] = self._random(
                "agentB")

        # エージェントCの入力を行う
        if self._inputTypeOfAgentC == "cpu":
            agentAction["agentC"]["act"], agentAction["agentC"]["rmAct"] = self._CPU(
                "agentC")

        elif self._inputTypeOfAgentC == "manual":
            agentAction["agentC"]["act"], agentAction["agentC"]["rmAct"] = self._manual(
                "agentC")

        elif self._inputTypeOfAgentC == "random":
            agentAction["agentC"]["act"], agentAction["agentC"]["rmAct"] = self._random(
                "agentC")

        # エージェントDの入力を行う
        if self._inputTypeOfAgentD == "cpu":
            agentAction["agentD"]["act"], agentAction["agentD"]["rmAct"] = self._CPU(
                "agentD")

        elif self._inputTypeOfAgentD == "manual":
            agentAction["agentD"]["act"], agentAction["agentD"]["rmAct"] = self._manual(
                "agentD")

        elif self._inputTypeOfAgentD == "random":
            agentAction["agentD"]["act"], agentAction["agentD"]["rmAct"] = self._random(
                "agentD")

        return agentAction

    def _CPU(self, agentName) -> dict:
        """
        指定したエージェントの動作の入力をCPUで行う
        @param agentName 指定したエージェントの名前
        @return baseAction, removeAction
        """

        # データベースから個々のエージェントの最善手を検索
        searchInformation = createSearchInfoForSearch(self._play)
        bestActionOfEachAgent = searchBestActionOfEachAgent(
            self._search, searchInformation
        )

        baseAction = ActType(bestActionOfEachAgent[agentName]["act"])
        removeAction = ActType(bestActionOfEachAgent[agentName]["rmAct"])

        return baseAction, removeAction

    def _manual(self, agentName):
        """
        指定したエージェントの動作の入力を手動で行う
        @param agentName 指定したエージェントの名前
        @return baseAction, removeAction
        """

        teamA = self._play.teamA
        teamB = self._play.teamB

        agentA = self._play.teamA[0]
        agentB = self._play.teamA[1]
        agentC = self._play.teamB[0]
        agentD = self._play.teamB[1]

        agentOfThisTurnNumber = None

        if agentName == agentA.name:
            agentOfThisTurnNumber = agentA
        elif agentName == agentB.name:
            agentOfThisTurnNumber = agentB
        elif agentName == agentC.name:
            agentOfThisTurnNumber = agentC
        elif agentName == agentD.name:
            agentOfThisTurnNumber = agentD

        baseAction = ActType.WAIT
        removeAction = ActType.WAIT

        # ユーザーに基本行動を入力させる
        print("\n0:停滞 1:右 2:右下 3:下 4:左下 5:左 6:左上 7:上 8:右上 9:タイル削除")
        while True:
            baseActionOfInput = input(f"[ {agentName} ]動作を入力 >> ")

            # 移動の場合(1~8までの数字が入力されたら)
            if re.match(r"^[0-8]$", baseActionOfInput):

                baseAction = ActType(int(baseActionOfInput))
                removeAction = ActType.WAIT

                # 入力された移動先が正しくなければ、警告を出し再入力を促す
                if not agentOfThisTurnNumber.checkAct(baseAction, teamA, teamB):
                    print("\n移動先が無効です\n")
                    continue

                # 入力が正しければ行動を確定
                break

            # タイル削除の場合(9が入力されたら)
            elif re.match(r"^9$", baseActionOfInput):

                baseAction = ActType.TILE_REMOVE

                # ユーザーに削除行動を入力させる
                removeActionOfInput = input(f"[ {agentName} ]削除マス を入力 >> ")
                removeAction = ActType(int(removeActionOfInput))

                # 入力された削除先が正しくなければ、警告を出し再入力を促す
                if not agentOfThisTurnNumber.checkRemoveTile(removeAction, teamA, teamB):
                    print("\n削除先が無効です\n")
                    continue

                # 入力が正しければ行動を確定
                break

            # 不適切な値が入力されたら警告し、再入力させる
            else:
                print("\n正しい値を入力してください\n")
                continue

        return baseAction, removeAction

    def _random(self, agentName) -> dict:
        """
        指定したエージェントの動作の入力をランダムで行う
        @param agentName 指定したエージェントの名前
        @return baseAction, removeAction
        """

        teamA = self._play.teamA
        teamB = self._play.teamB

        agentA = self._play.teamA[0]
        agentB = self._play.teamA[1]
        agentC = self._play.teamB[0]
        agentD = self._play.teamB[1]

        agentOfThisTurnNumber = None

        if agentName == agentA.name:
            agentOfThisTurnNumber = agentA
        elif agentName == agentB.name:
            agentOfThisTurnNumber = agentB
        elif agentName == agentC.name:
            agentOfThisTurnNumber = agentC
        elif agentName == agentD.name:
            agentOfThisTurnNumber = agentD

        # エージェントの行動をランダムに決める
        baseAction = ActType.WAIT
        removeAction = ActType.WAIT
        while True:
            # ランダムな基本行動の生成
            baseAction = ActType(random.randint(0, 9))

            # ランダムな削除行動の生成
            removeAction = ActType(random.randint(0, 8))

            # もし基本行動が待機なら
            if baseAction == ActType.WAIT:
                # 待機の割合を減らすため、50%の確率で再入力させる
                if random.randint(0, 1) == 1:
                    continue

            # ランダムで決められた行動が実際に行動できるかどうか判定する
            # 行動できない場合　もう一度ランダムで入力しなおす
            # 移動の場合
            if baseAction != ActType.TILE_REMOVE:
                if not agentOfThisTurnNumber.checkAct(baseAction, teamA, teamB):
                    continue

            # 削除の場合
            else:
                if not agentOfThisTurnNumber.checkRemoveTile(removeAction, teamA, teamB):
                    continue

            # ランダムで入力された行動が正しければ行動を確定
            break

        return baseAction, removeAction


def createInputTypeOfEachAgent():
    """
    個々のエージェントの入力形式を入力させる
    @return inputTypeOfEachAgent 個々のエージェントの入力形式
    """

    inputTypeOfEachAgent = {
        "agentA": None,
        "agentB": None,
        "agentC": None,
        "agentD": None
    }

    # 個々のエージェントの入力形式を入力させる
    print("\n手動:manual ランダム:random コンピューター:cpu")
    for agentName in inputTypeOfEachAgent.keys():
        while True:
            inputType = input(f"{agentName}の入力形式を入力してください: ")

            if inputType == "cpu":
                inputTypeOfEachAgent[agentName] = "cpu"
                break

            elif inputType == "manual":
                inputTypeOfEachAgent[agentName] = "manual"
                break

            elif inputType == "random":
                inputTypeOfEachAgent[agentName] = "random"
                break

            else:
                continue

    inputTypeOfEachAgent = {
        "inputTypeOfAgentA": inputTypeOfEachAgent["agentA"],
        "inputTypeOfAgentB": inputTypeOfEachAgent["agentB"],
        "inputTypeOfAgentC": inputTypeOfEachAgent["agentC"],
        "inputTypeOfAgentD": inputTypeOfEachAgent["agentD"],
    }

    return inputTypeOfEachAgent
