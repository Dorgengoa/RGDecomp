/* rgp:protos */
#define RGP_SELF_EvCmdMenuTransClose_25c0c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Known-positive sibling shape of EvCmdMenuCompleteCheckClose_25be80 (byte-identical, in cunits). */

/*rgp*/
/*rgp*/

extern u8 D_0045EF20[];
extern u8 D_0045EF30[];

s32 EvCmdMenuTransClose_25c0c0(void)
{
    s32 r2;

    TaskSetEnabled_27c2a0(0, D_0045EF20);
    TaskSetEnabled_27c2a0(0, D_0045EF30);
    r2 = (TransMenuClose_2037b0(), (s32)0);
    return 1;
}
