package lib.UIParts;

import lib.analysis.AnalysisQRText;
import lib.analysis.AnalysisTurnState;
import lib.createData.TurnStateData;
import javafx.scene.control.TextArea;


public class DisplayerOfLog {
    /**
     * ゲームのログを管理し、表示するためのクラス
     */
    private TextArea textAreaOfLog;
    private String log = "";

    public DisplayerOfLog(TextArea textAreaOfLog) {
        this.textAreaOfLog = textAreaOfLog;
    }

    public void display() {
        /**
         * ゲームのログを表示する
         */

        textAreaOfLog.setText(log);
    }

    public void append(AnalysisTurnState analysisTurnState, int nowTurn) {
        /**
         * ゲームのログを追加する
         * @param turnStateData そのターンにおける現状状況
         */

        // チームAの得点を取得
        int tilePointOfTeamA = analysisTurnState.getTilePointOfTeamA();
        int regionPointOfTeamA = analysisTurnState.getRegionPointOfTeamA();
        int allPointOfTeamA = analysisTurnState.getAllPointOfTeamA();

        // チームBの得点を取得
        int tilePointOfTeamB = analysisTurnState.getTilePointOfTeamB();
        int regionPointOfTeamB = analysisTurnState.getRegionPointOfTeamB();
        int allPointOfTeamB = analysisTurnState.getAllPointOfTeamB();

        // 個々のエージェントの座標を取得
        int[] agentAPos = analysisTurnState.getAgentAPos();
        int[] agentBPos = analysisTurnState.getAgentBPos();
        int[] agentCPos = analysisTurnState.getAgentCPos();
        int[] agentDPos = analysisTurnState.getAgentDPos();

        String turnLog = "";
        turnLog += "**************************" + "\n";
        turnLog += "ターン:" + nowTurn + "\n";
        turnLog += "タイルポイント:" + tilePointOfTeamA + ":" + tilePointOfTeamB + "\n";
        turnLog += "領域ポイント:" + regionPointOfTeamA + ":" + regionPointOfTeamB + "\n";
        turnLog += "合計ポイント:" + allPointOfTeamA + ":" + allPointOfTeamB + "\n";

        log += turnLog;
    }
}
