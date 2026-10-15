#include "types.h"

typedef struct R1f0 { u8 pad00[0x2]; s16 m2; } R1f0;

extern R1f0 *CharaResFindById_1efba0(void *);
extern void CharaDataReleaseForChara_1f09a0(void *, s32);

void CharaResReleaseCharaData_1f0960(void *a0)
{
    R1f0 *r;

    r = CharaResFindById_1efba0(a0);
    if (r != 0) {
        CharaDataReleaseForChara_1f09a0(a0, r->m2);
    }
}
