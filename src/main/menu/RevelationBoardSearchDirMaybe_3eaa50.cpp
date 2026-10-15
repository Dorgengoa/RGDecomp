#pragma opt_loop_invariants off
#include "types.h"

typedef struct {
    u8 a;
    u8 pad : 1;
    u8 v : 4;
    u8 rest : 3;
    u8 c;
    u8 d;
} Cell;

extern "C" Cell *RevelationBoardGetCells_3eb510(void);

extern "C" s32 RevelationBoardSearchDirMaybe_3eaa50(s32 pd0, s32 pd1, s32 x, s32 y, s32 dir, s32 lo, s32 hi) {
    Cell *grid;
    s32 bestY;
    s32 bestX;
    s32 ax;
    s32 ay;
    s32 px;
    s32 py;
    s32 ring;
    bool found;
    s32 r;
    s32 s;
    s32 nx;
    s32 ny;
    u8 v;

    grid = RevelationBoardGetCells_3eb510();
    if (grid == 0) {
        return -1;
    }
    bestY = y;
    bestX = x;
    ax = 0;
    ay = 0;
    px = 0;
    py = 0;
    switch (dir) {
    case 0:
        py = ax = -1;
        break;
    case 1:
        px = ay = -1;
        break;
    case 2:
        ay = 1;
        px = -1;
        break;
    case 3:
        ax = 1;
        py = -1;
        break;
    }
    if (ax != 0 || ay != 0) {
        ring = 1;
        for (;;) {
            x += ax;
            y += ay;
            if (x < 0 || x >= 18 || y < 0 || y >= 26) {
                break;
            }
            v = grid[x * 26 + y].v;
            if (v >= lo && v <= hi) {
                bestX = x;
                bestY = y;
                break;
            }
            found = 0;
            for (r = 1; r <= ring; r++) {
                for (s = 1; s >= -1; s -= 2) {
                    nx = x + r * (px * s);
                    ny = y + r * (py * s);
                    if (nx < 0 || nx >= 18 || ny < 0 || ny >= 26) {
                        break;
                    }
                    v = grid[nx * 26 + ny].v;
                    if (v >= lo && v <= hi) {
                        bestX = nx;
                        bestY = ny;
                        found = 1;
                        break;
                    }
                }
                if (found) {
                    break;
                }
            }
            if (found) {
                break;
            }
            ring++;
        }
    }
    return bestX * 26 + bestY;
}
