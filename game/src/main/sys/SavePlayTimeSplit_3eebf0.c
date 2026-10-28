/* rgp:protos */
#define RGP_SELF_SavePlayTimeSplit_3eebf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Five arguments in, four passed straight through; the first is dereferenced
   as a 64-bit handle (`ld`) and mapped through DoubleToU64_13ab28. */

long long SavePlayTimeSplit_3eebf0(s64 *h, s32 a, s32 b, s32 c, s32 d)
{
    return PlayTimeSplit_3d6350((long long)(DoubleToU64_13ab28(__builtin_bit_cast(double, (long long)(*h)))), a, b, c, d);
}
