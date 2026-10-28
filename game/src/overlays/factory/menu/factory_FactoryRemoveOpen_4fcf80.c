/* rgp:protos */
#define RGP_SELF_factory_FactoryRemoveOpen_4fcf80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004FCF80 -- 86 words, BYTE-IDENTICAL.
 *
 * 0x0047D4F4 is a `.lit4` POOL entry (0xC0490FDB = -3.1415927), not a global.
 * As an `extern f32` the `lwc1` cannot move above `sw $0,0x5C($4)` (mwcc will
 * not hoist a global load past a store that might alias it), so it landed six
 * words late; as a LITERAL it is a known constant and hoists into the prologue
 * slot between `sd $31` and `sq $16`, which is retail's schedule.  Six bad
 * words -> 0 from that one spelling.  levers.d/mwcc-float-literal-pool.md.
 *
 * Scoring: dv_osbuild alone shows 1 bad word (the gp immediate reads C7800000)
 * because it cannot place the object's `.lit4`; with the pool retarget
 * (build/lit4_im07.py -> 0x0047D4F4) it is 0 bad.
 */

typedef struct Job { s32 f00; } Job;

typedef struct Scr {
    u8    pad00[0x5C];
    s32   f5C;
    f32   f60;
    u8    f64;
    u8    f65;
    u8    pad66[0x2];
    void *f68;
} Scr;

extern void *D_00484A70;
extern void *D_004807EC;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void factory_FactoryRemoveOpen_4fcf80(Scr *o)
{
    Job *q;

    o->f5C = 0;
    o->f60 = -3.1415927f;
    UiSetSpriteFlags_290bd0(o->f68, 0x54, (long long)(0x200), 1, 0, 0);
    UiSetTextString_28f510(o->f68, 0x54, MsgTableLookup_28aa30(D_00484A70, 0x18), 0);
    UiSetTextString_28f510(o->f68, 0x54, MsgTableLookup_28aa30(D_00484A70, 9), 1);
    UiSetTextString_28f510(o->f68, 0x54, MsgTableLookup_28aa30(D_00484A70, 0xA), 2);
    UiSetTextString_28f510(o->f68, 0x54, MsgTableLookup_28aa30(D_00484A70, 7), 3);
    UiSetWidgetVisible_290010(o->f68, 0x55, 0, -1);
    UiSetWidgetVisible_290010(D_004807EC, 0x97, 0, -1);
    o->f64 = 0;
    q = ((Job *)FactoryGetRequestPtr_367ec0());
    q->f00 = 7;
    UiSetWidgetAlpha_2907a0(o->f68, 0x55, 0.0f);
    UiSetWidgetAlpha_2907a0(o->f68, 0x5A, 0.0f);
    UiSetWidgetAlpha_2907a0(D_004807EC, 0x97, 0.0f);
    o->f65 = 0;
    UiSetWidgetVisible_290010(o->f68, 0x56, 1, -1);
    UiSetWidgetAlpha_2907a0(o->f68, 0x56, 0.0f);
}
