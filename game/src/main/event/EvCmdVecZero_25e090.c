/* rgp:protos */
#define RGP_SELF_EvCmdVecZero_25e090 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { s32 a; s32 b; } T_0025e090;

/*rgp*/

s32 EvCmdVecZero_25e090(T_0025e090 *q)
{
    ScriptSetRefFloat_26a1c0(q++, 0.0f);
    ScriptSetRefFloat_26a1c0(q++, 0.0f);
    ScriptSetRefFloat_26a1c0(q, 0.0f);
    return 1;
}
