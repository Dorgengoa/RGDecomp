#include "types.h"

extern u8 D_004B2570[];

extern void CompleteCheckReleaseRes_39eb20(void);
extern void PadClearRepeatAll_183960(u8 *p);
extern void PadClearStickDpadThreshold_183940(u8 *p);
extern s32 GetMenuResGroup_206a40(void);
extern void ResGroupUnloadGroup_42b650(s32 a, s32 b);

extern s16 D_004836A8;
extern s16 D_0047FFD0;
extern s8 D_004836A0;
extern s16 D_004836AC;

void CompleteCheckClose_39e7f0(void)
{
    s32 x;

    CompleteCheckReleaseRes_39eb20();
    PadClearRepeatAll_183960(D_004B2570);
    PadClearStickDpadThreshold_183940(D_004B2570);
    x = GetMenuResGroup_206a40();
    ResGroupUnloadGroup_42b650(x, 2);
    D_004836A8 = 0;
    D_0047FFD0 = 1;
    D_004836A0 = 0;
    D_004836AC = 0;
}
