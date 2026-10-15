#include "types.h"
struct E8 { u8 b[8]; };
extern s32 ScriptGetInt_26a2a0(struct E8 *);
extern s32 MesMgrGetSlotWin_266af0(s32);
extern s32 MesWinLookupMsgThunk_274570(s32, s32);
extern void ScriptSetRefInt_26a1e0(struct E8 *, s32);
s32 EvCmdMesWinLookupMsg_265990(struct E8 *p0, s32 p1)
{
    struct E8 *q;
    s32 r0;
    s32 r1;
    s32 r2;
    s32 r3;

    q = p0;
    if (p1 != 3) {
        return 0;
    }
    r0 = ScriptGetInt_26a2a0(q++);
    r1 = ScriptGetInt_26a2a0(q++);
    r2 = MesMgrGetSlotWin_266af0(r0);
    if (r2 == 0) {
        return 0;
    }
    r3 = MesWinLookupMsgThunk_274570(r2, r1);
    ScriptSetRefInt_26a1e0(q, r3);
    return 1;
}
