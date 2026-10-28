/* rgp:protos */
#define RGP_SELF_OcclusionPlaneBuildFrustumMaybe_1971d0 1
#include "port/game_protos.h"
#line 1
/* PARKED: 1 round trip: u128/vector math conversion; length 0x204 vs retail 0x1BC (large gap). */
#include "types.h"
#include "vec.h"
#pragma opt_common_subs off

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void OcclusionPlaneBuildFrustumMaybe_1971d0(void *arg0, s32 arg1)
{ RG_VU0_FRAME;
    u128 sp60;
    u128 sp50;
    u128 sp40;
    u128 sp30;
    u128 sp20;
    f32 temp_f1;
    void *temp_4;
    void *temp_4_2;
    void *temp_4_3;
    void *temp_4_4;
    void *temp_4_5;
    void *temp_4_6;

    if (*(s32 *)((u8 *)arg0 + 0x0) != 0) {
        *(s32 *)((u8 *)arg0 + 0x50) = 1;
        MtxTransformPoints_13c810(&sp30, arg1, (u8 *)arg0 + 0x10, 4);
        VecMax4_13dfb0((u8 *)arg0 + 0xB0, &sp30, &sp40, &sp50, &sp60);
        sp20 = 0;
        VecTriCross_13de70((u8 *)arg0 + 0x60, &sp50, &sp40, &sp30);
        temp_4 = (u8 *)arg0 + 0x60;
        VecNormalize_13bd90(temp_4, temp_4);
        temp_f1 = -Vu0InnerProduct_13bd60((u8 *)arg0 + 0x60, &sp30);
        *(f32 *)((u8 *)arg0 + 0x6C) = temp_f1;
        if (!(temp_f1 <= 0.0f)) {
            VecTriCross_13de70((u8 *)arg0 + 0x60, &sp30, &sp40, &sp50);
            temp_4_2 = (u8 *)arg0 + 0x60;
            VecNormalize_13bd90(temp_4_2, temp_4_2);
            *(f32 *)((u8 *)arg0 + 0x6C) = -Vu0InnerProduct_13bd60((u8 *)arg0 + 0x60, &sp30);
            VecTriCross_13de70((u8 *)arg0 + 0x70, &sp20, &sp40, &sp50);
            VecTriCross_13de70((u8 *)arg0 + 0x80, &sp20, &sp60, &sp30);
            VecTriCross_13de70((u8 *)arg0 + 0x90, &sp20, &sp30, &sp40);
            VecTriCross_13de70((u8 *)arg0 + 0xA0, &sp20, &sp50, &sp60);
        } else {
            VecTriCross_13de70((u8 *)arg0 + 0x70, &sp20, &sp50, &sp40);
            VecTriCross_13de70((u8 *)arg0 + 0x80, &sp20, &sp30, &sp60);
            VecTriCross_13de70((u8 *)arg0 + 0x90, &sp20, &sp40, &sp30);
            VecTriCross_13de70((u8 *)arg0 + 0xA0, &sp20, &sp60, &sp50);
        }
        temp_4_3 = (u8 *)arg0 + 0x70;
        VecNormalize_13bd90(temp_4_3, temp_4_3);
        temp_4_4 = (u8 *)arg0 + 0x80;
        *(s32 *)((u8 *)arg0 + 0x7C) = 0;
        VecNormalize_13bd90(temp_4_4, temp_4_4);
        temp_4_5 = (u8 *)arg0 + 0x90;
        *(s32 *)((u8 *)arg0 + 0x8C) = 0;
        VecNormalize_13bd90(temp_4_5, temp_4_5);
        temp_4_6 = (u8 *)arg0 + 0xA0;
        *(s32 *)((u8 *)arg0 + 0x9C) = 0;
        VecNormalize_13bd90(temp_4_6, temp_4_6);
        *(s32 *)((u8 *)arg0 + 0xAC) = 0;
    }
}
