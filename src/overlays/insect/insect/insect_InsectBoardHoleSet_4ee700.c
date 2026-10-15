#include "types.h"
/* insect 0x004EE700 -- 124 bytes.  The same 7x5 byte grid at +0x13B that
 * 0x004EFA70 clears; one flag bit is OR'd in and a six-argument notify
 * follows.  The row stride is 5 (`y*4 + y`), the column index is added last. */
typedef struct Board {
    u8 pad000[0x13B];
    u8 b[7][5];                     /* +0x13B */
} Board;

extern s32  insect_InsectBoardInBounds_4efac0(Board *t, s32 x, s32 y);
extern void insect_InsectBoardTimerSet_4ee320(Board *t, s32 a, s32 x, s32 y, s32 e, s32 f);

void insect_InsectBoardHoleSet_4ee700(Board *t, s32 x, s32 y)
{
    if (insect_InsectBoardInBounds_4efac0(t, x, y) != 0) {
        t->b[y][x] |= 4;
        insect_InsectBoardTimerSet_4ee320(t, 0, x, y, 6, 0);
    }
}
