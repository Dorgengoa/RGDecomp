#include "types.h"

extern s32 MesMgrGetSlotWin_266af0(s32);
extern void ScriptSetRefInt_26a1e0(s32, s32);
extern s32 ScriptGetInt_26a2a0(s32);
extern s32 MesWinGetState_276a80(s32);

s32 EvCmdMesWinIsClosed_2664e0(s64 *arg0) {
    s32 temp_2;

    temp_2 = MesMgrGetSlotWin_266af0(ScriptGetInt_26a2a0((s32)arg0++));
    if (temp_2 == 0) {
        return 0;
    }
    ScriptSetRefInt_26a1e0((s32)arg0, MesWinGetState_276a80(temp_2) == 0);
    return 1;
}
