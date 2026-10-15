#include "types.h"
/* insect 0x00514C90 -- 8 B / 2 words.  `j insect_InsectPieceSetStatus_5132d0` with
 * `addiu $5, $0, 0x1C` in the delay slot.  005132D0 returns nothing (its
 * epilogue leaves $2 alone on the 0x29 arm), so this wrapper is void too. */

extern void insect_InsectPieceSetStatus_5132d0(void *e, s32 k);

void insect_InsectPieceSetActed_514c90(void *e)
{
    insect_InsectPieceSetStatus_5132d0(e, 0x1C);
}
