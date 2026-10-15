#include "types.h"

extern s32 MapObjIsLoaded_1e0a80(void *);
extern s32 ModelMotionEventReleaseHandlers_1b02b0(s32);

struct Obj0;

struct Obj0 {
    u8 pad000[0xC];
    s32 m0C;
    u8 pad010[0x4];
    s16 m14;
};

s32 MapObjReleaseMotionEvents_1e07f0(struct Obj0 *p0)
{
    s32 r0;
    s16 t0;

    r0 = MapObjIsLoaded_1e0a80(p0);
    if (r0 != 0) {
        t0 = p0->m14;
        if (t0 == 1) goto ok;
        if (t0 == 0) goto ok;
    }
    return r0;
ok:
    return ModelMotionEventReleaseHandlers_1b02b0(p0->m0C);
}
