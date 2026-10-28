/* rgp:protos */
#define RGP_SELF_UiHideWidgetIfFaded_2a59e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct SFUN_002a59e0 {  void *fh; };

/*rgp*/
/*rgp*/
/*rgp*/

s32 UiHideWidgetIfFaded_2a59e0(struct SFUN_002a59e0 *p, s32 q)
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
