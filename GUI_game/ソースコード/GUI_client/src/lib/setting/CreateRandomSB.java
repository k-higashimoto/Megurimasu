package lib.setting;

import java.util.Random;

public class CreateRandomSB {
    /**
     * ランダムなスコアボードを生成するクラス
     */

    public static int[][] createScoreBoard() {
        /**
         * ランダムなスコアボードを生成
         * @return scoreBoard スコアボード
         */

        Random random = new Random();
        int row = random.nextInt(6) + 1 + 6;
        int colomu = random.nextInt(6) + 1 + 6;
        int[][] scoreBoard = new int[colomu][row];

        for (int i = 0; i < colomu; i++) {
            for (int j = 0; j < row; j++) {
                scoreBoard[i][j] = random.nextInt(24) - 12;
            }
        }

        return scoreBoard;
    }

}
