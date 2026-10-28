/* rgp:protos */
#define RGP_SELF_CharaGetGaugeLevelCap_3aaeb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct S3AAEB0 { u8 pad000[0x5]; u8 f5; };

/*rgp*/

s32 CharaGetGaugeLevelCap_3aaeb0(s32 a0, int rgp_a1, int rgp_a2, int rgp_a3)
{
    struct S3AAEB0 *r;

    r = ((struct S3AAEB0 *)CharaFindLearnedAbility_3ad940(a0, 0x86, 0, (int)rgp_a3));
    if (r != 0) {
        return r->f5;
    }
    return 0;
}
