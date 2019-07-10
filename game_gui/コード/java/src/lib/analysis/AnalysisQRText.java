package lib.analysis;

import lib.crap.ArrayElementTF;

import java.util.Arrays;
import java.util.Comparator;


public class AnalysisQRText {
    /**
     * 試合設定のQRコードのテキストから、試合設定を解析するためのクラス
     */

    private String qrText;
    private int[] scoreBoardSize;
    private int[][] scoreBoard;
    private int[] agentAPos;
    private int[] agentBPos;

    public AnalysisQRText(String qrText) {
        this.qrText = qrText;
    }

    public void analysis() {
        /**
         * QRコードのテキストから試合設定を解析
         */

        qrText = qrText.replaceAll("\n", " ");
        qrText = qrText.substring(0, qrText.length()-1);
        String[] listOfGameSet = qrText.split(":");

        // スコアボードのサイズを取得する
        scoreBoardSize = ArrayElementTF.toIntFromStr(listOfGameSet[0].split(" "));

        // スコアボードを取得する
        scoreBoard = new int[scoreBoardSize[0]][scoreBoardSize[1]];
        for (int i = 0; i < scoreBoardSize[0]; i++) {
            scoreBoard[i] = ArrayElementTF.toIntFromStr(listOfGameSet[i+1].split(" "));
        }

        // エージェントAとBの座標を取得する
        agentAPos = ArrayElementTF.toIntFromStr(listOfGameSet[listOfGameSet.length-2].split(" "));
        agentBPos = ArrayElementTF.toIntFromStr(listOfGameSet[listOfGameSet.length-1].split(" "));

        // エージェントAとBの座標を調整する
        // カウント始めを1から0に変換
        agentAPos[0]--;
        agentAPos[1]--;
        agentBPos[0]--;
        agentBPos[1]--;

        // *座標(y, x) を (x, y)形式に変換
        int a = agentAPos[0];
        agentAPos[0] = agentAPos[1];
        agentAPos[1] = a;

        int b = agentBPos[0];
        agentBPos[0] = agentBPos[1];
        agentBPos[1] = b;
    }

    public int[] getScoreBoardSize() {
        return scoreBoardSize;
    }

    public int[][] getScoreBoard() {
        return scoreBoard;
    }

    public int[] getAgentBPos() {
        return agentBPos;
    }

    public int[] getAgentAPos() {
        return agentAPos;
    }
}
