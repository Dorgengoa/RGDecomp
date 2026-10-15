#include "types.h"

typedef struct R1f0 { u8 pad00[0x2]; s16 m2; } R1f0;

extern R1f0 *CharaResFindById_1efba0(void *);
extern void CharaAbilityDataRelease_1f0600(void *, s32);

void CharaResReleaseAbilityData_1f05c0(void *a0)
{
    R1f0 *r;

    r = CharaResFindById_1efba0(a0);
    if (r != 0) {
        CharaAbilityDataRelease_1f0600(a0, r->m2);
    }
}
