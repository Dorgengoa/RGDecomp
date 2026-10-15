#include "types.h"

typedef struct E8_FUN_00266180 {
    s32 a;
    s32 b;
} E8_FUN_00266180;

typedef struct R_FUN_00266180 {
    u8 pad000[0x1C40];
    void *m1C40;
} R_FUN_00266180;

extern void *ScriptGetInt_26a2a0(E8_FUN_00266180 *p);
extern R_FUN_00266180 *MesMgrGetSlotWin_266af0(void *a);
extern void ScriptSetRefInt_26a1e0(E8_FUN_00266180 *p, void *b);

s32 EvCmdMesWinGetChoiceStart_266180(E8_FUN_00266180 *q)
{
    void *a;
    R_FUN_00266180 *r;

    a = ScriptGetInt_26a2a0(q++);
    r = MesMgrGetSlotWin_266af0(a);
    if (r == 0) return 0;
    ScriptSetRefInt_26a1e0(q, r->m1C40);
    return 1;
}
