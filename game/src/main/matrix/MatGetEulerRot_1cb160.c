/* rgp:protos */
#define RGP_SELF_MatGetEulerRot_1cb160 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/*rgp*/
void MatGetEulerRot_1cb160(s32 p0, s32 p1)
{
    s32 v[4] __attribute__((aligned(16)));
    MatToRotPos_1cade0(p0, v, p1);
}
