/* rgp:protos */
#define RGP_SELF_HpGaugeGetTimer_31e6a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct E31E6A0 { s32 a; s32 b; };
struct T31E6A0 { u8 pad000[0x20]; struct E31E6A0 f20[1]; };

s32 HpGaugeGetTimer_31e6a0(struct T31E6A0 *p, s32 i)
{
    if (i >= 0x10) {
        i = 0xF;
    }
    return p->f20[i].a;
}
