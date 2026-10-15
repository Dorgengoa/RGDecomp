#include "types.h"

#pragma divbyzerocheck on

extern s32 MesWinCountLabelChars_24e460(void);

s32 MesWinCalcTextWaitFrames_24e2f0(void)
{
    s32 r;

    r = MesWinCountLabelChars_24e460();
    if (r < 0x14) return 0x3C;
    return ((r - 0x14) / 5 + 1) * 30 + 0x3C;
}
