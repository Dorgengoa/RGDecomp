/* rgp:protos */
#define RGP_SELF_AiCmdAngleDiffSign_2cc160 1
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

s32 AiCmdAngleDiffSign_2cc160(Arg *p)
{
    f32 a;
    f32 b;
    f32 c;

    a = ScriptSlotGetFloat_2cc9a0(p++);
    b = ScriptSlotGetFloat_2cc9a0(p++);
    c = ScriptSlotGetFloat_2cc9a0(p++);
    ScriptSlotStoreIntRef_2cc900(p, AngleDiffSign_13c0d0(a, b, c));
    return 1;
}
