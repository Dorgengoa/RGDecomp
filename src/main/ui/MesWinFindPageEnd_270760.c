#include "types.h"

extern s32 MesWinGetCharCode_274dd0(s32, s32);

s32 MesWinFindPageEnd_270760(s32 arg0, s32 arg1) {
    s32 var_17;
    s32 var_16;

    var_17 = 0;
    var_16 = 0;
    while (var_16 < 0x300) {
        if (((MesWinGetCharCode_274dd0(arg0, var_16) == 0) ||
             ((MesWinGetCharCode_274dd0(arg0, var_16) & 0xFFFF) == 0xFF01) ||
             ((MesWinGetCharCode_274dd0(arg0, var_16) & 0xFFFF) == 0xFF03)) &&
            (var_17 == arg1)) {
            return var_16 - 1;
        }
        if ((MesWinGetCharCode_274dd0(arg0, var_16) & 0xFFFF) == 0xFF03) {
            var_17 += 1;
        }
        var_16 += 1;
    }
    return -1;
}
