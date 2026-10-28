/* rgp:protos */
#define RGP_SELF_ScriptFnOptionsSetTacticsMode_3d68b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

extern struct Obj0 * D_00483960;
extern s32 D_00483964;

struct Obj0;

struct Obj0 {
    u8 pad000[0xC];
    s32 m0C;
};

void ScriptFnOptionsSetTacticsMode_3d68b0(s32 p0, s32 p1, s32 p2, s32 p3)
{
    s32 r1;
    s32 v;

    if (p0 != 0) {
        VariantSetS32_36f040(p0, 0, 1);
        if (D_00483960 != 0) {
            if (D_00483964 != 0) goto k1;
        }
    }
    return;
k1:
    if (p3 != 0) {
        if (p2 > 0) goto ok;
    }
    return;
ok:
    r1 = ((short)VariantGetS16_36fcc0(p3));
    OptionsSetTacticsMode_3d5f50(D_00483960->m0C, (s16)r1);
    v = 1;
    VariantSetS32_36f040(p0, v, v);
}
