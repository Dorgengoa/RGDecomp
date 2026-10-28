/* rgp:protos */
#define RGP_SELF_insect_InsectFormationDecodeCell_4effa0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004EFFA0 -- 25 instructions.  The packed byte is read TWICE (the
 * two `lbu 0x0($9)` share only the address register): the intervening stores
 * through the out-pointers stop mwcc CSEing the load -- insect-load-across-
 * store.  The `-0x81` constant is `~0x80` at int width, so the masked
 * expression must be the promoted `u8` and not a narrowed local. */

void insect_InsectFormationDecodeCell_4effa0(u8 *base, s32 off, s32 *outA, s32 *outB, s32 mode)
{
    s32 bias;

    *outA = base[off] & ~0x80;
    *outB = 5;
    bias = 0;
    if ((base[off] & 0x80) != 0) {
        bias = 1;
    }
    if (mode == 1) {
        *outB = 1;
        *outA = 4 - *outA;
        bias = -bias;
    }
    *outB = *outB + bias;
}
