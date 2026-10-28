/* rgp:protos */
#define RGP_SELF_GetScaledGravity_23b170 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern struct { f32 v; s32 pad[3]; } D_0045B078;
extern struct { f32 v; s32 pad[3]; } D_0045B080;
extern struct { f32 v; s32 pad[3]; } D_0045B088;

/*rgp*/
/*rgp*/

f32 GetScaledGravity_23b170(void)
{
    f32 k;
    void *q;
    f32 v;
    f32 x;

    k = D_0045B078.v;
    q = GetCurrentScene_1f5be0();
    v = GameSceneGetTimeStep_1ceba0(q);
    x = -2.0f * (D_0045B088.v * (D_0045B080.v / (k * k)));
    return x * v;
}
