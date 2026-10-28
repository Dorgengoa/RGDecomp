/* rgp:protos */
#define RGP_SELF_ScriptCmdEffectSetScale_3320b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Vec4 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4;

typedef struct E8 { u8 b[0x8]; } E8;

extern f32 D_0047F4F0;
extern f32 D_0047F4F4;
extern f32 D_0047F4F8;
extern f32 D_0047F4FC;
extern void *D_004826E0;
/*rgp*/
/*rgp*/
/*rgp*/

s32 ScriptCmdEffectSetScale_3320b0(E8 *a0, s32 mode)
{
    Vec4 v __attribute__((aligned(16)));
    E8 *q;
    void *p;

    q = a0;
    if (mode != 4) {
        return 0;
    }
    ScriptSlotGetInt_3348b0(q++);
    v.x = D_0047F4F0;
    v.y = D_0047F4F4;
    v.z = D_0047F4F8;
    v.w = D_0047F4FC;
    ScriptSlotsToVec4_334810(&v, q);
    p = D_004826E0;
    if (p == 0) {
        return 0;
    }
    EffectInstanceSetScale_2dd550(p, &v);
    return 1;
}
