package lib.formChecker;

import javafx.scene.control.Spinner;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;

public class GameFormChecker {
    /**
     * ゲームの試合設定のフォームのフォームチェックを行うクラス
     */
    private TextField textFieldOfScoreBoardColumn;
    private TextField textFieldOfScoreBoardRow;
    private TextArea textAreaOfScoreBoard;
    private Spinner spinnerOfAgentAX;
    private Spinner spinnerOfAgentAY;
    private Spinner spinnerOfAgentBX;
    private Spinner spinnerOfAgentBY;

    public GameFormChecker(TextField textFieldOfScoreBoardColumn,
                           TextField textFieldOfScoreBoardRow,
                           TextArea textAreaOfScoreBoard,
                           Spinner spinnerOfAgentAX,
                           Spinner spinnerOfAgentAY,
                           Spinner spinnerOfAgentBX,
                           Spinner spinnerOfAgentBY) {

        this.textFieldOfScoreBoardColumn = textFieldOfScoreBoardColumn;
        this.textFieldOfScoreBoardRow = textFieldOfScoreBoardRow;
        this.textAreaOfScoreBoard = textAreaOfScoreBoard;
        this.spinnerOfAgentAX = spinnerOfAgentAX;
        this.spinnerOfAgentAY = spinnerOfAgentAY;
        this.spinnerOfAgentBX = spinnerOfAgentBX;
        this.spinnerOfAgentBY = spinnerOfAgentBY;
    }

    public boolean checkAll() {
        if (!checkScoreBoardColumn()) {
            return false;
        }
        if (!checkScoreBoardRow()) {
            return false;
        }
        if (!checkScoreBoard()) {
            return false;
        }
        if (!checkAgentAPOS()) {
            return false;
        }
        if (!checkAgentBPOS()) {
            return false;
        }
        return true;
    }

    private boolean checkScoreBoardColumn() {
        /**
         * スコアボードの行数をチェックする
         * @return boolean 入力された値は正しいかどうか
         */

        if (textFieldOfScoreBoardColumn.getText().equals("")) {
            return false;
        } else {
            return true;
        }
    }

    private boolean checkScoreBoardRow() {
        /**
         * スコアボードの列数をチェックする
         * @return boolean 入力された値は正しいかどうか
         */

        if (textFieldOfScoreBoardRow.getText().equals("")) {
            return false;
        } else {
            return true;
        }
    }

    private boolean checkScoreBoard() {
        /**
         * スコアボードをチェックする
         * @return boolean 入力された値は正しいかどうか
         */

        if (textAreaOfScoreBoard.getText().equals("")) {
            return false;
        } else {
            return true;
        }
    }

    private boolean checkAgentAPOS() {
        /**
         * エージェントAの座標をチェックする
         * @return boolean 入力された値は正しいかどうか
         */

        int agentAX = (int)spinnerOfAgentAX.getValue();
        int agentAY = (int)spinnerOfAgentAY.getValue();

        int scoreBoardColumn = Integer.parseInt(textFieldOfScoreBoardColumn.getText());
        int scoreBoardRow = Integer.parseInt(textFieldOfScoreBoardRow.getText());

        if (agentAX >= scoreBoardRow || agentAY >= scoreBoardColumn) {
            return false;
        } else {
            return true;
        }
    }

    private boolean checkAgentBPOS() {
        /**
         * エージェントBの座標をチェックする
         * @return boolean 入力された値は正しいかどうか
         */

        int agentBX = (int)spinnerOfAgentBX.getValue();
        int agentBY = (int)spinnerOfAgentBY.getValue();

        int scoreBoardColumn = Integer.parseInt(textFieldOfScoreBoardColumn.getText());
        int scoreBoardRow = Integer.parseInt(textFieldOfScoreBoardRow.getText());

        if (agentBX >= scoreBoardRow || agentBY >= scoreBoardColumn) {
            return false;
        } else {
            return true;
        }
    }
}
