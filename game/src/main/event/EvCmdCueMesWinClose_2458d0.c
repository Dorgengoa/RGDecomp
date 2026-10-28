/* rgp:protos */
#define RGP_SELF_EvCmdCueMesWinClose_2458d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Ctx { u8 pad000[0x4]; void *m04; } Ctx;

extern Ctx *gEventContext;
/*rgp*/
/*rgp*/

s32 EvCmdCueMesWinClose_2458d0(void *rgp_a0)
{
    s32 m[4] __attribute__((aligned(16)));
    void *o;

    o = gEventContext->m04;
    m[0] = 4;
    m[1] = ScriptGetInt_2490f0((void *)rgp_a0);
    Vec4VectorPushBack_249120(o, m);
    return 1;
}
