package lib.setting;

public class Parameter {
    /**
     * ページ・コントロール間で値を共有するためだけのクラス
     */

    private static int maxTurn = 0;
    private static int[][] scoreBoard;
    private static int[] agentAPos, agentBPos, agentCPos, agentDPos;

    public static void setParameter(int maxTurn,
                                    int[][] scoreBoard,
                                    int[] agentAPos,
                                    int[] agentBPos,
                                    int[] agentCPos,
                                    int[] agentDPos) {
        /**
         * @param maxTurn 最大ターン数
         * @param scoreBoard スコアボード
         * @param agentAPos エージェントAの座標
         * @param agentBPos エージェントBの座標
         * @param agentCPos エージェントCの座標
         * @param agentDPos エージェントDの座標
         */

        Parameter.maxTurn = maxTurn;
        Parameter.scoreBoard = scoreBoard;
        Parameter.agentAPos = agentAPos;
        Parameter.agentBPos = agentBPos;
        Parameter.agentCPos = agentCPos;
        Parameter.agentDPos = agentDPos;
    }

    public static int getMaxTurn() {
        /**
         * 最大ターン数を返す
         */

        return maxTurn;
    }

    public static int[][] getScoreBoard() {
        /**
         * スコアボードを返す
         */

        return scoreBoard;
    }

    public static int[] getAgentPos(String agentName) {
        /**
         * 指定されたエージェントの座標を返す
         * @param agentName エージェントの名前
         * @return agent?Pos エージェントの座標[x, y]
         */

        switch (agentName) {
            case "agentA":
                return agentAPos;
            case "agentB":
                return agentBPos;
            case "agentC":
                return agentCPos;
            case "agentD":
                return agentDPos;
            default:
                return agentAPos;
        }
    }
}
