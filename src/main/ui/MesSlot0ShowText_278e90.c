#include "types.h"

extern void *GetMesMgr_277e90(void *a);
extern void *MesMgrGetSlot_277a20(void *a, s32 b);
extern void  MesWinInit_276f20(void *o);
extern void  MesWinSetMode_276e00(void *o, s32 v);
extern void  MesWinSetSeEnabled_272b50(void *o, s32 v);
extern void  MesWinSetKind_276c80(void *o, s32 v);
extern void  MesWinSetNameShown_271390(void *o, s32 v);
extern void  MesWinSetName_271300(void *o, s32 v);
extern void  MesWinSetTextWithEnd_2726c0(void *o, s32 a, s32 b);
extern void  MesWinShowMsg_272950(void *o, s32 v);
extern void  MesSlotSetCloseTimer_277d20(void *h, s32 v);

void MesSlot0ShowText_278e90(s32 a0, s32 a1, s32 a2, f32 x, f32 y)
{
    void *h;
    u8 *o;

    h = MesMgrGetSlot_277a20(GetMesMgr_277e90((void *)a0), 0);
    if (h == 0) {
        return;
    }
    o = *(u8 **)((u8 *)h + 4);
    if (o == 0) {
        return;
    }
    MesWinInit_276f20(o);
    MesWinSetMode_276e00(o, 0);
    MesWinSetSeEnabled_272b50(o, 0);
    MesWinSetKind_276c80(o, 1);
    if (0.0f <= x) {
        *(f32 *)(o + 0x48) = x;
    }
    if (0.0f <= y) {
        *(f32 *)(o + 0x4C) = y;
    }
    if (a1 != 0) {
        MesWinSetNameShown_271390(o, 1);
        MesWinSetName_271300(o, a1);
    } else {
        MesWinSetNameShown_271390(o, 0);
    }
    MesWinSetTextWithEnd_2726c0(o, a0, 0);
    MesWinShowMsg_272950(o, -1);
    MesSlotSetCloseTimer_277d20(h, a2);
}
