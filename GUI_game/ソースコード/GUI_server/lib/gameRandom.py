import math
from random import randint


def createRondomIntNumber(min: int,
                          max: int,
                          percentageOfPosNum: int):
    """
    指定された範囲のランダムな整数を生成する
    @param min 最小の数
    @param max 最大の数
    @param percentageOfPosNum 正の数の割合
    @return randomIntNumber ランダムな整数
    """

    randomIntNumber = randint(min, max)

    # 指定された割合分、正の数にする
    if percentageOfPosNum >= randint(0, 100):
        randomIntNumber = int(math.fabs(randomIntNumber))

    return  randomIntNumber
