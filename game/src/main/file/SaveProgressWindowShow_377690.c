/* rgp:protos */
#define RGP_SELF_SaveProgressWindowShow_377690 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_repositioncode on
/*rgp*/
/*rgp*/
/*rgp*/
extern u16 D_0047FAAC __attribute__((section(".sdata")));
extern s32 D_004831D0;

void SaveProgressWindowShow_377690(s32 arg0, s32 arg1, s32 arg2)
{
    if (D_004831D0 == 0) return;
    if (arg0 == 0) return;
    SaveSetProgressTotal_375a50(D_004831D0, (int)arg1);
    SaveProgressWindowSetVisible_377740(arg0, arg2);
    if (arg2 == 0) return;
    if ((arg1 & 0xFF) == 3) {
        UiSetWidgetPos_290f60(arg0, D_0047FAAC, 0x96, 0x118);
    } else {
        UiSetWidgetPos_290f60(arg0, D_0047FAAC, 0x96, 0x108);
    }
}
