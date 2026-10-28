/* rgp:protos */
#define RGP_SELF_EvCmdMenuHelpClose_25bd50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Known-positive sibling shape of EvCmdMenuCompleteCheckClose_25be80 (byte-identical, in cunits). */

/*rgp*/
/*rgp*/

extern u8 D_0045EE80[];
extern u8 D_0045EE90[];

s32 EvCmdMenuHelpClose_25bd50(void)
{
    s32 r2;

    TaskSetEnabled_27c2a0(0, D_0045EE80);
    TaskSetEnabled_27c2a0(0, D_0045EE90);
    r2 = (HelpMenuClose_203200(), (s32)0);
    return 1;
}
