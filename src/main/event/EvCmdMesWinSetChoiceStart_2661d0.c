#include "types.h"

struct Obj {
    u8 pad000[0x1C40];
    s32 m460;
};

extern void *ScriptGetInt_26a2a0(void *a);
extern struct Obj *MesMgrGetSlotWin_266af0(void *a);

s32 EvCmdMesWinSetChoiceStart_2661d0(void *a0)
{
    void *q;
    struct Obj *o;

    q = a0;
    a0 = (u8 *)a0 + 8;
    o = MesMgrGetSlotWin_266af0(ScriptGetInt_26a2a0(q));
    if (o == 0) {
        return 0;
    }
    o->m460 = (s32)ScriptGetInt_26a2a0(a0);
    return 1;
}
