#include "types.h"

extern s32 ScriptSlotStoreIntRef_2cc900(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern const s32 D_004DB974;

s32 AiCmdCtxListCount_2c5070(s32 p0)
{
    s32 r;

    r = ScriptSlotStoreIntRef_2cc900(p0, D_004DB974);
    return 1;
}
