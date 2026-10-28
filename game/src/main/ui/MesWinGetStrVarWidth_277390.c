/* rgp:protos */
#define RGP_SELF_MesWinGetStrVarWidth_277390 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 MesWinGetStrVarWidth_277390(u8 *p, s32 i)
{
    if (i < 0) {
        return -1;
    }
    if (i >= 0x10) {
        return -1;
    }
    return FontMeasureStringWidth_2773d0(p, p + i * 32 + 0x195D);
}
