/* rgp:protos */
#define RGP_SELF_factory_FactoryGridDirToAngle_4ff990 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern f32 D_0047D404;
/*rgp*/

f32 factory_FactoryGridDirToAngle_4ff990(s32 i)
{
    return AngleWrap_1cbf30(D_0047D404 * (i & 3));
}
