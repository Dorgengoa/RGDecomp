#include "types.h"
/* insect 0x00513340 -- 124 bytes, 31 instructions, 2 calls, 2 conditional
 * branches.  The lookup takes FOUR arguments -- $4 and $5 are never rewritten
 * before the `jal`, so this function's own two parameters are passed through
 * ahead of the two out-parameter addresses.  The explicit `andi 0xFF` on the
 * complement is a `(u8)` cast in the source.  The `return 0` is the TRAILING
 * block, not an early return: only then does mwcc branch straight to the
 * epilogue with `daddu $2,$0,$0` in the delay slot instead of spending a
 * separate `b` (measured: the early-return spelling is one word long).
 */

extern void insect_InsectPieceClearAllStatus_5133c0(void);
extern s32  insect_InsectPieceStatusBitIndex_5133f0(u8 *p, s32 t, s32 *off, s32 *bit);

s32 insect_InsectPieceClearStatus_513340(u8 *p, s32 t)
{
    s32 off;
    s32 bit;

    off = 0;
    bit = 0;
    if (t == 0x29) {
        insect_InsectPieceClearAllStatus_5133c0();
        return 1;
    }
    if (insect_InsectPieceStatusBitIndex_5133f0(p, t, &off, &bit) != 0) {
        p[off] &= (u8)~(1 << bit);
        return 1;
    }
    return 0;
}
