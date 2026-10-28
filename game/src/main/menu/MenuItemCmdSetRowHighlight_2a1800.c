/* rgp:protos */
#define RGP_SELF_MenuItemCmdSetRowHighlight_2a1800 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
extern s16 D_00450DD0[0x400];
extern s16 D_00450DD2[0x400];

s32 MenuItemCmdSetRowHighlight_2a1800(s32 *arg0, s32 arg1, s32 arg2, s32 arg3, s16 arg4)
{
    s32 off;
    s32 i;
    s16 *p;
    s16 *r;
    s32 h;

    off = arg4 * 4;
    p = (s16 *)((u8 *)D_00450DD0 + off);
    for (i = 0; i < 6; i++) {
        if (i == p[0]) {
            break;
        }
        h = p[1];
        UiSetSpriteSizeUvSize_28f670(*arg0, arg1, h, 0x1B, 4, 4, i);
    }
    {
        /*rgp*/
        UiSetSpriteSizeUvSize_28f670(*arg0, arg1, 0, 0, 0, 0, arg3);
    }
    r = ((s16 *)UiGetWidgetSprite_28fe10(*arg0, arg2, 0));
    if (r == NULL) {
        return 0;
    }
    r[0] = 5;
    r[1] = (s16)arg3 * 0x1B + 4;
    r[2] = *(s16 *)((u8 *)D_00450DD2 + off);
    r[3] = 0x1B;
    return 1;
}
