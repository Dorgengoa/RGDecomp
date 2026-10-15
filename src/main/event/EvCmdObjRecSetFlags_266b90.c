#include "types.h"

typedef struct E8 { s32 a; s32 b; } E8;

extern s32 ScriptGetInt_26a2a0(E8 *);
extern void ObjRecSetFlags_1c3e00(s32, s32, s32, s32);
extern void ObjRecClearFlags_1c3dc0(s32, s32, s32, s32);

extern s32 D_00481F78;

s32 EvCmdObjRecSetFlags_266b90(E8 *p0, s32 p1)
{
    s32 r0;
    s32 r1;
    s32 r2;
    s32 rv4;
    s32 t0;
    s32 t1;

    r0 = ScriptGetInt_26a2a0(p0++);
    r1 = ScriptGetInt_26a2a0(p0++);
    r2 = ScriptGetInt_26a2a0(p0++);
    rv4 = 1;
    if (p1 >= 4) {
        rv4 = ScriptGetInt_26a2a0(p0);
    }
    if (rv4 != 0) {
        t0 = D_00481F78;
        ObjRecSetFlags_1c3e00(t0, r0, r1, r2);
    } else {
        t1 = D_00481F78;
        ObjRecClearFlags_1c3dc0(t1, r0, r1, r2);
    }
    return 1;
}
