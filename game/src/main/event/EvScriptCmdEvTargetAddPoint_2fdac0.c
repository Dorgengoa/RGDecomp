/* rgp:protos */
#define RGP_SELF_EvScriptCmdEvTargetAddPoint_2fdac0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { f32 x, y, z, w; } Vec4;

extern u8 *D_00482890;
extern s32 D_00482894;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvScriptCmdEvTargetAddPoint_2fdac0(u8 *p, s32 kind)
{
    u8 *e;
    Vec4 *q;
    s32 i;
    s32 slot;

    if (kind != 4) {
        return 0;
    }
    if (D_00482890 == 0) {
        return 1;
    }
    i = ScriptArgGetInt_301a60(p);
    if (i < 0 || i >= D_00482894) {
        return 1;
    }
    e = D_00482890 + i * 0x140;
    slot = EvTargetGetPointCount_352950(e);
    if (slot >= 6) {
        return 1;
    }
    q = (Vec4 *)((u8 *)EvTargetGetPoints_352960(e));
    q[slot].x = ScriptArgGetFloat_301a20(p + 8);
    q[slot].y = ScriptArgGetFloat_301a20(p + 0x10);
    q[slot].z = ScriptArgGetFloat_301a20(p + 0x18);
    q[slot].w = 1.0f;
    EvTargetSetPointCount_352940(e, slot + 1);
    return 1;
}
