from lib.actionable_action import getActionableActionForGUI
from lib.calculate_point import calcTilePointOfTeam, calcRegionPointOfTeam, calcAllPointOfTeam
from lib.calculate_tile import calcTeamTile, calcTeamRegion
import lib.mass_game_database as db
from lib.game_cpu import createSearch, createSearchInfoForSearch
import json

from lib.game_cpu import searchBestActionOfEachAgent


def createStateLogOfJSON(play) -> str:
    # 連想配列の作成

    d = {
        "field": play.scoreBoard,
        "remaining_turn": play.turnNumber,
        "teamA": {
            "member": [
                {
                    "name": play.teamA[0].name,
                    "x": play.teamA[0].x,
                    "y": play.teamA[0].y,
                    "tile": play.teamA[0].tileCopy,
                },
                {
                    "name": play.teamA[1].name,
                    "x": play.teamA[1].x,
                    "y": play.teamA[1].y,
                    "tile": play.teamA[1].tileCopy
                }
            ],
            "tile": calcTeamTile(play.teamA),
            "region": calcTeamRegion(play.teamA),
            "onlyTileScore": calcTilePointOfTeam(play.teamA, play.scoreBoard),
            "onlyRegionScore": calcRegionPointOfTeam(play.teamA, play.scoreBoard),
            "Score": calcAllPointOfTeam(play.teamA, play.scoreBoard)
        },
        "teamB": {
            "member": [
                {
                    "name": play.teamB[0].name,
                    "x": play.teamB[0].x,
                    "y": play.teamB[0].y,
                    "tile": play.teamB[0].tileCopy
                },
                {
                    "name": play.teamB[1].name,
                    "x": play.teamB[1].x,
                    "y": play.teamB[1].y,
                    "tile": play.teamB[1].tileCopy
                }
            ],
            "tile": calcTeamTile(play.teamB),
            "region": calcTeamRegion(play.teamB),
            "onlyTileScore": calcTilePointOfTeam(play.teamB, play.scoreBoard),
            "onlyRegionScore": calcRegionPointOfTeam(play.teamB, play.scoreBoard),
            "Score": calcAllPointOfTeam(play.teamB, play.scoreBoard)
        }
    }
    return json.dumps(d)


################################################################################
def createTurnStateLogOfJSON(play) -> str:
    """ (ターンの最後に実行するのが) """

    myTurn = None
    log = []
    for i in play.log[::-1]:
        if myTurn is None:
            myTurn = i["remaining_turn"]
        if i["remaining_turn"] == myTurn:
            log.append(i)

    tileA = []
    team = calcTeamTile(play.teamA)
    for y in range(len(team)):
        for x in range(len(team[y])):
            if team[y][x]:
                tileA.append({"x": x, "y": y})

    tileB = []
    team = calcTeamTile(play.teamB)
    for y in range(len(team)):
        for x in range(len(team[y])):
            if team[y][x]:
                tileB.append({"x": x, "y": y})

    turnLog = {
        "action_log": log,
        "tile_teamA": tileA,
        "tile_teamB": tileB
    }

    return json.dumps(turnLog)


##############################################################################

def createActionableDataForClient(play) -> str:
    """
    クライアントに送るための行動可能データを生成
    @param play Playingクラスのインスタンス
    @return dataOfActionable 行動可能データ
    """

    dataOfActionable = ""
    actionable = play.getActionableAction()

    for action in actionable:

        moveAction = action[0]
        removeAction = 0 if action[1] is None else action[1]

        dataOfActionable += fr"{moveAction},{removeAction}"

    return dataOfActionable




