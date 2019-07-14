""""""
from lib.game_parts import MeguriMasuCore
from lib.game_start_set import recieveGameSetFromGUI
from lib.gui_input import GUIInput
from lib.gui_output import GUIOutput
from lib.socket_communication import sendDataToClient


def main():
    print("ゲームの試合設定を入力してください＞＞ ")
    megurimasu = MeguriMasuCore(recieveGameSetFromGUI())
	
    print("*ゲームの準備中*")
    guiInput = GUIInput(megurimasu.play)
    guiOutput = GUIOutput(megurimasu.play)
    print("*ゲームの準備が整いました*")
	
    sendDataToClient(guiOutput.createTurnStateDataForGUI())
    for act in megurimasu.act():
        #　GUIからの入力を受け付ける
        print("エージェントの行動を入力してください＞＞")
        act(guiInput.input())
		
        # GUIに現状データを送る
        print("*GUIにターン状況データを送信します*")
        sendDataToClient(guiOutput.createTurnStateDataForGUI())
    megurimasu.endAct()


if __name__ == "__main__":
    main()
