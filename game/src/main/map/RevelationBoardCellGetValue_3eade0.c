/* rgp:protos */
#define RGP_SELF_RevelationBoardCellGetValue_3eade0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Known-positive sibling shape of BlockHeapAllocTopAddr_1c2400 (byte-identical, in cunits). */

/*rgp*/

struct Obj0;

struct Obj0 {
    s32 m00;
};

s32 RevelationBoardCellGetValue_3eade0(s32 p0, s32 p1, s32 p2, int rgp_a3)
{
    struct Obj0 *r0;
    s32 t0;

    r0 = RevelationBoardCellGetEntry_3eae10(p0, p1, p2, (int)rgp_a3);
    if (r0 != 0) {
        t0 = r0->m00;
        return t0;
    }
    return 0;
}
