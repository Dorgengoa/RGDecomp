#include "types.h"

extern s32 GetCurrentScene_1f5be0(void);
extern s32 ObjRecGetLiveObject_1c4a90(s32, s32);
extern s32 ModelMotionEventReleaseHandlers_1b02b0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
};

s32 CharaCmdEffectReset_22d020(struct Obj0 *p0)
{
    s32 r0;
    s32 t0;
    s32 r1;
    s32 r2;

    r0 = GetCurrentScene_1f5be0();
    t0 = p0->m00;
    r1 = ObjRecGetLiveObject_1c4a90(r0, t0);
    if (r1 == 0) {
        return 1;
    }
    r2 = ModelMotionEventReleaseHandlers_1b02b0(r1);
    return 1;
}
