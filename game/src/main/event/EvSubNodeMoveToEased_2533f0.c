/* rgp:protos */
#define RGP_SELF_EvSubNodeMoveToEased_2533f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_arithtransformation off

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvSubNodeMoveToEased_2533f0(void *arg0, void *arg1)
{
    u8 *a0;
    u8 *a1;
    u8 sp30[0x10] __attribute__((aligned(16)));
    s32 temp_2;
    s32 temp_3;
    s32 temp_4;
    s32 temp_5;
    s32 temp_5_2;
    s32 var_3;
    s32 var_6;
    s32 var_6_2;
    u8 *t;

    a0 = (u8 *)arg0;
    a1 = (u8 *)arg1;
    temp_4 = *(s32 *)(a0 + 0x24);
    if (temp_4 == 0) {
        var_6 = *(s32 *)(a1 + 0xF0);
    } else {
        temp_5 = *(s32 *)(a1 + 0xF0);
        var_6 = temp_5 >> 1;
        if (temp_5 < 0) {
            var_6 = (temp_5 + 1) >> 1;
        }
    }
    temp_3 = *(s32 *)(a1 + 0x40);
    if (temp_3 >= (*(s32 *)(a0 + 0x20) + var_6)) {
        *(s32 *)(a1 + 0x40) = 0;
        return 0;
    }
    if (temp_3 <= 0) {
        VecSub_13be40(sp30, a0 + 0x10, a1 + 0x70);
        sceVu0DivVector(a1 + 0x90, sp30, (f32) *(s32 *)(a0 + 0x20));
        *(s32 *)(a1 + 0x9C) = 0x3F800000;
        *(s32 *)(a1 + 0xF0) = (s32) ((f32) *(s32 *)(a0 + 0x20) * *(f32 *)(a0 + 0x28));
        sceVu0CopyVector(a1 + 0xD0, a1 + 0x90);
        t = a1 + 0xD0;
        sceVu0DivVector(t, t, (f32) *(s32 *)(a1 + 0xF0));
        if (*(s32 *)(a0 + 0x24) != 2) {
            sceVu0CopyVector(a1 + 0xB0, a1 + 0xD0);
        } else {
            sceVu0CopyVector(a1 + 0xB0, a1 + 0x90);
        }
    } else {
        var_6_2 = 0;
        if (temp_3 < *(s32 *)(a1 + 0xF0)) {
            if (temp_4 == 0) goto body1;
            if (temp_4 == 1) {
body1:
            t = a1 + 0xB0;
            VecAdd_13be20(t, t, a1 + 0xD0);
            t = a1 + 0x70;
            VecAdd_13be20(t, t, a1 + 0xB0);
            var_6_2 = 1;
            *(s32 *)(a1 + 0x7C) = 0x3F800000;
            }
        }
        temp_5_2 = *(s32 *)(a0 + 0x24);
        if (temp_5_2 == 2) {
            var_3 = *(s32 *)(a1 + 0xF0) / 2;
            if (*(s32 *)(a1 + 0x40) < (*(s32 *)(a0 + 0x20) - var_3)) {
                goto block_22;
            }
            goto block_24;
        }
block_22:
        if ((temp_5_2 == 0) && (*(s32 *)(a1 + 0x40) >= *(s32 *)(a0 + 0x20))) {
block_24:
            t = a1 + 0xB0;
            VecSub_13be40(t, t, a1 + 0xD0);
            t = a1 + 0x70;
            VecAdd_13be20(t, t, a1 + 0xB0);
            var_6_2 = 1;
            *(s32 *)(a1 + 0x7C) = 0x3F800000;
        }
        if (var_6_2 == 0) {
            t = a1 + 0x70;
            VecAdd_13be20(t, t, a1 + 0x90);
            *(s32 *)(a1 + 0x7C) = 0x3F800000;
        }
    }
    *(s32 *)(a1 + 0x40) = *(s32 *)(a1 + 0x40) + 1;
    return 1;
}
