/* rgp:protos */
#define RGP_SELF_MesShowMsgByIndex_278fd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

void MesShowMsgByIndex_278fd0(s32 mode, void *p)
{
    void *r;
    f32 a;
    f32 b;

    r = MsgGetTextByIndex_279040(mode);
    if (r == 0) return;
    a = -1.0f;
    b = a;
    if (mode == 5) {
        a = 0.5f;
        b = a;
    }
    MesSlot0ShowText_278e90(r, 0, p, a, b);
}
