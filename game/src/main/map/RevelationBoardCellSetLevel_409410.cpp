#include "types.h"

typedef struct Cell {
    u8 m0;
    u8 b0 : 1;
    u8 lvl : 4;
    u8 rest : 3;
} Cell;

extern "C" {
extern Cell *RevelationBoardGetCell_409910(s32, s32, s32);
extern void RevelationBoardCellSetOpenDir_4099f0(Cell *, s32, bool);
}

extern "C" s32 RevelationBoardCellSetLevel_409410(s32 map, s32 x, s32 y, s32 lvl)
{
    Cell *c;
    bool f;
    Cell *n0;
    Cell *n1;
    Cell *n2;
    Cell *n3;
    Cell *n4;
    Cell *n5;
    Cell *n6;
    Cell *n7;

    c = RevelationBoardGetCell_409910(map, x, y);
    if (c == 0) {
        return 0;
    }
    if (c->lvl >= lvl) {
        return 0;
    }
    f = true;
    c->lvl = lvl;
    if (lvl < 11) {
        f = false;
    }
    n0 = RevelationBoardGetCell_409910(map, x - 1, y - 1);
    n1 = RevelationBoardGetCell_409910(map, x - 1, y);
    n2 = RevelationBoardGetCell_409910(map, x - 1, y + 1);
    n3 = RevelationBoardGetCell_409910(map, x, y - 1);
    n4 = RevelationBoardGetCell_409910(map, x, y + 1);
    n5 = RevelationBoardGetCell_409910(map, x + 1, y - 1);
    n6 = RevelationBoardGetCell_409910(map, x + 1, y);
    n7 = RevelationBoardGetCell_409910(map, x + 1, y + 1);
    if (n0 != 0) {
        RevelationBoardCellSetOpenDir_4099f0(n0, 7, f);
    }
    if (n1 != 0) {
        RevelationBoardCellSetOpenDir_4099f0(n1, 5, f);
        RevelationBoardCellSetOpenDir_4099f0(n1, 6, f);
        RevelationBoardCellSetOpenDir_4099f0(n1, 7, f);
    }
    if (n2 != 0) {
        RevelationBoardCellSetOpenDir_4099f0(n2, 5, f);
    }
    if (n3 != 0) {
        RevelationBoardCellSetOpenDir_4099f0(n3, 2, f);
        RevelationBoardCellSetOpenDir_4099f0(n3, 4, f);
        RevelationBoardCellSetOpenDir_4099f0(n3, 7, f);
    }
    if (n4 != 0) {
        RevelationBoardCellSetOpenDir_4099f0(n4, 0, f);
        RevelationBoardCellSetOpenDir_4099f0(n4, 3, f);
        RevelationBoardCellSetOpenDir_4099f0(n4, 5, f);
    }
    if (n5 != 0) {
        RevelationBoardCellSetOpenDir_4099f0(n5, 2, f);
    }
    if (n6 != 0) {
        RevelationBoardCellSetOpenDir_4099f0(n6, 0, f);
        RevelationBoardCellSetOpenDir_4099f0(n6, 1, f);
        RevelationBoardCellSetOpenDir_4099f0(n6, 2, f);
    }
    if (n7 != 0) {
        RevelationBoardCellSetOpenDir_4099f0(n7, 0, f);
    }
    return 1;
}
