/* rgp:protos */
#define RGP_SELF_DynFixVertexCCmd_168620 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E8_FUN_00168620 {
    s32 a;
    s32 b;
} E8_FUN_00168620;

typedef struct R_FUN_00168620 {
    u8 pad000[0x14];
    f32 m14;
    f32 m18;
    f32 m1C;
} R_FUN_00168620;

/*rgp*/
/*rgp*/

s32 DynFixVertexCCmd_168620(E8_FUN_00168620 *q, s32 n)
{
    R_FUN_00168620 *r;

    r = ((R_FUN_00168620 *)DynFixVertexBindFrame_168740(q));
    q += 2;
    if (r == 0) return 0;
    if (n >= 3) {
        r->m14 = VariantGetFloat_15f740(q++);
    }
    if (n >= 4) {
        r->m1C = VariantGetFloat_15f740(q);
    }
    r->m18 = 1.0f;
    return 1;
}
