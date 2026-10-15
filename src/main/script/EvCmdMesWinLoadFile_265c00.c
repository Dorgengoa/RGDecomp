#include "types.h"

extern s32 MesWinLoadFile_265cf0(s32, s32, s32, s32);
extern s32 MesMgrGetSlotWin_266af0(s32);
extern s32 ScriptGetCodeAddr_26a200(s32);
extern s32 ScriptGetInt_26a2a0(s32);
extern void MesWinSetTextFile_274e50(s32, s32, s32);

s32 EvCmdMesWinLoadFile_265c00(s64 *arg0, s32 arg1) {
    s32 temp_20;
    s32 temp_2;
    s32 var_16;
    s32 var_20;
    s32 var_2;

    var_20 = 0;
    temp_2 = MesMgrGetSlotWin_266af0(ScriptGetInt_26a2a0((s32)arg0++));
    var_20++;
    if (temp_2 == 0) {
        return 0;
    }
    var_16 = 0;
    if (*(s32 *)arg0 == 0) {
        var_16 = ScriptGetInt_26a2a0((s32)arg0++);
        var_20++;
        if (var_16 < 0) {
            MesWinSetTextFile_274e50(temp_2, 0, 0);
            return 1;
        }
    }
    temp_20 = ScriptGetCodeAddr_26a200((s32)arg0++);
    var_2 = 0;
    if (var_20 + 1 < arg1) {
        var_2 = ScriptGetCodeAddr_26a200((s32)arg0);
    }
    return MesWinLoadFile_265cf0(var_2, temp_20, temp_2, var_16);
}
