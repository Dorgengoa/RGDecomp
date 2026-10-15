#include "types.h"
/* insect 0x005132D0 -- 28 instructions.  The two out-parameters live at
 * 0x2C and 0x28 of the frame and stack locals are laid out in REVERSE
 * declaration order, so the byte offset is declared first and the bit index
 * second.  The `andi 0xFF` before the `or` is the `(u8)` on the shifted bit.
 */

extern s32 insect_InsectPieceClearStatus_513340(void);
extern s32 insect_InsectPieceStatusBitIndex_5133f0(u8 *p, s32 k, s32 *off, s32 *bit);

s32 insect_InsectPieceSetStatus_5132d0(u8 *p, s32 k)
{
    s32 off;
    s32 bit;

    if (k == 0x29) {
        return insect_InsectPieceClearStatus_513340();
    }
    if (insect_InsectPieceStatusBitIndex_5133f0(p, k, &off, &bit) != 0) {
        p[off] |= (u8)(1 << bit);
        return 1;
    }
    return 0;
}
