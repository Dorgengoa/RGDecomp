/* rgp:protos */
#define RGP_SELF_OstreamDtor_102fd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* lane N4 family: OstreamDtor_102fd0 / WostreamDtor_103510 / WistreamDtor_1035b0 (152 B each).
   Substitutions: the two vtable symbols, the sub-object vtable, and the
   member offsets (0x4/0x8 vs 0x10/0x18). */

extern u8 D_0046FEC0[];
extern u8 D_0046FECC[];
extern u8 D_0046FEA8[];

extern void IosBaseDtor_102970(void *, s32);
/*rgp*/

void *OstreamDtor_102fd0(u8 *o, s32 n)
{
    u8 *p;
    u8 *q;

    if (o != 0) {
        *(void **)(o + 0x4) = D_0046FEC0;
        p = *(u8 **)o;
        *(void **)p = D_0046FECC;
        q = *(u8 **)o;
        *(s32 *)(q + 0x48) = (s32)(o + 0x8) - (s32)q;
        if (n != 0) {
            if (o + 0x8 != 0) {
                *(void **)(o + 0x8) = D_0046FEA8;
                IosBaseDtor_102970(o + 0x8, 0);
            }
        }
        if ((s16)n > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
