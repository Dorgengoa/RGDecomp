#include "types.h"

/* Known-positive sibling shape of EvCmdMenuCompleteCheckClose_25be80 (byte-identical, in cunits). */

extern void TaskSetEnabled_27c2a0(s32, void *);
extern s32 InsectVsMenuClose_202df0(void);

extern u8 D_0045F060[];
extern u8 D_0045F080[];

s32 EvCmdMenuInsectVsClose_25f0f0(void)
{
    s32 r2;

    TaskSetEnabled_27c2a0(0, D_0045F060);
    TaskSetEnabled_27c2a0(0, D_0045F080);
    r2 = InsectVsMenuClose_202df0();
    return 1;
}
