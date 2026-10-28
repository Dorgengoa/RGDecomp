/* rgp:protos */
#define RGP_SELF_UiHideWidgetIfFaded_29caf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct SFUN_0029caf0 { u8 pad000[0x4C4]; void *fh; };

/*rgp*/
/*rgp*/
/*rgp*/

s32 UiHideWidgetIfFaded_29caf0(struct SFUN_0029caf0 *p, s32 q)
{
    if (((s32)UiFindWidget_290460(p->fh, (int)q)) == 0) {
        return -1;
    }
    if (UiGetWidgetAlpha_290770(p->fh, q) <= 0.0f) {
        UiSetWidgetVisible_290010(p->fh, q, 0, -1);
        return 1;
    }
    return 0;
}
