/* rgp:protos */
#define RGP_SELF_AiCmdSin_2cc060 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E8 { s32 a; s32 b; } E8;

/*rgp*/
/*rgp*/
/*rgp*/

s32 AiCmdSin_2cc060(E8 *a0, s32 mode)
{
    E8 *p;
    f32 v;

    p = a0;
    if (mode == 2) {
        goto body;
    }
    return 0;
body:
    v = ScriptSlotGetFloat_2cc9a0(p++);
    ScriptSlotStoreFloatRef_2cc8e0(p, Sinf_128fd0(v));
    return 1;
}
