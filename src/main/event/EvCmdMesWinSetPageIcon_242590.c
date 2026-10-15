#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Rec {
    u8 pad0000[0x1DEE];
    u8 m1DEE;
} Rec;

extern s32  ScriptGetInt_2490f0(R8 *p);
extern Rec *MesMgrGetSlotWin_24fcc0(s32 v);

s32 EvCmdMesWinSetPageIcon_242590(R8 *q)
{
    Rec *r;

    r = MesMgrGetSlotWin_24fcc0(ScriptGetInt_2490f0(q++));
    if (r == 0) {
        return 0;
    }
    r->m1DEE = (u8)ScriptGetInt_2490f0(q);
    return 1;
}
