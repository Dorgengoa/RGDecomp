/* rgp:protos */
#define RGP_SELF_DynFramePoseLCmd_168130 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct T168130 {
    u8 pad00[0x90];
    s32 m90;
    s32 *m94;
} T168130;

typedef struct O168130 {
    u8 pad00[0xC];
    s32 m0C;
} O168130;

extern T168130 *D_00481154;
/*rgp*/
/*rgp*/

s32 DynFramePoseLCmd_168130(void *p, int rgp_a1)
{
    O168130 *x;
    s32 i;
    s32 r;
    T168130 *t;

    x = ((O168130 *)DynFramePoseParse_1681b0(p, (int)rgp_a1));
    i = VariantGetInt_15f780(p);
    t = D_00481154;
    if (i < 0 || i >= t->m90) {
        r = 0;
    } else {
        r = t->m94[i];
    }
    if (x == 0 || r == 0) {
        return 0;
    }
    x->m0C = 1;
    return 1;
}
