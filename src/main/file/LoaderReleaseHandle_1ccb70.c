#include "types.h"

extern s32 GetLoaderMgr_1f59d0(void);
extern void LoaderReleaseById_1cd340(s32, s32);
extern void LoadHandleReset_1ccc10(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s16 m00;
};

void LoaderReleaseHandle_1ccb70(struct Obj0 *p0)
{
    s32 r0;
    s16 t0;

    r0 = GetLoaderMgr_1f59d0();
    t0 = p0->m00;
    LoaderReleaseById_1cd340(r0, t0);
    LoadHandleReset_1ccc10(p0);
}
