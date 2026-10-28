/* rgp:protos */
#define RGP_SELF_TextEntryPaletteTextStyleDrawCb_432ac0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void *D_00484104;
/*rgp*/

s32 TextEntryPaletteTextStyleDrawCb_432ac0(s32 a, s32 b, s32 c, s32 d, s32 e)
{
    if (D_00484104 != 0) TextEntryPaletteTextStyle_433490(D_00484104, a, b, c, d, e);
    return 1;
}
