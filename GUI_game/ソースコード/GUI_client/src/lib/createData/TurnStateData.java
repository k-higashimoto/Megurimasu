package lib.createData;

import lib.crap.ArrayElementTF;

public class TurnStateData {

    private int[][] tilePlaceState;
    private int[] tilePoint;
    private int[] regionPoint;
    private int[] allPoint;
    private int[] agentAPos;
    private int[] agentBPos;
    private int[] agentCPos;
    private int[] agentDPos;

    public TurnStateData(int[] tilePoint,
                         int[] regionPoint,
                         int[] allPoint,
                         int[] agentAPos,
                         int[] agentBPos,
                         int[] agentCPos,
                         int[] agentDPos,
                         int[][] tilePlaceState) {

        this.tilePoint = tilePoint;
        this.regionPoint = regionPoint;
        this.allPoint = allPoint;
        this.agentAPos = agentAPos;
        this.agentBPos = agentBPos;
        this.agentCPos = agentCPos;
        this.agentDPos = agentDPos;
        this.tilePlaceState = tilePlaceState;
    }

    public int[][] getTilePlaceState() {
        return tilePlaceState;
    }

    public int[] getAllPoint() {
        return allPoint;
    }

    public int[] getAgentDPos() {
        return agentDPos;
    }

    public int[] getAgentCPos() {
        return agentCPos;
    }

    public int[] getAgentBPos() {
        return agentBPos;
    }

    public int[] getAgentAPos() {
        return agentAPos;
    }

    public int[] getRegionPoint() {
        return regionPoint;
    }

    public int[] getTilePoint() {
        return tilePoint;
    }
}
