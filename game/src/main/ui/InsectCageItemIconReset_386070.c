/* rgp:protos */
#define RGP_SELF_InsectCageItemIconReset_386070 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;

struct T386070 { u8 pad000[0xC]; f32 f0C; s32 f10; };

void InsectCageItemIconReset_386070(struct T386070 *p)
{
    *(u128 *)p = 0;
    p->f0C = 1.0f;
    p->f10 = 0;
}
