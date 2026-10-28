/* rgp:protos */
#define RGP_SELF_EvCmdMenuInsectVsClose_25f0f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Known-positive sibling shape of EvCmdMenuCompleteCheckClose_25be80 (byte-identical, in cunits). */

/*rgp*/
/*rgp*/

extern u8 D_0045F060[];
extern u8 D_0045F080[];

s32 EvCmdMenuInsectVsClose_25f0f0(void)
{
    s32 r2;

    TaskSetEnabled_27c2a0(0, D_0045F060);
    TaskSetEnabled_27c2a0(0, D_0045F080);
    r2 = (InsectVsMenuClose_202df0(), (s32)0);
    return 1;
}
