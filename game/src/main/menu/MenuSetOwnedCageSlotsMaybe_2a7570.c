/* rgp:protos */
#define RGP_SELF_MenuSetOwnedCageSlotsMaybe_2a7570 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj001fede0_2a {
    u8 pad00[0x18];
    s32 unk18;
} Obj001fede0_2a;

/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047ECD8;
extern f32 D_0047ECDC;
extern f32 D_0047ECE0;
extern s32 D_00482374;

void MenuSetOwnedCageSlotsMaybe_2a7570(void) {
    f32 buf[3];
    s32 i;
    Obj001fede0_2a *obj;

    buf[0] = D_0047ECD8;
    buf[1] = D_0047ECDC;
    buf[2] = D_0047ECE0;
    obj = (Obj001fede0_2a *)GetGameData_1fede0();
    i = 0;
    do {
        if (InvHasItemInCategory_3c7f40(obj->unk18, *(s32 *)&buf[i], 0, 0) & 0xFF) {
            MenuSetItemSlot_2a4e90(D_00482374, i, *(s32 *)&buf[i]);
        } else {
            MenuSetItemSlot_2a4e90(D_00482374, i, 0);
        }
        i += 1;
    } while (i < 3);
}
