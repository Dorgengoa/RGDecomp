/* rgp:protos */
#define RGP_SELF_CharaAbilityViewGetNth_3a8100 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T3A8100 { u8 pad000[0x4]; void *f04; s32 f08; s32 f0C; };

/*rgp*/

s32 CharaAbilityViewGetNth_3a8100(struct T3A8100 *p, s32 a)
{
    void *q;

    q = p->f04;
    if (q != 0) {
        return CharaGetNthLearnedAbility_3adba0(q, a, p->f08, p->f0C, 0);
    }
    return 0;
}
