/* rgp:protos */
#define RGP_SELF_CompleteCheckClose_39e7f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u8 D_004B2570[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

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
    x = ((s32)GetMenuResGroup_206a40());
    ResGroupUnloadGroup_42b650(x, 2);
    D_004836A8 = 0;
    D_0047FFD0 = 1;
    D_004836A0 = 0;
    D_004836AC = 0;
}
