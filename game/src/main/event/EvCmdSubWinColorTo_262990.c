/* rgp:protos */
#define RGP_SELF_EvCmdSubWinColorTo_262990 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E8 { s32 a; s32 b; } E8;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdSubWinColorTo_262990(E8 *p0, s32 p1)
{
    f32 v[4] __attribute__((aligned(16)));
    s32 r0;
    s32 h;
    s32 x;

    h = 0;
    r0 = ScriptGetInt_26a2a0(p0++);
    v[0] = TaggedGetFloat_26a280(p0++);
    v[1] = TaggedGetFloat_26a280(p0++);
    v[2] = TaggedGetFloat_26a280(p0++);
    v[3] = TaggedGetFloat_26a280(p0++);
    if (p1 >= 6) {
        h = ScriptGetInt_26a2a0(p0);
    }
    x = ((s32)EvtGetSubMachine_26abb0(r0));
    if (x == 0) {
        return 0;
    }
    EventSubNodeAddWinColorTo_250f60(x, v, h);
    return 1;
}
