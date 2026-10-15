#include "types.h"

extern s32 GetCurrentScene_1f5be0(void);
extern f32 ScriptArgGetFloat_302cf0(s32);
extern s32 ParamTableSetAlpha_1cfb10(s32, s32, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
};

s32 CharaCmdAlpha_22ba10(struct Obj0 *p0, s32 p1, s32 p2)
{
    s32 rv3;
    s32 r0;
    f32 r1;
    s32 t0;
    s32 r2;

    rv3 = 1;
    if (p2 != 1) {
        rv3 = 0;
    } else {
        r0 = GetCurrentScene_1f5be0();
        r1 = ScriptArgGetFloat_302cf0(p1);
        t0 = p0->m00;
        r2 = ParamTableSetAlpha_1cfb10(r0, t0, r1);
        rv3 = 1;
    }
    return rv3;
}
