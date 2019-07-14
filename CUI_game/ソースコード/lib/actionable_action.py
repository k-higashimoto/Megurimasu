from lib.action_type import ActType


def getActionableBaseAction(play) -> dict:
    """
    行動可能な基本行動を返す
    @return actionableMoveAction エージェントA~Dの行動可能な移動行動
    """

    agentList = play.teamA + play.teamB
    actionableBaseAction = {"agentA": [], "agentB": [], "agentC": [], "agentD": []}

    for act in range(10):

        # エージェントごとに正しく動作できるかどうか判定する
        for i, agent in enumerate(agentList):

            # このエージェントの移動先は正しいか
            if agent.checkAct(act, play.teamA, play.teamB):
                actionableBaseAction[agent.name].append(act)

    return actionableBaseAction


def getActionableRemoveAction(play) -> dict:
    """
    行動可能な削除行動を返す
    @return actionableMoveAction エージェントA~Dの行動可能な削除行動
    """

    agentList = play.teamA + play.teamB
    actionableRemoveAction = {"agentA": [], "agentB": [], "agentC": [], "agentD": []}

    for rmAct in range(1, 9):

        # エージェントごとに正しく動作できるかどうか判定する
        for i, agent in enumerate(agentList):

            # このエージェントは正しくタイル除去ができるかどうか
            if agent.checkRemoveTile(rmAct, play.teamA, play.teamB):
                actionableRemoveAction[agent.name].append(rmAct)

    return actionableRemoveAction


def getActionableAction(play) -> dict:
    """
    エージェント行動可能な行動を返す
    @return actionableAction エージェントA~Dの行動可能な行動
    """

    actionableAction = {"agentA": [], "agentB": [], "agentC": [], "agentD": []}
    baseActions = getActionableBaseAction(play)
    removeActions = getActionableRemoveAction(play)

    for agentName in actionableAction.keys():

        action = []

        for baseAction in baseActions[agentName]:

            if ActType(int(baseAction)) != ActType.TILE_REMOVE:

                action.append([baseAction, None])

            else:

                for removeAction in removeActions[agentName]:
                    action.append([baseAction, removeAction])

        actionableAction[agentName] = action

    return actionableAction


def getActionableActionForGUI(play) -> dict:
    """
    GUI向けの行動可能な行動を返す
    @return actionableAction エージェントA~Dの行動可能な行動
    """

    actionableAction = {"agentA": [], "agentB": [], "agentC": [], "agentD": []}
    baseActions = getActionableBaseAction(play)
    removeActions = getActionableRemoveAction(play)

    for agentName in actionableAction.keys():

        action = []

        for baseAction in baseActions[agentName]:

            if ActType(int(baseAction)) != ActType.TILE_REMOVE:

                action.append([baseAction, 0])

            else:

                for removeAction in removeActions[agentName]:
                    action.append([removeAction, 0])


        actionableAction[agentName] = action

    return actionableAction