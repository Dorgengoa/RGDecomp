#include "types.h"
/* insect 0x004EF830 -- 148 bytes, 37 instructions, 1 call, 2 conditional
 * branches.  The two coordinates arrive in 32-bit registers and are narrowed
 * by `dsll32/dsra32 ..,16`, i.e. s32 parameters with EXPLICIT (s16) casts
 * ([[normal-s16-cast-sign-extension]]).  The address arithmetic is
 * row*20 + col*4 -- a `s32 [][5]` grid.  $4 is never rewritten before the
 * `jal`, so the grid pointer is the callee's first argument too.
 */

extern s32 insect_InsectBoardGetPiece_4ee9a0(s32 (*g)[5], s32 col, s32 row);

s32 insect_InsectBoardPlacePiece_4ef830(s32 (*g)[5], s32 v, s32 col, s32 row)
{
    if (v == 0) {
        return -1;
    }
    if (insect_InsectBoardGetPiece_4ee9a0(g, col, row) == 0) {
        g[(s16)row][(s16)col] = v;
        return 6;
    }
    return 3;
}
