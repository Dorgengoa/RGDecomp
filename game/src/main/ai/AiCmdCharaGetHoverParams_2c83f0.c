/* rgp:protos */
#define RGP_SELF_AiCmdCharaGetHoverParams_2c83f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { s32 a, b; } T_002c83f0;

extern struct { void *p; s32 pad[3]; } D_004DB92C;
/*rgp*/
/*rgp*/
/*rgp*/

s32 AiCmdCharaGetHoverParams_2c83f0(T_002c83f0 *q)
{
    void *g;

    g = D_004DB92C.p;
    if (g != 0) {
        ScriptSlotStoreFloatRef_2cc8e0(q++, CharaGetHoverHeight_213dc0(g));
        ScriptSlotStoreFloatRef_2cc8e0(q, CharaGetHoverMaxSpeed_213db0(g));
    }
    return 1;
}
