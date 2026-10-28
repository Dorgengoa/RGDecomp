/* rgp:protos */
#define RGP_SELF_EvCmdSubScaleTo_262870 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/


s32 EvCmdSubScaleTo_262870(s64 *arg0, s32 arg1)
{
    f32 v[4] __attribute__((aligned(16)));
    s32 a;
    s32 x;
    s32 r;
    s32 i;

    x = 0;
    a = ScriptGetInt_26a2a0((s32)arg0++);
    v[0] = TaggedGetFloat_26a280((s32)arg0++);
    v[1] = TaggedGetFloat_26a280((s32)arg0++);
    v[2] = TaggedGetFloat_26a280((s32)arg0++);
    v[3] = 1.0f;
    if (arg1 >= 5) {
        x = ScriptGetInt_26a2a0((s32)arg0);
    }
    r = ((s32)EvtGetSubMachine_26abb0(a));
    if (r == 0) {
        return 0;
    }
    EventSubNodeAddScaleTo_250ec0(r, v, x);
    return 1;
}
