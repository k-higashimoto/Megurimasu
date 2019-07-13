""" ゲームの入力に関する機能をまとめたモジュール　"""
from lib.actionable_action import getActionableActionForGUI
from lib.game_cpu import searchBestActionOfEachAgent, createSearchInfoForSearch, createSearch, \
    searchBestActionOfEachAgentForGUI
from lib.calculate_point import calcTilePointOfTeam, calcRegionPointOfTeam, calcAllPointOfTeam
from lib.calculate_tile import calcTeamTile
import json


class GUIOutput():
    """
    ゲームのエージェントの入力を行うクラス
    """

    def __init__(self, play):

        self._play = play
        self._search = createSearch(play)

    def createTurnStateDataForGUI(self) -> str:
        """
        クライアントに送るための現状データを生成
        @return turnStateDataWithJson ターンの現状データ
        """

        # 現在のフェーズを取得
        phase = ""
        if self._play.isFinishGame():
            phase = "finish"
        else:
            phase = "play"

        # 現在のターンを取得
        nowTurn = self._play.nowTurn

        # チームAのタイルとチームBのタイルから置かれたタイルの設置状況の配列を生成
        tileStatusOfTeamA = calcTeamTile(self._play.teamA)
        tileStatusOfTeamB = calcTeamTile(self._play.teamB)
        row = len(tileStatusOfTeamA[0])
        column = len(tileStatusOfTeamA)
        tileStatusOfAll = [[0 for x in range(row)]
                           for y in range(column)]
        for y in range(0, column):
            for x in range(0, row):
                if tileStatusOfTeamA[y][x]:
                    tileStatusOfAll[y][x] = 1

                elif tileStatusOfTeamB[y][x]:
                    tileStatusOfAll[y][x] = -1

        # チームAのポイントを取得
        tilePointOfTeamA = calcTilePointOfTeam(self._play.teamA, self._play.scoreBoard)
        regionPointOfTeamA = calcRegionPointOfTeam(self._play.teamA, self._play.scoreBoard)
        allPointOfTeamA = tilePointOfTeamA + regionPointOfTeamA

        # チームBのポイントを取得
        tilePointOfTeamB = calcTilePointOfTeam(self._play.teamB, self._play.scoreBoard)
        regionPointOfTeamB = calcRegionPointOfTeam(self._play.teamB, self._play.scoreBoard)
        allPointOfTeamB = tilePointOfTeamB + regionPointOfTeamB

        # 個々のエージェントの座標を取得
        agentAX = self._play.teamA[0].x
        agentAY = self._play.teamA[0].y
        agentBX = self._play.teamA[1].x
        agentBY = self._play.teamA[1].y
        agentCX = self._play.teamB[0].x
        agentCY = self._play.teamB[0].y
        agentDX = self._play.teamB[1].x
        agentDY = self._play.teamB[1].y

        # 個々のエージェントの基本行動を取得
        actionableActionForGUI = getActionableActionForGUI(self._play)
        actionableActionOfAgentA = actionableActionForGUI["agentA"]
        actionableActionOfAgentB = actionableActionForGUI["agentB"]
        actionableActionOfAgentC = actionableActionForGUI["agentC"]
        actionableActionOfAgentD = actionableActionForGUI["agentD"]

        # データベースから個々のエージェントの最善手を検索
        searchInformation = createSearchInfoForSearch(self._play)
        bestActionOfEachAgent = searchBestActionOfEachAgentForGUI(self._search, searchInformation)

        # 個々のエージェントの最善手を取得
        bestActionOfAgentA = bestActionOfEachAgent["agentA"]["direction"], bestActionOfEachAgent["agentA"]["do"]
        bestActionOfAgentB = bestActionOfEachAgent["agentB"]["direction"], bestActionOfEachAgent["agentB"]["do"]
        bestActionOfAgentC = bestActionOfEachAgent["agentC"]["direction"], bestActionOfEachAgent["agentC"]["do"]
        bestActionOfAgentD = bestActionOfEachAgent["agentD"]["direction"], bestActionOfEachAgent["agentD"]["do"]

        # ターンの現状データのjsonを作成
        turnStateDataWithJson = {
            "phase": phase,
            "nowTurn": nowTurn,
            "tilePlaceState": tileStatusOfAll,
            "teamA": {
                "agentA": {
                    "tileX": agentAX,
                    "tileY": agentAY,
                    "actionableBaseAction": actionableActionOfAgentA,
                    "bestAction": bestActionOfAgentA
                },
                "agentB": {
                    "tileX": agentBX,
                    "tileY": agentBY,
                    "actionableBaseAction": actionableActionOfAgentB,
                    "bestAction": bestActionOfAgentB
                },
                "tilePoint": tilePointOfTeamA,
                "regionPoint": regionPointOfTeamA,
                "allPoint": allPointOfTeamA,
            },
            "teamB": {
                "agentC": {
                    "tileX": agentCX,
                    "tileY": agentCY,
                    "actionableBaseAction": actionableActionOfAgentC,
                    "bestAction": bestActionOfAgentC
                },
                "agentD": {
                    "tileX": agentDX,
                    "tileY": agentDY,
                    "actionableBaseAction": actionableActionOfAgentD,
                    "bestAction": bestActionOfAgentD
                },
                "tilePoint": tilePointOfTeamB,
                "regionPoint": regionPointOfTeamB,
                "allPoint": allPointOfTeamB,
            }
        }
        # jsonをjson文字列に変換
        turnStateDataWithJson = json.dumps(turnStateDataWithJson)

        return turnStateDataWithJson
