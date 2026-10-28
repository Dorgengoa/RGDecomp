/* rgp:protos */
#define RGP_SELF_StateVarSet_3cc9c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void *D_004838C0;
/*rgp*/

s32 StateVarSet_3cc9c0(u8 *p, s32 i, s16 v, s32 flag)
{
    s16 *e;
    s16 old;
    s32 off;

    if (i < 0 || i >= 0x80) return 0;
    off = i * 2;
    e = (s16 *)(off + (s32)p + 0x128);
    old = *e;
    *e = v;
    if (D_004838C0 != 0) {
        if (flag == 0) {
            WorldOnStateVarChanged_3eda10(D_004838C0, i, v, old);
        }
    }
    return 1;
}
