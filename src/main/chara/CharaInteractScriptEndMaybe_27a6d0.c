#include "types.h"

extern s32 CameraPopModeNoApply_309bf0(void);
extern s32 SetFieldControlActive_27bd30(s32);
extern void * GetGameData_1fede0(void);
extern s32 GetActionMgr_1fdb50(void);
extern void * ActionMgrFindById_233b50(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0048217C;

struct Obj0;
struct Obj1;
struct Obj2;

struct Obj0 {
    u8 pad000[0x18];
    struct Obj1 *m18;
};

struct Obj1 {
    u8 pad000[0x18E];
    s16 m18E;
};

struct Obj2 {
    u8 pad000[0xA44];
    s32 mA44;
};

struct Obj2 *CharaInteractScriptEndMaybe_27a6d0(void)
{
    s32 r0;
    s32 r1;
    struct Obj0 *r2;
    s32 r3;
    struct Obj1 * t0;
    s16 t1;
    struct Obj2 *r4;
    s32 t2;
    s32 t3;
    s32 t4;

    r0 = CameraPopModeNoApply_309bf0();
    r1 = SetFieldControlActive_27bd30(1);
    r2 = (struct Obj0 *)GetGameData_1fede0();
    r3 = GetActionMgr_1fdb50();
    t0 = r2->m18;
    t1 = t0->m18E;
    r4 = ActionMgrFindById_233b50(r3, t1);
    if (r4 != 0) {
        t2 = r4->mA44;
        t3 = t2 & 0xF7FFFFFF;
        t4 = t3 & 0xEFFFFFFF;
        r4->mA44 = t3;
        r4->mA44 = t4;
    }
    D_0048217C = 0xFF;
    return r4;
}
