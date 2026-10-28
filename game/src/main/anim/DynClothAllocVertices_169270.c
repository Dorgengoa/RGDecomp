/* rgp:protos */
#define RGP_SELF_DynClothAllocVertices_169270 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"
#pragma optimization_level 3
#pragma opt_common_subs off

/*rgp*/                         /* extern */
/*rgp*/                         /* extern */

void * DynClothAllocVertices_169270(void *arg0, s32 arg1, s32 arg2) { void * rgp_v0 = 0;
    s32 temp_4;
    s32 temp_5;
    s32 var_6;
    u32 temp_3;
    u32 temp_3_2;
    u32 temp_3_3;
    u32 temp_3_4;
    u32 temp_3_5;
    u32 var_5;
    u32 var_5_2;
    u32 var_5_3;
    u32 var_5_4;
    u32 var_5_5;

    temp_3 = arg1 * 0x10;
    (*(s32*)((u8 *)(arg0) + 0xA0)) = arg1;
    if (temp_3 & 0xF) {
        var_5 = (temp_3 >> 4) + 1;
    } else {
        var_5 = temp_3 >> 4;
    }
    (*(s32*)((u8 *)(arg0) + 0xA4)) = MemStackAllocQw_14d950(arg2, var_5);
    temp_3_2 = (*(s32*)((u8 *)(arg0) + 0xA0)) * 0x10;
    if (!(temp_3_2 & 0xF)) {
        var_5_2 = temp_3_2 >> 4;
    } else {
        var_5_2 = (temp_3_2 >> 4) + 1;
    }
    (*(s32*)((u8 *)(arg0) + 0xA8)) = MemStackAllocQw_14d950(arg2, var_5_2);
    temp_3_3 = (*(s32*)((u8 *)(arg0) + 0xA0)) * 0x10;
    if (!(temp_3_3 & 0xF)) {
        var_5_3 = temp_3_3 >> 4;
    } else {
        var_5_3 = (temp_3_3 >> 4) + 1;
    }
    (*(s32*)((u8 *)(arg0) + 0xAC)) = MemStackAllocQw_14d950(arg2, var_5_3);
    temp_3_4 = (*(s32*)((u8 *)(arg0) + 0xA0)) * 0x10;
    if (!(temp_3_4 & 0xF)) {
        var_5_4 = temp_3_4 >> 4;
    } else {
        var_5_4 = (temp_3_4 >> 4) + 1;
    }
    (*(s32*)((u8 *)(arg0) + 0xB0)) = MemStackAllocQw_14d950(arg2, var_5_4);
    temp_3_5 = (*(s32*)((u8 *)(arg0) + 0xA0)) * 0x10;
    if (!(temp_3_5 & 0xF)) {
        var_5_5 = temp_3_5 >> 4;
    } else {
        var_5_5 = (temp_3_5 >> 4) + 1;
    }
    (*(s32 *)((u8 *)(arg0) + 0xB4)) = MemStackAllocQw_14d950(arg2, var_5_5);
    (*(s32*)((u8 *)(arg0) + 0xB8)) = (rgp_v0 = ((s32)MemStackNew_14e1b0((*(s32*)((u8 *)(arg0) + 0xA0)) * 4, arg2)));
    var_6 = 0;
    while (var_6 < (*(s32*)((u8 *)(arg0) + 0xA0))) {
        temp_5 = var_6 * 0x10;
        temp_4 = var_6 * 4;
        var_6 += 1;
        (*(u128 *)((u8 *)(*(s32*)((u8 *)(arg0) + 0xA4)) + (temp_5))) =  0;
        (*(u128 *)((u8 *)(*(s32*)((u8 *)(arg0) + 0xA8)) + (temp_5))) =  0;
        (*(u128 *)((u8 *)(*(s32*)((u8 *)(arg0) + 0xAC)) + (temp_5))) =  0;
        (*(u128 *)((u8 *)(*(s32*)((u8 *)(arg0) + 0xB0)) + (temp_5))) =  0;
        (*(s32 *)((u8 *)(*(s32*)((u8 *)(arg0) + 0xB8)) + (temp_4))) =  0;
    }
return rgp_v0; }
