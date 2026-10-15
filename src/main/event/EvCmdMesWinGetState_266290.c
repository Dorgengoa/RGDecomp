#include "types.h"

typedef struct E8 { s32 a; s32 b; } E8;

extern void *ScriptGetInt_26a2a0(E8 *p);
extern void *MesMgrGetSlotWin_266af0(void *a);
extern void *MesWinGetState_276a80(void *a);
extern void ScriptSetRefInt_26a1e0(E8 *p, void *q);

s32 EvCmdMesWinGetState_266290(E8 *p)
{
    void *r;
    void *q;

    r = MesMgrGetSlotWin_266af0(ScriptGetInt_26a2a0(p++));
    if (r == 0) {
        return 0;
    }
    q = MesWinGetState_276a80(r);
    ScriptSetRefInt_26a1e0(p, q);
    return 1;
}
