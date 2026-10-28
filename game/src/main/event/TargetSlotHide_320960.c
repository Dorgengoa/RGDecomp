/* rgp:protos */
#define RGP_SELF_TargetSlotHide_320960 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj_FUN_00320960 {
    u8 pad000[0x34];
    s32 f34;
} Obj_FUN_00320960;

extern u8 D_00527020[];
/*rgp*/
/*rgp*/
/*rgp*/

void TargetSlotHide_320960(Obj_FUN_00320960 *o)
{
    o->f34 = 1;
    TargetRefClear_2e71d0(o);
    if (GetLoadedOverlayId_1c3200() == 3) {
        func_4F1260(D_00527020, 0);
    }
}
