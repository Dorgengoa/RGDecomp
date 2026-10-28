/* rgp:protos */
#define RGP_SELF_EvCmdVecSet_25e030 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { f32 x, y, z, w; } V_0025e030;
typedef struct { s32 a, b; } T_0025e030;

/*rgp*/
/*rgp*/

s32 EvCmdVecSet_25e030(T_0025e030 *q)
{
    V_0025e030 v __attribute__((aligned(16)));

    ScriptArgsToVec4_26a220(&v, &q[3]);
    ScriptSetRefFloat_26a1c0(q++, v.x);
    ScriptSetRefFloat_26a1c0(q++, v.y);
    ScriptSetRefFloat_26a1c0(q, v.z);
    return 1;
}
