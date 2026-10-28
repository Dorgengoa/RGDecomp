/* rgp:protos */
#define RGP_SELF_EvCmdCueBgmPlay_241590 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { s32 a; s32 b; } E8_241590;
typedef struct { u8 pad0[4]; void *f4; } EvCtx_241590;

extern EvCtx_241590 *gEventContext;
/*rgp*/
/*rgp*/

s32 EvCmdCueBgmPlay_241590(E8_241590 *p0, s32 arg1)
{
    s32 r1;
    s32 r2;
    s32 r3;
    s32 msg[4] __attribute__((aligned(16)));

    r1 = ScriptGetInt_2490f0(p0++);
    r2 = ScriptGetInt_2490f0(p0++);
    r3 = 1;
    if (arg1 >= 3) {
        r3 = ScriptGetInt_2490f0(p0);
    }
    msg[0] = 5;
    msg[1] = r1;
    msg[2] = r2;
    msg[3] = r3;
    Vec4VectorPushBack_249120(gEventContext->f4, msg);
    return 1;
}
