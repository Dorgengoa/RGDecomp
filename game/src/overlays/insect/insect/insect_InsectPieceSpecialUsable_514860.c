/* rgp:protos */
#define RGP_SELF_insect_InsectPieceSpecialUsable_514860 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00514860 -- 136 bytes, 34 instructions, 2 calls. */

typedef struct Obj {
    u8 pad00[0x38];
    s8 f38;                         /* +0x38 */
    u8 pad39[0x4F - 0x39];
    s8 f4F;                         /* +0x4F */
} Obj;

/*rgp*/

s32 insect_InsectPieceSpecialUsable_514860(Obj *o)
{
    if (o->f4F <= 0) {
        return 0;
    }
    if (o->f38 == 0x11) {
        if (insect_InsectPieceTestStatus_513280(o, 0x19) != 0) {
            return 0;
        }
    }
    if (o->f38 == 0xC) {
        if (insect_InsectPieceTestStatus_513280(o, 0x18) != 0) {
            return 0;
        }
    }
    return 1;
}
