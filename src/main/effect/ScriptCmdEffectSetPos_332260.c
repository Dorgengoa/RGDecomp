#include "types.h"

typedef struct Vec4 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4;

typedef struct E8 { u8 b[0x8]; } E8;

extern f32 D_0047F4E0;
extern f32 D_0047F4E4;
extern f32 D_0047F4E8;
extern f32 D_0047F4EC;
extern void *D_004826E0;
extern void ScriptSlotGetInt_3348b0(E8 *);
extern void ScriptSlotsToVec4_334810(Vec4 *, E8 *);
extern void EffectInstanceSetPos_2dd570(void *, Vec4 *);

s32 ScriptCmdEffectSetPos_332260(E8 *a0, s32 mode)
{
    Vec4 v;
    E8 *q;
    void *p;

    q = a0;
    if (mode != 4) {
        return 0;
    }
    ScriptSlotGetInt_3348b0(q++);
    v.x = D_0047F4E0;
    v.y = D_0047F4E4;
    v.z = D_0047F4E8;
    v.w = D_0047F4EC;
    ScriptSlotsToVec4_334810(&v, q);
    p = D_004826E0;
    if (p == 0) {
        return 0;
    }
    EffectInstanceSetPos_2dd570(p, &v);
    return 1;
}
