/* rgp:protos */
#define RGP_SELF_MenuCharaAbilityListInputState_2b4990 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_0048235C;
extern s32 D_00482364;
extern s32 D_00482370;
extern u8 D_004B2570[0x400];

s32 MenuCharaAbilityListInputState_2b4990(s32 pad0, s32 arg1)
{
    s32 var_2;
    void *temp_16;

    if (arg1 != 0) {
        UiEntryListSelectByTag_28ea90(D_00482364, 0x16, 0);
        temp_16 = UiEntryListFindByTag_28ea40(D_00482364, 0x16);
        if (MenuGetListCount_29b580(D_00482370) < 6) {
            *(s16 *)((u8 *)temp_16 + 0xE) = MenuGetListCount_29b580(D_00482370) - 1;
        } else {
            *(s16 *)((u8 *)temp_16 + 0xE) = 4;
        }
        *(s16 *)((u8 *)temp_16 + 0x12) = (s16)(MenuGetListCount_29b580(D_00482370) - 1);
    }
    if (MenuGridCursorInput_28e170(D_00482364, &(*(u8 *)D_004B2570), 0, 0) == 2) {
        StateMachineSetState_28ede0(D_0048235C, 0x6C, 0);
    }
    return 1;
}
