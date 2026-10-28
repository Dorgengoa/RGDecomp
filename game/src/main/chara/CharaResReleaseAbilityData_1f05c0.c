/* rgp:protos */
#define RGP_SELF_CharaResReleaseAbilityData_1f05c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R1f0 { u8 pad00[0x2]; s16 m2; } R1f0;

/*rgp*/
/*rgp*/

void CharaResReleaseAbilityData_1f05c0(void *a0, int rgp_a1)
{
    R1f0 *r;

    r = ((R1f0 *)CharaResFindById_1efba0(a0, (int)rgp_a1));
    if (r != 0) {
        CharaAbilityDataRelease_1f0600(a0, r->m2);
    }
}
