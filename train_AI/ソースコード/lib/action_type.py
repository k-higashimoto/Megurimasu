from enum import IntEnum


class ActType(IntEnum):
    """ 動作を選ぶ際のENUM """

    WAIT = 0
    MOVE_RIGHT = 1
    MOVE_BOTTOM_RIGHT = 2
    MOVE_UNDER = 3
    MOVE_BOTTOM_LEFT = 4
    MOVE_LEFT = 5
    MOVE_UPPER_LEFT = 6
    MOVE_UP = 7
    MOVE_UPPER_RIGHT = 8
    TILE_REMOVE = 9