/* rgp:protos */
#define RGP_SELF_NavGraphGetEdge_310c20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E { u8 b[0x14]; } E;
typedef struct P { u8 pad0[0xB0]; E *fB0; u8 padA[0x4]; u16 fB8; } P;

E *NavGraphGetEdge_310c20(P *p, u32 i)
{
    E *base = p->fB0;
    if (base == 0 || p->fB8 <= i) return 0;
    return &base[i];
}
