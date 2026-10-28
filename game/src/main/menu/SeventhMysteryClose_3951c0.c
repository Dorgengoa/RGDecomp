/* rgp:protos */
#define RGP_SELF_SeventhMysteryClose_3951c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u8 D_004B2570[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

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
    x = ((s32)GetMenuResGroup_206a40());
    ResGroupUnloadGroup_42b650(x, 2);
    D_00483488 = 0;
    D_0047FF20 = 1;
    D_00483480 = 0;
    D_0048348C = 0;
}
