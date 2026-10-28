/* rgp:protos */
#define RGP_SELF_EvDoorObjAnyRefAreaHasFlag80_304300 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj_FUN_00304300 {
    u8 pad000[0x180];
    s32 *f180;
    u8 pad184[0x4];
    s16 f188;
} Obj_FUN_00304300;

/*rgp*/
/*rgp*/

s32 EvDoorObjAnyRefAreaHasFlag80_304300(Obj_FUN_00304300 *o)
{
    s32 i;

    if (TargetRefAreaHasFlag80_2e6d70((u8 *)o + 0xA0) != 0) {
        return 1;
    }
    for (i = 0; i < o->f188; i++) {
        if (EventRefListAnyAreaHasFlag80_304820(o->f180 + i * 3) != 0) {
            return 1;
        }
    }
    return 0;
}
