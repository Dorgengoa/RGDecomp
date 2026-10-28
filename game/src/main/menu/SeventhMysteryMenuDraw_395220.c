/* rgp:protos */
#define RGP_SELF_SeventhMysteryMenuDraw_395220 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s16 D_00483488 __attribute__((section(".sdata")));
extern u8 D_004E9550[];
/*rgp*/

void SeventhMysteryMenuDraw_395220(void)
{
    s32 v;

    v = D_00483488;
    if (v == 0) {
        return;
    }
    if ((s16)v == 2) {
        UiDrawWidgets_291910(D_004E9550);
    }
}
