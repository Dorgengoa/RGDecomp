/* rgp:protos */
#define RGP_SELF_EffectEntryFinishChr_2dc4d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
extern s32 EffectEntryBuildChr_2dc0f0(void *, s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x1A];
    s16 m1A;
};

s32 EffectEntryFinishChr_2dc4d0(struct Obj0 *p0, s32 p1)
{
    s32 v3C;
    s32 r0;
    s16 t0;
    s32 r1;
    s32 t1;
    s32 r2;

    r0 = ((s32)GetLoaderMgr_1f59d0());
    v3C = 0;
    t0 = p0->m1A;
    r1 = ((s32)LoaderGetData_1cd490(r0, t0, &v3C));
    t1 = v3C;
    r2 = EffectEntryBuildChr_2dc0f0(p0, p1, r1, t1);
    return r2;
}
