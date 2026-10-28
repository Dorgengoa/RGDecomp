/* rgp:protos */
#define RGP_SELF_EvCmdSubSetMotionRate_262e00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct E { s32 a; s32 b; };

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdSubSetMotionRate_262e00(struct E * p0)
{
    s32 a;
    f32 x;
    s32 r;

    a = ScriptGetInt_26a2a0(p0++);
    x = TaggedGetFloat_26a280(p0);

    r = ((s32)EvtGetSubMachine_26abb0(a));
    if (r == 0) {
        return 0;
    }
    EventSubNodeAddSetMotionRate_2511b0(r, x);
    return 1;
}
