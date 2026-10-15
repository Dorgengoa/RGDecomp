#include "types.h"

typedef struct T1680b0 {
    u8 pad00[0x90];
    s32 m90;
    s32 *m94;
} T1680b0;

typedef struct O1680b0 {
    u8 pad00[0xC];
    s32 m0C;
} O1680b0;

extern T1680b0 *D_00481154;
extern O1680b0 *DynFramePoseParse_1681b0(void *p);
extern s32 VariantGetInt_15f780(void *p);

s32 DynFramePoseCmd_1680b0(void *p)
{
    O1680b0 *x;
    s32 i;
    s32 r;
    T1680b0 *t;

    x = DynFramePoseParse_1681b0(p);
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
