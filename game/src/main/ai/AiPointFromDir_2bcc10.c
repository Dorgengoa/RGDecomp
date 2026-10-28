/* rgp:protos */
#define RGP_SELF_AiPointFromDir_2bcc10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void AiPointFromDir_2bcc10(void *a, void *b, void *c, void *d, void *e)
{
    f32 f;

    VecSub_1cbd00(c, e, d);
    VecNormalizeXZ_1cbb50(c, c);
    f = AiGetKeepDistanceMaybe_2c0f90(a);
    VecScale_1cbca0(b, c, f);
    VecAdd_1cbdc0(b, b, e);
}
