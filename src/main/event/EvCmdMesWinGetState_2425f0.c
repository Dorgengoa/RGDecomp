#include "types.h"

typedef struct E8 { s32 a; s32 b; } E8;

extern void *ScriptGetInt_2490f0(E8 *p);
extern void *MesMgrGetSlotWin_24fcc0(void *a);
extern void *MesWinGetState_276a80(void *a);
extern void ScriptSetRefInt_249030(E8 *p, void *q);

s32 EvCmdMesWinGetState_2425f0(E8 *p)
{
    void *r;
    void *q;

    r = MesMgrGetSlotWin_24fcc0(ScriptGetInt_2490f0(p++));
    if (r == 0) {
        return 0;
    }
    q = MesWinGetState_276a80(r);
    ScriptSetRefInt_249030(p, q);
    return 1;
}
