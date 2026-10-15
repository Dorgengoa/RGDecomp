#include "types.h"

typedef struct S8_00242500 {
    s32 a;
    s32 b;
} S8_00242500;

extern s32 ScriptGetInt_2490f0(S8_00242500 *p);
extern void *MesMgrGetSlotWin_24fcc0(s32 a);
extern void MesWinSetNumVar0_2769c0(void *h, s32 b);
extern void MesWinSetNumVar_2769a0(void *h, s32 b, s32 c, s32 d);

s32 EvCmdMesWinSetNumVar_242500(S8_00242500 *a0)
{
    S8_00242500 *p;
    void *h;
    s32 v1;
    s32 v2;

    p = a0;
    h = MesMgrGetSlotWin_24fcc0(ScriptGetInt_2490f0(p++));
    if (h == 0) {
        return 0;
    }
    v1 = ScriptGetInt_2490f0(p++);
    v2 = ScriptGetInt_2490f0(p);
    if (v1 == 0) {
        MesWinSetNumVar0_2769c0(h, v2);
    } else {
        MesWinSetNumVar_2769a0(h, v1 - 1, v2, 0);
    }
    return 1;
}
