package lib.createData;

import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.SerializationFeature;
import lib.createData.jsonData.GameSetDataOfJson;

import java.io.IOException;

public class CreateGameSetData {
    /**
     * 試合設定データを生成するクラス
     */

    private int maxTurn;
    private int[][] scoreBoard;
    private int[] agentAPos, agentBPos, agentCPos, agentDPos;

    public CreateGameSetData(int maxTurn,
                             int[][] scoreBoard,
                             int[] agentAPos,
                             int[] agentBPos,
                             int[] agentCPos,
                             int[] agentDPos) {

        this.maxTurn = maxTurn;
        this.scoreBoard = scoreBoard;
        this.agentAPos = agentAPos;
        this.agentBPos = agentBPos;
        this.agentCPos = agentCPos;
        this.agentDPos = agentDPos;
    }

    public String create() {
        /**
         * 試合設定データを生成する
         * return gameSetData 試合設定データ
         */

        GameSetDataOfJson gameSetDataOfJson = new GameSetDataOfJson();
        gameSetDataOfJson.maxTurn = maxTurn;
        gameSetDataOfJson.scoreBoard = scoreBoard;
        gameSetDataOfJson.agentAPos = agentAPos;
        gameSetDataOfJson.agentBPos = agentBPos;
        gameSetDataOfJson.agentCPos = agentCPos;
        gameSetDataOfJson.agentDPos = agentDPos;

        ObjectMapper mapper = new ObjectMapper();
        mapper.enable(SerializationFeature.INDENT_OUTPUT);
        String gameSetData = "";
        try {
            gameSetData = mapper.writeValueAsString(gameSetDataOfJson);
        } catch (IOException e) {
            e.printStackTrace();
        }

        return gameSetData;
    }
}
