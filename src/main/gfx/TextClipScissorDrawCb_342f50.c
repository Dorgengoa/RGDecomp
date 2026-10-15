#include "types.h"

extern void GsPktWriteAD_13ec80(s32, s32, u64);
extern void GsPktClose_13f5b0(s32);
extern void GsPktOpenPrim_13f730(s32, s32);
extern s32 DrawEnvGetHeight_1451d0(s32);
extern s32 DrawEnvGetWidth_1451e0(s32);
extern s32 GetDrawCtx_15de80(void);
extern void TextStyleClearClipRect_26f600(void *);
extern void TextStyleSetClipRect_26f620(void *, s32, s32, s32, s32);
extern u8 D_004DB150[];

#define SCISSOR(x0, x1, y0, y1) ((u64)(s64)(x0) | ((u64)(s64)(x1) << 16) | ((u64)(s64)(y0) << 32) | ((u64)(s64)(y1) << 48))

static inline void Setup(void *p) {
    if (p != 0) {
        TextStyleSetClipRect_26f620(p, 0, 0x200, 0xD2, 0x17E);
    }
}

static inline void Reset(void *p) {
    if (p != 0) {
        TextStyleClearClipRect_26f600(p);
    }
}

s32 TextClipScissorDrawCb_342f50(s32 arg0, s32 a1, s32 a2, s32 a3, s32 arg4)
{
    s32 id;
    s32 w;
    s32 h;
    void *p;

    p = D_004DB150;
    if (arg4 != 0) {
        Setup(p);
        if (arg0 != 0) {
            GsPktOpenPrim_13f730(arg0, 6);
            GsPktWriteAD_13ec80(arg0, 0x40, SCISSOR(0, 0x1FF, 0xD2, 0x17E));
            GsPktClose_13f5b0(arg0);
        }
    } else {
        Reset(p);
        id = GetDrawCtx_15de80();
        w = DrawEnvGetWidth_1451e0(id);
        h = DrawEnvGetHeight_1451d0(id);
        if (arg0 != 0) {
            GsPktOpenPrim_13f730(arg0, 6);
            GsPktWriteAD_13ec80(arg0, 0x40, SCISSOR(0, w - 1, 0, h - 1));
            GsPktClose_13f5b0(arg0);
        }
    }
    return 1;
}
