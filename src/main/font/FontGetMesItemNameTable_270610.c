#include "types.h"

extern s32 TextStyleGetFontType_26ede0(s32);
extern s32 MesItemNameTableAlt_2776f0(void);
extern s32 MesItemNameTableDefault_277700(void);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 FontGetMesItemNameTable_270610(s32 p0)
{
    s32 r0;
    s32 rv3;
    s32 r1;
    s32 r2;

    r0 = TextStyleGetFontType_26ede0(p0);
    rv3 = r2;
    if (r0 != 0) {
        r1 = MesItemNameTableAlt_2776f0();
        rv3 = r1;
    } else {
        r2 = MesItemNameTableDefault_277700();
        rv3 = r2;
    }
    return rv3;
}
