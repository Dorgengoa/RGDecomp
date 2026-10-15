#include "types.h"

typedef struct E8_FUN_00242230 {
    s32 a;
    s32 b;
} E8_FUN_00242230;

typedef struct R_FUN_00242230 {
    u8 pad000[0x1C40];
    void *m1C40;
} R_FUN_00242230;

extern void *ScriptGetInt_2490f0(E8_FUN_00242230 *p);
extern R_FUN_00242230 *MesMgrGetSlotWin_24fcc0(void *a);
extern void ScriptSetRefInt_249030(E8_FUN_00242230 *p, void *b);

s32 EvCmdMesWinGetChoiceStart_242230(E8_FUN_00242230 *q)
{
    void *a;
    R_FUN_00242230 *r;

    a = ScriptGetInt_2490f0(q++);
    r = MesMgrGetSlotWin_24fcc0(a);
    if (r == 0) return 0;
    ScriptSetRefInt_249030(q, r->m1C40);
    return 1;
}
