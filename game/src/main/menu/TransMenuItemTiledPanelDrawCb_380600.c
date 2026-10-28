/* rgp:protos */
#define RGP_SELF_TransMenuItemTiledPanelDrawCb_380600 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void *D_00484710;
extern s32 D_00484728;

/*rgp*/
/*rgp*/

s32 TransMenuItemTiledPanelDrawCb_380600(s32 a, s32 b, s32 c, s32 d, s32 e)
{
    s32 m[8] __attribute__((aligned(16)));

    if (e != 0) {
        m[0] = b;
        m[1] = c;
        m[2] = d;
        m[3] = 0x32C;
        m[4] = UiGetWidgetColor_2904b0(D_00484710, 0x75F8);
        m[5] = UiGetWidgetColor_2904b0(D_00484710, 0x7600);
        m[6] = D_00484728;
        UiDrawSpriteTiled_28c430(m);
    }
    return 1;
}
