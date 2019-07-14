package lib.analysis;

import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import lib.crap.ArrayElementTF;
import lib.crap.ListElementTF;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Iterator;
import java.util.List;
import java.util.regex.Pattern;

public class AnalysisTurnState {

    private String turnStateData;
    private String phase;
    private int nowTurn;
    private int tilePointOfTeamA, tilePointOfTeamB;
    private int regionPointOfTeamA, regionPointOfTeamB;
    private int allPointOfTeamA, allPointOfTeamB;
    private int[] agentAPos = new int[2];
    private int[] agentBPos = new int[2];
    private int[] agentCPos = new int[2];
    private int[] agentDPos = new int[2];
    private int[][] actionableActionOfAgentA;
    private int[][] actionableActionOfAgentB;
    private int[][] actionableActionOfAgentC;
    private int[][] actionableActionOfAgentD;
    private int[] bestActionOfAgentA = new int[2];
    private int[] bestActionOfAgentB = new int[2];
    private int[] bestActionOfAgentC = new int[2];
    private int[] bestActionOfAgentD = new int[2];
    private int[][] tilePlaceState;

    public AnalysisTurnState(String turnStateData) {
        this.turnStateData = turnStateData;
    }

    public void analysis() {
        ObjectMapper mapper = new ObjectMapper();
        try {
            JsonNode node = mapper.readTree(turnStateData);

            // 現在のフェーズの解析
            phase = node.get("phase").asText();

            // 現在のターンの解析
            nowTurn = node.get("nowTurn").asInt();

            // チームAの得点の解析
            tilePointOfTeamA = node.get("teamA").get("tilePoint").asInt();
            regionPointOfTeamA = node.get("teamA").get("regionPoint").asInt();
            allPointOfTeamA = node.get("teamA").get("allPoint").asInt();

            // チームBの得点の解析
            tilePointOfTeamB = node.get("teamB").get("tilePoint").asInt();
            regionPointOfTeamB = node.get("teamB").get("regionPoint").asInt();
            allPointOfTeamB = node.get("teamB").get("allPoint").asInt();

            JsonNode nodeOfAgentA = node.get("teamA").get("agentA");
            JsonNode nodeOfAgentB = node.get("teamA").get("agentB");
            JsonNode nodeOfAgentC = node.get("teamB").get("agentC");
            JsonNode nodeOfAgentD = node.get("teamB").get("agentD");

            // 個々のエージェントのタイル座標の解析
            agentAPos[0] = nodeOfAgentA.get("tileX").asInt();
            agentAPos[1] = nodeOfAgentA.get("tileY").asInt();
            agentBPos[0] = nodeOfAgentB.get("tileX").asInt();
            agentBPos[1] = nodeOfAgentB.get("tileY").asInt();
            agentCPos[0] = nodeOfAgentC.get("tileX").asInt();
            agentCPos[1] = nodeOfAgentC.get("tileY").asInt();
            agentDPos[0] = nodeOfAgentD.get("tileX").asInt();
            agentDPos[1] = nodeOfAgentD.get("tileY").asInt();
            
            // 個々のエージェントの行動可能基本行動の解析
            int actionableActionOfAgentAColumn = nodeOfAgentA.get("actionableBaseAction").size();
            int actionableActionOfAgentARow = nodeOfAgentA.get("actionableBaseAction").get(0).size();
            actionableActionOfAgentA = new int[actionableActionOfAgentAColumn][actionableActionOfAgentARow];
            for (int y = 0; y < actionableActionOfAgentAColumn; y++) {
                for (int x = 0; x < actionableActionOfAgentARow; x++) {
                    actionableActionOfAgentA[y][x] =
                            nodeOfAgentA.get("actionableBaseAction").get(y).get(x).asInt();
                }
            }

            int actionableActionOfAgentBColumn = nodeOfAgentB.get("actionableBaseAction").size();
            int actionableActionOfAgentBRow = nodeOfAgentB.get("actionableBaseAction").get(0).size();
            actionableActionOfAgentB = new int[actionableActionOfAgentBColumn][actionableActionOfAgentBRow];
            for (int y = 0; y < actionableActionOfAgentBColumn; y++) {
                for (int x = 0; x < actionableActionOfAgentBRow; x++) {
                    actionableActionOfAgentB[y][x] =
                            nodeOfAgentB.get("actionableBaseAction").get(y).get(x).asInt();
                }
            }

            int actionableActionOfAgentCColumn = nodeOfAgentC.get("actionableBaseAction").size();
            int actionableActionOfAgentCRow = nodeOfAgentC.get("actionableBaseAction").get(0).size();
            actionableActionOfAgentC = new int[actionableActionOfAgentCColumn][actionableActionOfAgentCRow];
            for (int y = 0; y < actionableActionOfAgentCColumn; y++) {
                for (int x = 0; x < actionableActionOfAgentCRow; x++) {
                    actionableActionOfAgentC[y][x] =
                            nodeOfAgentC.get("actionableBaseAction").get(y).get(x).asInt();
                }
            }

            int actionableActionOfAgentDColumn = nodeOfAgentD.get("actionableBaseAction").size();
            int actionableActionOfAgentDRow = nodeOfAgentD.get("actionableBaseAction").get(0).size();
            actionableActionOfAgentD = new int[actionableActionOfAgentDColumn][actionableActionOfAgentDRow];
            for (int y = 0; y < actionableActionOfAgentDColumn; y++) {
                for (int x = 0; x < actionableActionOfAgentDRow; x++) {
                    actionableActionOfAgentD[y][x] =
                            nodeOfAgentD.get("actionableBaseAction").get(y).get(x).asInt();
                }
            }

            // 個々のエージェントの最善手の解析
            bestActionOfAgentA[0] = nodeOfAgentA.get("bestAction").get(0).asInt();
            bestActionOfAgentA[1] = nodeOfAgentA.get("bestAction").get(1).asInt();
            bestActionOfAgentB[0] = nodeOfAgentB.get("bestAction").get(0).asInt();
            bestActionOfAgentB[1] = nodeOfAgentB.get("bestAction").get(1).asInt();
            bestActionOfAgentC[0] = nodeOfAgentC.get("bestAction").get(0).asInt();
            bestActionOfAgentC[1] = nodeOfAgentC.get("bestAction").get(1).asInt();
            bestActionOfAgentD[0] = nodeOfAgentD.get("bestAction").get(0).asInt();
            bestActionOfAgentD[1] = nodeOfAgentD.get("bestAction").get(1).asInt();

            // タイル設置状況配列を解析
            int column = node.get("tilePlaceState").size();
            int row = node.get("tilePlaceState").get(0).size();
            tilePlaceState = new int[column][row];
            for (int y = 0; y <column; y++) {
                for (int x = 0; x < row; x++) {
                    tilePlaceState[y][x] = node.get("tilePlaceState").get(y).get(x).asInt();
                }
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public int[] getAgentAPos() {
        return agentAPos;
    }

    public int[] getAgentBPos() {
        return agentBPos;
    }

    public int[] getAgentCPos() {
        return agentCPos;
    }

    public int[] getAgentDPos() {
        return agentDPos;
    }

    public int[][] getTilePlaceState() {
        return tilePlaceState;
    }

    public int getTilePointOfTeamA() {
        return tilePointOfTeamA;
    }

    public int getTilePointOfTeamB() {
        return tilePointOfTeamB;
    }

    public int getRegionPointOfTeamA() {
        return regionPointOfTeamA;
    }

    public int getRegionPointOfTeamB() {
        return regionPointOfTeamB;
    }

    public int getAllPointOfTeamB() {
        return allPointOfTeamB;
    }

    public int getAllPointOfTeamA() {
        return allPointOfTeamA;
    }

    public int[][] getActionableActionOfAgentA() {
        return actionableActionOfAgentA;
    }

    public int[][] getActionableActionOfAgentB() {
        return actionableActionOfAgentB;
    }

    public int[][] getActionableActionOfAgentC() {
        return actionableActionOfAgentC;
    }

    public int[][] getActionableActionOfAgentD() {
        return actionableActionOfAgentD;
    }

    public int[] getBestActionOfAgentA() {
        return bestActionOfAgentA;
    }

    public int[] getBestActionOfAgentB() {
        return bestActionOfAgentB;
    }

    public int[] getBestActionOfAgentC() {
        return bestActionOfAgentC;
    }

    public int[] getBestActionOfAgentD() {
        return bestActionOfAgentD;
    }

    public int getNowTurn() {
        return nowTurn;
    }

    public String getPhase() {
        return phase;
    }
}
