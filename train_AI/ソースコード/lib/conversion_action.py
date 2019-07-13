""" CUIのアクションとGUIのアクションを変換するためのモジュール"""
from lib.action_type import ActType


def conversioActionToGUIFromCUI(actionOfEachAgentForCUI):
    """
    CUIのアクションからGUIのアクションに変換する関数
    @param actionOfEachAgentForCUI
    @return actionOfEachAgentForGUI
    """

    actionOfEachAgentForGUI = {
        "agentA": {
            "direction": 0,
            "do": 0,
        },
        "agentB": {
            "direction": 0,
            "do": 0,
        },
        "agentC": {
            "direction": 0,
            "do": 0,
        },
        "agentD": {
            "direction": 0,
            "do": 0,
        }
    }

    for agentName in actionOfEachAgentForCUI.keys():
        baseAction = actionOfEachAgentForCUI[agentName]["act"]
        removeAction = actionOfEachAgentForCUI[agentName]["rmAct"]
        direction = 0
        do = 0

        if baseAction != ActType.TILE_REMOVE:
            direction = int(baseAction)
            do = 0
        else:
            direction = int(removeAction)
            do = 1

        actionOfEachAgentForGUI[agentName]["direction"] = direction
        actionOfEachAgentForGUI[agentName]["do"] = do

    return actionOfEachAgentForGUI


def conversioActionToCUIFromGUI(actionOfEachAgentForGUI):
    """
    GUIのアクションからCUIのアクションに変換する関数
    @param actionOfEachAgentForCUI
    @return actionOfEachAgentForGUI
    """

    actionOfEachAgentForCUI = {
        "agentA": {
            "act": ActType.WAIT,
            "rmAct": ActType.WAIT,
        },
        "agentB": {
            "act": ActType.WAIT,
            "rmAct": ActType.WAIT,
        },
        "agentC": {
            "act": ActType.WAIT,
            "rmAct": ActType.WAIT,
        },
        "agentD": {
            "act": ActType.WAIT,
            "rmAct": ActType.WAIT,
        }
    }

    for agentName in actionOfEachAgentForGUI.keys():
        direction = actionOfEachAgentForGUI[agentName]["direction"]
        do = actionOfEachAgentForGUI[agentName]["do"]
        baseAction = ActType.WAIT
        removeAction = ActType.WAIT

        if do == 1:
            baseAction = ActType.TILE_REMOVE
            removeAction = ActType(direction)
        else:
            baseAction = ActType(direction)
            removeAction = ActType.WAIT

        actionOfEachAgentForCUI[agentName]["act"] = baseAction
        actionOfEachAgentForCUI[agentName]["rmAct"] = removeAction

    return actionOfEachAgentForCUI