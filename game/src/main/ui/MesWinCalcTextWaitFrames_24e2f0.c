/* rgp:protos */
#define RGP_SELF_MesWinCalcTextWaitFrames_24e2f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

#pragma divbyzerocheck on

/*rgp*/

s32 MesWinCalcTextWaitFrames_24e2f0(int rgp_a0)
{
    s32 r;

    r = MesWinCountLabelChars_24e460((int)rgp_a0);
    if (r < 0x14) return 0x3C;
    return ((r - 0x14) / 5 + 1) * 30 + 0x3C;
}
