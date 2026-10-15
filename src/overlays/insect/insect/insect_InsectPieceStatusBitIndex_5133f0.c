#include "types.h"
/* insect 0x005133F0 -- 56 bytes, 14 instructions.  Splits a signed count into
 * a /8 quotient and a %8 remainder through two out-parameters; both divisions
 * are the branch-and-bias shift idiom, no `div` and so no zero trap.  $4 is an
 * UNUSED first parameter.  The return re-READS the quotient through its
 * pointer (`lw $2, 0x0($6)`), it does not reuse the register. */

s32 insect_InsectPieceStatusBitIndex_5133f0(s32 unused, s32 n, s32 *q, s32 *r)
{
    *q = n / 8;
    *r = n % 8;
    return *q < 0x10;
}
