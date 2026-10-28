/* rgp:protos */
#define RGP_SELF_EvCmdMenuWinFadeColorTo_2434d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E8 { s32 a; s32 b; } E8;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdMenuWinFadeColorTo_2434d0(E8 *q)
{
    f32 m[4] __attribute__((aligned(16)));
    void *o;
    s32 t;

    o = MenuWinGet_2653e0(ScriptGetInt_2490f0(q++));
    if (o == 0) {
        return 0;
    }
    t = q->a;
    switch (t) {
    case 0:
        m[0] = (f32)ScriptGetInt_2490f0(q++);
        m[1] = (f32)ScriptGetInt_2490f0(q++);
        m[2] = (f32)ScriptGetInt_2490f0(q++);
        m[3] = (f32)ScriptGetInt_2490f0(q++);
        break;
    case 1:
        m[0] = TaggedGetFloat_2490d0(q++);
        m[1] = TaggedGetFloat_2490d0(q++);
        m[2] = TaggedGetFloat_2490d0(q++);
        m[3] = TaggedGetFloat_2490d0(q++);
        break;
    }
    MenuWinFadeColorTo_26c210(o, m, ScriptGetInt_2490f0(q));
    return 1;
}
