/* rgp:protos */
#define RGP_SELF_ScriptCmdAngleDiffSign_334210 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Arg {
    s32 a;
    s32 b;
} Arg;

/*rgp*/
/*rgp*/
/*rgp*/

s32 ScriptCmdAngleDiffSign_334210(Arg *p)
{
    f32 a;
    f32 b;
    f32 c;

    a = ScriptSlotGetFloat_334890(p++);
    b = ScriptSlotGetFloat_334890(p++);
    c = ScriptSlotGetFloat_334890(p++);
    ScriptSlotStoreIntRef_3347f0(p, AngleDiffSign_13c0d0(a, b, c));
    return 1;
}
