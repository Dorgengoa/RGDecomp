#include "types.h"

typedef struct Vec4 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4;

extern f32 D_0047F5B0;
extern f32 D_0047F5B4;
extern f32 D_0047F5B8;
extern f32 D_0047F5BC;
extern s32 D_004826E0;
extern void EffectInstanceGetScale_2dd520(s32, Vec4 *);
extern void ScriptSlotStoreVec3_334790(void *, Vec4 *);

s32 ScriptCmdEffectGetScale_32d490(void *a0, s32 mode)
{
    Vec4 v;
    Vec4 *pv;
    s32 p;

    if (mode != 3) {
        return 0;
    }
    v.x = D_0047F5B0;
    v.y = D_0047F5B4;
    v.z = D_0047F5B8;
    v.w = D_0047F5BC;
    pv = &v;
    p = D_004826E0;
    if (p != 0) {
        EffectInstanceGetScale_2dd520(p, pv);
    }
    ScriptSlotStoreVec3_334790(a0, &v);
    return 1;
}
