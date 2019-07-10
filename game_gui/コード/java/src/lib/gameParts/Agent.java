package lib.gameParts;

public class Agent {
    /**
     * エージェントのクラス
     * 座標を2つ持つ
     * キャンバスに描写するための draw座標
     * ゲームのタイル管理のための tile座標
     */

    private String name;
    private char team;
    private double drawX, drawY;
    private int tileX, tileY;
    private double dw, dh;
    private int[] action = new int[2];
    private int[][] actionableAction = {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {8, 0}};
    public static String whoseTurn;


    public Agent(String name,
                 char team,
                 int drawX,
                 int drawY,
                 int tileX,
                 int tileY,
                 double dw,
                 double dh) {

        this.name = name;
        this.team = team;
        this.drawX = drawX;
        this.drawY = drawY;
        this.tileX = tileX;
        this.tileY = tileY;
        this.dw = dw;
        this.dh = dh;
    }

    public void setDrawPosition(int drawX, int drawY) {
        /**
         * draw座標(キャンバスに描画するための座標）を設定する
         */

        this.drawX = drawX;
        this.drawY = drawY;
    }

    public void setDrawPosition(double drawX, double drawY) {
        /**
         * draw座標(キャンバスに描画するための座標）を設定する
         */

        this.drawX = drawX;
        this.drawY = drawY;
    }

    public void setTilePosition(int tileX, int tileY) {
        /**
         * tile座標(タイル管理のための座標)を設定する
         */

        this.tileX = tileX;
        this.tileY = tileY;
    }

    public static void passNextAgent() {
        /**
         * エージェントの入力手番を次のエージェントに渡す
         */

        switch (Agent.whoseTurn) {
            case "agentA":
                Agent.whoseTurn = "agentB";
                break;
            case "agentB":
                Agent.whoseTurn = "agentC";
                break;
            case "agentC":
                Agent.whoseTurn = "agentD";
                break;
            case "agentD":
                Agent.whoseTurn = "agentA";
                break;
        }
    }

    public String getName() {
        return name;
    }

    public double getDrawX() {
        return drawX;
    }

    public double getDrawY() {
        return drawY;
    }

    public int getTileX() {
        return tileX;
    }

    public int getTileY() {
        return tileY;
    }

    public char getTeam() {
        return team;
    }

    public double getDw() {
        return dw;
    }

    public double getDh() {
        return dh;
    }

    public int[] getAction() {
        return action;
    }

    public void setAction(int moveAction, int removeAction) {
        this.action[0] = moveAction;
        this.action[1] = removeAction;
    }

    public void setTeam(char team) {
        this.team = team;
    }

    public void setDw(double dw) {
        this.dw = dw;
    }

    public int[][] getActionableAction() {
        return actionableAction;
    }

    public void setActionableBaseAction(int[][] actionableAction) {
        this.actionableAction = actionableAction;
    }
}
