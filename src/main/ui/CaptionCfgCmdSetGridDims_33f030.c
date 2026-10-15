#include "types.h"

/* Two-operand script-command handler.  Cursor is a post-incremented 8-byte
   operand pointer (see CaptionCfgCmdSetGlyphOrigin_33ec50.c). */

typedef struct SArg {
    s32 w[2];
} SArg;

extern s32 GetCaptionCfg_340430(void);
extern s32 VariantGetInt_15f780(SArg *);
extern s32 CaptionCfgSetGridDims_3401b0(s32, s32, s32);

s32 CaptionCfgCmdSetGridDims_33f030(SArg *p0)
{
    s32 r0;
    s32 r1;
    s32 r2;

    r0 = GetCaptionCfg_340430();
    r1 = VariantGetInt_15f780(p0++);
    r2 = VariantGetInt_15f780(p0);
    CaptionCfgSetGridDims_3401b0(r0, r1, r2);
    return 1;
}
