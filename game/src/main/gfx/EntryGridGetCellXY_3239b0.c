/* rgp:protos */
#define RGP_SELF_EntryGridGetCellXY_3239b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_repositioncode off

/*rgp*/
/*rgp*/

s32 EntryGridGetCellXY_3239b0(s32 arg0, s32 arg1, s32 arg2)
{
    s32 w;
    s32 h;
    s32 i;

    if (arg1 < 0 || arg2 < 0) return 0;
    EntryGetGridSize_323bb0(arg0, &w, &h);
    if (arg1 >= w || arg2 >= h) return 0;
    i = arg1 + arg2 * w;
    if (i >= w * h || i < 0) return 0;
    return EntryGridGetCell_323a60(arg0, i);
}
