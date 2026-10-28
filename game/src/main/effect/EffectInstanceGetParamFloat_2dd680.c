/* rgp:protos */
#define RGP_SELF_EffectInstanceGetParamFloat_2dd680 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T2DD680 { u8 pad000[0xF0]; f32 fF0[1]; };

void EffectInstanceGetParamFloat_2dd680(struct T2DD680 *p, s32 i, f32 *out)
{
    *out = p->fF0[i];
}
