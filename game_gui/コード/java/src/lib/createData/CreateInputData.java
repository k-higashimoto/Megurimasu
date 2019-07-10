package lib.createData;

import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.SerializationFeature;
import lib.createData.jsonData.InputDataOfJson;
import lib.gameParts.Agent;

import java.io.IOException;
import java.util.ArrayList;


public class CreateInputData  {

    private ArrayList<Agent> agents;

    public CreateInputData(ArrayList<Agent> agents) {
        this.agents = agents;
    }

    public String create() {
        /**
         * エージェントの入力データを生成する
         * @return inputData エージェントA~Dの入力データ
         */

        InputDataOfJson inputDataOfJson = new InputDataOfJson();
        Agent agentA = agents.get(0);
        Agent agentB = agents.get(1);
        Agent agentC = agents.get(2);
        Agent agentD = agents.get(3);

        inputDataOfJson.actionOfAgentA = agentA.getAction();
        inputDataOfJson.actionOfAgentB = agentB.getAction();
        inputDataOfJson.actionOfAgentC = agentC.getAction();
        inputDataOfJson.actionOfAgentD = agentD.getAction();

        ObjectMapper mapper = new ObjectMapper();
        mapper.enable(SerializationFeature.INDENT_OUTPUT);
        String inputData = "";
        try {
            inputData = mapper.writeValueAsString(inputDataOfJson);
        } catch (IOException e) {
            e.printStackTrace();
        }

        return inputData;
    }
}
