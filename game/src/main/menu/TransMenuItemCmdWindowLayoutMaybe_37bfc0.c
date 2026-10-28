/* rgp:protos */
#define RGP_SELF_TransMenuItemCmdWindowLayoutMaybe_37bfc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct P_FUN_0037bfc0 {
    u8 pad000[0x12];
    s16 m12;
} P_FUN_0037bfc0;

extern void *D_00484710;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 TransMenuItemCmdWindowLayoutMaybe_37bfc0(P_FUN_0037bfc0 *p)
{
    void *w;

    w = UiGetWidgetSprite_28fe10(D_00484710, 0x762A, 0);
    if (w == 0) return 0;
    UiLayoutWindowFrame_28b8e0(w, 0xE8, 0x59, 3);
    UiSetSpriteW_28fbf0(D_00484710, 0x762A, 0, p->m12 + 4);
    UiSetSpriteUvW_28f850(D_00484710, 0x762A, 0, p->m12 + 4);
    UiSetSpritePos_28fd10(D_00484710, 0x7609, 0xB8, p->m12 * 27 + 0xB2, 0);
    return 1;
}
