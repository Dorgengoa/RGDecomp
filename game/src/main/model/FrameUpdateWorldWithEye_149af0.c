/* rgp:protos */
#define RGP_SELF_FrameUpdateWorldWithEye_149af0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;

/* %gp_rel: the global must stay in small data, so it is declared at the
   8-byte threshold and written through a u128 cast. */
extern u64 D_00481090;
/*rgp*/
/*rgp*/

void FrameUpdateWorldWithEye_149af0(u8 *p0, u128 *p1, void *p2)
{
    u8 tmp[0x40] __attribute__((aligned(16)));

    *(u128 *)&D_00481090 = *p1;
    if (*(s8 *)(p0 + 0x28) != 0) {
        FrameCalcWorldMatrix_148ff0(p0, tmp);
    }
    FrameUpdateWorld_149680(p0, p2);
}
