#include "types.h"

extern s32 ScriptArgGetAreaId_3019b0(void *);
extern s32 ScriptArgGetStr_301a00(void *);
extern void EvObjLinkCtorWithKey_367870(void *, s32, s32, s32, s32);
extern s32 GetEventObjMgr_2d1960(void);
extern void EventObjMgrCreateLink_2ea030(s32, s32, s32, void *);
typedef unsigned __int128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0047F0C0;
extern s32 D_0047F0C4;

struct Obj0;

struct Obj0 {
    u8 pad000[0x8];
    s32 m08;
};

s32 EvScriptCmdObjLinkCreate_2ff790(struct Obj0 *p0, s32 p1)
{
    u128 v40[15];
    s32 r0;
    s32 rv1;
    s32 t0;
    s32 r2;
    s32 r3;
    s32 r4;
    s32 r6;
    s32 t1;
    s32 t2;

    if (p1 != 4) {
        return 0;
    }
    r0 = ScriptArgGetAreaId_3019b0((struct Obj0 *)((u8 *)p0 + 8));
    rv1 = r0;
    if (r0 < 0) {
        t0 = p0->m08;
        if (t0 == 0) {
            return 1;
        }
        rv1 = t0;
    }
    r2 = ScriptArgGetStr_301a00(p0);
    r3 = ScriptArgGetStr_301a00((struct Obj0 *)((u8 *)p0 + 0x10));
    r4 = ScriptArgGetStr_301a00((struct Obj0 *)((u8 *)p0 + 0x18));
    EvObjLinkCtorWithKey_367870(v40, r2, r0, r3, r4);
    r6 = GetEventObjMgr_2d1960();
    t1 = D_0047F0C0;
    t2 = D_0047F0C4;
    EventObjMgrCreateLink_2ea030(r6, t1, t2, v40);
    return 1;
}
