#include "types.h"

/* ONE symbol, TWO entries: a `j` TAIL CALL that folds `base + i * 26`
   (sll 1, addu, sll 2, addu, sll 1) into the second argument, then a bounds
   check written as ONE `||` -- op1 threads `daddu $2,$0,$0` into the `bltzl`
   likely slot, op2 threads the payload's `sll` into the `bnel` slot, and the
   shared THEN falls out as the 3-word `daddu / b / nop`. */

void *FUN_00409910_e1(u8 *a, s32 j);

void *RevelationBoardGetCell_409910(u8 *a, s32 i, s32 base)
{
    return FUN_00409910_e1(a, base + i * 26);
}

void *FUN_00409910_e1(u8 *a, s32 j)
{
    if (j < 0 || j >= 0x1D4) return 0;
    return a + j * 4 + 4;
}
