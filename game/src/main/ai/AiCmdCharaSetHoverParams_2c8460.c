/* rgp:protos */
#define RGP_SELF_AiCmdCharaSetHoverParams_2c8460 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { s32 a, b; } T_002c8460;

extern struct { void *p; s32 pad[3]; } D_004DB92C;
/*rgp*/
/*rgp*/

s32 AiCmdCharaSetHoverParams_2c8460(T_002c8460 *q)
{
    void *g;
    f32 a;
    f32 b;

    g = D_004DB92C.p;
    if (g != 0) {
        a = ScriptSlotGetFloat_2cc9a0(q++);
        b = ScriptSlotGetFloat_2cc9a0(q);
        CharaSetHoverParams_2138e0(g, a, b);
    }
    return 1;
}
