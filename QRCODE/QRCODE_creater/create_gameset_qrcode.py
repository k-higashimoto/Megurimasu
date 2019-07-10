from lib.game_start_set import createRandomGameSet
import qrcode


def main():

    # ランダムな試合設定を取得
    gameStartSet = createRandomGameSet()

    column = gameStartSet["column"]
    row = gameStartSet["row"]
    scoreBoard = gameStartSet["scoreBoard"]
    agentAX = gameStartSet["agentAX"]
    agentAY = gameStartSet["agentAY"]
    agentBX = gameStartSet["agentBX"]
    agentBY = gameStartSet["agentBY"]

    # 試合設定のQRコードテキストを生成する
    # スコアボードの行数と列数をQRコードテキストにセットする
    gameStartSetQRText = ""
    gameStartSetQRText += f"{column} {row}:"

    # スコアボードをQRコードテキストにセットする
    for y in range(column):
        for x in range(row):
            gameStartSetQRText += str(scoreBoard[y][x])
            if x < row - 1:
                gameStartSetQRText += " "
        gameStartSetQRText += ":"

    # エージェントAとBの座標をQRコードにセットする
    gameStartSetQRText += f"{agentAX} {agentAY}:"
    gameStartSetQRText += f"{agentBX} {agentBY}:"

    # QRコードのテキストからQRコードを生成する
    gameStartSetQRImage = qrcode.make(gameStartSetQRText)

    # QRコードを表示する
    gameStartSetQRImage.show()

    # QRコードをPNGとして出力する
    gameStartSetQRImage.save(
        f"game_start_set_qr{column}{row}{agentAX}{agentAY}{agentBX}{agentBY}.png"
    )





if __name__ == "__main__":
    main()