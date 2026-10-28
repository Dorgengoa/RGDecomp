/* rgp:protos */
#define RGP_SELF_MesWinCalcCharWaitFrames_24e270 1
#include "port/game_protos.h"
#line 1
#include "types.h"

#pragma divbyzerocheck on

/*rgp*/

s32 MesWinCalcCharWaitFrames_24e270(int rgp_a0)
{
    s32 n;
    s32 t;

    n = MesWinCountLabelChars_24e460((int)rgp_a0);
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
