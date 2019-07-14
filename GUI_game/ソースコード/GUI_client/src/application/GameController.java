package application;

import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.event.EventHandler;
import javafx.scene.Scene;
import javafx.util.Duration;
import lib.UIParts.DisplayerOfLog;
import lib.UIParts.DisplayerOfBestAction;
import lib.UIParts.Timer;
import lib.UIParts.TurnCounter;
import lib.analysis.AnalysisTurnState;
import lib.crap.*;
import lib.createData.CreateGameSetData;
import lib.createData.CreateInputData;
import lib.gameParts.Agent;
import lib.gameParts.GameCanvas;
import lib.gameParts.Tile;
import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.chart.LineChart;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.input.MouseEvent;
import lib.setting.Parameter;
import lib.socketCommunication.Client;
import lib.tableView.Point;
import lib.tableView.Position;

import java.net.URL;
import java.util.ArrayList;
import java.util.Optional;
import java.util.ResourceBundle;

public class GameController implements Initializable {
    @FXML private MenuItem runButton, restartButton, stopButton;
    @FXML private TextField textFieldOfTimer;
    @FXML private TextField textFieldOfTurn;
    @FXML private TextArea textAreaOfBestActionOfTeamA, textAreaOfBestActionOfTeamB;
    @FXML private TableView<Point> pointTable;
    @FXML private TableView<Position> positionTable;
    @FXML private TableColumn itemOfPoint, teamAPoint, teamBPoint;
    @FXML private TableColumn itemOfPosition, teamAPosition, teamBPosition;
    @FXML private LineChart<Number, Number> lineChartOfAllPoint;
    @FXML private NumberAxis turnAxis, allPointAxis;
    @FXML private TextArea textAreaOfLog;
    @FXML private Canvas canvas;
    private GameCanvas gameCanvas;
    private Timer timer;
    private TurnCounter turnCounter;
    private DisplayerOfBestAction displayerOfBestAction;
    private DisplayerOfLog displayerOfLog;
    private GraphicsContext gc;
    private XYChart.Series<Number, Number> xy;
    private Tile[][] tiles;
    private ArrayList<Agent> agents;


    @FXML
    protected void onRunButton(ActionEvent event) {
        /**
         * メニュー＞Run＞ゲームの開始がクリックされたとき実行
         */

        // ゲームを開始していいかを確認
        Alert alert = new Alert(Alert.AlertType.CONFIRMATION);
        alert.setContentText("ゲームを開始します");

        // 取り消しボタンが押されたら何もしない
        if (alert.showAndWait().get() != ButtonType.OK) {
            return;
        }

        // キャンバスを操作可能にする
        canvas.setDisable(false);

        // ゲームの開始ボタンを二度とクリックできないようにする
        runButton.setDisable(true);

        // ゲームの停止ボタンをクリックできるようにする
        stopButton.setDisable(false);

        // タイマーを開始する
        timer.play();

        CreateInputData createInputData = new CreateInputData(agents);
        String sendDataOfInput = createInputData.create();

        // サーバーに入力データを送信
        String response= Client.sendData(sendDataOfInput);

        // サーバーの出力データを解析
        AnalysisTurnState alzTurnState = new AnalysisTurnState(response);
        alzTurnState.analysis();

        // 現在のターンを取得
        int nowTurn = alzTurnState.getNowTurn();
        turnCounter.setNowTurn(nowTurn);
        turnCounter.display();

        // 個々のチームの得点を取得
        int tilePointOfTeamA = alzTurnState.getTilePointOfTeamA();
        int tilePointOfTeamB = alzTurnState.getTilePointOfTeamB();

        int regionPointOfTeamA = alzTurnState.getRegionPointOfTeamA();
        int regionPointOfTeamB = alzTurnState.getRegionPointOfTeamB();

        int allPointOfTeamA = alzTurnState.getAllPointOfTeamA();
        int allPointOfTeamB = alzTurnState.getAllPointOfTeamB();

        // 個々のチームの得点をセット
        pointTable.getItems().add(new Point("タイルポイント", tilePointOfTeamA, tilePointOfTeamB));
        pointTable.getItems().add(new Point("領域ポイント", regionPointOfTeamA, regionPointOfTeamB));
        pointTable.getItems().add(new Point("合計ポイント", allPointOfTeamA, allPointOfTeamB));

        // 個々のエージェントの最善手を取得
        displayerOfBestAction.setBestActionOfAgentA(alzTurnState.getBestActionOfAgentA());
        displayerOfBestAction.setBestActionOfAgentB(alzTurnState.getBestActionOfAgentB());
        displayerOfBestAction.setBestActionOfAgentC(alzTurnState.getBestActionOfAgentC());
        displayerOfBestAction.setBestActionOfAgentD(alzTurnState.getBestActionOfAgentD());

        // 個々のエージェントの最善手を表示
        displayerOfBestAction.display();
    }

    @FXML
    protected void onRestartButton(ActionEvent event) {
        /**
         * メニュー＞Run＞ゲームの再開がクリックされたとき実行
         */

        // ゲームを再開してよいかユーザーに確認する
        Alert gameRestartAlert = new Alert(Alert.AlertType.CONFIRMATION);
        gameRestartAlert.setContentText("ゲームを再開します");

        // 取り消しボタンが押されたら何もしない
        if (gameRestartAlert.showAndWait().get() != ButtonType.OK) {
            return;
        }

        // キャンバスを操作可能にする
        canvas.setDisable(false);

        // ゲームの再開ボタンをクリックできないようにする
        restartButton.setDisable(true);

        // ゲームの停止ボタンをクリックできるようにする
        stopButton.setDisable(false);

        // タイマーを開始する
        timer.play();
    }

    @FXML
    protected void onStopButton(ActionEvent event) {
        /**
         * メニュー＞Stop＞ゲームの一時停止がクリックされたとき実行
         */

        // ゲームを一時停止してよいかユーザーに確認する
        Alert gameStopConfirmationAlert = new Alert(Alert.AlertType.CONFIRMATION);
        gameStopConfirmationAlert.setContentText("ゲームを一時停止してもよろしいですか？");

        // 取り消しボタンが押されたら何もしない
        if (gameStopConfirmationAlert.showAndWait().get() != ButtonType.OK) {
            return;
        }

        // キャンバスを操作不可能にする
        canvas.setDisable(true);

        // ゲームの停止ボタンをクリックできないようにする
        stopButton.setDisable(true);

        // ゲームの再開ボタンをクリックできるようにする
        restartButton.setDisable(false);

        // タイマーをストップする
        timer.stop();
    }

    @FXML
    protected void onFinishButtonClicked(ActionEvent event) {
        /**
         * メニュー＞ファイル＞終了ボタンがクリックされたら実行
         */

        Platform.exit();
    }

    @FXML
    protected void onCanvasClicked(MouseEvent event){
        /**
         * キャンバスがクリックされたとき実行
         */

        // キャンバスの座標を取得し、タイル座標[0~11, 0~11]に変換
        double dw = tiles[0][0].getDw();
        double dh = tiles[0][0].getDh();
        double canvasWidth = canvas.getWidth();
        double canvasHeight = canvas.getHeight();
        int row = (int)(canvasWidth / dw);
        int column = (int)(canvasHeight / dh);

        double canvasDrawX = event.getX();
        double canvasDrawY = event.getY();
        int canvasTileX = 0;
        int canvasTileY = 0;
        for (double y = 0; y <= canvasHeight; y += dh) {
            for (double x = 0; x <= canvasWidth; x += dw) {
                double drawX = canvasDrawX;
                double drawY = canvasDrawY;
                if (drawX > x && drawX < x + dw) {
                    if (drawY > y && drawY < y + dh) {
                        canvasTileX = (int)(x / dw);
                        canvasTileY = (int)(y / dh);
                    }
                }
            }
        }

        //　4人のエージェントの中の誰の手番なのかを判断する
        Agent agentOfThisTurnNumber;
        Agent agentOfNextTurnNumber;
        switch (Agent.whoseTurn) {
            case "agentA":
                agentOfThisTurnNumber = agents.get(0);
                agentOfNextTurnNumber = agents.get(1);
                break;
            case "agentB":
                agentOfThisTurnNumber = agents.get(1);
                agentOfNextTurnNumber = agents.get(2);
                break;
            case "agentC":
                agentOfThisTurnNumber = agents.get(2);
                agentOfNextTurnNumber = agents.get(3);
                break;
            case "agentD":
                agentOfThisTurnNumber = agents.get(3);
                agentOfNextTurnNumber = agents.get(0);
                break;
            default:
                agentOfThisTurnNumber = agents.get(0);
                agentOfNextTurnNumber = agents.get(1);
        }

        // エージェントのタイル座標とクリックされたタイルのタイル座標から方向(0~8)を求める
        int agentTileX = agentOfThisTurnNumber.getTileX();
        int agentTileY = agentOfThisTurnNumber.getTileY();
        int direction = ConversionDirPos.toDirFromPos(
                agentTileX,
                agentTileY,
                canvasTileX,
                canvasTileY
        );

        // エージェントの行動範囲外がクリックされたときは何もしない
        if (direction == -1) {
            return;
        }

        // 自チームのタイルを選択した時、移動か削除かを確認するアラート
        Alert confirmationOfMyTeamTile = new Alert(
                Alert.AlertType.CONFIRMATION,
                "自チームのタイルを選択しています\n" +
                        "自分チームのタイルを削除しますか？",
                ButtonType.YES,
                ButtonType.NO
        );

        // 自チームのタイルに移動することを確認するアラート
        Alert alertOfMyTeamTile = new Alert(
                Alert.AlertType.CONFIRMATION,
                "自チームのタイルに移動します"
        );

        char agentTeam = agentOfThisTurnNumber.getTeam();

        // 移動とタイル削除の分岐処理
        Tile clickedTile = tiles[canvasTileY][canvasTileX];
        switch (clickedTile.getWhoseTile()) {

            // 選択されたタイルが誰のものでもないなら
            case 0:
                // 移動　[方向(0~8), 削除(0)]をセット
                agentOfThisTurnNumber.setAction(direction, 0);
                break;

            // 選択されたタイルがチームAのものなら
            case 1:
                if (agentTeam == 'A') {
                    if (confirmationOfMyTeamTile.showAndWait().get() == ButtonType.NO) {

                        alertOfMyTeamTile.showAndWait();
                        // 移動　[移動(0~8), 0]をセット
                        agentOfThisTurnNumber.setAction(direction, 0);

                    } else {
                        // 削除　[方向(0~8), 削除(1)]をセット
                        agentOfThisTurnNumber.setAction(direction, 1);
                    }
                } else {

                    // 削除　[方向(0~8), 削除(9)]をセット
                    agentOfThisTurnNumber.setAction(direction, 1);
                }
                break;

            // 選択されたタイルがチームBのものなら
            case -1:
                if (agentTeam == 'B') {
                    if (confirmationOfMyTeamTile.showAndWait().get() == ButtonType.NO) {

                        alertOfMyTeamTile.showAndWait();
                        // 移動　[移動(0~8), 0]をセット
                        agentOfThisTurnNumber.setAction(direction, 0);
                    } else {
                        // 削除　[方向(0~8), 削除(1)]をセット
                        agentOfThisTurnNumber.setAction(direction, 1);
                    }
                } else {

                    // 削除　[方向(0~8), 削除(1)]をセット
                    agentOfThisTurnNumber.setAction(direction, 1);
                }
        }

        // エージェントの入力手番を次に渡す
        Agent.passNextAgent();

        // 行動可能なタイルをリセットする
        for (int y = 0; y < column; y++) {
            for (int x = 0; x < row; x++) {
                tiles[y][x].setActionableTile(0);
            }
        }

        // 行動可能なタイルをセットする
        int actionableActionColumn = agentOfNextTurnNumber.getActionableAction().length;
        for (int y = 0; y < actionableActionColumn; y++) {
            int baseAction = agentOfNextTurnNumber.getActionableAction()[y][0];

            int[] actionableTilePos =
                    ConversionDirPos.toPosFromDir(baseAction,
                            agentOfNextTurnNumber.getTileX(),
                            agentOfNextTurnNumber.getTileY()
                    );
            int actionableTileX = actionableTilePos[0];
            int actionableTileY = actionableTilePos[1];
            Tile actionableTile = tiles[actionableTileY][actionableTileX];

            if (agentOfNextTurnNumber.getTeam() == 'A') {
                actionableTile.setActionableTile(1);

            } else if (agentOfNextTurnNumber.getTeam() == 'B') {
                actionableTile.setActionableTile(-1);
            }
        }

        gameCanvas.clearCanvas();
        gameCanvas.drawTiles();
        gameCanvas.drawAgents();

        // もし1ターン中のエージェント4人の入力がすべて完了していないなら
        if (!agentOfThisTurnNumber.getName().equals("agentD")) {
            return;
        }

        // 入力を確定してよいかどうかユーザーに確認する
        Alert inputConfirmation = new Alert(
                Alert.AlertType.CONFIRMATION,
                "入力を確定しますか？" + "\n"
                        + "agentA: " + agents.get(0).getAction()[0] + agents.get(0).getAction()[1] + "\n"
                        + "agentB: " + agents.get(1).getAction()[0] + agents.get(1).getAction()[1] + "\n"
                        + "agentC: " + agents.get(2).getAction()[0] + agents.get(2).getAction()[1] + "\n"
                        + "agentD: " + agents.get(3).getAction()[0] + agents.get(3).getAction()[1],
                ButtonType.YES,
                ButtonType.NO
        );

        // キャンセルボタンが押されたら入力をキャンセルする
        if (inputConfirmation.showAndWait().get() != ButtonType.YES) {
            return;
        }

        // サーバーに送るための入力データを生成
        CreateInputData createInputData = new CreateInputData(agents);
        String sendDataOfInput = createInputData.create();

        // サーバーに入力データを送信
        Client.sendData(sendDataOfInput);

        // サーバーの処理待ち
        try {
            Thread.sleep(500);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        // サーバーから現状データを受信
        String response = Client.sendData("");

        // サーバーから受信した現状データを解析
        AnalysisTurnState alzTurnState = new AnalysisTurnState(response);
        alzTurnState.analysis();

        // 現在のターンを取得
        int nowTurn = alzTurnState.getNowTurn();

        // ターンカウンターを更新
        turnCounter.setNowTurn(nowTurn);
        turnCounter.display();

        // 出力データに基づいてタイルの更新
        int[][] tilePlaceState = alzTurnState.getTilePlaceState();
        for (int y = 0; y < column; y++) {
            for (int x = 0; x < row; x++) {
                Tile tile = tiles[y][x];
                int whoseTile = tilePlaceState[tile.getTileY()][tile.getTileX()];
                tile.setWhoseTile(whoseTile);
            }
        }

        // 個々のエージェントの座標の取得
        int[] agentAPos = alzTurnState.getAgentAPos();
        int[] agentBPos = alzTurnState.getAgentBPos();
        int[] agentCPos = alzTurnState.getAgentCPos();
        int[] agentDPos = alzTurnState.getAgentDPos();

        // 個々のエージェントの座標を更新
        agents.get(0).setTilePosition(agentAPos[0], agentAPos[1]);
        agents.get(1).setTilePosition(agentBPos[0], agentBPos[1]);
        agents.get(2).setTilePosition(agentCPos[0], agentCPos[1]);
        agents.get(3).setTilePosition(agentDPos[0], agentDPos[1]);
        agents.get(0).setDrawPosition(agentAPos[0]*dw, agentAPos[1]*dh);
        agents.get(1).setDrawPosition(agentBPos[0]*dw, agentBPos[1]*dh);
        agents.get(2).setDrawPosition(agentCPos[0]*dw, agentCPos[1]*dh);
        agents.get(3).setDrawPosition(agentDPos[0]*dw, agentDPos[1]*dh);

        // 個々のエージェントの行動可能基本行動を取得
        agents.get(0).setActionableBaseAction(alzTurnState.getActionableActionOfAgentA());
        agents.get(1).setActionableBaseAction(alzTurnState.getActionableActionOfAgentB());
        agents.get(2).setActionableBaseAction(alzTurnState.getActionableActionOfAgentC());
        agents.get(3).setActionableBaseAction(alzTurnState.getActionableActionOfAgentD());

        // 個々のエージェントの最善手を取得
        int[] bestActionOfAgentA = alzTurnState.getBestActionOfAgentA();
        int[] bestActionOfAgentB = alzTurnState.getBestActionOfAgentB();
        int[] bestActionOfAgentC = alzTurnState.getBestActionOfAgentC();
        int[] bestActionOfAgentD = alzTurnState.getBestActionOfAgentD();

        // 個々のエージェントの最善手をセット
        displayerOfBestAction.setBestActionOfAgentA(bestActionOfAgentA);
        displayerOfBestAction.setBestActionOfAgentB(bestActionOfAgentB);
        displayerOfBestAction.setBestActionOfAgentC(bestActionOfAgentC);
        displayerOfBestAction.setBestActionOfAgentD(bestActionOfAgentD);

        // 個々のエージェントの最善手を表示
        displayerOfBestAction.display();

        // 得点表を更新
        // チームAの得点の取得
        int tilePointOfTeamA = alzTurnState.getTilePointOfTeamA();
        int regionPointOfTeamA = alzTurnState.getRegionPointOfTeamA();
        int allPointOfTeamA = alzTurnState.getAllPointOfTeamA();

        // チームAの得点を更新
        pointTable.getItems().get(0).teamAPointProperty().set(tilePointOfTeamA);
        pointTable.getItems().get(1).teamAPointProperty().set(regionPointOfTeamA);
        pointTable.getItems().get(2).teamAPointProperty().set(allPointOfTeamA);

        // チームBの得点の取得
        int tilePointOfTeamB = alzTurnState.getTilePointOfTeamB();
        int regionPointOfTeamB = alzTurnState.getRegionPointOfTeamB();
        int allPointOfTeamB = alzTurnState.getAllPointOfTeamB();

        // チームBの得点を更新
        pointTable.getItems().get(0).teamBPointProperty().set(tilePointOfTeamB);
        pointTable.getItems().get(1).teamBPointProperty().set(regionPointOfTeamB);
        pointTable.getItems().get(2).teamBPointProperty().set(allPointOfTeamB);

        // 座標表を更新
        // エージェントAの座標を更新
        positionTable.getItems().get(0).teamAPositionProperty().set(agentAPos[0]);
        positionTable.getItems().get(0).teamBPositionProperty().set(agentAPos[1]);

        // エージェントBの座標を更新
        positionTable.getItems().get(1).teamAPositionProperty().set(agentBPos[0]);
        positionTable.getItems().get(1).teamBPositionProperty().set(agentBPos[1]);

        // エージェントCの座標を更新
        positionTable.getItems().get(2).teamAPositionProperty().set(agentCPos[0]);
        positionTable.getItems().get(2).teamBPositionProperty().set(agentCPos[1]);

        // エージェントDの座標を更新
        positionTable.getItems().get(3).teamAPositionProperty().set(agentDPos[0]);
        positionTable.getItems().get(3).teamBPositionProperty().set(agentDPos[1]);

        // 合計ポイントの推移グラフを更新
        xy.getData().add(
                new XYChart.Data<>(
                        turnCounter.getNowTurn(),
                        allPointOfTeamA-allPointOfTeamB
                )
        );

        // ゲームのログを更新
        displayerOfLog.append(alzTurnState, turnCounter.getNowTurn()-1);
        displayerOfLog.display();

        // 行動可能なタイルをリセットする
        for (int y = 0; y < column; y++) {
            for (int x = 0; x < row; x++) {
                tiles[y][x].setActionableTile(0);
            }
        }

        // 行動可能なタイルをセットする
        actionableActionColumn = agentOfNextTurnNumber.getActionableAction().length;
        for (int y = 0; y < actionableActionColumn; y++) {
            int baseAction = agentOfNextTurnNumber.getActionableAction()[y][0];

            int[] actionableTilePos =
                    ConversionDirPos.toPosFromDir(baseAction,
                            agentOfNextTurnNumber.getTileX(),
                            agentOfNextTurnNumber.getTileY()
                    );
            int actionableTileX = actionableTilePos[0];
            int actionableTileY = actionableTilePos[1];
            Tile actionableTile = tiles[actionableTileY][actionableTileX];

            if (agentOfNextTurnNumber.getTeam() == 'A') {
                actionableTile.setActionableTile(1);

            } else if (agentOfNextTurnNumber.getTeam() == 'B') {
                actionableTile.setActionableTile(-1);
            }
        }

        // キャンバスに描画
        gameCanvas.clearCanvas();
        gameCanvas.drawTiles();
        gameCanvas.drawAgents();

        // ゲームのフェーズを取得
        String phase = alzTurnState.getPhase();

        // ゲームが終了したら終了処理を行う
        if (phase.equals("finish")) {
            canvas.setDisable(true);
            Alert gameFinishAlert = new Alert(
                    Alert.AlertType.INFORMATION,
                    "ゲームが終了しました"
            );
            gameFinishAlert.showAndWait();
        }
    }

    @Override
    public void initialize(URL location, ResourceBundle resources) {

        int[][] scoreBoard = Parameter.getScoreBoard();
        int row = scoreBoard[0].length;
        int column= scoreBoard.length;
        int dw = (int)(canvas.getWidth() / row);
        int dh = (int)(canvas.getHeight() / column);

        // タイルの準備
        tiles = new Tile[column][row];
        for (int y = 0; y < column; y++) {
            for (int x = 0; x < row; x++) {
                int tileX = x;
                int tileY = y;
                double drawX = tileX*dw;
                double drawY = tileY*dh;
                int point = scoreBoard[y][x];
                tiles[y][x] = new Tile(
                        drawX,
                        drawY,
                        tileX,
                        tileY,
                        dw,
                        dh,
                        point
                );
            }
        }

        // エージェントの準備
        agents = new ArrayList<>();
        String[] agentNames = {"agentA", "agentB", "agentC", "agentD"};
        for (String name: agentNames) {
            char team;
            int[] position = Parameter.getAgentPos(name);
            int tileX = position[0];
            int tileY = position[1];
            int drawX = tileX*dw;
            int drawY = tileY*dh;

            if (name.equals("agentA") || name.equals("agentB")) {
                team = 'A';
            } else {
                team = 'B';
            }

            agents.add(
                    new Agent(
                        name,
                        team,
                        drawX,
                        drawY,
                        tileX,
                        tileY,
                        30,
                        30
                    )
            );
        }

        // 手番をエージェントAにセットしておく
        Agent.whoseTurn = "agentA";

        // 個々のエージェントの足元にタイルをセットしておく
        for (Agent agent: agents) {
            if (agent.getTeam() == 'A') {
                tiles[agent.getTileY()][agent.getTileX()].setWhoseTile(1);
            } else {
                tiles[agent.getTileY()][agent.getTileX()].setWhoseTile(-1);
            }

        }

        // ターンカウンターの準備
        int maxTurn = Parameter.getMaxTurn();
        turnCounter = new TurnCounter(textFieldOfTurn, maxTurn);
        turnCounter.display();

        // タイマーの準備
        timer = new Timer(textFieldOfTimer);

        // 得点表の準備
        itemOfPoint.setCellValueFactory(new PropertyValueFactory<Point, String>("itemOfPoint"));
        teamAPoint.setCellValueFactory(new PropertyValueFactory<Point, Integer>("teamAPoint"));
        teamBPoint.setCellValueFactory(new PropertyValueFactory<Point, Integer>("teamBPoint"));

        // 座標表の準備
        itemOfPosition.setCellValueFactory(new PropertyValueFactory<Position, String>("itemOfPosition"));
        teamAPosition.setCellValueFactory(new PropertyValueFactory<Position, Integer>("teamAPosition"));
        teamBPosition.setCellValueFactory(new PropertyValueFactory<Position, Integer>("teamBPosition"));

        // 個々のエージェントの座標を取得
        int[] agentAPos = Parameter.getAgentPos("agentA");
        int[] agentBPos = Parameter.getAgentPos("agentB");
        int[] agentCPos = Parameter.getAgentPos("agentC");
        int[] agentDPos = Parameter.getAgentPos("agentD");

        // 個々のエージェントの座標をセット
        positionTable.getItems().add(new Position("エージェントA", agentAPos[0], agentAPos[1]));
        positionTable.getItems().add(new Position("エージェントB", agentBPos[0], agentBPos[1]));
        positionTable.getItems().add(new Position("エージェントC", agentCPos[0], agentCPos[1]));
        positionTable.getItems().add(new Position("エージェントD", agentDPos[0], agentDPos[0]));

        // 折れ線グラフの準備
        turnAxis.setLowerBound(1);
        turnAxis.setUpperBound(turnCounter.getMaxTurn());
        turnAxis.setTickUnit(10);
        xy = new XYChart.Series<>();
        xy.setName("合計ポイントの差");
        lineChartOfAllPoint.getData().add(xy);

        // ゲームのログの準備
        displayerOfLog = new DisplayerOfLog(textAreaOfLog);

        // 最善手の準備
        displayerOfBestAction = new DisplayerOfBestAction(
                textAreaOfBestActionOfTeamA,
                textAreaOfBestActionOfTeamB
        );

        // 最善手のセット
        displayerOfBestAction.setBestActionOfAgentA(new int[]{0, 0});
        displayerOfBestAction.setBestActionOfAgentB(new int[]{0, 0});
        displayerOfBestAction.setBestActionOfAgentC(new int[]{0, 0});
        displayerOfBestAction.setBestActionOfAgentD(new int[]{0, 0});
        displayerOfBestAction.display();

        // キャンバスの準備
        gc = canvas.getGraphicsContext2D();
        gameCanvas = new GameCanvas(gc, canvas.getWidth(), canvas.getHeight(), agents, tiles);

        // サーバーの処理待ち
        try {
            Thread.sleep(500);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        // サーバーに送るための設定データを生成する
        // @param 最大ターン数
        // @param スコアボード
        // @param エージェントAのタイル座標
        // @param エージェントBのタイル座標
        // @param エージェントCのタイル座標
        // @param エージェントDのタイル座標
        CreateGameSetData createGameSetData = new CreateGameSetData(
                maxTurn,
                scoreBoard,
                agentAPos,
                agentBPos,
                agentCPos,
                agentDPos
        );
        String sendDataOfSet = createGameSetData.create();

        // ソケット通信でgui_main.pyに試合設定を送信
        Client.sendData(sendDataOfSet);

        // キャンバスを描画
        gameCanvas.clearCanvas();
        gameCanvas.drawTiles();
        gameCanvas.drawAgents();
    }
}
