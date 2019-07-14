package application;

import javafx.scene.control.*;
import lib.analysis.AnalysisQRText;
import lib.crap.ArrayElementTF;
import lib.createData.CreateGameSetData;
import javafx.stage.FileChooser;
import lib.formChecker.GameFormChecker;
import lib.readQR.QRReader;
import lib.socketCommunication.Client;
import lib.setting.CreateRandomSB;
import lib.setting.Parameter;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;

public class GameSetController implements Initializable {

    @FXML private TextArea textAreaOfQRText;
    @FXML private Slider sliderOfMaxTurn;
    @FXML private TextField textFieldOfScoreBoardColumn;
    @FXML private TextField textFieldOfScoreBoardRow;
    @FXML private TextArea textAreaOfScoreBoard;
    @FXML private Spinner spinnerOfAgentAX, spinnerOfAgentAY;
    @FXML private Spinner spinnerOfAgentBX, spinnerOfAgentBY;


    @FXML
    protected void onReadQRButton(ActionEvent event) {
        /**
         * QR読み込みボタンが押されたとき実行
         */

        // QRコードの画像ファイルを選択させる
        FileChooser fileChooser = new FileChooser();
        fileChooser.setTitle("QRコードの選択");
        File QRFile = fileChooser.showOpenDialog(null);

        // 何も選択されなければ何もしない
        if (QRFile == null) {
            return;
        }

        // 選択されたファイルを画像に変換
        BufferedImage QRImage = null;
        try {
            QRImage = ImageIO.read(QRFile) ;
        } catch (IOException e) {
            e.printStackTrace();
        }

        // QRコードを読み込む
        QRReader qrReader = new QRReader(QRImage);

        // QRコードの文字列を取得する
        String QRText = qrReader.readQR();

        // QRコードの文字列をセットする
        textAreaOfQRText.setText(QRText);
    }

    @FXML
    protected void onAnalysisQRButton(ActionEvent event) {
        /**
         * QR適用ボタンが押されたとき実行
         */

        // QRコードテキストから試合設定を解析
        String qrText = textAreaOfQRText.getText();
        AnalysisQRText analysisQRText = new AnalysisQRText(qrText);
        analysisQRText.analysis();

        // スコアボードの取得
        int[][] scoreBoard = analysisQRText.getScoreBoard();
        int column = analysisQRText.getScoreBoardSize()[0];
        int row = analysisQRText.getScoreBoardSize()[1];

        String scoreBoardText = "";
        for (int y = 0; y < column; y++) {
            for (int x = 0; x < row; x++) {
                scoreBoardText += scoreBoard[y][x];

                if (x != row-1) {
                    scoreBoardText += ",";
                }
            }
            scoreBoardText += "\n";
        }
        // スコアボードの行数をセット
        textFieldOfScoreBoardColumn.setText(Integer.toString(column));

        // スコアボードの列数をセット
        textFieldOfScoreBoardRow.setText(Integer.toString(row));

        // スコアボードをセット
        textAreaOfScoreBoard.setText(scoreBoardText);

        // エージェントAとBの座標を取得
        int agentAX = analysisQRText.getAgentAPos()[0];
        int agentAY = analysisQRText.getAgentAPos()[1];
        int agentBX = analysisQRText.getAgentBPos()[0];
        int agentBY = analysisQRText.getAgentBPos()[1];

        // エージェントAとBの座標をセット
        spinnerOfAgentAX.getValueFactory().setValue(agentAX);
        spinnerOfAgentAY.getValueFactory().setValue(agentAY);
        spinnerOfAgentBX.getValueFactory().setValue(agentBX);
        spinnerOfAgentBY.getValueFactory().setValue(agentBY);
    }

    @FXML
    protected void onCreateRandomScoreBoardButton(ActionEvent event) {
        /**
         * スコアボードランダム生成ボタンが押されたとき実行
         */

        // ランダムなスコアボードを生成する
        int[][] scoreBoard = CreateRandomSB.createScoreBoard();

        int row = scoreBoard[0].length;
        int column = scoreBoard.length;

        String scoreBoardText = "";
        for (int y = 0; y < column; y++) {
            for (int x = 0; x < row; x++) {
                scoreBoardText += scoreBoard[y][x];

                if (x != row-1) {
                    scoreBoardText += ",";
                }
            }
            scoreBoardText += "\n";
        }

        // スコアボードの行数をセットする
        textFieldOfScoreBoardColumn.setText(Integer.toString(column));

        // スコアボードの列数をセットする
        textFieldOfScoreBoardRow.setText(Integer.toString(row));

        // スコアボードをセットする
        textAreaOfScoreBoard.setText(scoreBoardText);
    }

    @FXML
    protected void onNextButton(ActionEvent event) {
        /**
         * 決定ボタンが押されたとき実行
         */

        GameFormChecker gameFormChecker = new GameFormChecker(
                textFieldOfScoreBoardColumn,
                textFieldOfScoreBoardRow,
                textAreaOfScoreBoard,
                spinnerOfAgentAX,
                spinnerOfAgentAY,
                spinnerOfAgentBX,
                spinnerOfAgentBY
        );

        // 入力された設定が正しくなければ、再入力を促す
        if (!gameFormChecker.checkAll()) {
            return;
        }

        // スコアボードの読み込み
        String scoreBoardText = textAreaOfScoreBoard.getText();
        int row = Integer.parseInt(textFieldOfScoreBoardRow.getText());
        int column = Integer.parseInt(textFieldOfScoreBoardColumn.getText());
        int[][] scoreBoard = new int[column][row];
        for (int y = 0; y < column; y++) {
            for (int x = 0; x < row; x++) {
                String[] columns = scoreBoardText.split("\n");
                int[] rows = ArrayElementTF.toIntFromStr(columns[y].split(","));
                scoreBoard[y][x] = rows[x];
            }
        }

        // ターン数の読み込み
        int maxTurn = (int) sliderOfMaxTurn.getValue();

        // 座標の読み込み
        int agentAX = (int) spinnerOfAgentAX.getValueFactory().getValue();
        int agentAY = (int) spinnerOfAgentAY.getValueFactory().getValue();
        int agentBX = (int) spinnerOfAgentBX.getValueFactory().getValue();
        int agentBY = (int) spinnerOfAgentBY.getValueFactory().getValue();

        int[] agentAPos = {agentAX, agentAY};
        int[] agentBPos = {agentBX, agentBY};
        int[] agentCPos = {agentAPos[0], agentBPos[1]};
        int[] agentDPos = {agentBPos[0], agentAPos[1]};

        // 次のコントローラーに値を渡すためにパラメーターに値をセット
        Parameter.setParameter(
                maxTurn,
                scoreBoard,
                agentAPos,
                agentBPos,
                agentCPos,
                agentDPos
        );

        // ゲーム画面に遷移
        Stage stage = (Stage) textAreaOfQRText.getScene().getWindow();
        stage.hide();

        Parent parent = null;
        try {
            parent = FXMLLoader.load(getClass().getResource("game.fxml"));
        } catch (IOException e) {
            e.printStackTrace();
        }

        if (parent == null) {
            return;
        }
        stage.setScene(new Scene(parent));
        stage.setMaximized(true);
        stage.setResizable(false);
        stage.show();
    }

    @Override
    public void initialize(URL location, ResourceBundle resources) {
        SpinnerValueFactory<Integer> valueFactorOfAgentAX = //
                new SpinnerValueFactory.IntegerSpinnerValueFactory(0, 11, 1);
        SpinnerValueFactory<Integer> valueFactorOfAgentAY = //
                new SpinnerValueFactory.IntegerSpinnerValueFactory(0, 11, 1);
        SpinnerValueFactory<Integer> valueFactorOfAgentBX = //
                new SpinnerValueFactory.IntegerSpinnerValueFactory(0, 11, 5);
        SpinnerValueFactory<Integer> valueFactorOfAgentBY = //
                new SpinnerValueFactory.IntegerSpinnerValueFactory(0, 11, 5);

        spinnerOfAgentAX.setValueFactory(valueFactorOfAgentAX);
        spinnerOfAgentAY.setValueFactory(valueFactorOfAgentAY);
        spinnerOfAgentBX.setValueFactory(valueFactorOfAgentBX);
        spinnerOfAgentBY.setValueFactory(valueFactorOfAgentBY);
    }
}
