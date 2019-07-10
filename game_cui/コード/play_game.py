from lib.game_cpu import createTurnDataForLearn
from lib.game_parts import MeguriMasuCore
from lib.game_start_set import createRandomGameSet
from lib.cui_input import CUIInput, createInputTypeOfEachAgent
from lib.cui_output import CUIOutput


def main():
    megurimasu = MeguriMasuCore(createRandomGameSet())
    cuiInput = CUIInput(megurimasu.play, **createInputTypeOfEachAgent())
    cuiOutput = CUIOutput(megurimasu.play)

    # ゲームの説明を行う
    cuiOutput.printGameExplain()

    for act in megurimasu.act():
        # ターンの状態を表示する
        cuiOutput.printTurnStatus()
        act(cuiInput.input())
    megurimasu.endAct()

    # ゲームの終了メッセージを表示する
    cuiOutput.printGameEndMessage()


if __name__ == "__main__":
    main()
