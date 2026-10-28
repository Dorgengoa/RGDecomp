/* rgp:protos */
#define RGP_SELF_TransMenuItemTransferState_37d700 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Obj1 { u8 pad[0x3C]; s32 unk3C; };
struct Obj2 { u8 pad[0x18]; s32 unk18; };

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_0048470C;
extern struct Obj1 *D_00484740;

s32 TransMenuItemTransferState_37d700(void)
{
    s32 temp_2;
    s32 var_16;
    s32 temp_2_2;

    temp_2 = MenuGetSelItem_2a02d0(D_00484740);
    if (temp_2 == 0) {
        return 0;
    }
    temp_2_2 = MenuGetMode_2a4e30(D_00484740);
    if (temp_2_2 == 0) {
        var_16 = 1;
    } else if (temp_2_2 == 1) {
        var_16 = 0;
    }
    InvMoveItemToCategoryMaybe_3c59b0(((struct Obj2 *)GetGameData_1fede0())->unk18, temp_2, var_16, D_00484740->unk3C, 0, 0, 0, 0);
    StateMachineSetState_28ede0(D_0048470C, 0x3F, 0);
    return 1;
}
