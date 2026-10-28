/* rgp:hwaccess */ #include "port/hwaccess.h"
#line 1
/* rgp:protos */
#define RGP_SELF_DmaPktAddCallTag_141b80 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef rg_u128 u128;
typedef struct S00141b80 {
    u8 pad00[0x4];
    u8 *f4;
} S00141b80;

extern u128 D_0047DE40 __attribute__((section(".sdata")));

void DmaPktAddCallTag_141b80(S00141b80 *s, u32 v)
{
    *(u128 *)s->f4 = D_0047DE40;
    *(u32 *)(s->f4 + 4) = (v);
    s->f4 = s->f4 + 0x10;
}
