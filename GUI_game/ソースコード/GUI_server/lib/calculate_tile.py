""" タイルの計算を行う機能をまとめたクラス　"""
from typing import List
import sys
sys.setrecursionlimit(10000)


checked: List[List[bool]]  # チェックのための配列
preChecked = None  # 移動中に使うメモ配列
memoRegionMap = []  # 作成中のマップ


def calcTeamTile(team):
    """
    チームのタイルを合わせた配列を返す
    @param team チーム
    @return combinedTile 結合後のタイル
    """

    row = len(team[0].tile[0])
    columu = len(team[0].tile)
    agentATile = team[0].tile
    agentBTile = team[1].tile
    combinedTile = [[False for x in range(row)]
                    for y in range(columu)]

    for y in range(0, columu):
        for x in range(0, row):
            if agentATile[y][x] or agentBTile[y][x]:
                combinedTile[y][x] = True


    return combinedTile


def calcTeamRegion(team):
    """ タイルの配置を元に領域の場所を求める """

    global checked
    global memoRegionMap

    m = calcTeamTile(team)  # タイルが置かれている場所の配列
    result = []  # 実際に返す確定した領域の配列
    checked = [[False for j in i] for i in m]
    memoRegionMap = [[False for j in i] for i in m]

    def innerRegion(m, x: int, y: int) -> bool:
        global preChecked
        global checked
        global memoRegionMap

        # return この場所の領域
        isOneTime = False

        # 今の場所をメモ
        if preChecked is None:
            preChecked = [[False for j in i] for i in m]
            isOneTime = True
        preChecked[y][x] = True

        # とりあえず絞る
        if not searchRegion(m, x, y):
            if isOneTime:
                checked[y][x] = True
                preChecked = None
            return False

        # 自分がチェック済ならそのまま
        if searchChecked(checked, x, y):
            if isOneTime:
                checked[y][x] = True
                preChecked = None
            return m[y][x]

        # 隣のマスがチェック済か?
        # 左
        left_checked = searchChecked(checked, x - 1, y) and (not searchTile(m, x - 1, y))
        if left_checked:
            if isOneTime:
                checked[y][x] = True
                preChecked = None
            return memoRegionMap[y][x - 1]
        # 右
        right_checked = searchChecked(checked, x + 1, y) and (not searchTile(m, x + 1, y))
        if right_checked:
            if isOneTime:
                checked[y][x] = True
                preChecked = None
            return memoRegionMap[y][x + 1]
        # 上
        up_checked = searchChecked(checked, x, y - 1) and (not searchTile(m, x, y - 1))
        if up_checked:
            if isOneTime:
                checked[y][x] = True
                preChecked = None
            return memoRegionMap[y - 1][x]
        # 下
        bot_checked = searchChecked(checked, x, y + 1) and (not searchTile(m, x, y + 1))
        if bot_checked:
            if isOneTime:
                checked[y][x] = True
                preChecked = None
            return memoRegionMap[y + 1][x]

        # 隣のマスで同じ処理
        left_ans = True
        right_ans = True
        top_ans = True
        bot_ans = True
        # 左
        if not (searchChecked(preChecked, x - 1, y) or searchTile(m, x - 1, y)):
            left_ans = innerRegion(m, x - 1, y)
        # 右
        if not (searchChecked(preChecked, x + 1, y) or searchTile(m, x + 1, y)):
            right_ans = innerRegion(m, x + 1, y)
        # 上
        if not (searchChecked(preChecked, x, y - 1) or searchTile(m, x, y - 1)):
            top_ans = innerRegion(m, x, y - 1)
        # 下
        if not (searchChecked(preChecked, x, y + 1) or searchTile(m, x, y + 1)):
            bot_ans = innerRegion(m, x, y + 1)

        all_ans = left_ans and right_ans and top_ans and bot_ans

        # 完全に囲まれているなら True
        if isOneTime:
            checked[y][x] = True
            preChecked = None
        return all_ans

    def searchTile(m, x: int, y: int) -> bool:
        if not ((0 <= y < len(m)) and (0 <= x < len(m[0]))):
            return False
        return m[y][x]

    def searchChecked(c, x: int, y: int) -> bool:
        """ チェック済みか """

        if not ((0 <= y < len(c)) and (0 <= x < len(c[0]))):
            return False
        return c[y][x]

    def searchRegion(m, x: int, y: int) -> bool:
        """ 領域の可能性のあるマス(上下左右の延長線上にタイルがない かつ 今の場所がタイルではないマス) """

        flag = True
        # とりあえずタイルなら
        if m[y][x]:
            return False
        # 右
        if flag:
            counter = x
            while counter < len(m[0]):
                if m[y][counter]:  # もしタイルがあるなら
                    break
                counter += 1
            if counter == len(m[0]):  # 端まで行った
                flag = False
        # 左
        if flag:
            counter = x
            while counter >= 0:
                if m[y][counter]:  # もしタイルがあるなら
                    break
                counter -= 1
            if counter == -1:  # 端まで行った
                flag = False
        # 下
        if flag:
            counter = y
            while counter < len(m):
                if m[counter][x]:
                    break
                counter += 1
            if counter == len(m):
                flag = False
        # 上
        if flag:
            counter = y
            while counter >= 0:
                if m[counter][x]:
                    break
                counter -= 1
            if counter == -1:
                flag = False
        return flag

    for y in range(len(m)):
        innner_result = []
        for x in range(len(m[y])):
            re = innerRegion(m, x, y)
            innner_result.append(re)
            memoRegionMap[y][x] = re
        result.append(innner_result)

    memoRegionMap = []
    return result




