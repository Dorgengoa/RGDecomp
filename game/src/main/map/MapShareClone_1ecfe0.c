/* rgp:protos */
#define RGP_SELF_MapShareClone_1ecfe0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Known-positive sibling shape of MapBlockClone_1df760 (byte-identical, in cunits). */

/*rgp*/
/*rgp*/

s32 MapShareClone_1ecfe0(s32 p0, s32 p1)
{
    s32 r0;
    s32 rv2;
    s32 r1;

    r0 = MapDataCloneNames_1e7110(p0, p1);
    rv2 = r1;
    if (r0 == 0) {
        rv2 = 0;
    } else {
        r1 = ReturnTrue_1ed0a0();
        rv2 = r1;
    }
    return rv2;
}
