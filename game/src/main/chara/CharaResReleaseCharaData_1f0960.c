/* rgp:protos */
#define RGP_SELF_CharaResReleaseCharaData_1f0960 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R1f0 { u8 pad00[0x2]; s16 m2; } R1f0;

/*rgp*/
/*rgp*/

void CharaResReleaseCharaData_1f0960(void *a0, int rgp_a1)
{
    R1f0 *r;

    r = ((R1f0 *)CharaResFindById_1efba0(a0, (int)rgp_a1));
    if (r != 0) {
        CharaDataReleaseForChara_1f09a0(a0, r->m2);
    }
}
