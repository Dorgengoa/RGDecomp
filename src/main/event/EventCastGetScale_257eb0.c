#include "types.h"

typedef unsigned __int128 u128;

extern void NodeGetScale_186560(void *, void *);
extern void MenuWinGetScale_26c2c0(void *, f32 *, f32 *);

typedef struct {
    s32 unk0;
    u8 pad4[0xC - 4];
    void *unkC;
} Item;

s32 EventCastGetScale_257eb0(s32 arg0, s32 arg1, u8 *arg2) {
    f32 sp2C;
    f32 sp28;
    s32 temp_3;
    void *temp_3_2;
    Item *temp_4;
    void *temp_4_2;
    void *temp_4_3;
    void *temp_4_4;

    if (arg1 < 0) {
        goto block_4;
    }
    if (arg1 >= 0x20) {
        goto block_4;
    }
    goto in_range;
block_4:
    return 0;

in_range:
    temp_4 = (Item *)(arg0 + (arg1 * 0x10));
    temp_3 = temp_4->unk0;
    if (temp_3 == 4) {
        goto case4;
    }
    if (temp_3 == 2) {
        goto case2;
    }
    if (temp_3 == 1) {
        goto case1;
    }
    if (temp_3 == 0) {
        goto case0;
    }
    return 0;

case0:
    temp_3_2 = temp_4->unkC;
    if (temp_3_2 == NULL) {
        return 0;
    }
    *(u128 *)arg2 = *(u128 *)((u8 *)temp_3_2 + 0x1A0);
    return 1;

case1:
    temp_4_4 = temp_4->unkC;
    if (temp_4_4 == NULL) {
        return 0;
    }
    NodeGetScale_186560(temp_4_4, arg2);
    goto block_38;

case2:
    temp_4_3 = temp_4->unkC;
    if (temp_4_3 == NULL) {
        return 0;
    }
    MenuWinGetScale_26c2c0(temp_4_3, &sp2C, &sp28);
    *(f32 *)(arg2 + 0x0) = sp2C;
    *(f32 *)(arg2 + 0x4) = sp28;
    *(s32 *)(arg2 + 0x8) = 0;
    *(s32 *)(arg2 + 0xC) = 0;
    return 1;

case4:
    temp_4_2 = temp_4->unkC;
    if (temp_4_2 == NULL) {
        return 0;
    }
    NodeGetScale_186560(temp_4_2, arg2);
block_38:
    return 1;
}
