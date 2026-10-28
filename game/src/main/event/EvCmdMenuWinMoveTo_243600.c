/* rgp:protos */
#define RGP_SELF_EvCmdMenuWinMoveTo_243600 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E8 { s32 a; s32 b; } E8;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdMenuWinMoveTo_243600(E8 *p0)
{
    f32 v[4] __attribute__((aligned(16)));
    s32 i;
    void *o;
    s32 a;
    s32 b;
    s32 c;

    i = ScriptGetInt_2490f0(p0++);
    o = MenuWinGet_2653e0(i);
    if (o == 0) {
        return 0;
    }
    switch (p0->a) {
    case 0:
        a = ScriptGetInt_2490f0(p0++);
        v[0] = (f32)(a + 0x100);
        b = ScriptGetInt_2490f0(p0++);
        v[1] = (f32)(b + 0xE0);
        v[2] = 0.0f;
        v[3] = 0.0f;
        break;
    case 1:
        v[0] = TaggedGetFloat_2490d0(p0++);
        v[1] = TaggedGetFloat_2490d0(p0++);
        v[2] = TaggedGetFloat_2490d0(p0++);
        v[3] = 0.0f;
        break;
    }
    c = ScriptGetInt_2490f0(p0);
    MenuWinMoveTo_26c220(o, v, c);
    return 1;
}
