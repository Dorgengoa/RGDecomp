/* rgp:protos */
#define RGP_SELF_MenuItemTabCycleCb_2b14e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

typedef struct S1_002b14e0 {
    u8 pad0[0x10];
    s8 unk10;
    s8 unk11;
} S1_002b14e0;

typedef struct S2_002b14e0 {
    u8 pad0[0x95];
    u8 unk95;
} S2_002b14e0;

extern u8 D_004823CC;
extern S1_002b14e0 *D_00482374;
extern S2_002b14e0 *D_00482384;
extern s32 D_0048235C;

s32 MenuItemTabCycleCb_2b14e0(void)
{
    s32 sp2C;
    s64 var_16;
    s32 temp_16;

    if (D_004823CC != 0 && D_00482384->unk95 == 6) {
        return 1;
    }
    sp2C = D_00482374->unk11;
    temp_16 = D_00482374->unk10;
    if (MenuTabCycleWrap_2b15a0(&sp2C, (s8)temp_16) != 0) {
        var_16 = 0;
        if (sp2C == temp_16 - 1) {
            var_16 = MenuItemGetOpenModeMaybe_2a4ec0(D_00482374);
            if (var_16 == 1) {
                StateMachineSetState_28ede0(D_0048235C, 0x14, 0);
            }
        }
        MenuItemSelectTab_2b3550(sp2C, (s16)var_16, 1);
    }
    return 1;
}
