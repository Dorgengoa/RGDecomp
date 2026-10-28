/* rgp:protos */
#define RGP_SELF_EvCmdAngleDiffSign_25d9b0 1
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

s32 EvCmdAngleDiffSign_25d9b0(Arg *p)
{
    f32 a;
    f32 b;
    f32 c;

    a = TaggedGetFloat_26a280(p++);
    b = TaggedGetFloat_26a280(p++);
    c = TaggedGetFloat_26a280(p++);
    ScriptSetRefInt_26a1e0(p, AngleDiffSign_13c0d0(a, b, c));
    return 1;
}
