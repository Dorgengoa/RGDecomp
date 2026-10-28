/* rgp:protos */
#define RGP_SELF_MapDataGetColorA_1e7510 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S { u8 b[1]; } S;

/*rgp*/
/*rgp*/

f32 MapDataGetColorA_1e7510(S *o)
{
    return dpmul(0.00390625, UIntToDouble_100320(o->b[0x53]));
}
