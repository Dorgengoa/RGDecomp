/* rgp:protos */
#define RGP_SELF_DmaTagMake_1d4770 1
#include "port/game_protos.h"
#line 1
#include "types.h"
void DmaTagMake_1d4770(u64 *p0, u32 p1, u32 p2, u32 p3)
{
    *p0 = ((u64)p1 << 32) | ((u64)p2 << 28) | (u64)p3;
}
