#include "types.h"

typedef struct { s32 a, b; } T_00332030;
typedef struct { f32 x, y, z, w; } V_00332030;

extern f32 D_0047F500, D_0047F504, D_0047F508, D_0047F50C;
extern void *D_004826E0;
extern void ScriptSlotGetInt_3348b0(T_00332030 *);
extern void EffectInstanceGetPos_2dd540(void *, V_00332030 *);
extern void ScriptSlotStoreVec3_334790(T_00332030 *, V_00332030 *);

s32 ScriptCmdEffectGetPos_332030(T_00332030 *q, s32 mode)
{
    V_00332030 v;
    V_00332030 *pv;
    void *g;

    if (mode != 4) return 0;
    ScriptSlotGetInt_3348b0(q++);
    v.x = D_0047F500;
    v.y = D_0047F504;
    v.z = D_0047F508;
    v.w = D_0047F50C;
    g = D_004826E0;
    pv = &v;
    if (g != 0) {
        EffectInstanceGetPos_2dd540(g, pv);
    }
    ScriptSlotStoreVec3_334790(q, &v);
    return 1;
}
