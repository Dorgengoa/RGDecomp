/* rgp:protos */
#define RGP_SELF_ShopRowGetPrice_3ce6e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
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
    if (ShopRowIsUnavailable_3ce6b0((void *)arg0) != 0) {
        return -1;
    }
    temp_16 = ((short)ItemGetBuyPrice_3d4340(*arg0));
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
