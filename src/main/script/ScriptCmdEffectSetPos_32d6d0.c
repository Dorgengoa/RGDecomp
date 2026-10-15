#include "types.h"

typedef struct { f32 x, y, z, w; } V_0032d6d0;

extern f32 D_0047F580, D_0047F584, D_0047F588, D_0047F58C;
extern void *D_004826E0;
extern void ScriptSlotsToVec4_334810(V_0032d6d0 *, void *);
extern void EffectInstanceSetPos_2dd570(void *, V_0032d6d0 *);

s32 ScriptCmdEffectSetPos_32d6d0(void *p, s32 mode)
{
    V_0032d6d0 v;

    if (mode != 3) return 0;
    v.x = D_0047F580;
    v.y = D_0047F584;
    v.z = D_0047F588;
    v.w = D_0047F58C;
    ScriptSlotsToVec4_334810(&v, p);
    if (D_004826E0 == 0) return 0;
    EffectInstanceSetPos_2dd570(D_004826E0, &v);
    return 1;
}
