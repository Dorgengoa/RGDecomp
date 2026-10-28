/* rgp:protos */
#define RGP_SELF_normal_BtlChgPageStart_506030 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00506030 -- the reset path: clear 0x43E, two local calls, then a
 * fetch guarded `return 0`, two func_290010 calls, an optional call under
 * `b >= 0` and a shared tail call. */
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_BtlChgPageStart_506030(void *p, s32 b)
{
    void *w;

    *(s16 *)((u8 *)p + 0x43E) = 0;
    normal_BtlChgPageSetStateId_5061d0(p, -1);
    normal_BtlChgPageStateIdInc_5061b0(p);
    w = normal_UiPageGetLayout_289b60(p);
    if (w == 0) {
        return 0;
    }
    UiSetWidgetVisible_290010(w, 0x2B, 1, -1);
    UiSetWidgetVisible_290010(w, 1, 1, -1);
    if (b > -1) {
        normal_BtlChgPageSetMember_505fa0(p, b);
    }
    normal_BtlChgPageSetAbilityReq_5052f0(p, -1, 0);
    return 1;
}
