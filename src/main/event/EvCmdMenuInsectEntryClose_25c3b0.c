#include "types.h"

/* Known-positive sibling shape of EvCmdMenuCompleteCheckClose_25be80 (byte-identical, in cunits). */

extern void TaskSetEnabled_27c2a0(s32, void *);
extern s32 InsectEntryMenuClose_203300(void);

extern u8 D_0045EF60[];
extern u8 D_0045EF80[];

s32 EvCmdMenuInsectEntryClose_25c3b0(void)
{
    s32 r2;

    TaskSetEnabled_27c2a0(0, D_0045EF60);
    TaskSetEnabled_27c2a0(0, D_0045EF80);
    r2 = InsectEntryMenuClose_203300();
    return 1;
}
