/* rgp:protos */
#define RGP_SELF_EvObjLiftFindStopAt_335f00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

s32 EvObjLiftFindStopAt_335f00(void *arg0, s32 arg1) {
    s32 p;
    s32 i;

    if (!(((*(u32 *)((u8 *)arg0 + 0xD0) & 0x80000000) != 0) ^ 1)) {
        return -1;
    }
    p = *(s32 *)((u8 *)arg0 + 0xE4);
    for (i = 0; i < *(s16 *)((u8 *)arg0 + 0xEA); i++, p += 0x118) {
        if (EvTargetSetHitTest_336720(p, arg1) != 0) {
            return i;
        }
    }
    if (EvObjLiftVolumeContainsPoint_335e50(arg0, arg1) != 0) {
        return *(s16 *)((u8 *)arg0 + 0x10C);
    }
    return -1;
}
