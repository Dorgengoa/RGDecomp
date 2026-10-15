#include "types.h"

extern s32 ScriptGetInt_26a2a0(s32);
extern s32 MesMgrGetSlotWin_266af0(s32);
extern s32 MesWinIsPageWait_2721f0(s32);
extern void MesWinAdvance_2768f0(s32);

s32 EvCmdMesWinAdvance_2667e0(s32 p0)
{
    s32 r0;
    s32 r1;
    s32 r2;

    r0 = ScriptGetInt_26a2a0(p0);
    r1 = MesMgrGetSlotWin_266af0(r0);
    if (r1 == 0) {
        return 0;
    }
    r2 = MesWinIsPageWait_2721f0(r1);
    if (r2 != 0) goto ok;
    return 1;
ok:
    MesWinAdvance_2768f0(r1);
    return 1;
}
