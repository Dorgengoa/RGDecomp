#include "types.h"
/* insect 0x00512BF0 -- 132 bytes, 33 instructions.
 * `% 100` by a constant is a real `div` with no trap, so no
 * `#pragma divbyzerocheck` is needed.  The tail is `slt` + `xori 1`, i.e. the
 * two-return-constants fold of [[ixa03 lever 3]] written as a value.
 */

extern s32 insect_InsectPieceTestStatus_513280(void *, s32);
extern s32 func_133710(void);

s32 insect_InsectPieceRollVsResist_512bf0(void *o, s32 a, s32 b)
{
    if (insect_InsectPieceTestStatus_513280(o, 0xD) != 0) {
        return 0;
    }
    if (b >= 0x2710) {
        return 1;
    }
    return (func_133710() % 100) >= (a - ((b - 1) * 10));
}
