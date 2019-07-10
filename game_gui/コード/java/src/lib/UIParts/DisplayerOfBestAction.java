package lib.UIParts;

import javafx.scene.control.TextArea;

public class DisplayerOfBestAction {
    /**
     * 最善手を管理し、表示するためのクラス
     */

    private TextArea textAreaOfBestActionOfTeamA, textAreaOfBestActionOfTeamB;
    private int[] bestActionOfAgentA;
    private int[] bestActionOfAgentB;
    private int[] bestActionOfAgentC;
    private int[] bestActionOfAgentD;

    public DisplayerOfBestAction(TextArea textAreaOfBestActionOfTeamA,
                                 TextArea textAreaOfBestActionOfTeamB) {
        
        this.textAreaOfBestActionOfTeamA = textAreaOfBestActionOfTeamA;
        this.textAreaOfBestActionOfTeamB = textAreaOfBestActionOfTeamB;
    }

    public void display() {
        /**
         * 最善手を表示する
         */

        String textOfBestActionOfTeamA = "";
        textOfBestActionOfTeamA += "チームA\n";
        textOfBestActionOfTeamA += "エージェントA: " + bestActionOfAgentA[0] + bestActionOfAgentA[1] + "\t";
        textOfBestActionOfTeamA += direction(bestActionOfAgentA[0]) + " " + toDo(bestActionOfAgentA[1]) + "\t";
        textOfBestActionOfTeamA += "エージェントB: " + bestActionOfAgentB[0] + bestActionOfAgentB[1] + "\t";
        textOfBestActionOfTeamA += direction(bestActionOfAgentB[0]) + " " + toDo(bestActionOfAgentB[1]);

        String textOfBestActionOfTeamB = "";
        textOfBestActionOfTeamB += "チームB\n";
        textOfBestActionOfTeamB += "エージェントC: " + bestActionOfAgentC[0] + bestActionOfAgentC[1] + "\t";
        textOfBestActionOfTeamB += direction(bestActionOfAgentC[0]) + " " + toDo(bestActionOfAgentC[1]) + "\t";
        textOfBestActionOfTeamB += "エージェントD: " + bestActionOfAgentD[0] + bestActionOfAgentD[1] + "\t";
        textOfBestActionOfTeamB += direction(bestActionOfAgentD[0]) + " " + toDo(bestActionOfAgentD[1]);

        this.textAreaOfBestActionOfTeamA.setText(textOfBestActionOfTeamA);
        this.textAreaOfBestActionOfTeamB.setText(textOfBestActionOfTeamB);
    }

    private String direction(int direction) {
        /**
         * 数字の方向を文字列に変換するメソッド
         */

        switch (direction) {
            case 0:
                return "・";
            case 1:
                return "→";
            case 2:
                return "↘";
            case 3:
                return "↓";
            case 4:
                return "↙";
            case 5:
                return "←";
            case 6:
                return "↖";
            case 7:
                return "↑";
            case 8:
                return "↗";
            default:
                return "・";
        }
    }

    private String toDo(int toDo) {
        /**
         * 数字の移動or削除を文字列に変換するメソッド
         */

        if (toDo == 0) {
            return "移";
        } else {
            return "削";
        }

    }

    public void setBestActionOfAgentA(int[] bestActionOfAgentA) {
        this.bestActionOfAgentA = bestActionOfAgentA;
    }

    public void setBestActionOfAgentB(int[] bestActionOfAgentB) {
        this.bestActionOfAgentB = bestActionOfAgentB;
    }

    public void setBestActionOfAgentC(int[] bestActionOfAgentC) {
        this.bestActionOfAgentC = bestActionOfAgentC;
    }

    public void setBestActionOfAgentD(int[] bestActionOfAgentD) {
        this.bestActionOfAgentD = bestActionOfAgentD;
    }
}
