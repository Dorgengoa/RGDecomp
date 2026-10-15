#include "types.h"

extern void TaskEnableFieldSet_2874a0(void);
extern void TaskSetEnabled_27c2a0(s32, void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0045FF78[];
extern u8 D_00460010[];
extern u8 D_00460210[];
extern u8 D_00460390[];
extern u8 D_004605D8[];
extern u8 D_00460740[];
extern u8 D_00460760[];
extern u8 D_00460870[];
extern u8 D_00460A60[];

void TaskEnableBattleSet_2873f0(void)
{
    TaskEnableFieldSet_2874a0();
    TaskSetEnabled_27c2a0(1, D_00460390);
    TaskSetEnabled_27c2a0(1, D_00460A60);
    TaskSetEnabled_27c2a0(0, D_004605D8);
    TaskSetEnabled_27c2a0(0, D_0045FF78);
    TaskSetEnabled_27c2a0(0, D_00460210);
    TaskSetEnabled_27c2a0(0, D_00460760);
    TaskSetEnabled_27c2a0(0, D_00460870);
    TaskSetEnabled_27c2a0(0, D_00460010);
    TaskSetEnabled_27c2a0(0, D_00460740);
}
