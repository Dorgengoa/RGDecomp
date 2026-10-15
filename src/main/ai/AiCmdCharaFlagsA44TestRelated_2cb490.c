#include "types.h"

extern s32 CharaFlagsA44TestRelated_215000(s32);
extern s32 ScriptSlotStoreIntRef_2cc900(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern const s32 D_004DB92C;

s32 AiCmdCharaFlagsA44TestRelated_2cb490(s32 p0)
{
    s32 t0;
    s32 rv2;
    s32 r0;
    s32 r1;

    t0 = D_004DB92C;
    rv2 = 1;
    if (t0 == 0) {
        rv2 = 0;
    } else {
        r0 = CharaFlagsA44TestRelated_215000(t0);
        r1 = ScriptSlotStoreIntRef_2cc900(p0, (r0 & 0xFF));
        rv2 = 1;
    }
    return rv2;
}
