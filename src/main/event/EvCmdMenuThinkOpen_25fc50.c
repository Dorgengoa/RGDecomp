#include "types.h"

extern void TaskSetEnabled_27c2a0(s32, void *);
extern s32 ThinkMenuOpen_203670(void);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0045F0A0[];
extern u8 D_0045F0B0[];

s32 EvCmdMenuThinkOpen_25fc50(void)
{
    s32 r2;

    TaskSetEnabled_27c2a0(1, D_0045F0A0);
    TaskSetEnabled_27c2a0(1, D_0045F0B0);
    r2 = ThinkMenuOpen_203670();
    return 1;
}
