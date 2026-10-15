#include "types.h"

extern s32 sceMcSync_12d098(s32, s32, s32);
extern void sceMcEnd_12c870(void);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0048316C;
extern s32 D_00483170;
extern s32 D_00483174;
extern s16 D_00483180;
extern u8 D_00483184;

void McEndSession_372d60(void)
{
    u8 t0;
    s32 r0;

    t0 = D_00483184;
    if (t0 != 0) {
        r0 = sceMcSync_12d098(0, 0, 0);
        D_00483174 = r0;
        sceMcEnd_12c870();
        D_0048316C = 0;
    } else {
        D_0048316C = 0;
    }
    D_00483170 = 0;
    D_00483184 = 0;
    D_00483174 = 0;
    D_00483180 = 0;
}
