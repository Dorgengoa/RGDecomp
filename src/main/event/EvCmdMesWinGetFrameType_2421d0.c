#include "types.h"

extern void *ScriptGetInt_2490f0(void *a);
extern void *MesMgrGetSlotWin_24fcc0(void *a);
extern void *MesWinGetFrameTypeThunk_272b20(void *a);
extern void ScriptSetRefInt_249030(void *a, void *b);

s32 EvCmdMesWinGetFrameType_2421d0(void *a0)
{
    void *q;
    void *x;
    void *y;

    q = a0;
    a0 = (u8 *)a0 + 8;
    x = ScriptGetInt_2490f0(q);
    y = MesMgrGetSlotWin_24fcc0(x);
    if (y == 0) {
        return 0;
    }
    ScriptSetRefInt_249030(a0, MesWinGetFrameTypeThunk_272b20(y));
    return 1;
}
