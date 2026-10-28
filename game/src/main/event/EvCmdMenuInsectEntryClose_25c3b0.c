/* rgp:protos */
#define RGP_SELF_EvCmdMenuInsectEntryClose_25c3b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Known-positive sibling shape of EvCmdMenuCompleteCheckClose_25be80 (byte-identical, in cunits). */

/*rgp*/
/*rgp*/

extern u8 D_0045EF60[];
extern u8 D_0045EF80[];

s32 EvCmdMenuInsectEntryClose_25c3b0(void)
{
    s32 r2;

    TaskSetEnabled_27c2a0(0, D_0045EF60);
    TaskSetEnabled_27c2a0(0, D_0045EF80);
    r2 = (InsectEntryMenuClose_203300(), (s32)0);
    return 1;
}
