#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern const s32 D_004DB974;
extern const s32 D_004DB978;

s32 AiCmdCtxListRecordBegin_2c5190(void)
{
    *(s32 *)&D_004DB974 = 0;
    *(s32 *)&D_004DB978 = 1;
    return 1;
}
