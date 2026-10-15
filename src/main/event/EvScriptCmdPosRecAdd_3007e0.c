#include "types.h"

/* The three arms are reached with beql INTO the arm, so this is a compiled
   `switch` whose case order is REVERSED in the listing (9, 6, 5 tested; 5, 6, 9
   written).  Case 5 has an empty body - the arm's only instruction was already
   duplicated into the branch's delay slot.
   Callee-saved FPRs descend from the highest in declaration order, so
   x/y/z/w come out $f23/$f22/$f21/$f20. */

extern void *D_0047F0C0;
extern void *D_0047F0C4;

extern void *ScriptArgGetStr_301a00(u8 *p);
extern s32 ScriptArgGetInt_301a60(u8 *p);
extern f32 ScriptArgGetFloat_301a20(u8 *p);
extern void EvScriptTemplatesReset_301c20(void);
extern void *GetEventObjMgr_2d1960(void);
extern void EventPosRecCtorInit_2e3780(f32 *m, void *a, s32 b, f32 x, f32 y, f32 z);
extern void EventObjMgrAddPosRec_2ea130(void *a, void *b, void *c, f32 *m);

s32 EvScriptCmdPosRecAdd_3007e0(u8 *p, s32 argc)
{
    f32 x;
    f32 y;
    f32 z;
    f32 w;
    void *a;
    s32 b;
    f32 m[8];

    EvScriptTemplatesReset_301c20();
    if (argc != 5 && argc != 6 && argc != 9) {
        return 0;
    }
    x = ScriptArgGetFloat_301a20(p + 0x10);
    y = ScriptArgGetFloat_301a20(p + 0x18);
    z = ScriptArgGetFloat_301a20(p + 0x20);
    switch (argc) {
    case 5:
        break;
    case 6:
        w = ScriptArgGetFloat_301a20(p + 0x28);
        x = x / w;
        y = y / w;
        z = z / w;
        break;
    case 9:
        w = ScriptArgGetFloat_301a20(p + 0x40);
        x = (ScriptArgGetFloat_301a20(p + 0x28) - x) / w;
        y = (ScriptArgGetFloat_301a20(p + 0x30) - y) / w;
        z = (ScriptArgGetFloat_301a20(p + 0x38) - z) / w;
        break;
    }
    a = ScriptArgGetStr_301a00(p);
    b = ScriptArgGetInt_301a60(p + 8);
    EventPosRecCtorInit_2e3780(m, a, b, x, y, z);
    EventObjMgrAddPosRec_2ea130(GetEventObjMgr_2d1960(), D_0047F0C0, D_0047F0C4, m);
    return 1;
}
