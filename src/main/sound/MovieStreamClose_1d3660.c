#include "types.h"

extern s32 GetSoundStreamTable_1bf7c0(void);
extern void SoundStreamHandleResolve_1bfa50(void *, s32, void *);
extern s32 SoundStreamLockAcquire_1bfb40(void *);
extern s32 SoundStreamQueueClose_1c01b0(s32);
extern void SoundStreamLockDtor_1bfab0(void *, s32);
extern void SoundStreamCloseByHandle_1bf7d0(s32, void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
};

s32 MovieStreamClose_1d3660(struct Obj0 *p0)
{
    s32 v3C;
    s32 v38;
    s32 v34;
    s32 r0;
    s32 t0;
    s32 t1;
    s32 rv4;
    s32 r2;
    s32 r3;
    s32 t2;

    r0 = GetSoundStreamTable_1bf7c0();
    t0 = p0->m00;
    v38 = t0;
    SoundStreamHandleResolve_1bfa50(&v3C, r0, &v38);
    t1 = v3C;
    rv4 = t1;
    if (t1 != 0) {
        r2 = SoundStreamLockAcquire_1bfb40(&v3C);
        r3 = SoundStreamQueueClose_1c01b0(r2);
        rv4 = r3;
    }
    SoundStreamLockDtor_1bfab0(&v3C, -1);
    t2 = p0->m00;
    v34 = t2;
    SoundStreamCloseByHandle_1bf7d0(r0, &v34);
    return 1;
}
