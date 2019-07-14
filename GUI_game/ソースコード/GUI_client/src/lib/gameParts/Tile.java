package lib.gameParts;

public class Tile {
    private final double drawX, drawY;
    private final int tileX, tileY;
    private final double dw, dh;
    private int point;
    private int whoseTile = 0;
    private int actionableTile = 0;

    public Tile(double drawX,
                double drawY,
                int tileX,
                int tileY,
                double dw,
                double dh,
                int point) {
        /**
         * @param drawX キャンバスに描画するためのX座標
         * @param drawY キャンバスに描画するためのY座標
         * @param tileX タイル管理のためのX座標
         * @param tileY タイル管理のためのY座標
         * @param dw タイルの横の大きさ
         * @param dh タイルの縦の大きさ
         * @param point タイルの点数
         */

        this.drawX = drawX;
        this.drawY = drawY;
        this.tileX = tileX;
        this.tileY = tileY;
        this.dw = dw;
        this.dh = dh;
        this.point = point;
    }

    public void setWhoseTile(int whoseTile) {
        /**
         * タイルがどのチームのものなのかをセットする
         * @param whoseTile 0: 誰のものでもない 1: チームAのタイル -1: チームBのタイル
         */

        switch(whoseTile) {
            // 正常値(0, 1, -1)の場合
            case 0:
            case 1:
            case -1:

                this.whoseTile = whoseTile;
                break;

            // 異常値の場合
            default:

                this.whoseTile = 0;
        }
    }

    public void setActionableTile(int actionableTile) {
        /**
         * タイルが行動可能なのかどうかセットする
         * @param actionableTile 真偽値
         */

        this.actionableTile = actionableTile;
    }

    public int getTileX() {
        return this.tileX;
    }

    public int getTileY() {
        return this.tileY;
    }

    public double getDrawX() {
        return this.drawX;
    }

    public double getDrawY() {
        return this.drawY;
    }

    public double getDw() {
        return this.dw;
    }

    public double getDh() {
        return this.dh;
    }

    public int getWhoseTile() {
        return this.whoseTile;
    }

    public int getPoint() {
        return this.point;
    }

    public int getActionableTile() {
        return actionableTile;
    }
}
