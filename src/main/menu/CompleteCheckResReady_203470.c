#include "types.h"

extern s32 CompleteCheckResPollThunk_39eb80(void);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

u8 CompleteCheckResReady_203470(void)
{
    s32 r;

    r = CompleteCheckResPollThunk_39eb80();
    return (r != 0);
}
