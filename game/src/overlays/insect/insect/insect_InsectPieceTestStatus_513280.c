/* rgp:protos */
#define RGP_SELF_insect_InsectPieceTestStatus_513280 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00513280 -- 80 bytes, 20 instructions.  Test one bit of a bitmap.
 * The two out-parameter slots are 4 apart, so they are WORD locals, and the
 * stack allocates them in reverse declaration order (off at 0x2C, bit at
 * 0x28). */

/*rgp*/

s32 insect_InsectPieceTestStatus_513280(u8 *p, s32 k)
{
    s32 off;
    s32 bit;

    if (insect_InsectPieceStatusBitIndex_5133f0(p, k, &off, &bit) != 0) {
        return (1 << bit) & p[off];
    }
    return 0;
}
