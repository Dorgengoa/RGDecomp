/* rgp:protos */
#define RGP_SELF_TargetRefBuildMatrix_3368d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { u8 pad[0x30]; s32 f30; } Q_003368d0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void TargetRefBuildMatrix_3368d0(void *p, Q_003368d0 *q)
{
    if (((short)TargetRefGetKind_2e7130(p)) == 1) {
        MatRotY_1cb200(q, TargetRefGetRadius_2e7100(p));
        TargetRefGetPos_2e6a60(p, &q->f30);
    } else {
        TargetRefGetMatrix_2e6870(p, q);
    }
}
