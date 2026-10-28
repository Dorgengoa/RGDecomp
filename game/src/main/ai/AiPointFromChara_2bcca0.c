/* rgp:protos */
#define RGP_SELF_AiPointFromChara_2bcca0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { f32 m[4]; } M_002bcca0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void AiPointFromChara_2bcca0(void *a, void *b, void *c, void *d)
{
    M_002bcca0 m __attribute__((aligned(16)));
    f32 f;

    if (c == 0) return;
    CharaGetPos_2388a0(c, &m);
    f = AiGetKeepDistanceMaybe_2c0f90(a);
    VecScale_1cbca0(b, d, f);
    VecAdd_1cbdc0(b, b, &m);
}
