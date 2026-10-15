#include "types.h"

s32 MemStackNew_14e230(s32, s32);
void CaptionGlyphNodeSetAdvance_340320(s32, s32);
s32 CaptionGlyphNodeGetNext_340330(s32);
void CaptionGlyphNodeSetNext_340340(s32, s32);
void CaptionGlyphNodeSetCode_340360(s32, s32);
void CaptionGlyphNodeSetSheet_340380(s32, s32);
void CaptionGlyphNodeSetKey_3403a0(s32, s32);
void CaptionGlyphNodeReset_3403b0(s32);
s32 CaptionGlyphNodeCtor_3403f0(s32);

static inline s32 mk(s32 h) {
    s32 o = MemStackNew_14e230(0xC, h);
    if (o != 0) {
        o = CaptionGlyphNodeCtor_3403f0(o);
    }
    return o;
}
s32 CaptionGlyphNodeListAppend_340010(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 p;
    s32 o;
    u8 *self;

    self = arg0;
    if (*(s32 *)(self + 0) == 0) {
        return 0;
    }
    o = mk(*(s32 *)(self + 0));
    if (o == 0) {
        return 0;
    }
    CaptionGlyphNodeReset_3403b0(o);
    CaptionGlyphNodeSetKey_3403a0(o, arg1);
    CaptionGlyphNodeSetCode_340360(o, arg2);
    CaptionGlyphNodeSetSheet_340380(o, arg3);
    CaptionGlyphNodeSetAdvance_340320(o, arg4);
    if (*(s32 *)(self + 0x50) == 0) {
        *(s32 *)(self + 0x50) = o;
        return 1;
    } else {
        p = *(s32 *)(self + 0x50);
        while (CaptionGlyphNodeGetNext_340330(p) != 0) {
            p = CaptionGlyphNodeGetNext_340330(p);
        }
        CaptionGlyphNodeSetNext_340340(p, o);
    }
    return 1;
}
