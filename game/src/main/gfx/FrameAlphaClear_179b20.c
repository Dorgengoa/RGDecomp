/* rgp:protos */
#define RGP_SELF_FrameAlphaClear_179b20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;
typedef struct { __extension__ unsigned int lo:32; unsigned int  : 0, f:32; } __attribute__((aligned(8))) Bits;
typedef struct { u8 pad[0x80]; Bits b; } Sub;
typedef struct { u8 pad[0x270]; Sub *s; } Obj;

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

void FrameAlphaClear_179b20(void) {
    Obj *o;
    s32 g;
    s32 r[4] __attribute__((aligned(16)));

    o = ((Obj *)GetDrawCtx_15de80());
    o->s->b.f = 0xFFFFFF;
    DrawEnvGetFrameRect_145040(o, r);
    g = ((s32)DrawListBeginPrim_141b00(o));
    GsPktEnableZTest_13e460(g, 0);
    GsPktSetZWriteMask_13e430(g, 1);
    GsPktSetZTest_13e450(g, 0);
    GsPktSetTextured_13e400(g, 0);
    GsPktSetAlphaBlend_13e500(g, 0);
    GsPktSetDestAlphaTest_13e4a0(g, 1);
    GsPktSetDestAlphaMode_13e4b0(g, 1);
    GsPktSetFrameMask_13e420(g, 2);
    GsPktOpenPrim_13f730(g, 6);
    GsPktSetRGBAQ_13ee40(g, 100, 0, 0, 0);
    GsPktSetXYZPixel_13f110(g, r[1], r[0], 0);
    GsPktSetXYZPixel_13f110(g, r[3], r[2], 0);
    GsPktClose_13f5b0(g);
    DrawListEndPrim_141a20(o);
}
