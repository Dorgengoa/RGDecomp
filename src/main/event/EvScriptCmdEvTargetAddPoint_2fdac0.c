#include "types.h"

typedef struct { f32 x, y, z, w; } Vec4;

extern u8 *D_00482890;
extern s32 D_00482894;

extern s32 ScriptArgGetInt_301a60(u8 *p);
extern f32 ScriptArgGetFloat_301a20(u8 *p);
extern s32 EvTargetGetPointCount_352950(u8 *e);
extern u8 *EvTargetGetPoints_352960(u8 *e);
extern void EvTargetSetPointCount_352940(u8 *e, s32 n);

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
    q = (Vec4 *)EvTargetGetPoints_352960(e);
    q[slot].x = ScriptArgGetFloat_301a20(p + 8);
    q[slot].y = ScriptArgGetFloat_301a20(p + 0x10);
    q[slot].z = ScriptArgGetFloat_301a20(p + 0x18);
    q[slot].w = 1.0f;
    EvTargetSetPointCount_352940(e, slot + 1);
    return 1;
}
