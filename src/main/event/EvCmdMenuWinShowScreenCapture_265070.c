#include "vec.h"

/* Each %gp_rel float is its OWN 4-byte extern: a 16-byte Vec4 extern would
   leave small data and cost a %hi/%lo pair (measured: 4 lui/lo pairs).

   MEASURED (8-arm sweep, build/zz/sw-q08-EvCmdMenuWinShowScreenCapture_265070): the member writes have
   to go through a NAMED `Vec4 *` local.  With plain `a.x = ...` mwcc bunches
   the gp loads three at a time (8 bad words); through a named pointer it emits
   retail's strictly alternating load/store pipeline.  A CAST at the use site
   (`((Vec4 *)&a)->x`) is NOT the same lever - it is ONE OBJECT with the plain
   form.  Member order is then the natural a.x..a.w, b.x..b.w. */

typedef struct Cmd { s32 a, b; } Cmd;

extern s32 ScriptGetInt_26a2a0(s32);
extern void *MenuWinGet_2653e0(s32);
extern void MenuWinSetDrawMode_26c3e0(void *, s32);
extern void MenuWinSetPos_26c3b0(void *, Vec4 *);
extern void MenuWinSetColor_26c380(void *, Vec4 *);
extern void MenuWinSetAlphaBlend_26c260(void *, s32);
extern void MenuWinSetAlphaTest_26c250(void *, s32);
extern void MenuWinSetSize_26c320(void *, s32, s32);
extern void MenuWinSetUvRect_26c300(void *, s32, s32, s32, s32);
extern void MenuWinSetUseCaptureTex_26c400(void *, s32);
extern void ScreenFadeCaptureFrame_1cf550(s32);

extern f32 D_0047E920, D_0047E924, D_0047E928, D_0047E92C;
extern f32 D_0047E930, D_0047E934, D_0047E938, D_0047E93C;
extern s32 D_00481F78;

s32 EvCmdMenuWinShowScreenCapture_265070(Cmd *p0)
{
    Vec4 a, b;
    Vec4 *qa = &a;
    Vec4 *qb = &b;
    void *h;

    h = MenuWinGet_2653e0(ScriptGetInt_26a2a0((s32)p0));
    if (h == 0) {
        return 0;
    }
    qa->x = D_0047E920;
    qa->y = D_0047E924;
    qa->z = D_0047E928;
    qa->w = D_0047E92C;
    qb->x = D_0047E930;
    qb->y = D_0047E934;
    qb->z = D_0047E938;
    qb->w = D_0047E93C;
    MenuWinSetDrawMode_26c3e0(h, 0);
    MenuWinSetPos_26c3b0(h, &a);
    MenuWinSetColor_26c380(h, &b);
    MenuWinSetAlphaBlend_26c260(h, 0);
    MenuWinSetAlphaTest_26c250(h, 0);
    MenuWinSetSize_26c320(h, 0x200, 0x1C0);
    MenuWinSetUvRect_26c300(h, 0, 0, 0x200, 0x1C0);
    MenuWinSetUseCaptureTex_26c400(h, 1);
    ScreenFadeCaptureFrame_1cf550(D_00481F78);
    return 1;
}
