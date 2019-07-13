""" ゲームの得点計算に関する機能をまとめたモジュール　"""
from lib.calculate_tile import calcTeamTile, calcTeamRegion


def calcTilePointOfTeam(team, scoreBoard) -> int:
    """
    チームのタイルポイントを求めて返す
    @param team エージェントのリスト
    @param scoreBoard スコアボード
    @return tilePoint チームのタイルポイント
    """

    tilePoint = 0
    teamTile = calcTeamTile(team)
    for y in range(len(teamTile)):
        for x in range(len(teamTile[0])):
            if teamTile[y][x]:
                tilePoint += scoreBoard[y][x]

    return tilePoint


def calcRegionPointOfTeam(team, scoreBoard) -> int:
    """
    チームの領域ポイントを求めて返す
    @param team エージェントのリスト
    @param scoreBoard スコアボード
    @return regionPoint チームの領域ポイント
    """

    regionPoint = 0
    teamRegion = calcTeamRegion(team)
    row = len(teamRegion[0])
    columu = len(teamRegion)

    for y in range(columu):
        for x in range(row):
            if teamRegion[y][x]:
                regionPoint += abs(scoreBoard[y][x])

    return regionPoint


def calcAllPointOfTeam(team, scoreBoard) -> int:
    """
    チームの合計点数を求めて返す(タイルポイント+領域ポイント)
    @param team エージェントのリスト
    @param スコアボード　スコアボード
    @return allPoint チームのタイルポイント＋領域ポイント
    """

    allPoint = calcTilePointOfTeam(team, scoreBoard) + calcRegionPointOfTeam(team, scoreBoard)
    return allPoint