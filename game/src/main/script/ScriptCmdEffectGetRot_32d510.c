/* rgp:protos */
#define RGP_SELF_ScriptCmdEffectGetRot_32d510 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Vec4 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4;

extern f32 D_0047F5A0;
extern f32 D_0047F5A4;
extern f32 D_0047F5A8;
extern f32 D_0047F5AC;
extern s32 D_004826E0;
/*rgp*/
/*rgp*/

s32 ScriptCmdEffectGetRot_32d510(void *a0, s32 mode)
{
    Vec4 v __attribute__((aligned(16)));
    Vec4 *pv;
    s32 p;

    if (mode != 3) {
        return 0;
    }
    v.x = D_0047F5A0;
    v.y = D_0047F5A4;
    v.z = D_0047F5A8;
    v.w = D_0047F5AC;
    pv = &v;
    p = D_004826E0;
    if (p != 0) {
        EffectInstanceGetRot_2dd530(p, pv);
    }
    ScriptSlotStoreVec3_334790(a0, &v);
    return 1;
}
