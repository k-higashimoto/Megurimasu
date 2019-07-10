import lib.mass_game_database as db
from lib.calculate_tile import calcTeamTile
from lib.conversion_action import conversioActionToGUIFromCUI


def createSearch(play):
    column = len(play.scoreBoard)
    row = len(play.scoreBoard[0])

    # データベースから個々のエージェントの最善手を検索
    search = db.Search(row, column)
    return search

def createInitDataForLearn(play):
    """
    学習用のゲームの試合設定データを生成
    @param play Playingクラスのインスタンス
    @return initializeData 学習用のゲームの試合設定データ
    """

    initializeData = {"Board": [], "size": []}

    scoreBoardRow = len(play.scoreBoard[0])
    scoreBoardColunmn = len(play.scoreBoard)
    scoreBoard = [    ]

    for y in range(scoreBoardColunmn):
        for x in range(scoreBoardRow):

            scoreBoard.append(play.scoreBoard[y][x])

    initializeData["Board"] = scoreBoard
    initializeData["Size"] = [scoreBoardRow, scoreBoardColunmn]

    return initializeData

def createTurnDataForLearn(play):
    """
    学習用のターンの現状データを生成
    @param play Playingクラスのインスタンス
    @return　turnData ターンの現状データ
    """

    turn_data = {
        'AteamAgentA': [],
        'AteamAgentB': [],
        'BteamAgentA': [],
        'BteamAgentB': [],
        "Board": []
    }

    agentAX = play.teamA[0].x
    agentAY = play.teamA[0].y
    agentBX = play.teamA[1].x
    agentBY = play.teamA[1].y
    agentCX = play.teamB[0].x
    agentCY = play.teamB[0].y
    agentDX = play.teamB[1].x
    agentDY = play.teamB[1].y

    baseActionOfAgentA = int(play.teamA[0].baseAction)
    removeActionOfAgentA = int(play.teamA[0].removeAction)
    baseActionOfAgentB = int(play.teamA[1].baseAction)
    removeActionOfAgentB = int(play.teamA[1].removeAction)
    baseActionOfAgentC = int(play.teamB[0].baseAction)
    removeActionOfAgentC = int(play.teamB[0].removeAction)
    baseActionOfAgentD = int(play.teamB[1].baseAction)
    removeActionOfAgentD = int(play.teamB[1].removeAction)

    scoreBoardRow = len(play.scoreBoard[0])
    scoreBoardColunmn = len(play.scoreBoard)

    allPlaceTileState = [[0 for x in range(scoreBoardRow)]
                         for y in range(scoreBoardColunmn)]
    teamAPlaceTileState = calcTeamTile(play.teamA)
    teamBPlaceTileState = calcTeamTile(play.teamB)

    for y in range(scoreBoardColunmn):
        for x in range(scoreBoardRow):
            if teamAPlaceTileState[y][x]:
                allPlaceTileState[y][x] = 1

            if teamBPlaceTileState[y][x]:
                allPlaceTileState[y][x] = 2

    allPlaceTileState = [flatten for inner in allPlaceTileState for flatten in inner]

    turn_data["AteamAgentA"] = [agentAX, agentAY, baseActionOfAgentA, removeActionOfAgentA]
    turn_data["AteamAgentB"] = [agentBX, agentBY, baseActionOfAgentB, removeActionOfAgentB]
    turn_data["BteamAgentA"] = [agentCX, agentCY, baseActionOfAgentC, removeActionOfAgentC]
    turn_data["BteamAgentB"] = [agentDX, agentDY, baseActionOfAgentD, removeActionOfAgentD]
    turn_data["Board"] = allPlaceTileState

    return turn_data

def createTurmDataForLearn(play):
    """
    学習用の勝敗データを生成
    @param play Playingクラスのインスタンス
    @return turmData 勝敗データ
    """

    turmData = {"Ateam": "lose", "Bteam": "lose"}

    victory = play.judgmentVictory()

    if victory == "teamAWin":
        turmData["Ateam"] = "win"

    else:
        turmData["Bteam"] = "win"

    return turmData


def createSearchInfoForSearch(play):
    """
    レコード検索用の検索データを生成
    @param play Playingクラスのインスタンス
    @return searchInformation レコード検索用の検索データ
    """

    searchInfomation = {
        "Board": [],
        'AteamAgentA': [],
        'AteamAgentB': [],
        'BteamAgentA': [],
        'BteamAgentB': [],
        "Similarity": [300]
    }

    scoreBoardRow = len(play.scoreBoard[0])
    scoreBoardColunmn = len(play.scoreBoard)
    scoreBoard = []

    for y in range(scoreBoardColunmn):
        for x in range(scoreBoardRow):

            scoreBoard.append(play.scoreBoard[y][x])

    agentAX = play.teamA[0].x
    agentAY = play.teamA[0].y
    agentBX = play.teamA[1].x
    agentBY = play.teamA[1].y
    agentCX = play.teamB[0].x
    agentCY = play.teamB[0].y
    agentDX = play.teamB[1].x
    agentDY = play.teamB[1].y

    searchInfomation["Board"] = scoreBoard
    searchInfomation["AteamAgentA"] = [agentAX, agentAY]
    searchInfomation["AteamAgentB"] = [agentBX, agentBY]
    searchInfomation["BteamAgentA"] = [agentCX, agentCY]
    searchInfomation["BteamAgentB"] = [agentDX, agentDY]

    return searchInfomation


def searchBestActionOfEachAgent(search, searchInformation):
    """
    データベースから個々のエージェントの最善手を検索
    @param play Playingクラスのインスタンス
    @return bestActionOfEachAgent 個々のエージェントの最善手
    """

    bestActionOfEachAgent = search.SearchRecode(searchInformation)

    # 検索結果を扱いやすい形式に変換
    bestActionOfEachAgent = {
        "agentA": {
            "act": bestActionOfEachAgent["AteamAgentA"][0],
            "rmAct": bestActionOfEachAgent["AteamAgentA"][1],
        },
        "agentB": {
            "act": bestActionOfEachAgent["AteamAgentB"][0],
            "rmAct": bestActionOfEachAgent["AteamAgentB"][1],
        },
        "agentC": {
            "act": bestActionOfEachAgent["BteamAgentA"][0],
            "rmAct": bestActionOfEachAgent["BteamAgentA"][1],
        },
        "agentD": {
            "act": bestActionOfEachAgent["BteamAgentB"][0],
            "rmAct": bestActionOfEachAgent["BteamAgentB"][1],
        }
    }

    return bestActionOfEachAgent

def searchBestActionOfEachAgentForGUI(search, searchInformation):
    """
    データベースから個々のエージェントの最善手を検索
    @param play Playingクラスのインスタンス
    @return bestActionOfEachAgent 個々のエージェントの最善手
    """

    # データベースから個々のエージェントの最善手を検索する
    bestActionOfEachAgentForCUI = search.SearchRecode(searchInformation)

    # 検索結果を扱いやすい形式に変換
    bestActionOfEachAgentForCUI = {
        "agentA": {
            "act": bestActionOfEachAgentForCUI["AteamAgentA"][0],
            "rmAct": bestActionOfEachAgentForCUI["AteamAgentA"][1],
        },
        "agentB": {
            "act": bestActionOfEachAgentForCUI["AteamAgentB"][0],
            "rmAct": bestActionOfEachAgentForCUI["AteamAgentB"][1],
        },
        "agentC": {
            "act": bestActionOfEachAgentForCUI["BteamAgentA"][0],
            "rmAct": bestActionOfEachAgentForCUI["BteamAgentA"][1],
        },
        "agentD": {
            "act": bestActionOfEachAgentForCUI["BteamAgentB"][0],
            "rmAct": bestActionOfEachAgentForCUI["BteamAgentB"][1],
        }
    }

    # CUI形式のアクションをGUI形式に変換
    bestActionOfEachAgentForGUI = conversioActionToGUIFromCUI(bestActionOfEachAgentForCUI)

    return bestActionOfEachAgentForGUI