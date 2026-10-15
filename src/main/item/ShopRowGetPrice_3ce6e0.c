#include "types.h"

extern s32 InvHasItemInCategory_3c7f40(s32, s32, s32, s32);
extern s32 ShopRowIsUnavailable_3ce6b0(void);
extern s32 ItemGetBuyPrice_3d4340(s32);
extern void *D_00483910;
extern f32 D_0047D278;
extern f32 D_0047D3E4;
extern f32 D_0047D3E8;

s32 ShopRowGetPrice_3ce6e0(s32 *arg0)
{
    s32 temp_16;
    f32 f20;

    if (*arg0 == 0) {
        return -1;
    }
    if (D_00483910 == NULL) {
        return -1;
    }
    if (ShopRowIsUnavailable_3ce6b0() != 0) {
        return -1;
    }
    temp_16 = ItemGetBuyPrice_3d4340(*arg0);
    f20 = 1.0f;
    if (InvHasItemInCategory_3c7f40(*(s32 *)((u8 *)D_00483910 + 0x18), 0x40FB, 0xA, 0) != 0) {
        f20 = D_0047D278;
    } else if (InvHasItemInCategory_3c7f40(*(s32 *)((u8 *)D_00483910 + 0x18), 0x40FC, 0xA, 0) != 0) {
        f20 = D_0047D278;
    } else if (InvHasItemInCategory_3c7f40(*(s32 *)((u8 *)D_00483910 + 0x18), 0x40FD, 0xA, 0) != 0) {
        f20 = D_0047D3E4;
    }
    return (s32)(D_0047D3E8 + (f32)temp_16 * f20);
}
