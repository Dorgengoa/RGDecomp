/* rgp:protos */
#define RGP_SELF_CompleteCheckMenuDraw_39e850 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s16 D_004836A8 __attribute__((section(".sdata")));
extern u8 D_004E96B0[];
/*rgp*/

void CompleteCheckMenuDraw_39e850(void)
{
    s32 v;

    v = D_004836A8;
    if (v == 0) {
        return;
    }
    if ((s16)v == 2) {
        UiDrawWidgets_291910(D_004E96B0);
    }
}
