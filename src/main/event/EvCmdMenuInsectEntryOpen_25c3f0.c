#include "types.h"

extern void TaskSetEnabled_27c2a0(s32, void *);
extern s32 InsectEntryMenuInit_2033b0(void);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0045EF60[];
extern u8 D_0045EF80[];

s32 EvCmdMenuInsectEntryOpen_25c3f0(void)
{
    s32 r2;

    TaskSetEnabled_27c2a0(1, D_0045EF60);
    TaskSetEnabled_27c2a0(1, D_0045EF80);
    r2 = InsectEntryMenuInit_2033b0();
    return 1;
}
