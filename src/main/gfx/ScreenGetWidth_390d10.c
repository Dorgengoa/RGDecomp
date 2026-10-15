#include "types.h"

extern s32 GetDrawCtx_15de80(void);
extern void DrawEnvGetWidth_1451e0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void ScreenGetWidth_390d10(void)
{
    s32 r0;

    r0 = GetDrawCtx_15de80();
    DrawEnvGetWidth_1451e0(r0);
}
