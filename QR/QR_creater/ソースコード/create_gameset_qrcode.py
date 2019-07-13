from lib.game_start_set import createRandomGameSet
import qrcode


def main():
    """
    試合設定のQRコードテキストを生成

    行数 列数:
    スコアボード:
    エージェントAのX座標 エージェントAのY座標:
    エージェントBのX座標 エージェントBのY座標:
    """

    # ランダムな試合設定を取得
    gameStartSet = createRandomGameSet()
    
    scoreBoard = gameStartSet["scoreBoard"]
    column     = gameStartSet["column"]
    row        = gameStartSet["row"]
    agentAX = gameStartSet["agentAX"]
    agentAY = gameStartSet["agentAY"]
    agentBX = gameStartSet["agentBX"]
    agentBY = gameStartSet["agentBY"]

    gameStartSetQRText = ""
    gameStartSetQRText += f"{column} {row}:"

    for y in range(column):
        for x in range(row):
            gameStartSetQRText += str(scoreBoard[y][x])

            if x < row - 1:
                gameStartSetQRText += " "
        gameStartSetQRText += ":"

    gameStartSetQRText += f"{agentAX} {agentAY}:"
    gameStartSetQRText += f"{agentBX} {agentBY}:"

    # QRコードのテキストからQRコードを生成
    gameStartSetQRImage = qrcode.make(gameStartSetQRText)

    # QRコードを表示
    gameStartSetQRImage.show()

    # QRコードをPNGとして出力
    gameStartSetQRImage.save(
        f"game_start_set_qr{column}{row}{agentAX}{agentAY}{agentBX}{agentBY}.png"
    )



if __name__ == "__main__":
    main()