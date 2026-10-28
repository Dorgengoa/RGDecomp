/* rgp:protos */
#define RGP_SELF_Swap128_1cb4f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "libvu0.h"

typedef rg_u128 u128;

void Swap128_1cb4f0(u128 *a, u128 *b)
{ RG_VU0_FRAME;
    Vu0SwapVector(a, b);
}
