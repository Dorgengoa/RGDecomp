/* PARK 1/3: RIGHT LENGTH (73w), 51 bad -- a switch-case codegen/ordering mismatch, not a length problem. */
#include "types.h"

void ModelObjPlayMotionByName_1867a0(s32, void *, s32);
extern u8 D_00462DB8[];
extern u8 D_00462DC0[];
extern u8 D_00462DD0[];
extern u8 D_00462DD8[];
extern s32 D_004823D0;
extern s32 D_00483078;

s32 MenuWeaponCombineStartAnim_362360(u8 *arg0, s32 arg1) {
    s32 temp_3;

    if (*(u8 *)(arg0 + 0x60) != 0) {
        return 0;
    }
    temp_3 = arg1 & 0xFF;
    switch (temp_3) {
    case 0:
        ModelObjPlayMotionByName_1867a0(D_004823D0, D_00462DB8, 2);
        *(u8 *)(arg0 + 0x60) = 1;
        *(u8 *)(arg0 + 0x61) = 0;
        *(u8 *)(arg0 + 0x95) = 2;
        *(u8 *)(arg0 + 0x96) = 0;
        break;
    case 1:
        ModelObjPlayMotionByName_1867a0(D_004823D0, D_00462DC0, 2);
        *(u8 *)(arg0 + 0x60) = 1;
        *(u8 *)(arg0 + 0x61) = 1;
        *(u8 *)(arg0 + 0x95) = 4;
        *(u8 *)(arg0 + 0x96) = 0;
        break;
    case 3:
        if (*(u8 *)(arg0 + 0x94) != 2) {
            ModelObjPlayMotionByName_1867a0(D_004823D0, D_00462DD0, 2);
            *(u8 *)(arg0 + 0x60) = 1;
            *(u8 *)(arg0 + 0x61) = 3;
            *(s32 *)(arg0 + 0x78) = 0;
        }
        break;
    case 4:
        ModelObjPlayMotionByName_1867a0(D_004823D0, D_00462DD8, 2);
        *(u8 *)(arg0 + 0x60) = 1;
        *(u8 *)(arg0 + 0x61) = 4;
        *(u8 *)(arg0 + 0x95) = 1;
        *(u8 *)(arg0 + 0x96) = 0;
        D_00483078 = 0;
        break;
    }
    return 1;
}
