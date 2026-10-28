/* rgp:protos */
#define RGP_SELF_ScriptStrTableGet_2ccd90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* A null check on a small-data pointer in front of the asymmetric guard pair.
   Three separate `return 0` blocks: the null one fills its own `b` delay slot,
   the bounds one does not -- the shared-label predecessor effect only reaches
   the two guards that share `none:`. */

extern s32 *D_004825DC;

s32 ScriptStrTableGet_2ccd90(s32 index)
{
    s32 *base;
    u8 ok;

    base = D_004825DC;
    if (base == 0) {
        return 0;
    }
    if (index < 0) {
        goto none;
    }
    ok = index < 0xC;
    if (ok != 0) {
        goto found;
    }
none:
    return 0;
found:
    return base[index];
}
