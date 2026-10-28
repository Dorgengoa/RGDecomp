/* rgp:protos */
#define RGP_SELF_ScriptCmdMovingLineSetUvRect_32e890 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 ScriptCmdMovingLineSetUvRect_32e890(s64 *arg0, s32 arg1)
{
    s32 t;
    s32 id;
    f32 a;
    f32 b;
    f32 c;
    f32 d;

    if (arg1 != 5) {
        return 0;
    }
    id = ScriptSlotGetInt_3348b0((s32)arg0++);
    a = ScriptSlotGetFloat_334890((s32)arg0++);
    b = ScriptSlotGetFloat_334890((s32)arg0++);
    c = ScriptSlotGetFloat_334890((s32)arg0++);
    d = ScriptSlotGetFloat_334890((s32)arg0);
    t = ((s32)MovingLineGet_2d8df0(id));
    if (t != 0) {
        MovingLineSetUvRect_2d6400(t, a, b, c, d);
    }
    return 1;
}
