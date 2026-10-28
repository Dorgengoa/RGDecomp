/* rgp:protos */
#define RGP_SELF_ScriptCmdSqrt_334350 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E8_FUN_00334350 {
    s32 a;
    s32 b;
} E8_FUN_00334350;

extern f32 sqrtf(f32 x);
/*rgp*/
/*rgp*/

s32 ScriptCmdSqrt_334350(E8_FUN_00334350 *q, s32 mode)
{
    f32 v;

    if (mode != 2) return 0;
    v = ScriptSlotGetFloat_334890(q++);
    ScriptSlotStoreFloatRef_3347d0(q, sqrtf(v));
    return 1;
}
