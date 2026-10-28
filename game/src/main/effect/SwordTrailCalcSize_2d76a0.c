/* rgp:protos */
#define RGP_SELF_SwordTrailCalcSize_2d76a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

u32 SwordTrailCalcSize_2d76a0(s32 a0, s32 n)
{
    return (u32)AlignUp16_1cacd0(n * 48) >> 4;
}
