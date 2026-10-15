#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Rec {
    u8 pad0000[0x1DEE];
    u8 m1DEE;
} Rec;

extern s32  ScriptGetInt_26a2a0(R8 *p);
extern Rec *MesMgrGetSlotWin_266af0(s32 v);

s32 EvCmdMesWinSetPageIcon_266600(R8 *q)
{
    Rec *r;

    r = MesMgrGetSlotWin_266af0(ScriptGetInt_26a2a0(q++));
    if (r == 0) {
        return 0;
    }
    r->m1DEE = (u8)ScriptGetInt_26a2a0(q);
    return 1;
}
