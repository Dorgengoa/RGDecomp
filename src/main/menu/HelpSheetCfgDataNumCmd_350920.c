#include "types.h"

extern s32 VariantGetInt_15f780(s32);
extern s32 MemStackNew_14e1b0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482334;
extern s32 D_00482E98;
extern s32 D_00482E9C;

s32 HelpSheetCfgDataNumCmd_350920(s32 p0)
{
    s32 r0;
    s32 t0;
    s32 r1;

    r0 = VariantGetInt_15f780(p0);
    D_00482E98 = r0;
    t0 = D_00482334;
    r1 = MemStackNew_14e1b0((((r0 * 0x3C) + r0) << 1), t0);
    D_00482E9C = r1;
    return 1;
}
