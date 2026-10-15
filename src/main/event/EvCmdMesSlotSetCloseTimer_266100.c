#include "types.h"
struct E8 { u8 b[8]; };
extern s32 GetMesMgr_277e90(void);
extern s32 ScriptGetInt_26a2a0(struct E8 *);
extern s32 MesMgrGetSlot_277a20(s32, s32);
extern void MesSlotSetCloseTimer_277d20(s32, s32);
s32 EvCmdMesSlotSetCloseTimer_266100(struct E8 *p0, s32 p1)
{
    struct E8 *q;
    s32 r0;
    s32 r1;
    s32 r2;
    s32 r3;

    q = p0;
    if (p1 != 2) {
        return 0;
    }
    r0 = GetMesMgr_277e90();
    r1 = ScriptGetInt_26a2a0(q++);
    r2 = MesMgrGetSlot_277a20(r0, r1);
    r3 = ScriptGetInt_26a2a0(q);
    MesSlotSetCloseTimer_277d20(r2, r3);
    return 1;
}
