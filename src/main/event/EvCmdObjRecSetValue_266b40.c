#include "types.h"

struct E8 {
    s32 a;
    s32 b;
};

extern s32 ScriptGetInt_26a2a0(struct E8 *);
extern s32 ObjRecSetValue_1c3d60(s32, s32, s32, s32);

extern s32 D_00481F78;

s32 EvCmdObjRecSetValue_266b40(struct E8 *p0)
{
    struct E8 *q;
    s32 r0;
    s32 r1;
    s32 t0;

    q = p0;
    r0 = ScriptGetInt_26a2a0(q++);
    r1 = ScriptGetInt_26a2a0(q);
    t0 = D_00481F78;
    ObjRecSetValue_1c3d60(t0, 1, r0, r1);
    return 1;
}
