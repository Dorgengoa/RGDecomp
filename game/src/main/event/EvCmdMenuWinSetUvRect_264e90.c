/* rgp:protos */
#define RGP_SELF_EvCmdMenuWinSetUvRect_264e90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdMenuWinSetUvRect_264e90(s64 *arg0)
{
    s32 t;
    s32 e;
    s32 b;
    s32 c;
    s32 a;
    s32 d;

    a = ScriptGetInt_26a2a0(arg0++);
    b = ScriptGetInt_26a2a0(arg0++);
    c = ScriptGetInt_26a2a0(arg0++);
    d = ScriptGetInt_26a2a0(arg0++);
    e = ScriptGetInt_26a2a0(arg0);
    t = ((s32)MenuWinGet_2653e0(a));
    if (t == 0) {
        return 0;
    }
    MenuWinSetUvRect_26c300(t, b, c, d, e);
    return 1;
}
