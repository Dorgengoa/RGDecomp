#include "types.h"

typedef struct { s32 a, b; } T_00266770;

extern void *ScriptGetInt_26a2a0(T_00266770 *);
extern void *MesMgrGetSlotWin_266af0(void *);
extern f32 TaggedGetFloat_26a280(T_00266770 *);

s32 EvCmdMesWinSetAnchor_266770(T_00266770 *q)
{
    void *a;
    void *b;

    a = ScriptGetInt_26a2a0(q++);
    b = MesMgrGetSlotWin_266af0(a);
    if (b == 0) return 0;
    *(f32 *)((s32)b + 0x48) = TaggedGetFloat_26a280(q++);
    *(f32 *)((s32)b + 0x4C) = TaggedGetFloat_26a280(q);
    return 1;
}
