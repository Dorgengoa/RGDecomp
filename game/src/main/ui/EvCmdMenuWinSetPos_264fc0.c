/* rgp:protos */
#define RGP_SELF_EvCmdMenuWinSetPos_264fc0 1
#include "port/game_protos.h"
#line 1
#include "vec.h"

typedef struct Cmd { s32 a, b; } Cmd;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* the 1.0f w store is HOISTED to the top of the frame (its `lui` is the second
   instruction of the function), so `v.w = 1.0f;` is the first statement, not
   the one after `v.z` as in the EvCmdCameraSplineAddPoint_264430 family. */
s32 EvCmdMenuWinSetPos_264fc0(Cmd *p0, s32 n)
{
    Vec4 v __attribute__((aligned(16)));
    s32 id;
    void *h;

    VEC4_ZERO(v);
    v.w = 1.0f;
    id = ScriptGetInt_26a2a0((s32)p0++);
    v.x = TaggedGetFloat_26a280((s32)p0++);
    v.y = TaggedGetFloat_26a280((s32)p0++);
    if (n >= 4) {
        v.z = TaggedGetFloat_26a280((s32)p0);
    }
    h = MenuWinGet_2653e0(id);
    if (h == 0) {
        return 0;
    }
    MenuWinSetPos_26c3b0(h, &v);
    return 1;
}
