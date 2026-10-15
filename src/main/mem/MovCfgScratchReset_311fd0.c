#include "types.h"

extern void MovCfgScratchRewind_312080(void);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004829A0;
extern s32 D_004829A4;
extern s32 D_004829A8;
extern s32 D_004829AC;

void MovCfgScratchReset_311fd0(void)
{
    MovCfgScratchRewind_312080();
    D_004829A0 = 0;
    D_004829A4 = 0;
    D_004829A8 = 0;
    D_004829AC = 0;
}
