#include "types.h"

typedef struct Obj001fede0_2a {
    u8 pad00[0x18];
    s32 unk18;
} Obj001fede0_2a;

extern void *GetGameData_1fede0(void);
extern void MenuSetItemSlot_2a4e90(s32, s32, s32);
extern s32 InvHasItemInCategory_3c7f40(s32, s32, s32, s32);
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
