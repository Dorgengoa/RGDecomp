/* rgp:protos */
#define RGP_SELF_CharaAbilityViewCount_3a8140 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T3A8140 { u8 pad000[0x4]; void *f04; s32 f08; s32 f0C; };

/*rgp*/

s32 CharaAbilityViewCount_3a8140(struct T3A8140 *p)
{
    void *q;

    q = p->f04;
    if (q != 0) {
        return CharaCountAbilitiesFilteredMaybe_3add30(q, p->f08, p->f0C, 0);
    }
    return 0;
}
