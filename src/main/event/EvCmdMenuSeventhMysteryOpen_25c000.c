#include "types.h"

extern void TaskSetEnabled_27c2a0(s32, void *);
extern s32 SeventhMysteryMenuOpen_203570(void);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0045EEE0[];
extern u8 D_0045EF00[];

s32 EvCmdMenuSeventhMysteryOpen_25c000(void)
{
    s32 r2;

    TaskSetEnabled_27c2a0(1, D_0045EEE0);
    TaskSetEnabled_27c2a0(1, D_0045EF00);
    r2 = SeventhMysteryMenuOpen_203570();
    return 1;
}
