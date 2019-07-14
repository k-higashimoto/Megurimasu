""" ゲームのコンソールに表示する機能をまとめたモジュール """

from lib.game_parts import Playing
from lib.calculate_point import calcAllPointOfTeam
from lib.calculate_tile import calcTeamTile


class CUIOutput:
    
    def __init__(self, play):
        self._play = play
    
    def printGameExplain(self):
        """
        ゲームの説明を表示する
        コマンド説明
        最大ターン数
        チームA
            エージェントの座標
        チームB
            エージェントの座標
        フィールドの状況
    
        @param play Playingクラスのインスタンス
        """
    
        print(f"""[ 巡ります CUIゲーム説明 ]
    
       [ コマンド ]
       \t何もしない: 0
       \t動く(右): 1
       \t動く(右下): 2
       \t動く(下): 3
       \t動く(左下): 4
       \t動く(左): 5
       \t動く(左上): 6
       \t動く(上): 7
       \t動く(右上): 8
       \t削除: 9
    
       [ 初期設定 ]
    
       ターン数: {self._play.MAX_TURN}
    
       チームA:
       \t{self._play.teamA[0].name} (x: {self._play.teamA[0].x}, y: {self._play.teamA[0].y})
       \t{self._play.teamA[1].name} (x: {self._play.teamA[1].x}, y: {self._play.teamA[1].y})
    
       チームB:
       \t{self._play.teamB[0].name} (x: {self._play.teamB[0].x}, y: {self._play.teamB[0].y})
       \t{self._play.teamB[1].name} (x: {self._play.teamB[1].x}, y: {self._play.teamB[1].y})
    
       フィールド :
       [見かた] [ ポイント : タイルの所有権 ] 囲いが < > の場合はエージェントの位置を示す
       """)
    
        self.fieldWatch()
        print("\n - - Let's play " + ("- - " * 20) + "\n")
    
    
    def fieldWatch(self):
        """
        フィールドの状況を表示する
        スコアボード
        エージェントの位置
        タイルの設置状況
        @param play Playingクラスのインスタンス
        """
    
        f = self._play.scoreBoard
        for y in range(len(f) + 1):
            if y == 0:
                for x in range(len(f[0]) + 1):
                    if x == 0:
                        print("", end="\t")
                    else:
                        print(x - 1, end="\t")
                print()
            else:
                for x in range(len(f[y - 1]) + 1):
                    if x == 0:
                        print(f"    {y - 1}", end="\t")
                    else:
                        OK_A = (x - 1, y - 1) in [
                            (self._play.teamA[0].x, self._play.teamA[0].y),
                            (self._play.teamA[1].x, self._play.teamA[1].y)
                        ]
                        OK_B = (x - 1, y - 1) in [
                            (self._play.teamB[0].x, self._play.teamB[0].y),
                            (self._play.teamB[1].x, self._play.teamB[1].y)
                        ]
                        if OK_A or OK_B:
                            if calcTeamTile(self._play.teamA)[y - 1][x - 1]:
                                print(f"<{f[y-1][x-1]}:A>", end="\t")
                            elif calcTeamTile(self._play.teamB)[y - 1][x - 1]:
                                print(f"<{f[y-1][x-1]}:B>", end="\t")
                            else:
                                print(f"<{f[y-1][x-1]}: >", end="\t")
                        else:
                            if calcTeamTile(self._play.teamA)[y - 1][x - 1]:
                                print(f"[{f[y-1][x-1]}:A]", end="\t")
                            elif calcTeamTile(self._play.teamB)[y - 1][x - 1]:
                                print(f"[{f[y-1][x-1]}:B]", end="\t")
                            else:
                                print(f"[{f[y-1][x-1]}: ]", end="\t")
                print()
        print()
    
    
    def printTurnStatus(self):
        """
        現在のターンの状況を表示する
        現在のターン/最大ターン数
    
        チームA
            エージェントAの座標
            エージェントBの座標
    
        チームB
            エージェントCの座標
            エージェントDの座標
    
        フィールド状況
    
        @param play Playingクラスのインスタンス
        @param nowTurn 現在のターン
        @param MAX_TURN 最大ターン数
        """
    
        print(f"""
               {self._play.nowTurn}/{self._play.MAX_TURN} ターン目
    
               チームA:
               \t{self._play.teamA[0].name} (x: {self._play.teamA[0].x}, y: {self._play.teamA[0].y})
               \t{self._play.teamA[1].name} (x: {self._play.teamA[1].x}, y: {self._play.teamA[1].y})
    
               チームB:
               \t{self._play.teamB[0].name} (x: {self._play.teamB[0].x}, y: {self._play.teamB[0].y})
               \t{self._play.teamB[1].name} (x: {self._play.teamB[1].x}, y: {self._play.teamB[1].y})
               """)
        self.fieldWatch()
    
    
    def printGameEndMessage(self):
        """
        ゲーム終了時のメッセージを表示する
        チームA
            合計ポイント
        チームB
            合計ポイント
        フィールド状況
    
        @param play playingクラスのインスタンス
        """
    
        print(f"""
       [ バトル終了 ]
    
       [ スコア ]
       \tteamA: {calcAllPointOfTeam(self._play.teamA, self._play.scoreBoard)}点
       \tteamB: {calcAllPointOfTeam(self._play.teamB, self._play.scoreBoard)}点
    
       [ フィールド ]
    
       """)
        self.fieldWatch()