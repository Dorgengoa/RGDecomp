#include "types.h"

typedef struct Src_FUN_002b0230 {
    u8  pad000[0x12];
    s16 f0x12;
} Src_FUN_002b0230;

typedef struct Dst_FUN_002b0230 {
    u8  pad000[0x42];
    s16 f0x42;
} Dst_FUN_002b0230;

extern Dst_FUN_002b0230 *D_00482374;
extern void MenuItemCmdSetRowHighlight_2a1800(Dst_FUN_002b0230 *, s32, s32, s32, s32);

s32 MenuItemCmdRowHighlightCb_2b0230(Src_FUN_002b0230 *p)
{
    s32 v = *(volatile s16 *)&p->f0x12;

    MenuItemCmdSetRowHighlight_2a1800(D_00482374, 0x7E, 0x7D, v, D_00482374->f0x42);
    return 1;
}
