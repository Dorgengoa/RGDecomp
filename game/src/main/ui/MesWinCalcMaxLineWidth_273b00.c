/* rgp:protos */
#define RGP_SELF_MesWinCalcMaxLineWidth_273b00 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_common_subs off

/*rgp*/

void MesWinCalcMaxLineWidth_273b00(void *self)
{
    s16 best;
    s32 i;

    i = 0;
    *(s16 *)((u8 *)self + 0x54) = 0;
    do {
        if (((short)MesWinGetLineWidth_272350(self, i)) >= 0) {
            best = *(s16 *)((u8 *)self + 0x54);
            if (best < ((short)MesWinGetLineWidth_272350(self, i))) {
                *(s16 *)((u8 *)self + 0x54) = ((short)MesWinGetLineWidth_272350(self, i));
            }
        }
        i += 1;
    } while (i < 0x14);
}
