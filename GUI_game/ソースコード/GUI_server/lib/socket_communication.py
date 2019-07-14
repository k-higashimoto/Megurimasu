""" ソケット通信に関する機能をまとめたモジュール　"""

import socket


class Server():
    """
    クライアントとソケット通信をするためのサーバー側のクラス
    """

    def __init__(self, host: str, port: int):
        self._host = host
        self._port = port
        self._s = None
        self._response = ""
        self._soc = None
        self._add = None

    def openStream(self):
        """
        指定したアドレスとソケット通信を開始する
        """

        self._s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

        # 指定したホスト(IP)とポートをソケットに設定
        self._s.bind((self._host, self._port))


    def sendData(self, sendData: str):
        """
        クライアント側に文字列データを送る
        @param sendData クライアントに送るデータ
        """

        # 1つの接続要求を待つ
        self._s.listen(1)

        # 要求が来るまでブロック
        self._soc, self._addr = self._s.accept()

        # データを受信（1024バイトまで)
        self._response = self._soc.recv(1024)
        self._response = self._response.decode("utf-8")
        self._soc.send(sendData.encode())

    def closeStream(self):
        """
        クライアントとのソケット通信を終了する
        """

        self._soc.close()

    def getResponse(self):
        """
        クライアントから受信したデータを取得する
        @return _response クライアントから受信したデータ
        """

        return self._response


def sendDataToClient(data) ->str:
    """
    クライアントとソケット通信を行う
    @param data データ
    @return response クライアントから受信したデータ
    """

    server = Server("localhost", 1000)
    server.openStream()
    server.sendData(data)
    server.closeStream()
    response = server.getResponse()

    return response