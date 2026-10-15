#include "types.h"
typedef struct { s32 a, b; } E8_266380;
extern s32 ScriptGetInt_26a2a0(E8_266380 *);
extern s32 MesMgrGetSlotWin_266af0(s32);
extern void MesWinSetItemSlot_2769d0(s32, s32, s32);

s32 EvCmdMesWinSetItemSlot_266380(E8_266380 *p0)
{
    s32 a;
    s32 b;
    s32 c;
    s32 h;

    a = ScriptGetInt_26a2a0(p0++);
    h = MesMgrGetSlotWin_266af0(a);
    if (h == 0) {
        return 0;
    }
    b = ScriptGetInt_26a2a0(p0++);
    c = ScriptGetInt_26a2a0(p0);
    MesWinSetItemSlot_2769d0(h, b - 1, c);
    return 1;
}
