/* rgp:protos */
#define RGP_SELF_ObjAllocPartArrays_1ac780 1
#include "port/game_protos.h"
#line 1
/* PARKED: 1 round trip: mechanical conversion; length 0x11C vs retail 0x114. */
#include "types.h"
#pragma optimization_level 3
#pragma opt_common_subs off

/*rgp*/
/*rgp*/
/*rgp*/

void ObjAllocPartArrays_1ac780(void *arg0, s32 arg1, s32 arg2)
{
    s32 temp_19;
    s32 var_16;

    if (arg1 != 0) {
        *(s32 *)((u8 *)arg0 + 0x218) = ((s32)ConstructNewArray_100710(((s32)MemStackNew_14e1b0((arg1 * 0x50) + 0x10, arg2)), 0, 0, 0x50, arg1));
        *(s32 *)((u8 *)arg0 + 0x21C) = ((s32)ConstructNewArray_100710(((s32)MemStackNew_14e1b0((arg1 * 0x50) + 0x10, arg2)), 0, 0, 0x50, arg1));
        if ((*(s32 *)((u8 *)arg0 + 0x218) != 0) && (*(s32 *)((u8 *)arg0 + 0x21C) != 0)) {
            *(s32 *)((u8 *)arg0 + 0x214) = arg1;
            var_16 = 0;
            while (var_16 < arg1) {
                temp_19 = var_16 * 0x50;
                ModelPartClear_152810(*(s32 *)((u8 *)arg0 + 0x218) + temp_19);
                ModelPartClear_152810(*(s32 *)((u8 *)arg0 + 0x21C) + temp_19);
                var_16 += 1;
            }
            return;
        }
        *(s32 *)((u8 *)arg0 + 0x218) = 0;
        *(s32 *)((u8 *)arg0 + 0x21C) = 0;
        *(s32 *)((u8 *)arg0 + 0x214) = 0;
    }
}
