package lib.gameParts;

import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;

import java.util.ArrayList;

public class GameCanvas {
    /**
     * キャンバスの描写に関する関数を寄せ集めたクラス
     */

    private GraphicsContext gc;
    private double width, height;
    private ArrayList<Agent> agents;
    private Tile[][] tiles;

    public GameCanvas(GraphicsContext gc,
                      double width,
                      double height,
                      ArrayList<Agent> agents,
                      Tile[][] tiles) {

        this.gc = gc;
        this.width = width;
        this.height = height;
        this.agents = agents;
        this.tiles = tiles;
    }

    public void clearCanvas() {
        /**
         * キャンバスの初期化
         */

        gc.setFill(Color.BLACK);
        gc.fillRect(0, 0, width, height);
    }

    public void drawTiles() {
        /**
         * タイルの描画
         */

        drawTilePlaceState();
        drawActionableTiles();
        drawTilePoints();
    }

    private void drawTilePlaceState() {
        /**
         * タイルの設置状況を描画する
         */

        gc.setStroke(Color.WHITE);

        int column = tiles.length;
        int row = tiles[0].length;
        for (int y = 0; y < column; y++) {
            for (int x = 0; x < row; x++) {
                // タイルの色の判定
                // 黒: どのチームのタイルでもない 赤: チームAのタイル 青: チームBのタイル
                Tile tile = tiles[y][x];
                switch (tiles[y][x].getWhoseTile()) {
                    case 0:
                        gc.setFill(Color.BLACK);
                        break;
                    case 1:
                        gc.setFill(Color.RED);
                        break;
                    case -1:
                        gc.setFill(Color.BLUE);
                        break;
                    default:
                        gc.setFill(Color.BLACK);
                }

                // タイルを描画
                gc.fillRect(tile.getDrawX(), tile.getDrawY(), tile.getDw(), tile.getDh());
                gc.strokeRect(tile.getDrawX(), tile.getDrawY(), tile.getDw(), tile.getDh());
            }
        }
    }

    private void drawActionableTiles() {
        /**
         * 行動可能なタイルを描画する
         */

        gc.setStroke(Color.WHITE);

        int column = tiles.length;
        int row = tiles[0].length;
        for (int y = 0; y < column; y++) {
            for (int x = 0; x < row; x++) {
                Tile tile = tiles[y][x];
                switch (tile.getActionableTile()) {
                    case 0:
                        gc.setFill(new Color(1, 1, 1, 0.0));
                        break;
                    case 1:
                        gc.setFill(new Color(1, 1, 0, 0.4));
                        break;
                    case -1:
                        gc.setFill(new Color(1, 1, 0, 0.4));
                        break;
                    default:
                        break;
                }

                // タイルを描画
                gc.fillRect(tile.getDrawX(), tile.getDrawY(), tile.getDw(), tile.getDh());
                gc.strokeRect(tile.getDrawX(), tile.getDrawY(), tile.getDw(), tile.getDh());
            }
        }
    }

    private void drawTilePoints() {
        /**
         * タイルの得点を描画する
         */

        // フォントサイズ:17pixel
        gc.setFont(new Font(17));

        // フォント色:白
        gc.setFill(Color.WHITE);

        int column = tiles.length;
        int row = tiles[0].length;
        for (int y = 0; y < column; y++) {
            for (int x = 0; x < row; x++) {
                Tile tile = tiles[y][x];
                int tilePoint = tile.getPoint();

                gc.fillText(String.valueOf(tilePoint),
                        tile.getDrawX() + (tile.getDw() / 2),
                        tile.getDrawY() + (tile.getDh() / 2)
                );
            }
        }
    }

    public void drawAgents() {
        /**
         * エージェントの描画
         * @param ArrayList<Agent> エージェントのリスト
         */

        drawAgentTurnNumber();
        drawAgentNames();
    }

    private void drawAgentTurnNumber() {
        /**
         * エージェントの手番を入力する
         */
        for (Agent agent : agents) {

            // エージェントの手番の判定
            // 黄色: 手番 灰色: 手番ではない
            if (Agent.whoseTurn.equals(agent.getName())) {
                gc.setFill(Color.GOLD);
            } else {
                gc.setFill(Color.GRAY);
            }

            gc.fillOval(agent.getDrawX(), agent.getDrawY(), agent.getDw(), agent.getDh());
        }
    }

    private void drawAgentNames() {
        /**
         * エージェントの頭文字を描画する
         */

        // フォントサイズ:17pixel
        gc.setFont(new Font(agents.get(0).getDw()));

        // フォント色:白
        gc.setFill(Color.WHITE);

        for (Agent agent: agents) {
            String agentInitials = "A";
            switch (agent.getName()) {
                case "agentA":
                    agentInitials = "A";
                    break;
                case "agentB":
                    agentInitials = "B";
                    break;
                case "agentC":
                    agentInitials = "C";
                    break;
                case "agentD":
                    agentInitials = "D";
                    break;
            }

            gc.fillText(
                    agentInitials,
                    agent.getDrawX(),
                    agent.getDrawY() + (agent.getDh() / 2)
            );
        }
    }
}
