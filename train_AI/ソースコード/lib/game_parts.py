from lib.calculate_point import calcRegionPointOfTeam, calcAllPointOfTeam, calcTilePointOfTeam
from lib.game_start_set import createRandomGameSet
from lib.create_state_data import createStateLogOfJSON
from lib.calculate_tile import calcTeamTile, calcTeamRegion
from lib.action_type import ActType


class MeguriMasuCore:
    # ゲームをカプセル化する

    def __init__(self,
                 settingData=None,
                 additionalFunc=None,
                 initializeFunc=None):

        self.play: Playing  # ゲームの制御
        self.MAX_TURN: int  # ゲームのターン数
        self.state: str = "SET"  # ゲームの状態

        # play の初期化
        if (settingData is not None):
            self.play = Playing(**settingData)

        # settingData が None なら ランダムなデータをセットする
        else:
            self.play = Playing(**createRandomGameSet())

        self.MAX_TURN = self.play.MAX_TURN

        # もし追加動作がある場合は additionalFunc に かく
        if (initializeFunc is not None):
            additionalFunc(self.playData())

    ############################################################################
    def act(self):
        # 　状態を更新

        self.state = "PLAY"

        # ゲームの進行
        while not self.play.isFinishGame():
            # ターンごとの動作を定義

            nowTurn = self.play.nowTurn  # 現在のターン数

            def actNowTurn(agentAction,
                           additionalFunc=None,
                           initializeFunc=None,
                           endFunc=None):
                """
                ターンごとに実行する処理
                @param agentAction エージェントA~Dの行動データ
                """

                # 入力されたエージェントの行動を確認する
                checkedAgentAction = self.play.checkAgentAction(agentAction)
                agentList = self.play.teamA + self.play.teamB

                # エージェントを一人一人行動させる
                for agent in agentList:
                    baseAction = checkedAgentAction[agent.name]["act"]
                    removeAction = checkedAgentAction[agent.name]["rmAct"]

                    agent.baseAction = baseAction
                    agent.removeAction = removeAction


                    self.play.action(agent)

                self.play.turnEnd()

                if (initializeFunc is not None):
                    additionalFunc(self.playData())

            # ターンごとの動作を返す(関数が返る)
            yield actNowTurn

        # 状態を更新
        self.state = "END"

    ############################################################################

    def endAct(self,
               additionalFunc=None,
               endFunc=None):
        """ ゲーム終了時の処理 """
        # TODO: 勝ち負けの判定を返す

        if (endFunc is not None):
            endFunc(self.playData())
            # 　終了動作を返す(関数が返る)

    ############################################################################
    def playData(self) -> dict:

        actionableAction = self.play.getActionableAction()

        d = {
            "field": self.play.scoreBoard,
            "fieldWidth": len(self.play.scoreBoard[0]),
            "filedHeight": len(self.play.scoreBoard),
            "remainingTurn": self.play.turnNumber,
            "nowTurn": self.MAX_TURN - self.play.turnNumber + 1,
            "teamA": {
                "member": [
                    {
                        "name": self.play.teamA[0].name,
                        "x": self.play.teamA[0].x,
                        "y": self.play.teamA[0].y,
                        "tile": self.play.teamA[0].tileCopy,
                        "actionableAction": actionableAction["agentA"]
                    },
                    {
                        "name": self.play.teamA[1].name,
                        "x": self.play.teamA[1].x,
                        "y": self.play.teamA[1].y,
                        "tile": self.play.teamA[1].tileCopy,
                        "actionableAction": actionableAction["agentB"]
                    }
                ],
                "tile": calcTeamTile(self.play.teamA),
                "region": calcTeamRegion(self.play.teamA),
                "onlyTileScore": calcTilePointOfTeam(self.play.teamA, self.play.scoreBoard),
                "onlyRegionScore": calcRegionPointOfTeam(self.play.teamA, self.play.scoreBoard),
                "Score": calcAllPointOfTeam(self.play.teamA, self.play.scoreBoard)
            },
            "teamB": {
                "member": [
                    {
                        "name": self.play.teamB[0].name,
                        "x": self.play.teamB[0].x,
                        "y": self.play.teamB[0].y,
                        "tile": self.play.teamB[0].tileCopy,
                        "actionableAction": actionableAction["agentC"]
                    },
                    {
                        "name": self.play.teamB[1].name,
                        "x": self.play.teamB[1].x,
                        "y": self.play.teamB[1].y,
                        "tile": self.play.teamB[1].tileCopy,
                        "actionableAction": actionableAction["agentD"]
                    }
                ],
                "tile": calcTeamTile(self.play.teamB),
                "region": calcTeamRegion(self.play.teamB),
                "onlyTileScore": calcTilePointOfTeam(self.play.teamB, self.play.scoreBoard),
                "onlyRegionScore": calcRegionPointOfTeam(self.play.teamB, self.play.scoreBoard),
                "Score": calcAllPointOfTeam(self.play.teamB, self.play.scoreBoard)
            }
        }
        return d


class Playing:
    """
    ゲームの進行に携わるクラス
    @param maxTurn 最大ターン数
    @param agentAX エージェントAのX座標
    @param agentAY エージェントAのY座標
    @param agentCX エージェントCのX座標
    @param agentCY エージェントCのY座標
    @param row スコアボードの列数
    @param column　スコアボードの行数
    @param scoreBoard　スコアボード
    """

    ##### 初期化関連  ################################################################
    def __init__(self,
                 maxTurn: int,
                 agentAX: int,
                 agentAY: int,
                 agentBX: int,
                 agentBY: int,
                 row: int,
                 column: int,
                 scoreBoard,
                 ):

        # 最大ターン数を設定
        self.MAX_TURN = maxTurn

        # 現在のターン数を設定
        self.nowTurn = 1

        # スコアボードを設定
        self.scoreBoard = scoreBoard

        # チームAのエージェントリスト

        self.teamA = [Agent("agentA", agentAX, agentAY, row, column),
                      Agent("agentB", agentBX, agentBY, row, column)]
        # チームBのエージェントリスト
        self.teamB = [Agent("agentC", agentAX, agentBY, row, column),
                      Agent("agentD", agentBX, agentAY, row, column)]

        # とりあえずログ、型は要相談
        self.log = []

    ##### 動作関連  #################################################################

    def action(self, agent: object):
        """
        一体ずつactまたはremoveTileを実行
        """

        agent.action(self.teamA, self.teamB)

    ###### 動作判定  ##########################################################################
    def checkAgentAction(self, agentAction: dict) -> dict:
        """
        エージェントの行動を判定する
        @param agentAct エージェントA~Dのそれぞれの行動データ
        @return checkedAgentAction 判定後のエージェントA~Dのそれぞれの行動データ
        """

        checkedAgentAction = agentAction.copy()
        agentList = self.teamA + self.teamB

        # エージェント各々が移動,除去しようと予定している座標
        agentXY = []

        for agent in agentList:

            if agentAction[agent.name]["act"] != ActType.TILE_REMOVE:

                XY = agent._transAct(agentAction[f"{agent.name}"]["act"], agent.x, agent.y)
                # 移動しようと予定しているマスを書き込む
                agentXY.append(XY)

            else:

                XY = agent._transAct(agentAction[f"{agent.name}"]["rmAct"], agent.x, agent.y)
                # 削除しようと予定しているマスを書き込む
                agentXY.append(XY)

        # エージェントごとに正しく動作できるかどうか判定する
        for i, agent in enumerate(agentList):

            act = agentAction[agent.name]["act"]
            rmAct = agentAction[agent.name]["rmAct"]

            # エージェントの動作が移動の場合
            if act != ActType.TILE_REMOVE:

                # このエージェントの移動先が正しくないなら
                if not agent.checkAct(act, self.teamA, self.teamB):
                    checkedAgentAction[agent.name]["act"] = ActType.WAIT

                # 同じタイルに移動しようとしている人がいるなら
                if not agentXY.count(agent._transAct(act, agent.x, agent.y)) < 2:
                    checkedAgentAction[agent.name]["act"] = ActType.WAIT

            # エージェントの動作が削除の場合
            else:

                # そのタイルが除去できないものなら
                if not agent.checkRemoveTile(rmAct, self.teamA, self.teamB):
                    checkedAgentAction[agent.name]["act"] = ActType.WAIT
                    checkedAgentAction[agent.name]["rmAct"] = ActType.WAIT

                # 同じタイルを除去しようとしている人がいたら
                if not agentXY.count(agent._transAct(rmAct, agent.x, agent.y)) < 2:
                    checkedAgentAction[agent.name]["act"] = ActType.WAIT
                    checkedAgentAction[agent.name]["rmAct"] = ActType.WAIT

        return checkedAgentAction

    ###### 終了判定  ##########################################################################

    def isFinishGame(self) -> bool:
        """
        ゲームが終わったかどうか判定
        @return bool 終っていたならTrue 終っていないならFalse
        """

        if self.nowTurn > self.MAX_TURN:
            return True
        else:
            return False

    def judgmentVictory(self):
        """
        チームAとチームBの勝敗を判定する
        @return 勝敗 teamAWin or teamBWin or draw
        """

        allPointOfTeamA = calcAllPointOfTeam(self.teamA, self.scoreBoard)
        allPointOfTeamB = calcAllPointOfTeam(self.teamB, self.scoreBoard)

        if allPointOfTeamA > allPointOfTeamB:
            return "teamAWin"

        elif allPointOfTeamB > allPointOfTeamA:
            return "teamBWin"

        else:
            return "draw"

    ###### ターン終了宣言  ##########################################################################
    def turnEnd(self):

        self.nowTurn += 1

    def logAppend(self):
        """
        ゲームのすべてのデータのログをとる
        """

        self.log.append(createStateLogOfJSON(self))


class Agent:
    """ エージェントのクラス """

    ##### 初期化関連  ################################################################
    def __init__(self,
                 name: str,
                 startX: int,
                 startY: int,
                 row: int,
                 columu: int):
        """
        @param name エージェントの名前
        @param startX 配列上でのX座標
        @param startY 配列上でのY座標
        @param row スコアボードの列数
        @param columu スコアボードの行数
        """

        self._name = name
        self._x: int = startX
        self._y: int = startY

        # このエージェントの置いたタイルの配列

        self.tile  = \
            [[False for _ in range(row)] for i in range(columu)]

        self._baseAction = None  # このエージェントの移動行動
        self._removeAction = None  # このエージェントの削除行動

        # 初期位置にタイルを置く
        self.tile[startY][startX] = True

    ##### property  #################################################################
    @property
    def name(self):
        return self._name

    @property
    def x(self):
        return self._x

    @property
    def y(self):
        return self._y

    @property
    def tileCopy(self):
        """ タイルの配列のコピーを返す　"""

        return self.tile.copy()

    @property
    def baseAction(self):
        return self._baseAction

    @property
    def removeAction(self):
        return self._removeAction

    ##### setter  #################################################################
    @name.setter
    def name(self, name):
        self._name = name

    @x.setter
    def x(self, x):
        self._x = x

    @y.setter
    def y(self, y):
        self._y = y

    @baseAction.setter
    def baseAction(self, baseAction):
        self._baseAction = baseAction

    @removeAction.setter
    def removeAction(self, removeAction):
        self._removeAction = removeAction

    ##### 動作関連  #################################################################
    def action(self, teamA, teamB):
        """
        行動させる関数
        """

        if self.baseAction != ActType.TILE_REMOVE:
            self._moveTile()

        else:
            self._removeTile(teamA, teamB)

    def _moveTile(self):
        """
        タイルを移動する
        """

        # ActTypeから移動後のx, y座標を求め、移動する
        self._x, self._y = self._transAct(self.baseAction, self._x, self._y)

        # 移動先にタイルをセットする
        self.tile[self._y][self._x] = True


    def _removeTile(self, teamA, teamB):
        """
        タイルを削除する
        """

        removeX, removeY = self._transAct(self.removeAction, self._x, self._y)  # ActTypeをx, y座標に変換

        # タイルを削除する
        teamA[0].tile[removeY][removeX] = False
        teamA[1].tile[removeY][removeX] = False
        teamB[0].tile[removeY][removeX] = False
        teamB[1].tile[removeY][removeX] = False


    def _transAct(self, actType: ActType, x: int, y: int) -> tuple:
        """
        ActTypeをx, y座標に変換する
        @param actType ActType
        @param x x座標
        @param y y座標
        @return
        """

        if actType == ActType.WAIT:
            pass
        elif actType == ActType.MOVE_RIGHT:
            x += 1
        elif actType == ActType.MOVE_BOTTOM_RIGHT:
            x += 1
            y += 1
        elif actType == ActType.MOVE_UNDER:
            y += 1
        elif actType == ActType.MOVE_BOTTOM_LEFT:
            x -= 1
            y += 1
        elif actType == ActType.MOVE_LEFT:
            x -= 1
        elif actType == ActType.MOVE_UPPER_LEFT:
            x -= 1
            y -= 1
        elif actType == ActType.MOVE_UP:
            y -= 1
        elif actType == ActType.MOVE_UPPER_RIGHT:
            x += 1
            y -= 1

        return tuple([x, y])


    def checkAct(self, actType: ActType, teamA, teamB) -> bool:
        """ その移動ができるかどうか判定する """

        eTeam = teamA if self in teamB else teamB  # このエージェントに対する敵チーム
        mTeam = teamA if self in teamA else teamB  # このエージェントの所属している自分のチーム
        partner: object = list(filter(lambda x: x.name != self.name, mTeam))[0]  # 自分のチームのもう一人のエージェント（相方)

        checkX, checkY = self._transAct(actType, self._x, self._y)

        # 移動先が配列の範囲外なら移動できない
        if (checkX < 0 or checkY < 0) or (checkX >= len(self.tile[0])) or (checkY >= len(self.tile)):
            return False

        # 移動先に相手チームの人がいるなら移動できない
        if ((checkX, checkY) == (eTeam[0].x, eTeam[0].y)) or ((checkX, checkY) == (eTeam[1].x, eTeam[1].y)):
            return False

        # 移動先に自分チームの人(partner)がいるなら移動できない
        if (checkX, checkY) == (partner.x, partner.y):
            return False

        # 移動先に相手チームのタイルがあるなら移動できない
        if (eTeam[0].tile[checkY][checkX]) or (eTeam[1].tile[checkY][checkX]):
            return False

        return True

    def checkRemoveTile(self, rmAct: ActType, teamA, teamB) -> bool:
        """ そのタイルが削除できるかどうか判定する """

        eTeam = teamA if self in teamB else teamB  # このエージェントに対する敵チーム
        mTeam = teamA if self in teamA else teamB  # このエージェントの所属している自分のチーム
        partner: object = list(filter(lambda x: x.name != self.name, mTeam))[0]  # 自分のチームのもう一人のエージェント（相方)

        removeX, removeY = self._transAct(rmAct, self._x, self._y)

        # 削除先が配列の範囲外なら何もしない
        if (removeX < 0 or removeY < 0) or (removeX >= len(eTeam[0].tile[0])) or (removeY >= len(eTeam[0].tile)):
            return False

        # 削除先に相手チームの人がいるなら何もしない
        if (removeX, removeY) == (eTeam[0].x, eTeam[0].y) or (removeX, removeY) == (eTeam[1].x, eTeam[1].y):
            return False

        # 削除先に相手チームの人がいるなら何もしない
        if (removeX, removeY) == (mTeam[0].x, mTeam[0].y) or (removeX, removeY) == (mTeam[1].x, mTeam[1].y):
            return False

        # 削除先にタイルがないなら
        if (eTeam[0].tile[removeY][removeX] is False) and \
                (eTeam[1].tile[removeY][removeX] is False) and \
                (mTeam[0].tile[removeY][removeX] is False) and \
                (mTeam[1].tile[removeY][removeX] is False):
            return False

        # タイルが削除可能なら
        return True
