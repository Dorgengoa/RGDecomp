/* rgp:protos */
#define RGP_SELF_EventRefListClone_304650 1
#include "port/game_protos.h"
#line 1
#pragma opt_common_subs off
/* PARKED: 1 round trip: mechanical conversion; length 0x144 vs retail 0x134. */
#include "types.h"


/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EventRefListClone_304650(void *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    s32 temp_2;
    s32 temp_2_2;
    s32 temp_2_3;
    s32 var_17;
    s32 var_16;

    EventRefListReset_3049c0((void *)arg0);
    if ((arg1 == 0) || (!((arg2 != 0) && (arg3 != 0)))) return 0;
    temp_2 = EventRefListGetPathRec_304810(arg1);
    *(s32 *)((u8 *)arg0 + 0x0) = temp_2;
    if (temp_2 == 0) {
        return 0;
    }
    temp_2_2 = EventRefListGetCount_3047a0(arg1);
    temp_2_3 = ((s32)ConstructNewArray_100710(((s32)MemStackNew_14e1b0((temp_2_2 * 0x30) + 0x10, arg3)), &TargetRefCtor_2e71f0, 0, 0x30, temp_2_2));
    *(s32 *)((u8 *)arg0 + 0x4) = temp_2_3;
    if (temp_2_3 == 0) {
        return 0;
    }
    *(s32 *)((u8 *)arg0 + 0x8) = EventRefListGetCount_3047a0(arg1);
    var_17 = *(s32 *)((u8 *)arg0 + 0x4);
    var_16 = 0;
    while (var_16 < *(s32 *)((u8 *)arg0 + 0x8)) {
        if (TargetRefCopy_2e7140(var_17, ((s32)EventRefListGetAt_3047c0(arg1, var_16)), arg3) == 0) {
            return 0;
        }
        var_16 += 1;
        var_17 += 0x30;
    }
    return 1;
    return 0;
}
