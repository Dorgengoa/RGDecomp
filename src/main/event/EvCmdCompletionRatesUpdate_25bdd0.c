#include "types.h"

extern s32 GetGameData_1fede0(void);
extern s32 CompletionRatesUpdate_3e7800(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvCmdCompletionRatesUpdate_25bdd0(void)
{
    s32 r0;
    s32 r1;

    r0 = GetGameData_1fede0();
    r1 = CompletionRatesUpdate_3e7800(r0);
    return 1;
}
