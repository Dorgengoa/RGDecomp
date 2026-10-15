#include "types.h"

extern s32 GetDrawCtx_15de80(void);
extern s32 GetDrawCtxNameTable_15de40(void);
extern s32 DrawCtxNameTableConfigureMaybe_145980(s32, s32, s32, s32);
extern s32 RefracTexInit_140430(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void DrawCtxNameTableSetupMaybe_202560(s32 p0)
{
    s32 r0;
    s32 r1;
    s32 r2;
    s32 r3;

    if (p0 != 0) {
        r0 = GetDrawCtx_15de80();
        r1 = GetDrawCtxNameTable_15de40();
        r2 = DrawCtxNameTableConfigureMaybe_145980(r0, 0x1C0, 0x33A, p0);
        r3 = RefracTexInit_140430(r0);
        return;
    }
}
