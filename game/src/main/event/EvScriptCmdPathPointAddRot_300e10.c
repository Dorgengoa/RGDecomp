/* rgp:protos */
#define RGP_SELF_EvScriptCmdPathPointAddRot_300e10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

s32 EvScriptCmdPathPointAddRot_300e10(void *p, s32 mode)
{
    f32 a, b, c;

    if (mode != 3) return 0;
    a = ScriptArgGetFloat_301a20(p);
    b = ScriptArgGetFloat_301a20((void *)((u8 *)p + 8));
    c = ScriptArgGetFloat_301a20((void *)((u8 *)p + 0x10));
    return EventPathRecPointPush_3010a0(0.0f, 0.0f, 0.0f, a, b, c, 1.0f, 1.0f, 1.0f);
}
