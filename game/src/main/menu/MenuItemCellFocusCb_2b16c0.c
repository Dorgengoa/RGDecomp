/* rgp:protos */
#define RGP_SELF_MenuItemCellFocusCb_2b16c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_common_subs off

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void *D_00482374;
extern u8 D_004DB430[0x400];

typedef struct { u8 pad[0x10]; s16 x10; s16 x12; } O2B16;
#pragma opt_common_subs on
s32 MenuItemCellFocusCb_2b16c0(O2B16 *arg0) {
    u8 sp30[0x10] __attribute__((aligned(16)));
    s32 temp_16;
    s32 temp_17;

    UiSelFrameSetGridCell_28db00(&(*(u8 *)D_004DB430), 0x78, arg0->x10, arg0->x12, 0x62, 0x49);
    temp_16 = MenuGetItemAtCell_2a7000(*(s8 *)((u8 *)D_00482374 + 0x11), arg0);
    temp_17 = arg0->x10 + (arg0->x12 * 8);
    MenuItemInfoWidgetsCache_2a65f0(sp30);
    MenuItemInfoPopupShow_2a33e0(D_00482374, temp_16, 0x1AA, 0x1A9, sp30, 0x68, 0x15E, temp_17, 2.0f);
    if (!(*(s8 *)((u8 *)D_00482374 + 0x1C) == 0)) {
        MenuCageBaitIconUpdate_2a7370(temp_16, 0);
    } else {
        MenuCageBaitIconUpdate_2a7370(temp_16, 1);
    }
    return 1;
}
