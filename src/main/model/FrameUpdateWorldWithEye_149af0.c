#include "types.h"

typedef unsigned __int128 u128;

/* %gp_rel: the global must stay in small data, so it is declared at the
   8-byte threshold and written through a u128 cast. */
extern u64 D_00481090;
extern void FrameCalcWorldMatrix_148ff0(void *, void *);
extern void FrameUpdateWorld_149680(void *, void *);

void FrameUpdateWorldWithEye_149af0(u8 *p0, u128 *p1, void *p2)
{
    u8 tmp[0x40];

    *(u128 *)&D_00481090 = *p1;
    if (*(s8 *)(p0 + 0x28) != 0) {
        FrameCalcWorldMatrix_148ff0(p0, tmp);
    }
    FrameUpdateWorld_149680(p0, p2);
}
