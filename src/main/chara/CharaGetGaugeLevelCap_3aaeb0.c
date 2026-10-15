#include "types.h"

struct S3AAEB0 { u8 pad000[0x5]; u8 f5; };

extern struct S3AAEB0 *CharaFindLearnedAbility_3ad940(s32, s32, s32);

s32 CharaGetGaugeLevelCap_3aaeb0(s32 a0)
{
    struct S3AAEB0 *r;

    r = CharaFindLearnedAbility_3ad940(a0, 0x86, 0);
    if (r != 0) {
        return r->f5;
    }
    return 0;
}
