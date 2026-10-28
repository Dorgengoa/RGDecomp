/* rgp:protos */
#define RGP_SELF_AiCmdCos_2cc010 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S8 {
    s32 a;
    s32 b;
} S8;

/*rgp*/
/*rgp*/
/*rgp*/

s32 AiCmdCos_2cc010(S8 *a0, s32 mode)
{
    S8 *p;
    f32 v;

    p = a0;
    if (mode == 2) {
        goto body;
    }
    return 0;
body:
    v = ScriptSlotGetFloat_2cc9a0(p++);
    ScriptSlotStoreFloatRef_2cc8e0(p, Cosf_128d30(v));
    return 1;
}
