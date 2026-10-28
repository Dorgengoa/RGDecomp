/* rgp:protos */
#define RGP_SELF_CaptionCfgCmdAddGlyph_33ef30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Script-command handler with an optional third operand.  The operand count
   p1 gates it: retail's slti p1,3 / bnez skips the third accessor call, so
   the fall-through is the "p1 >= 3" body.  The zero default is materialised
   in the branch delay slot. */

typedef struct SArg {
    s32 w[2];
} SArg;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 CaptionCfgCmdAddGlyph_33ef30(SArg *p0, s32 p1)
{
    s32 r0;
    s32 r1;
    s32 r2;
    s32 r3;

    r0 = ((s32)GetCaptionCfg_340430());
    r1 = SlotGetInt_15f720(p0++);
    r2 = VariantGetInt_15f780(p0++);
    r3 = 0;
    if (p1 >= 3) {
        r3 = VariantGetInt_15f780(p0);
    }
    CaptionGlyphNodeListAppend_340010(r0, r1, r2, 0, r3);
    return 1;
}
