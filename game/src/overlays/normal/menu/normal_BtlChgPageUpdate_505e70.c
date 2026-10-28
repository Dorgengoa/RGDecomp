/* rgp:protos */
#define RGP_SELF_normal_BtlChgPageUpdate_505e70 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00505E70 -- the close path.  f43E is re-read at both of its sites
 * (a fresh `lh` each time), so it stays a field reference. */

typedef struct Obj { u8 pad000[0x43E]; s16 f43E; } Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_BtlChgPageUpdate_505e70(Obj *p)
{
    void *w;

    if (normal_BtlChgPageGetStateId_5061a0(p) == -1) {
        if (p->f43E == 0) {
            return 0;
        }
    }
    w = normal_UiPageGetLayout_289b60(p);
    if (w == 0) {
        return 0;
    }
    if (p->f43E != 0) {
        if (UiPageWidgetAtTargetPos_2899b0(p, 0x2B) != 0) {
            p->f43E = 0;
            UiSetWidgetVisible_290010(w, 0x2B, 0, -1);
        }
    }
    StateMachineUpdate_28ed70((u8 *)p + 0x28);
    normal_BtlChgPageLayoutUpdate_506160(p);
    return 1;
}
