/* rgp:protos */
#define RGP_SELF_UiPanelSetupFrameQuad_33e410 1
#include "port/game_protos.h"
#line 1
#pragma opt_propagation off
#include "types.h"

typedef struct { f32 x, y, z, w; } Vec4;
typedef struct { s16 a0, a2, a4, a6, a8, aA, aC, aE; s32 b10, b14; s16 c18, c1A; } Blk;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 UiPanelSetupFrameQuad_33e410(void *arg0)
{
    s32 sp5C;
    s32 sp58;
    f32 v40[4] __attribute__((aligned(16)));
    Vec4 v30 __attribute__((aligned(16)));
    Blk *b;
    void *o;
    s32 h;
    s32 t;

    o = UiFindWidget_290460(((s32)UiPanelGetWidgetList_33e860((void *)arg0)), 2);
    if (o == NULL) {
        return 0;
    }
    b = *(Blk **)((u8 *)o + 0x20);
    if (b == NULL) {
        return 0;
    }
    UiPanelGetGlyphSpacing_33dfc0(arg0);
    UiPanelGetCellSize_33e920(arg0, &sp5C, &sp58);
    h = GetDrawCtx_15de80();
    if (h == 0) {
        return 0;
    }
    DrawEnvGetWidth_1451e0(h);
    t = *(s32 *)((u8 *)arg0 + 0x10);
    if (t == 0) {
        return 0;
    }
    CaptionCfgGetFrameRect_33ff80(&v30, t);
    {
        f32 *d = v40;
        f32 *s = &v30.x;
        d[0] = s[0];
        d[1] = s[1];
        d[2] = s[2];
        d[3] = s[3];
    }
    if (UiPanelGetFrameVisible_33d4e0(arg0) != 0) {
        b->a0 = -0x60;
        b->a2 = sp58;
        b->a4 = 0;
        b->a6 = *(s32 *)&v40[3];
        b->aC = *(s32 *)&v40[2];
        b->aE = *(s32 *)&v40[3];
        b->a8 = *(s32 *)&v40[0];
        b->aA = *(s32 *)&v40[1];
        b->b10 = b->b14 = 0;
        b->c18 = b->c1A = 0;
    } else {
        b->a0 = b->a2 = 0;
        b->a4 = b->a6 = 0;
        b->aC = b->aE = 0;
        b->a8 = b->aA = 0;
        b->b10 = b->b14 = 0;
        b->c18 = b->c1A = 0;
    }
    return 1;
}
