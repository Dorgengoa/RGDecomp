/* rgp:protos */
#define RGP_SELF_ItemDefGetUseEffectTargetKind_40dc10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Sub {
    u8 pad000[0x8];
    s8 f5 : 5;
    s8 f3 : 3;
} Sub;

typedef struct O {
    u8   pad000[0x24];
    Sub *m24;
} O;

s32 ItemDefGetUseEffectTargetKind_40dc10(O *o)
{
    if (o->m24 == 0) goto bad;
    return o->m24->f5;
bad:
    return -1;
}
