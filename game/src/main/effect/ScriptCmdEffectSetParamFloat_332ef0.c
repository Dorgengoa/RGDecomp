/* rgp:protos */
#define RGP_SELF_ScriptCmdEffectSetParamFloat_332ef0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E8 { s32 a; s32 b; } E8;

/*rgp*/
/*rgp*/
/*rgp*/

extern void *D_004826E0;

s32 ScriptCmdEffectSetParamFloat_332ef0(E8 *p0, s32 p1)
{
    void *o;
    f32 t;
    s32 r;

    if (p1 != 2 && p1 != 3) {
        return 0;
    }
    o = 0;
    switch (p1) {
    case 2:
        o = D_004826E0;
        break;
    case 3:
        o = D_004826E0;
        break;
    }
    if (o == 0) {
        return 0;
    }
    t = ScriptSlotGetFloat_334890(p0++);
    r = ScriptSlotGetInt_3348b0(p0);
    EffectInstanceSetParamFloat_2dd6b0(o, r, t);
    return 1;
}
