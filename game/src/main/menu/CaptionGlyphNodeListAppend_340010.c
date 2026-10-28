/* rgp:protos */
#define RGP_SELF_CaptionGlyphNodeListAppend_340010 1
#define RGP_SELF_mk 1
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

static inline s32 mk(s32 h) {
    s32 o = ((s32)MemStackNew_14e230(0xC, h));
    if (o != 0) {
        o = ((s32)CaptionGlyphNodeCtor_3403f0(o));
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
