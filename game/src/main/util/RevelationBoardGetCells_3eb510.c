/* rgp:protos */
#define RGP_SELF_RevelationBoardGetCells_3eb510 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Known-positive sibling shape of CharaDataGetSubRecMemStack_1ed430 (byte-identical, in cunits). */

/*rgp*/

s32 RevelationBoardGetCells_3eb510(s32 p0, s32 p1, s32 p2, int rgp_a3)
{
    s32 r0;

    r0 = RevelationBoardFindById_3eb540(p0, p1, p2, (int)rgp_a3);
    if (r0 != 0) {
        return (r0 + 0x4);
    }
    return 0;
}
