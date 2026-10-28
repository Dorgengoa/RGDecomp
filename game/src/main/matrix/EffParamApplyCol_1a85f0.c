/* rgp:protos */
#define RGP_SELF_EffParamApplyCol_1a85f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T1A85F0 { u8 pad000[0xC]; f32 fC; };

/*rgp*/

void EffParamApplyCol_1a85f0(u8 *a, struct T1A85F0 *b, void *rgp_a2)
{
    f32 t;

    t = b->fC;
    VecMul_13bd40(b, a + 0x40, (void *)rgp_a2);
    b->fC = t;
}
