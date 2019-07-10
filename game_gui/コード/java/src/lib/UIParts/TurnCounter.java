package lib.UIParts;

import javafx.scene.control.TextField;

public class TurnCounter {
    /**
     * ターンを管理するためのクラス
     */
    private TextField textFieldOfTurn;
    private int maxTurn;
    private int nowTurn = 1;

    public TurnCounter(TextField textFieldOfTurn, int maxTurn) {
        this.textFieldOfTurn = textFieldOfTurn;
        this.maxTurn = maxTurn;
    }

    public int getNowTurn() {
        return nowTurn;
    }

    public int getMaxTurn() { return maxTurn; }

    public void setNowTurn(int nowTurn) {
        /**
         * 現在のターンを設定する
         */
        this.nowTurn = nowTurn;
    }

    public void display() {
        /**
         * ターンをテキストフィールドに描画
         */
        textFieldOfTurn.setText(nowTurn + "/" + maxTurn);
    }
}
