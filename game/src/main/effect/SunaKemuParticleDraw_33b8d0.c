/* rgp:protos */
#define RGP_SELF_SunaKemuParticleDraw_33b8d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047F640;
extern f32 D_0047F644;
extern f32 D_0047F648;
extern f32 D_0047F64C;

void SunaKemuParticleDraw_33b8d0(f32 *arg0, f32 *arg1, s32 arg2)
{
    s32 spB0[4] __attribute__((aligned(16)));
    s32 spA0[4] __attribute__((aligned(16)));
    f32 sp90[4] __attribute__((aligned(16)));
    f32 sp80[4] __attribute__((aligned(16)));
    f32 sp40[4][4] __attribute__((aligned(16)));

    sp80[0] = D_0047F640;
    sp80[1] = D_0047F644;
    sp80[2] = D_0047F648;
    sp80[3] = D_0047F64C;
    MtxRotY_13ce20(sp40, arg1[0]);
    MtxMulVec4_10a8c0(sp90, sp40, sp80);
    VecScale_13be00(sp90, sp90, arg1[3]);
    sceVu0AddVector(sp90, sp90, arg0);
    sp90[3] = 1.0f;
    if (CameraProjectBillboardRect_15cde0(spB0, spA0, arg1[1], arg1[1], sp90) != 0) {
        GsPktOpenPrim_13f730(arg2, 4);
        GsPktSetTexture_13ec00(arg2, *(s32 *)((u8 *)arg0 + 0x10));
        GsPktSetUV_13ed60(arg2, 0, 0);
        GsPktSetRGBAQ_13ee40(arg2, 0x80, 0x80, 0x80, 0x30);
        GsPktSetXYZ_13ef10(arg2, spB0[0], spB0[1], spB0[2]);
        GsPktSetUV_13ed60(arg2, 0x3F, 0);
        GsPktSetRGBAQ_13ee40(arg2, 0x80, 0x80, 0x80, 0x30);
        GsPktSetXYZ_13ef10(arg2, spA0[0], spB0[1], spB0[2]);
        GsPktSetUV_13ed60(arg2, 0, 0x3F);
        GsPktSetRGBAQ_13ee40(arg2, 0x80, 0x80, 0x80, 0x30);
        GsPktSetXYZ_13ef10(arg2, spB0[0], spA0[1], spB0[2]);
        GsPktSetUV_13ed60(arg2, 0x3F, 0x3F);
        GsPktSetRGBAQ_13ee40(arg2, 0x80, 0x80, 0x80, 0x30);
        GsPktSetXYZ_13ef10(arg2, spA0[0], spA0[1], spB0[2]);
        GsPktClose_13f5b0(arg2);
    }
}
