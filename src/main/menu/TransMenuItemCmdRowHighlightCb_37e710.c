#include "types.h"

typedef struct Src_FUN_0037e710 {
    u8  pad000[0x12];
    s16 f0x12;
} Src_FUN_0037e710;

typedef struct Dst_FUN_0037e710 {
    u8  pad000[0x42];
    s16 f0x42;
} Dst_FUN_0037e710;

extern Dst_FUN_0037e710 *D_00484740;
extern void MenuItemCmdSetRowHighlight_2a1800(Dst_FUN_0037e710 *, s32, s32, s32, s32);

s32 TransMenuItemCmdRowHighlightCb_37e710(Src_FUN_0037e710 *p)
{
    s32 v = *(volatile s16 *)&p->f0x12;

    MenuItemCmdSetRowHighlight_2a1800(D_00484740, 0x760A, 0x7609, v, D_00484740->f0x42);
    return 1;
}
