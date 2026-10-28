/* rgp:protos */
#define RGP_SELF_MenuFadeDraw_29fe50 1
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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x4C];
    f32 m4C;
    u8 m50;
    u8 m51;
    u8 m52;
};

f32 MenuFadeDraw_29fe50(struct Obj0 *p0)
{
    f32 t0;
    s32 r0;
    s32 r1;
    f32 t1;
    u8 t2;
    u8 t3;
    u8 t4;
    s32 r13;
    s32 r14;

    t0 = p0->m4C;
    if (t0 > 0.0f) {
        r0 = GetDrawCtx_15de80();
        r1 = ((s32)DrawListBeginPrim_141b00(r0));
        GsPktSetAlphaBlend_13e500(r1, 1);
        GsPktSetBlendMode_13e4f0(r1, 1);
        GsPktEnableAlphaTest_13e4d0(r1, 1);
        GsPktSetAlphaTestFunc_13e4c0(r1, 1, 0);
        GsPktEnableZTest_13e460(r1, 0);
        GsPktSetZWriteMask_13e430(r1, 1);
        GsPktSetTexFilter_13e3d0(r1, 0);
        GsPktSetTextured_13e400(r1, 0);
        GsPktOpenPrim_13f730(r1, 6);
        t1 = p0->m4C;
        t2 = p0->m50;
        t3 = p0->m51;
        t4 = p0->m52;
        GsPktSetRGBAQ_13ee40(r1, t2, t3, t4, ((s32)(128.0f * t1)));
        GsPktSetXYZPixel_13f110(r1, 0, 0, 0);
        r13 = DrawEnvGetWidth_1451e0(r0);
        r14 = DrawEnvGetHeight_1451d0(r0);
        GsPktSetXYZPixel_13f110(r1, r13, r14, 0);
        GsPktClose_13f5b0(r1);
        DrawListEndPrim_141a20(r0);
        return;
    }
    return 0.0f;
}
