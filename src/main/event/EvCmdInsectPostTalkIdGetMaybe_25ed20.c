#include "types.h"

extern void * GetGameData_1fede0(void);
extern s32 StateVarGet_3ccac0(s32, s32);
extern s32 InsectBattlePickPostTalkIdMaybe_319660(void);
extern s32 ScriptSetRefInt_26a1e0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x10];
    s32 m10;
};

s32 EvCmdInsectPostTalkIdGetMaybe_25ed20(s32 p0, s32 p1)
{
    s32 rv5;
    struct Obj0 *r0;
    s32 t0;
    s32 r1;
    s32 rv3;
    s32 r2;
    s32 r4;

    rv5 = 1;
    if (p1 != 1) {
        rv5 = 0;
    } else {
        r0 = GetGameData_1fede0();
        t0 = r0->m10;
        r1 = StateVarGet_3ccac0(t0, 0x1C);
        rv3 = r2;
        if (r1 > 0) {
            rv3 = (r1 + -1);
        } else {
            r2 = InsectBattlePickPostTalkIdMaybe_319660();
            rv3 = r2;
        }
        r4 = ScriptSetRefInt_26a1e0(p0, rv3);
        rv5 = 1;
    }
    return rv5;
}
