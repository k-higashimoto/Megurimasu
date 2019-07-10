package lib.socketCommunication;

import java.io.*;
import java.net.Socket;


public class Client {
    /**
     * ソケット通信（クライアント側）をするためのクラス
     */

    public static String sendData(String sendData) {
        /**
         * サーバーにデータを送信
         * @param sendData サーバーに送信する文字列データ
         * @return response サーバから受信した文字列データ
         */

        Socket socket = null;
        BufferedReader reader = null;
        PrintWriter writer = null;
        String response = "";

        try {

            socket = new Socket("localhost", 1000);
            reader = new BufferedReader
                    (new InputStreamReader
                            (socket.getInputStream()));
            writer = new PrintWriter(
                    socket.getOutputStream(), true);

            // サーバーにデータを送信する
            writer.println(sendData);

            // サーバーからデータを受信する
            response = reader.readLine();

        } catch (Exception e) {

            e.printStackTrace();

        } finally {
            try {
                if (reader!=null){
                    reader.close();
                }
                if (writer!=null){
                    writer.close();
                }
                if (socket!=null){
                    socket.close();
                }
            } catch (IOException e) {
                e.printStackTrace();
            }

            return response;
        }
    }
}
