""" ゲームの試合設定を生成する機能をまとめたモジュール　"""
from lib.socket_communication import sendDataToClient
from lib.gameRandom import createRondomIntNumber
import random
import math
import json


def createRandomGameSet():
    """
    ランダムな試合設定を生成(MeguriMasuCoreの引数を生成)
    @return gameSetWithRandom ランダムに生成された設定データ
    """

    # ランダムな最大ターン数を生成(範囲　40~80 step 10）
    maxTurn = 80 - (10 * random.randint(0, 4))

    # スコアボードの行数(6~12)と列数(6~12)を生成
    row = random.randint(6, 12)
    column = random.randint(6, 12)

    # 行数と列数を用いてランダムなスコアボードを生成
    scoreBoard = createRandomScoreBoard(column, row)

    # エージェントAとBのランダムな初期位置を生成
    agentAPos, agentBPos = createRandomAgentPosition(column, row)
    agentAX, agentAY = agentAPos[0], agentAPos[1]
    agentBX, agentBY = agentBPos[0], agentBPos[1]

    gameSetWithRandom = {
        "maxTurn": maxTurn,
        "agentAX": agentAX,
        "agentAY": agentAY,
        "agentBX": agentBX,
        "agentBY": agentBY,
        "row": row,
        "column": column,
        "scoreBoard": scoreBoard,
    }

    return gameSetWithRandom


def recieveGameSetFromGUI() -> dict:
    """
    クライアントから試合設定を受信する(MeguriMasuCoreの引数を生成)
    @return gameSetWithClient クライアントから送られてきた設定
    """

    # クライアントとソケット通信を行い、設定データを受信
    response = sendDataToClient("")

    # 受信した設定データを解析する
    gameSetData = json.loads(response)

    # 最大ターン数の解析
    maxTurn = gameSetData["maxTurn"]

    # エージェントAのX座標とY座標を解析
    agentAX, agentAY = gameSetData["agentAPos"]

    # エージェントBのX座標とY座標を解析
    agentBX, agentBY = gameSetData["agentBPos"]

    # スコアボードを解析
    scoreBoard = gameSetData["scoreBoard"]

    # スコアボードの行数と列数を解析
    row = len(scoreBoard[0])
    column = len(scoreBoard)

    gameSetWithClient = {
        "maxTurn": maxTurn,
        "agentAX": agentAX,
        "agentAY": agentAY,
        "agentBX": agentBX,
        "agentBY": agentBY,
        "row": row,
        "column": column,
        "scoreBoard": scoreBoard
    }

    return gameSetWithClient


def createRandomScoreBoard(column: int, row: int):
    """
    行数と列数を用いてランダムなスコアボードを生成
    @param column 行数
    @param row 列数
    @return scoreBoard スコアボード
    """

    # 行数と列数を用いてランダムなスコアボードを生成
    scoreBoard = [[0 for j in range(row)]
                  for i in range(column)]

    # スコアボードの左上1/4にランダムな数をセット
    for y in range(math.ceil(column / 2)):
        for x in range(math.ceil(row / 2)):
            scoreBoard[y][x] = createRondomIntNumber(-16, 16, 90)

    # スコアボード全体に対照的な数をセット
    for y in range(math.ceil(column)):
        for x in range(math.ceil(row)):
            scoreBoard[y][-x - 1] = scoreBoard[y][x]
            scoreBoard[-y - 1][x] = scoreBoard[y][x]
            scoreBoard[-y - 1][-x - 1] = scoreBoard[y][x]

    return scoreBoard


def createRandomAgentPosition(column:int, row: int):
    """
    エージェントAとBのランダムな初期座標を生成する
    @param column スコアボードの行数
    @param row スコアボードの列数
    @return agentAPos, agentBPos エージェントAとBのランダムな初期座標
    """

    agentAPos = [0, 0]
    agentBPos = [0, 0]
    while True:
        # エージェントAのランダムな初期位置を生成
        agentAPos[0] = random.randint(0, int(row / 2))
        agentAPos[1] = random.randint(0, int(column / 2))

        # エージェントBのランダムな初期位置を生成
        agentBPos[0] = row - 1 - random.randint(0, int(row / 2))
        agentBPos[1] = column - 1 - random.randint(0, int(column / 2))

        if agentAPos[0] == agentBPos[0]:
            continue
        elif agentAPos[1] == agentBPos[1]:
            continue
        else:
            break

    return agentAPos, agentBPos


if __name__ == "__main__":
    print(createRandomGameSet())