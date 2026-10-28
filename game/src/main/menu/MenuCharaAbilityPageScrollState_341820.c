/* rgp:protos */
#define RGP_SELF_MenuCharaAbilityPageScrollState_341820 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern void *D_00482378;

s32 MenuCharaAbilityPageScrollState_341820(void)
{
    u8 sp2C[4];
    s32 sp28;
    s32 i; void *p;

    UiGetWidgetPos_2910a0(D_00482360, 0x190, sp2C, &sp28);
    if ((sp28 == 0x1B) || (sp28 == -0x1B)) {
        p = UiEntryListFindByTag_28ea40(D_00482364, 0x19);
        MenuCharaAbilityPageFill_3406a0(D_00482378, *(s8 *)((u8 *)D_00482378 + 0x6C),
            *(s16 *)((u8 *)p + 0x1A));
        i = 0;
        do {
            UiSetWidgetPos_290f60(D_00482360, (i + 0x191) & 0xFFFF, 0, 0);
            i += 1;
        } while (i < 5);
        UiSetWidgetPos_290f60(D_00482360, 0x190, 0, 0);
        StateMachineSetState_28ede0(D_0048235C, 0x7C, 0);
    }
    return 1;
}
