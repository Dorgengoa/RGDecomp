/* rgp:protos */
#define RGP_SELF_VecCopy_1cbe30 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "libvu0.h"

typedef rg_u128 u128;

void VecCopy_1cbe30(u128 *dst, u128 *src)
{ RG_VU0_FRAME;
    Vu0CopyVector(dst, src);
}
