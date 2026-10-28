/* rgp:protos */
#define RGP_SELF_CaptionCfgCmdSetAltGlyphOrigin_33ecd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Script-command handler family (0x33ec50/0x33ecd0/0x33ee10 differ only in
   the sink they call).  The operand stream is read 8 bytes at a time; retail
   keeps a REAL incrementing cursor in a callee-saved register (daddu a0,cur /
   addiu cur,8 in the jal delay slot), which is the POST-INCREMENT form
   f(p++).  "f(p); p += 8;" folds into base+offset and comes out short. */

typedef struct SArg {
    s32 w[2];
} SArg;

/*rgp*/
/*rgp*/
/*rgp*/

s32 CaptionCfgCmdSetAltGlyphOrigin_33ecd0(SArg *p0)
{
    s32 r0;
    s32 v[4] __attribute__((aligned(16)));

    r0 = ((s32)GetCaptionCfg_340430());
    v[0] = VariantGetInt_15f780(p0++);
    v[1] = VariantGetInt_15f780(p0++);
    v[2] = VariantGetInt_15f780(p0++);
    v[3] = VariantGetInt_15f780(p0);
    CaptionCfgSetAltGlyphOrigin_33ff30(r0, v);
    return 1;
}
