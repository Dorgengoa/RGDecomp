/* rgp:protos */
#define RGP_SELF_MtxCopy_1cbde0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "libvu0.h"

typedef rg_u128 u128;

void MtxCopy_1cbde0(u128 *d, u128 *s)
{ RG_VU0_FRAME;
    Vu0CopyMatrix(d, s);
}
