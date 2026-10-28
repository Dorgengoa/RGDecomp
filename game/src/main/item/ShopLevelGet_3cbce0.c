/* rgp:protos */
#define RGP_SELF_ShopLevelGet_3cbce0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct P { u8 pad0[0x400]; s8 f400[0x40]; } P;

s32 ShopLevelGet_3cbce0(P *p, s32 i)
{
    if (i < 0 || 0x40 <= i) return -1;
    return p->f400[i];
}
