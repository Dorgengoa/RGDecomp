/* rgp:protos */
#define RGP_SELF_MapPartTableCollectAtPoint_1ddf10 1
#include "port/game_protos.h"
#line 1
/* PARKED: 1 round trip: length OK (93w) but 75/93 bad words -- likely a wrong field width/order. */
#include "types.h"
#pragma opt_dead_code off

/*rgp*/

typedef struct {
    u8 pad0[0x4];
    s32 *unk4;
    s16 unk8;
    u8 padA[0x1a];
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    f32 unk38;
} T1ddf10_arg0;

s32 MapPartTableCollectAtPoint_1ddf10(void *arg0, s32 arg1, s32 arg2, void *arg3, f32 fparg0)
{
    f32 temp_f2;
    f32 temp_f3;
    f32 temp_f4;
    s32 *var_16;
    s32 temp_2;
    s32 var_22;
    s32 var_21;

    var_16 = ((T1ddf10_arg0 *) arg0)->unk4;
    if (!((var_16 != NULL) && (((T1ddf10_arg0 *) arg0)->unk8 > 0))) {
        return 0;
    }
    temp_f4 = *(f32 *)((u8 *)arg3 + 0x0);
    if ((temp_f4 + fparg0) < ((T1ddf10_arg0 *) arg0)->unk30) {
        return 0;
    }
    temp_f3 = *(f32 *)((u8 *)arg3 + 0x4);
    if ((temp_f3 + fparg0) < ((T1ddf10_arg0 *) arg0)->unk34) {
        return 0;
    }
    temp_f2 = *(f32 *)((u8 *)arg3 + 0x8);
    if ((temp_f2 + fparg0) < ((T1ddf10_arg0 *) arg0)->unk38) {
        return 0;
    }
    if ((temp_f4 - fparg0) > ((T1ddf10_arg0 *) arg0)->unk24) {
        return 0;
    }
    if ((temp_f3 - fparg0) > ((T1ddf10_arg0 *) arg0)->unk28) {
        return 0;
    }
    if ((temp_f2 - fparg0) > ((T1ddf10_arg0 *) arg0)->unk2C) {
        return 0;
    }
    var_22 = 0;
    var_21 = 0;
    while (var_21 < ((T1ddf10_arg0 *) arg0)->unk8) {
        if ((MapBlockContainsPoint_1dfb80(*var_16, arg3, fparg0) == 0) ||
            ((temp_2 = var_22 * 4), (var_22 += 1), (*(s32 *)((u8 *)arg1 + temp_2) = *var_16),
             ((var_22 < arg2) != 0))) {
            var_21 += 1;
            var_16 += 0x1;
            continue;
        }
        break;
    }
    return var_22;
    return 0;
}
