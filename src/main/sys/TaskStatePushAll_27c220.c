#include "types.h"

extern void TaskTableStatePush_1f53e0(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482278;
extern u8 D_004D7FA0[];

void TaskStatePushAll_27c220(void)
{
    TaskTableStatePush_1f53e0(D_004D7FA0);
    D_00482278 = (D_00482278 + 1);
}
