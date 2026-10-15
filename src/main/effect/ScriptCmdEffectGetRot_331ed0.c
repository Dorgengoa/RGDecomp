#include "types.h"

typedef struct V4 { f32 x, y, z, w; } V4;
extern void EffectInstanceGetRot_2dd530(s32, V4 *);
extern void ScriptSlotStoreVec3_334790(s32, V4 *);
extern void ScriptSlotStoreFloatRef_3347d0(s32, f32);
extern void ScriptSlotGetInt_3348b0(s32);
extern const f32 D_0047F520 __attribute__((section(".sdata")));
extern const f32 D_0047F524 __attribute__((section(".sdata")));
extern const f32 D_0047F528 __attribute__((section(".sdata")));
extern const f32 D_0047F52C __attribute__((section(".sdata")));
extern const s32 D_004826E0 __attribute__((section(".sdata")));

s32 ScriptCmdEffectGetRot_331ed0(s64 *arg0, s32 arg1)
{
    V4 v;
    s32 t;
    V4 *p;

    if (arg1 != 2 && arg1 != 4) {
        return 0;
    }
    ScriptSlotGetInt_3348b0((s32)arg0++);
    t = D_004826E0;
    p = &v;
    v.x = D_0047F520;
    v.y = D_0047F524;
    v.z = D_0047F528;
    v.w = D_0047F52C;
    if (t != 0) {
        EffectInstanceGetRot_2dd530(t, p);
    }
    if (arg1 == 2) {
        ScriptSlotStoreFloatRef_3347d0((s32)arg0, v.y);
    }
    if (arg1 == 4) {
        ScriptSlotStoreVec3_334790((s32)arg0, &v);
    }
    return 1;
}
