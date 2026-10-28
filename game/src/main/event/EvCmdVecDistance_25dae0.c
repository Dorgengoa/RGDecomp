/* rgp:protos */
#define RGP_SELF_EvCmdVecDistance_25dae0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { f32 x, y, z, w; } V_0025dae0;
typedef struct { u8 d[0x30]; } P_0025dae0;

/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdVecDistance_25dae0(P_0025dae0 *p)
{
    V_0025dae0 a __attribute__((aligned(16)));
    V_0025dae0 b __attribute__((aligned(16)));
    f32 r;

    ScriptArgsToVec4_26a220(&a, p);
    ScriptArgsToVec4_26a220(&b, (void *)((u8 *)p + 0x18));
    p = (P_0025dae0 *)((u8 *)p + 0x30);
    r = VecDistance_13d3d0(&a, &b);
    ScriptSetRefFloat_26a1c0(p, r);
    return 1;
}
