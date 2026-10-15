#include "types.h"

#pragma divbyzerocheck on

extern s32 MesWinCountLabelChars_24e460(void);

s32 MesWinCalcCharWaitFrames_24e270(void)
{
    s32 n;
    s32 t;

    n = MesWinCountLabelChars_24e460();
    if (n == 0) {
        n = 1;
    }
    if (n < 0x14) {
        t = 0x3C;
    } else {
        t = (((n - 0x14) / 5 + 1) * 15) * 2 + 0x3C;
    }
    return t / n;
}
