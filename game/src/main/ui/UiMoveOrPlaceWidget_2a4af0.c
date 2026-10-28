/* rgp:protos */
#define RGP_SELF_UiMoveOrPlaceWidget_2a4af0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

s32 UiMoveOrPlaceWidget_2a4af0(s32 *p, f32 v, s32 a, s32 b, s32 c)
{
    f32 z;

    z = 0.0f;
    if (v != z) {
        UiMoveWidgetUniform_290f50(*p, a, b, c, (float)v, 1);
    } else {
        UiSetWidgetPos_290f60(*p, (int)a, (int)b, (int)c);
    }
    return 1;
}
