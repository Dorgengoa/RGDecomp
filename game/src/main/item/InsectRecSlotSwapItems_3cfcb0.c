/* rgp:protos */
#define RGP_SELF_InsectRecSlotSwapItems_3cfcb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

extern s32 D_004838E8;

s32 InsectRecSlotSwapItems_3cfcb0(s32 p0, s32 p1, s32 p2, s32 p3)
{
    s32 t0;

    t0 = D_004838E8;
    if (t0 == 0) {
        return 0;
    }
    if (p1 != 0) {
        if (p2 != 0) {
            if (p3 != 0) goto ok;
        }
    }
    return 0;
ok:
    InsectRecSlotRemoveItem_3cfde0(p0, p1, 0);
    InsectRecSlotMoveItem_3cfd50(p0, p2, p3);
    InsectRecSlotAddItem_3d0190(p2, p1);
    return 1;
}
