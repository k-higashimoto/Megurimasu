package lib.crap;

public class ConversionDirPos {
    /**
     * 方向[0~8]と座標[x, y]を変換するためだけのクラス
     */

    public static int toDirFromPos(int tileX1,
                                   int tileY1,
                                   int tileX2,
                                   int tileY2) {
        /**
         * 座標から方向を求める
         * @param tileX1 移動元タイル座標X
         * @param tileY1 移動元タイル座標Y
         * @param tileX2 移動先タイル座標X
         * @param tileY2 移動先タイル座標Y
         * @return direction 方向[0~8]
         */

        double dx = tileX2 - tileX1;
        double dy = tileY2 - tileY1;

        // もし移動元と移動先のタイル間隔が、2つ以上離れていたらエラー: -1を返す
        if (Math.abs(dx) >= 2) {
            return -1;
        } else if (Math.abs(dy) >= 2) {
            return  -1;
        }

        // 移動元と移動先が同じなら待機: 0を返す
        int direction = 0;
        if (dx == 0 && dy == 0) {
            return direction;
        }

        double degree = Math.toDegrees(Math.atan2(dy, dx));
        int angle = (int)(degree + 360) % 360;
        switch (angle) {
            // 右: 1
            case 0:
                direction = 1;
                return direction;
            // 右斜下: 2
            case 45:
                direction = 2;
                return direction;
            // 下: 3
            case 90:
                direction = 3;
                return  direction;
            // 左斜下: 4
            case 135:
                direction = 4;
                return direction;
            // 左: 5
            case 180:
                direction = 5;
                return direction;
            // 左斜上: 6
            case 225:
                direction = 6;
                return direction;
            // 上: 7
            case 270:
                direction = 7;
                return direction;
            // 右斜上: 8
            case 315:
                direction = 8;
                return direction;
            default:
                direction = 0;
                return direction;
        }
    }

    public static int[] toPosFromDir(int direction, int tileX, int tileY) {
        /**
         * 方向と移動元座標から移動先座標を求める
         * @param direction 方向
         * @param position 移動元座標
         * @return rearPosition 移動先座標
         */

        int[] rearPosition = {tileX, tileY};

        switch (direction) {
            case 0:
                return rearPosition;
            case 1:
                rearPosition[0]++;
                return  rearPosition;
            case 2:
                rearPosition[0]++;
                rearPosition[1]++;
                return  rearPosition;
            case 3:
                rearPosition[1]++;
                return rearPosition;
            case 4:
                rearPosition[0]--;
                rearPosition[1]++;
                return rearPosition;
            case 5:
                rearPosition[0]--;
                return rearPosition;
            case 6:
                rearPosition[0]--;
                rearPosition[1]--;
                return rearPosition;
            case 7:
                rearPosition[1]--;
                return rearPosition;
            case 8:
                rearPosition[0]++;
                rearPosition[1]--;
                return rearPosition;
            default:
                return rearPosition;
        }
    }
}
