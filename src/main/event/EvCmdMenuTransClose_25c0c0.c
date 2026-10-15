#include "types.h"

/* Known-positive sibling shape of EvCmdMenuCompleteCheckClose_25be80 (byte-identical, in cunits). */

extern void TaskSetEnabled_27c2a0(s32, void *);
extern s32 TransMenuClose_2037b0(void);

extern u8 D_0045EF20[];
extern u8 D_0045EF30[];

s32 EvCmdMenuTransClose_25c0c0(void)
{
    s32 r2;

    TaskSetEnabled_27c2a0(0, D_0045EF20);
    TaskSetEnabled_27c2a0(0, D_0045EF30);
    r2 = TransMenuClose_2037b0();
    return 1;
}
