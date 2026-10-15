#include "types.h"
/* insect 0x00513210 -- 108 bytes, 27 instructions.  The null guard is NESTED
 * (`beqz $17` straight to the epilogue, void return), and the loop counter's
 * increment is duplicated into the `beql`'s annulled slot. */

extern s32  insect_InsectPieceTestStatus_513280(void *p, s32 k);
extern void insect_InsectPieceSetStatus_5132d0(void *a, s32 i);

void insect_InsectPieceCopyStatus_513210(void *a, void *b)
{
    s32 i;

    if (b != 0) {
        for (i = 0; i < 0x29; i++) {
            if (insect_InsectPieceTestStatus_513280(b, i) != 0) {
                insect_InsectPieceSetStatus_5132d0(a, i);
            }
        }
    }
}
