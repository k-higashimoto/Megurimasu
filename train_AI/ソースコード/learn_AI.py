""" ゲームの学習を行うためのプログラム """
from lib.game_parts import MeguriMasuCore
from lib.game_start_set import createRandomGameSet
from lib.cui_input import CUIInput, createInputTypeOfEachAgent
from lib.game_cpu import createInitDataForLearn, createTurnDataForLearn, createTurmDataForLearn
from lib.mass_game_database import Learning as Learn
import datetime


def main():
    startTime = datetime.datetime.now()

    # 標準入力から、エージェントの入力形式を取得
    inputTypeOfEachAgent = createInputTypeOfEachAgent()

    epoch = int(input("試行回数を入力してください　＞＞"))

    learn = Learn()

    # 入力された回数分、試合を実行&学習
    for gameCount in range(epoch):
        # ゲームの試合設定
        megurimasu = MeguriMasuCore(createRandomGameSet())
        cuiInput = CUIInput(megurimasu.play, **inputTypeOfEachAgent)

        # ゲームの試合設定をlearnにセット
        learn.SetInit(createInitDataForLearn(megurimasu.play))

        # ゲームの進行
        for act in megurimasu.act():
            act(cuiInput.input())

            # ゲームのターンごとの現状状況をlearnにセット
            learn.PushTurn(createTurnDataForLearn((megurimasu.play)))
        megurimasu.endAct()

        # ゲームの勝敗データをlearnにセット
        learn.SetTerm(createTurmDataForLearn(megurimasu.play))

        # 学習データをデータベースに記録
        saveResult = learn.Save()

        # 学習データを破棄
        learn.Clear()

        nowTime = datetime.datetime.now()
        print(f"{gameCount}試合目:", saveResult, f"{(nowTime-startTime)}s")
        print("-"*30)

    finishedTime = datetime.datetime.now()

    # 学習完了結果を表示
    print("-"*30)
    print("学習が完了しました\n")
    print(f"試合回数: {epoch}")
    print(f"計測時間: {finishedTime-startTime}s")


if __name__ == "__main__":
    main()
