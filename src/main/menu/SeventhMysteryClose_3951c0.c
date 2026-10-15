#include "types.h"

extern u8 D_004B2570[];

extern void SeventhMysteryReleaseRes_395500(void);
extern void PadClearRepeatAll_183960(u8 *p);
extern void PadClearStickDpadThreshold_183940(u8 *p);
extern s32 GetMenuResGroup_206a40(void);
extern void ResGroupUnloadGroup_42b650(s32 a, s32 b);

extern s16 D_00483488;
extern s16 D_0047FF20;
extern s8 D_00483480;
extern s16 D_0048348C;

void SeventhMysteryClose_3951c0(void)
{
    s32 x;

    SeventhMysteryReleaseRes_395500();
    PadClearRepeatAll_183960(D_004B2570);
    PadClearStickDpadThreshold_183940(D_004B2570);
    x = GetMenuResGroup_206a40();
    ResGroupUnloadGroup_42b650(x, 2);
    D_00483488 = 0;
    D_0047FF20 = 1;
    D_00483480 = 0;
    D_0048348C = 0;
}
