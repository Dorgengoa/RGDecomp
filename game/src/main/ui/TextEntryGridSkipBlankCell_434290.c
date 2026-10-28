/* rgp:protos */
#define RGP_SELF_TextEntryGridSkipBlankCell_434290 1
#include "port/game_protos.h"
#line 1
#include "types.h"

#pragma divbyzerocheck on

typedef struct {
    u8 pad0[0x10];
    s16 x;
    s16 y;
} Cur;

typedef struct {
    s16 x;
    s16 y;
} Pos;

/*rgp*/

s32 TextEntryGridSkipBlankCell_434290(s32 arg0, Cur *p, s8 *grid, Pos *prev)
{
    s16 y;
    s16 x;
    s16 idx;
    s8 c;
    s16 r;

    y = p->y;
    x = p->x;
    idx = x + y * 29;
    c = grid[idx];
    if (c == '_' || c == '.') {
        if (prev->x != x) {
            r = TextEntryGridFindValidCellMaybe_433e90(arg0, grid, idx, 0, x - prev->x);
            p->x = r % 29;
            p->y = r / 29;
            y = p->y;
            idx = p->x + y * 29;
        }
        if (prev->y != y) {
            r = TextEntryGridFindValidCellMaybe_433e90(arg0, grid, idx, 1, (s16)(y - prev->y) * 29);
            p->x = r % 29;
            p->y = r / 29;
        }
    }
    prev->x = p->x;
    prev->y = p->y;
    return 0;
}
