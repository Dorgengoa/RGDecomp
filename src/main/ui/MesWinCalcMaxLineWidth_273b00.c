#include "types.h"
#pragma opt_common_subs off

extern s32 MesWinGetLineWidth_272350(void *, s32);

void MesWinCalcMaxLineWidth_273b00(void *self)
{
    s16 best;
    s32 i;

    i = 0;
    *(s16 *)((u8 *)self + 0x54) = 0;
    do {
        if (MesWinGetLineWidth_272350(self, i) >= 0) {
            best = *(s16 *)((u8 *)self + 0x54);
            if (best < MesWinGetLineWidth_272350(self, i)) {
                *(s16 *)((u8 *)self + 0x54) = MesWinGetLineWidth_272350(self, i);
            }
        }
        i += 1;
    } while (i < 0x14);
}
