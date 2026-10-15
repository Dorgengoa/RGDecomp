#include "types.h"

typedef struct E8_FUN_00168590 {
    s32 a;
    s32 b;
} E8_FUN_00168590;

typedef struct R_FUN_00168590 {
    u8 pad000[0x14];
    f32 m14;
    f32 m18;
    f32 m1C;
} R_FUN_00168590;

extern R_FUN_00168590 *DynFixVertexBindFrame_168740(E8_FUN_00168590 *q);
extern f32 VariantGetFloat_15f740(E8_FUN_00168590 *p);

s32 DynFixVertexSCmd_168590(E8_FUN_00168590 *q, s32 n)
{
    R_FUN_00168590 *r;

    r = DynFixVertexBindFrame_168740(q);
    q += 2;
    if (r == 0) return 0;
    if (n >= 3) {
        r->m14 = VariantGetFloat_15f740(q++);
    }
    if (n >= 4) {
        r->m1C = VariantGetFloat_15f740(q);
    }
    r->m18 = -1.0f;
    return 1;
}
