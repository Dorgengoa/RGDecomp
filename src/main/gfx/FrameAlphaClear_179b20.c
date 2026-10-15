#include "types.h"

typedef unsigned __int128 u128;
typedef struct { u64 lo:32; u64 f:32; } Bits;
typedef struct { u8 pad[0x80]; Bits b; } Sub;
typedef struct { u8 pad[0x270]; Sub *s; } Obj;

extern Obj *GetDrawCtx_15de80(void);
extern void DrawEnvGetFrameRect_145040(Obj *, s32 *);
extern s32 DrawListBeginPrim_141b00(Obj *);
extern void GsPktEnableZTest_13e460(s32, s32);
extern void GsPktSetZWriteMask_13e430(s32, s32);
extern void GsPktSetZTest_13e450(s32, s32);
extern void GsPktSetTextured_13e400(s32, s32);
extern void GsPktSetAlphaBlend_13e500(s32, s32);
extern void GsPktSetDestAlphaTest_13e4a0(s32, s32);
extern void GsPktSetDestAlphaMode_13e4b0(s32, s32);
extern void GsPktSetFrameMask_13e420(s32, s32);
extern void GsPktOpenPrim_13f730(s32, s32);
extern void GsPktSetRGBAQ_13ee40(s32, s32, s32, s32, s32);
extern void GsPktSetXYZPixel_13f110(s32, s32, s32, s32);
extern void GsPktClose_13f5b0(s32);
extern void DrawListEndPrim_141a20(Obj *);

void FrameAlphaClear_179b20(void) {
    Obj *o;
    s32 g;
    s32 r[4];

    o = GetDrawCtx_15de80();
    o->s->b.f = 0xFFFFFF;
    DrawEnvGetFrameRect_145040(o, r);
    g = DrawListBeginPrim_141b00(o);
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
