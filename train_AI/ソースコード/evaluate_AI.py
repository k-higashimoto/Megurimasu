""" ゲームの勝敗統計を行うためのプログラム """
from lib.game_parts import MeguriMasuCore
from lib.game_start_set import createRandomGameSet
from lib.cui_input import CUIInput, createInputTypeOfEachAgent


def main():
    # 標準入力から、エージェントの入力形式を取得
    inputTypeOfEachAgent = createInputTypeOfEachAgent()

    # 標準入力から、試行回数を取得
    epoch = int(input("試行回数を入力してください　＞＞"))

    # 指定された回数分、試合を実行
    teamAWinCounter = 0
    for gameCount in range(epoch):
        # 試合設定
        megurimasu = MeguriMasuCore(createRandomGameSet())
        gameInput = CUIInput(megurimasu.play, **inputTypeOfEachAgent)

        # ゲームを進行
        for act in megurimasu.act():
            act(gameInput.input())
        megurimasu.endAct()

        # ゲームの勝敗を記録
        if (megurimasu.play.judgmentVictory() == "teamAWin"):
            teamAWinCounter += 1

    # ゲームの統計結果を表示
    print("\n")
    print("-"*30)
    print(f"試合数：{epoch}")
    print(f"チームAの勝率: {teamAWinCounter/epoch}")
    print(f"チームBの勝率: {1-(teamAWinCounter/epoch)}")


if __name__ == "__main__":
    main()
