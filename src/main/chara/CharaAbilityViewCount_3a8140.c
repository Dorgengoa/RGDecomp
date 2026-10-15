#include "types.h"

struct T3A8140 { u8 pad000[0x4]; void *f04; s32 f08; s32 f0C; };

extern s32 CharaCountAbilitiesFilteredMaybe_3add30(void *q, s32 b, s32 c, s32 d);

s32 CharaAbilityViewCount_3a8140(struct T3A8140 *p)
{
    void *q;

    q = p->f04;
    if (q != 0) {
        return CharaCountAbilitiesFilteredMaybe_3add30(q, p->f08, p->f0C, 0);
    }
    return 0;
}
