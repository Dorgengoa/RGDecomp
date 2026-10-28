/* rgp:protos */
#define RGP_SELF_InsectCageMenuStepMaybe_38a500 1
#include "port/game_protos.h"
#line 1
#pragma optimization_level 3
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D400;
extern s16 D_0047FBD4;
extern s16 D_0047FBD8;
extern f32 D_004832E0;
extern u16 D_00483334;
extern u8 D_004E94E0[];

void InsectCageMenuStepMaybe_38a500(void) {
    u8 hit;
    u8 busy;

    InsectCageCameraControl_38a620();
    hit = 0;
    if ((u8)UiEntryListCurrentTagIs_28ea10(D_004E94E0, 0x7531) == 1) {
        hit = 1;
    }
    if (hit) {
        MenuObjsAnimStepMaybe_38a790();
    }
    InsectCageMenuCursorBobUpdate_389700(0);
    D_004832E0 += D_0047D400;
    while (3.1415927f < D_004832E0) {
        D_004832E0 -= 3.1415927f;
    }
    busy = 0;
    if (UiEntryListCurrentTagIs_28ea10(D_004E94E0, 0x753F) != 0) {
        busy = 1;
    }
    if (D_0047FBD8 > 0 || D_0047FBD4 > 0) {
        busy = 1;
    }
    UiEntryListUpdateNop_28ecc0();
    MenuGridCursorInput_28e170(D_004E94E0, ((s32)GetPad0_1c6c60()), busy | D_00483334, 0);
    MapAuxAreaTexAnimUpdate_200ba0();
}
