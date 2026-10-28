/* rgp:protos */
#define RGP_SELF_MenuTiledPanelDrawCb_2b3b50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void *D_00482360;
extern s32 D_0048234C;

/*rgp*/
/*rgp*/

s32 MenuTiledPanelDrawCb_2b3b50(s32 a, s32 b, s32 c, s32 d, s32 e)
{
    s32 m[8] __attribute__((aligned(16)));

    if (e != 0) {
        m[0] = b;
        m[1] = c;
        m[2] = d;
        m[3] = 0x32E;
        m[4] = UiGetWidgetColor_2904b0(D_00482360, 0x65);
        m[5] = UiGetWidgetColor_2904b0(D_00482360, 0x74);
        m[6] = D_0048234C;
        UiDrawSpriteTiled_28c430(m);
    }
    return 1;
}
