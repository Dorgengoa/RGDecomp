/* rgp:protos */
#define RGP_SELF_MapShareInit_1ed040 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Known-positive sibling shape of MapBlockInit_1e0100 (byte-identical, in cunits). */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void MapShareInit_1ed040(s32 p0)
{
    MapDataInit_1e7c50(p0);
    Nop_1ed0b0();
    Nop_1ed090();
    MapDataSetType_1e7430(p0, 0x3);
    MapDataClearLoadStateThunk_1e7c30(p0);
}
