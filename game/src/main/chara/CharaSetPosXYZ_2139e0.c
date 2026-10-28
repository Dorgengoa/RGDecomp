/* rgp:protos */
#define RGP_SELF_CharaSetPosXYZ_2139e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { f32 x, y, z, w; } V_002139e0;

extern f32 D_0047E620;
extern f32 D_0047E624;
extern f32 D_0047E628;
extern f32 D_0047E62C;

/*rgp*/
/*rgp*/

void CharaSetPosXYZ_2139e0(void *p, f32 x, f32 y, f32 z)
{
    V_002139e0 v __attribute__((aligned(16)));

    v.x = D_0047E620;
    v.y = D_0047E624;
    v.z = D_0047E628;
    v.w = D_0047E62C;
    v.x = x;
    v.y = y;
    v.z = z;
    CharaSetPosVec_2387e0(p, &v);
    SrtSetPosFromVecThunk_1c7410(p, &v);
}
