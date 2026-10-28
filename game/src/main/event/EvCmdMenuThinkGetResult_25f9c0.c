/* rgp:protos */
#define RGP_SELF_EvCmdMenuThinkGetResult_25f9c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct { f32 x, y, z; } V_0025f9c0;
typedef union { f32 f; s32 i; } U_0025f9c0;
/*rgp*/
/*rgp*/

s32 EvCmdMenuThinkGetResult_25f9c0(void *p)
{
    U_0025f9c0 b[3] __attribute__((aligned(16)));
    V_0025f9c0 a __attribute__((aligned(16)));

    func_5219C0(&a);
    *(V_0025f9c0 *)b = a;
    ScriptSetRefInt_26a1e0(p, b[1].i);
    return 1;
}
